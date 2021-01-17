<div align="center">
    <h1>The Leaf programming language</h1>
    A simple and fast programming language.
</div><br/>

```
module main;

func greet(name) {
    val firstname = name.split()[0];
    val message = "Hello %{ firstname }!";
    println(message);
}

greet('John Doe');
```

## Features
* Easy: The simple syntax can be learned in only a few minutes.
* Fast compilation: Compiles itself in less than 1 sec.
* Speed: As fast as C is.
* Lightweight: Only `24.9kB` in size.

## Installation
Install using `git`:
```bash
git clone https://github.com/robincunningham2/Leaf.git
cd Leaf
make install
```

Now, Leaf can be found using the `leaf` command.
