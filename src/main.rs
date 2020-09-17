use std::env;
use std::fs;

mod syntax;

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() != 2 {
        println!("usage: {} <filename>", &args[0]);
    } else {
        let filename = &args[1];
        let contents = fs::read_to_string(filename);
        match contents {
            Err(e) => {
                println!("unable to read file {}: {}", filename, e);
            }
            Ok(source) => {
                let ast = syntax::parse(&source);
                println!("-----------------------------");
                println!("AST = {:?}", ast);
            }
        }
    }
}
