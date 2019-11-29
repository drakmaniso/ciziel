#include "lex.h"


void lexMake (Lexer *l, char *filepath, String input) {
    *l = (Lexer) {
        .name = filepath,
        .input = input,
        .start = 0,
        .pos = 0,
    };
}


// Equivalent to:
//     typedef void* (*stateFunc) (Lexer *l);
typedef struct state {
    struct state (*func) (Lexer *l);
} state;


void lexEmit (Lexer *l, TokenType typ) {
    Token tok = (Token) {
        .value = stringSlice (l->input, l->start, l->pos),
        .type = typ,
    };
    l->start = l->pos;
    lexPrint (tok);
    printf ("\n");
}


int isSpace (Rune r) {
    return r == ' ' || r == '\n' || r == '\t';
}


int isLetter (Rune r) {
    return (r >= 'A' && r <= 'Z')
        || (r >= 'a' && r <= 'z')
        || r == '_';
}


int isDigit (Rune r) {
    return r >= '0' && r <= '9';
}


Rune lexNext (Lexer *l) {
    if (l->pos >= stringLength (l->input)) {
        return '\0';
    }
    Rune result = stringAt (l->input, l->pos);
    l->pos++;
    return result;
}


void lexIgnore (Lexer *l) {
    l->start = l->pos;
}


void lexBackup (Lexer *l) {
    l->pos--;
}


Rune lexPeek (Lexer *l) {
    Rune r = lexNext (l);
    lexBackup (l);
    return r;
}


// LEXER STATES


state lexSpace (Lexer *l);
state lexIdentifier (Lexer *l);
state lexNumber (Lexer *l);
state lexInvalid (Lexer *l);


state lexSpace (Lexer *l) {
    while (1) {
        Rune r = lexNext (l);

        if (r == '\0') {
            lexEmit (l, tokEOF);
            return (state) {NULL};
        }

        if (isSpace (r)) {
            lexIgnore (l);
            continue;
        }

        if (r == '=') {
            lexEmit (l, tokDefine);
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


state lexIdentifier (Lexer *l) {
    while (1) {
        Rune r = lexNext (l);

        if (isLetter (r) || isDigit (r)) {
            continue;
        }

        lexBackup (l);
        lexEmit (l, tokIdentifier);
        return (state) {lexSpace};
    }
}


state lexNumber (Lexer *l) {
    while (1) {
        Rune r = lexNext (l);

        if (isDigit (r)) {
            continue;
        }

        lexBackup (l);
        lexEmit (l, tokNumber);
        return (state) {lexSpace};
    }
}


state lexInvalid (Lexer *l) {
    while (1) {
        Rune r = lexNext (l);

        if (r == '\0' || r == '\n') {
            lexBackup (l);
            lexEmit (l, tokInvalid);
            return (state){lexSpace};
        }
    }
}


void lexRun (Lexer *l) {
    state s = (state) { .func = lexSpace };
    for (; s.func != NULL; ) {
        s = s.func (l);
    }
}


void lexPrint (Token t) {
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
