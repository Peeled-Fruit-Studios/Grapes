**WARNING: This project is now defunct and is no longer maintained, Pull Requests and Issues / Feature requests will not be accepted!**

# Grapes

[![Gitpod ready-to-code](https://img.shields.io/badge/Gitpod-ready--to--code-blue?logo=gitpod)](https://gitpod.io/#https://github.com/Peeled-Fruit-Studios/Grapes)

The Grapes Programming Language is a Easy to Learn, Interpreted and Dynamically typed programming language.

*Note: This Programming language is in the very, very early stages and is Under Heavy construction*

It's Syntax is a cross between Javascript and Python, Taking the best from both worlds.

Here is a simple example;

````javascript

fun greet(name) {
  print "Hello " + name;
}

print greet("Github");

````

For a more advanced example, check out the docs folder.

## Building

This project uses cmake to build the compiler, so you will need to have it installed.

Linux and Mac OS:

````bash

$ ./cmake.sh

````
Windows:

````bash

$ cmake.bat

````

*Note: This command will place the build compiler in the root directory and remove all generated build artifacts except for the compiler*
