#include <stdbool.h>
#include "scanner.h"


bool isSpace (Rune r) {
    return r == ' ' || r == '\n' || r == '\t';
}


bool isLetter (Rune r) {
    return (r >= 'A' && r <= 'Z')
        || (r >= 'a' && r <= 'z')
        || r == '_';
}


bool isDigit (Rune r) {
    return r >= '0' && r <= '9';
}


Rune next (Scanner *s);
void ignore (Scanner *s);
void backup (Scanner *s);
Rune peek (Scanner *s);
void emit (Scanner *s, TokenType typ);


// LEXICAL STATES


typedef struct state {
    // The type is recursive, so it must be embedded in a struct
    struct state (*func) (Scanner *s);
} state;


state lexSpace (Scanner *s);
state lexIdentifier (Scanner *s);
state lexNumber (Scanner *s);
state lexInvalid (Scanner *s);


state lexSpace (Scanner *s) {
    while (true) {
        Rune r = next (s);

        if (r == '\0') {
            emit (s, tokEOF);
            return (state) {NULL};
        }

        if (isSpace (r)) {
            ignore (s);
            continue;
        }

        if (r == '=') {
            emit (s, tokDefine);
            return (state) {lexSpace};
        }

        if (isLetter (r)) {
            return (state) {lexIdentifier};
        }

        if (isDigit (r)) {
            return (state) {lexNumber};
        }

        // Invalid rune in input
        return (state) {lexInvalid};
    }
}


state lexIdentifier (Scanner *s) {
    while (true) {
        Rune r = next (s);

        if (isLetter (r) || isDigit (r)) {
            continue;
        }

        backup (s);
        emit (s, tokIdentifier);
        return (state) {lexSpace};
    }
}


state lexNumber (Scanner *s) {
    while (true) {
        Rune r = next (s);

        if (isDigit (r)) {
            continue;
        }

        backup (s);
        emit (s, tokNumber);
        return (state) {lexSpace};
    }
}


state lexInvalid (Scanner *s) {
    while (true) {
        Rune r = next (s);

        if (r == '\0' || r == '\n') {
            backup (s);
            emit (s, tokInvalid);
            return (state){lexSpace};
        }
    }
}


// SCANNER


void scanMake (Scanner *s, char *filepath, String input) {
    *s = (Scanner) {
        .name = filepath,
        .input = input,
        .start = 0,
        .pos = 0,
    };
}


void scanRun (Scanner *s) {
    state st = (state) { .func = lexSpace };
    for (; st.func != NULL; ) {
        st = st.func (s);
    }
}


Rune next (Scanner *s) {
    if (s->pos >= stringLength (s->input)) {
        return '\0';
    }
    Rune result = stringAt (s->input, s->pos);
    s->pos++;
    return result;
}


void ignore (Scanner *s) {
    s->start = s->pos;
}


void backup (Scanner *s) {
    s->pos--;
}


Rune peek (Scanner *s) {
    Rune r = next (s);
    backup (s);
    return r;
}


void emit (Scanner *s, TokenType typ) {
    Token tok = (Token) {
        .value = stringSlice (s->input, s->start, s->pos),
        .type = typ,
    };
    s->start = s->pos;
    scanPrint (tok);
    printf ("\n");
}


void scanPrint (Token t) {
    if (t.type == tokEOF) {
        printf ("EOF");
        return;
    }

    switch (t.type) {
        case tokKeyword:
            printf ("Keyword{");
            break;

        case tokIdentifier:
            printf ("Identifier{");
            break;

        case tokNumber:
            printf ("Number{");
            break;

        case tokDefine:
            printf ("Define");
            return;

        case tokInvalid:
            printf ("Invalid{");
            break;

        default:
            printf ("UNKNOWN{");
    }
    stringPrint (t.value);
    printf ("}");
}
