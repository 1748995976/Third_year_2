@echo off
::cmd客户端中运行./run.bat指令即可
bison -d -v parser.y
flex lex.l
gcc -o parser lex.yy.c parser.tab.c ast.c
chcp 65001
parser test.c
pause