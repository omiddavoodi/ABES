flex a.l
bison -d a.y
python tabdil.py a.tab.h
g++ lex.yy.c a.tab.c -o a.exe