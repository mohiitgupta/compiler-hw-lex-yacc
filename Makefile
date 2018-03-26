hw3: y.tab.c lex.yy.c 
	gcc y.tab.c lex.yy.c -o hw3
y.tab.c : hw3.y 
	bison -y -d -g hw3.y 
lex.yy.c: hw3.l 
	lex hw3.l 
clean: 
	rm -f lex.yy.c y.tab.c hw3
