//! Syntactical analysis

use std::iter::Peekable;

mod scanner;
use scanner::Token;

/// Parses a program source.
pub fn parse(source: String) -> Result<Definition, String> {
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

struct Parser {
    tokens: Peekable<std::vec::IntoIter<Token>>,
}

fn parse_definition(parser: &mut Parser) -> Result<Definition, String> {
    let peeked = parser.tokens.peek().ok_or("expected identifier")?.clone();
    let name;
    match peeked {
        Token::Name(s) => name = s,
        _ => return Err("expected identifier".into()),
    };
    parser.tokens.next();

    match parser.tokens.peek() {
        Some(Token::Define) => {
            parser.tokens.next();
        }
        _ => return Err("expected `=`".to_string()),
    }

    let expr = parse_expression(parser)?;

    match parser.tokens.peek() {
        Some(Token::Semicolon) => {
            parser.tokens.next();
        }
        _ => return Err("expected `;`".to_string()),
    }

    Ok(Definition {
        name: name.clone(),
        expression: expr,
    })
}

fn parse_expression(parser: &mut Parser) -> Result<Expression, String> {
    let peeked = parser
        .tokens
        .peek()
        .ok_or("expected an expression")?
        .clone();
    match peeked {
        Token::Name(s) => {
            parser.tokens.next();
            Ok(Expression::Name(s.clone()))
        }
        Token::Number(s) => {
            parser.tokens.next();
            Ok(Expression::Number(s.clone()))
        }
        _ => Err("expected an expression".to_string()),
    }
}
