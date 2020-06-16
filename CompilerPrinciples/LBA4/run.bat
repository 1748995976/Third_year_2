@echo off
bison -d -v parser.y
flex lex.l
gcc -o parser lex.yy.c parser.tab.c ast.c semantic.c objectCode.c
chcp 65001
parser test.c
pause