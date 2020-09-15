use std::iter::Peekable;
use std::str::Chars;

struct Scanner<'a> {
    filename: String,
    tokens: Vec<Token>,
    remaining: Peekable<Chars<'a>>,
}

#[derive(Debug)]
enum Token {
    // Delimiters
    LeftParen,
    RightParen,
    Comma,
    Semicolon,
    // Keywords
    Do,
    End,
    If,
    Then,
    Else,
    // Special Operators
    Define,
    Arrow,
    // Others
    Name(String),
    Number(String),
    Operator(String),
}

pub fn scan(filename: String, source: String) {
    let mut scanner = Scanner {
        filename,
        tokens: Vec::new(),
        remaining: source.chars().peekable(),
    };
    let mut f = scan_between(&mut scanner);
    loop {
        f = match f {
            Step::Between => scan_between(&mut scanner),
            Step::Whitespace => scan_whitespace(&mut scanner),
            Step::Name => scan_name(&mut scanner),
            Step::Number => scan_number(&mut scanner),
            Step::Symbol => scan_symbol(&mut scanner),
            Step::EndOfFile => break,
        }
    }
    println!("tokens = {:?}", scanner.tokens);
}

enum Step {
    Between,
    Whitespace,
    Name,
    Number,
    Symbol,
    EndOfFile,
}

fn scan_between(scanner: &mut Scanner) -> Step {
    match scanner.remaining.peek() {
        None => Step::EndOfFile,
        Some(c) => {
            if c.is_whitespace() {
                return Step::Whitespace;
            } else if c.is_lowercase() {
                return Step::Name;
            } else if c.is_ascii_digit() {
                return Step::Number;
            } else if c.is_ascii_punctuation() {
                return Step::Symbol;
            } else {
                println!("invalid character in file \"{}\": {}", scanner.filename, c);
                scanner.remaining.next();
                Step::Between
            }
        }
    }
}

fn scan_whitespace(scanner: &mut Scanner) -> Step {
    while let Some(c) = scanner.remaining.peek() {
        if c.is_whitespace() {
            scanner.remaining.next();
        } else {
            break;
        }
    }
    Step::Between
}

fn scan_name(scanner: &mut Scanner) -> Step {
    let mut s = String::with_capacity(30);
    while let Some(c) = scanner.remaining.peek() {
        if c.is_alphanumeric() || *c == '_' {
            s.push(*c);
            scanner.remaining.next();
        } else {
            break;
        }
    }
    if s == "do" {
        scanner.tokens.push(Token::Do);
    } else if s == "end" {
        scanner.tokens.push(Token::End);
    } else if s == "if" {
        scanner.tokens.push(Token::If);
    } else if s == "then" {
        scanner.tokens.push(Token::Then);
    } else if s == "else" {
        scanner.tokens.push(Token::Else);
    } else {
        scanner.tokens.push(Token::Name(s));
    }
    Step::Between
}

fn scan_number(scanner: &mut Scanner) -> Step {
    let mut s = String::with_capacity(30);
    while let Some(c) = scanner.remaining.peek() {
        if c.is_ascii_digit() || *c == '_' {
            s.push(*c);
            scanner.remaining.next();
        } else {
            break;
        }
    }
    scanner.tokens.push(Token::Number(s));
    Step::Between
}

fn scan_symbol(scanner: &mut Scanner) -> Step {
    if let Some(c) = scanner.remaining.peek() {
        if is_delimiter(*c) {
            match *c {
                '(' => scanner.tokens.push(Token::LeftParen),
                ')' => scanner.tokens.push(Token::RightParen),
                ',' => scanner.tokens.push(Token::Comma),
                ';' => scanner.tokens.push(Token::Semicolon),
                _ => {}
            }
            scanner.remaining.next();
        } else {
            let mut s = String::with_capacity(8);
            while let Some(c) = scanner.remaining.peek() {
                if is_delimiter(*c) {
                    break;
                } else if c.is_ascii_punctuation() {
                    s.push(*c);
                    scanner.remaining.next();
                } else {
                    break;
                }
            }
            if s == "=" {
                scanner.tokens.push(Token::Define);
            } else if s == "->" {
                scanner.tokens.push(Token::Arrow);
            } else {
                scanner.tokens.push(Token::Operator(s));
            }
        }
    }
    Step::Between
}

fn is_delimiter(c: char) -> bool {
    match c {
        '(' | ')' | ',' | ';' => true,
        _ => false,
    }
}
