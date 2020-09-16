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
    let name_tok = parser
        .tokens
        .next()
        .ok_or("I expected a name for a definition, but reached the end of the file")?;
    let name = match name_tok {
        Token::Name(s) => s,
        _ => {
            return Err(format!(
                "I expected a name for a definitiion, but got {:?} instead",
                name_tok
            )
            .to_string())
        }
    };

    match parser.tokens.next() {
        Some(Token::Define) => (),
        _ => return Err("missing \"=\" in definition".to_string()),
    }

    let expr = parse_expression(parser)?;

    match parser.tokens.next() {
        Some(Token::Semicolon) => (),
        _ => return Err("missing \";\" after a definition".to_string()),
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
        .ok_or("I expected an expression, but reached the end of the file")?
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
        _ => Err("I expected an expression, but got something else instead".to_string()),
    }
}
