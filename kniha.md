# Chapter 11

## fork1.c

	gcc fork1.c -o fork1; ./fork1
	# otvorit v druhej konzole
	watch "ps afx | grep fork"

Ukazka ako pracuje proces, kto je jeho rodicom a co sa deje ked dieta 
uz skonci svoje pracovanie ale jeho rodic este pracuje.

* Dieta skoncilo, rodic este bezí - dieta sa stava zobie procesom, je nutne aby rodicovsky proces po nom popratal
* Rodic skoncil, dieta este bezi - hlavny systemovy proces si "adoptuje" detsky proces

## wait.c

	gcc wait.c -o wait; ./wait
	watch "ps afx | grep wait"

Narozdiel od fork1.c tento caka kym sa ukonci cinnost deti a az potom
sa ukoncuje hlavny rodicovsky proces.

## pexec.c

	gcc pexec.c -o pexec; ./pexec
	watch "ps afx | grep pexec"

Exec v aktualnom procese nahradi kod za kod z programu ktory volame 
pomocou exec.

## fork3.c

	gcc fork3.c -o fork3; ./fork3

Do forknuteho procesu nacitame program ps a vykoname ho.

## alarm.c

Registracia akcii na volanie kill do procesu (vlastna obsluha prijateho 
signalu).

	signal(SIGALARM, ding);
	// registruje volanie SIGALARM, a urci ako obsluznu funkciu ding

> Pri vyuzivani obsluh musime dbat na to aby tieto funkcie boli
> atomicke (dalej nedelitelne)

# Jokes

> Sa celý tento proces skartoval. (Stali sa z neho karty)
> Myslim ten zavadziaci proces
