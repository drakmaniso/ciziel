//! Syntactical analysis

mod scanner;

/// Parses a program source.
pub fn parse(source: String) {
    let tokens = scanner::scan(source);
    println!("tokens = {:?}", tokens);
}
