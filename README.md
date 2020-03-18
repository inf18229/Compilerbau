# Compilerbau
This is the repository for a Compiler to compile Predicate logic

## Compile 

```bison -d Praed_Lex.y
flex -tv Praed_Lex.l>Praed_Lex.c
gcc -c -o Praed_Lex.o Praed_Lex.c
gcc -c -o Praed_Lex.tab.o Praed_Lex.tab.c
gcc Praed_Lex.o Praed_Lex.tab.o -o Parser
```

