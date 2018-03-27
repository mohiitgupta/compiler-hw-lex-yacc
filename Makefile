hw3: y.tab.c lex.yy.c 
	gcc y.tab.c lex.yy.c -o hw5
y.tab.c : hw5.y 
	bison -y -d -g hw5.y 
lex.yy.c: hw5.l 
	lex hw5.l 
clean: 
	rm -f lex.yy.c y.tab.c hw5
