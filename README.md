# Compilerbau
This is the repository for a Compiler to compile Predicate logic

## Compile

`./start-scan`

if you get some errors with start-scan use
```bison -d Praed_Lex.y
flex -tv Praed_Lex.l>Praed_Lex.c
gcc -c -o Praed_Lex.o Praed_Lex.c
gcc -c -o Praed_Lex.tab.o Praed_Lex.tab.c
gcc Praed_Lex.o Praed_Lex.tab.o -o Parser
```

## Usage
To use the generated Parser type in

`./Parser [Your File]`

You can also call without parameters
`./Parser`
and then type in a valid formula but be carefull to use CONTROLL+D for linebreak, so that the application will come to an end.
