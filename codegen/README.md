# Codegen
it uses the parsetree generated in parser
and generates intermediate code.

## How to use
1. download from github
2. make the following directory using this command:
```
mkdir gen/lib/bin
```
3. install flex, bison
For debian based systems
```
sudo apt install flex
sudo apt install bison
```

4. requires ```g++``` compiler. If not installed install.

## How to run
```
make
./codegen.out input.txt
```
