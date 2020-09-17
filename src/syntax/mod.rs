//! Syntactical analysis

use std::iter::Peekable;

mod scanner;
use scanner::Token;

/// Parses a program source.
pub fn parse(source: &str) -> Result<Definition, String> {
    let tokens = scanner::scan(source);
    println!("tokens = {:?}", tokens);
    let mut parser = Parser {
        tokens: tokens.into_iter().peekable(),
    };
    parse_definition(&mut parser)
}

#[derive(Clone, Debug)]
pub struct Definition {
    name: String,
    expression: Expression,
}

#[derive(Clone, Debug)]
pub enum Expression {
    Name(String),
    Number(String),
}

// Private

struct Parser<'a> {
    tokens: Peekable<std::vec::IntoIter<Token<'a>>>,
}

fn parse_definition(parser: &mut Parser) -> Result<Definition, String> {
    let name =
        match parser.tokens.peek() {
            Some(&Token::Name(s)) => {
                parser.tokens.next();
                s.to_string()
            },
            _ => return Err("expected identifier".into()),
        };

    match parser.tokens.peek() {
        Some(&Token::Define) => {
            parser.tokens.next();
        }
        _ => return Err("expected `=`".to_string()),
    }

    let expr = parse_expression(parser)?;

    match parser.tokens.peek() {
        Some(&Token::Semicolon) => {
            parser.tokens.next();
        }
        _ => return Err("expected `;`".to_string()),
    }

    Ok(Definition {
        name: name,
        expression: expr,
    })
}

fn parse_expression(parser: &mut Parser) -> Result<Expression, String> {
    match parser.tokens.peek() {
        Some(&Token::Name(s)) => {
            parser.tokens.next();
            Ok(Expression::Name(s.to_string()))
        }
        Some(&Token::Number(s)) => {
            parser.tokens.next();
            Ok(Expression::Number(s.to_string()))
        }
        _ => Err("expected an expression".to_string()),
    }
}
