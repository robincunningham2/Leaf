<div align="center">
    <h1>Leaf</h1>
    <a href="https://www.patreon.com/robincunningham"><img src="https://badgejs.herokuapp.com/donate" alt="Donate"></a>
    <a href="https://github.com/robincunningham2/Leaf/issues"><img src="https://badgejs.herokuapp.com/github/issues/robincunningham2/Leaf" alt="Donate"></a>
    <a href="LICENSE"><img src="https://badgejs.herokuapp.com/badge/license/MIT/cyan" alt="Donate"></a>
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

**DISCLAIMER:** Leaf is in development, and is not ready for production _yet_.

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

## License
[MIT](LICENSE)
