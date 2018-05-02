hw6: y.tab.c lex.yy.c 
	gcc y.tab.c lex.yy.c -o hw7
y.tab.c : hw7.y 
	bison -y -d -g hw7.y 
lex.yy.c: hw7.l 
	lex hw7.l 
clean: 
	rm -f lex.yy.c y.tab.c hw7
