hw6: y.tab.c lex.yy.c 
	gcc y.tab.c lex.yy.c -o hw6
y.tab.c : hw6.y 
	bison -y -d -g hw6.y 
lex.yy.c: hw6.l 
	lex hw6.l 
clean: 
	rm -f lex.yy.c y.tab.c hw6
