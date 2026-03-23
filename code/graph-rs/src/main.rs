use std::{
    fmt,
    io::{Write as _, stdin, stdout},
    str::FromStr,
};

struct Node<T>
where
    T: fmt::Display,
{
    data: T,
    children: Vec<usize>,
}

struct Graph<T: fmt::Display>(Vec<Node<T>>);

impl<T> Node<T>
where
    T: fmt::Display,
{
    fn new(data: T, children: Vec<usize>) -> Node<T> {
        Node {
            data: data,
            children: children,
        }
    }
}

impl<T> Graph<T>
where
    T: fmt::Display,
{
    fn new() -> Graph<T> {
        Graph(Vec::<Node<T>>::new())
    }

    fn create_node(&mut self) -> ()
    where
        T: FromStr,
    {
        let data = get_data::<T>("data for node: ");
        let mut children = Vec::<usize>::new();
        println!("enter nodes that this node links to, negative to continue");
        loop {
            let node = get_data::<isize>("> ");
            if node < 0 {
                self.0.push(Node::new(data, children));
                return;
            }
            children.push(node as usize);
        }
    }

    fn edit_node(&mut self) -> () {
        let node = get_data::<isize>(format!("node to edit (0-{}): ", self.0.len() - 1).as_str());
        if node > 0 {
            return;
        }
    }
}

impl<T> fmt::Display for Graph<T>
where
    T: fmt::Display,
{
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        for (index, node) in self.0.iter().enumerate() {
            writeln!(f, "{}: '{}'", index, node.data)?;
            for child_index in node.children.iter() {
                writeln!(f, "{} -> {}", index, child_index)?;
            }
        }
        Ok(())
    }
}

fn get_data<T>(prompt: &str) -> T
where
    T: FromStr,
{
    print!("{}", prompt);
    stdout().flush().unwrap();
    loop {
        let mut input = String::new();
        stdin().read_line(&mut input).unwrap();
        match input.trim().parse::<T>() {
            Ok(value) => return value,
            Err(_) => {
                print!("error parsing number, please try again: ");
                stdout().flush().unwrap();
            }
        }
    }
}

fn print_help() {
    println!();
    println!("0: help menu");
    println!("1: create node");
    println!("2: print graph");
    println!("or negative to quit");
    println!();
}

fn main() {
    let mut graph = Graph::<isize>::new();
    print_help();
    loop {
        match get_data::<i32>("> ") {
            i32::MIN..0 => return,
            1 => {
                graph.create_node();
                println!();
            }
            2 => println!("{}", graph),
            0 | _ => print_help(),
        }
    }
}
