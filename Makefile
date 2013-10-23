check: outclean run
	for i in $$(seq 1 16); do test -e $$i.png || exit 2; done
run: callouts
	./callouts 12 12 $$(seq 1 16)
callouts: callouts.c
	gcc -pedantic -Werror -Wall $^ -lcairo -o $@
outclean:
	rm -f *.png
clean:
	rm -f callouts
destroy: clean
	rm -f .gitignore LICENSE README callouts.c Makefile
