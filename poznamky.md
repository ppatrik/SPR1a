# Prednaska 17.02.2016

Uvodne stretnutie k zopakovaniu jazyka c++.

Heslo do virtualneho stroja **student**

Materialy: http://ics.upjs.sk/~pisarcik/sp/

## Programovanie v c++

### Zakladne typy

* **int** - minimalne 16 bitovy (podla specifikacie)
* **short**
* **byte** 8bit (vacsinou unsigned, char je podobny)
* **char** 8bit
* **long**

#### Znamienkove / neznamienkove typy

Pred typ zadame definovanie:

* **unsigned** - neznamienkovy typ
* **signed** - znamienkovy typ - nemusime zadavat je to defaultny typ

### S pohyblivou desatinou ciarkou:

* **float** - min 16bit
* **double** - min 32bit

### Typy premennych

* **auto** - automaticky vznikaju automaticky zanikaju
* **static** - nedochadza k destrukcii hodnoty
* **register** - tak aby hodnota premennej bola v registri procesora (register je najrychlejsia pamat)
* **extern** - pracujes s premennou ktora je v inom subore
* **const** - oznaci ako nemeniacu premennu
* **volatile** - (volatile - inkontinentna [Peto povedal]) pamat ktora po odpojeni elektriny strati obsah - kompilator nerobi optimalizaciu ale spravujeme si to sami (kompilator by mohol vyhodit cele bloky tohto kodu)

## Princip zavedenia programu do pamäte

Toto je vsetko v operacnej pamati, v rámci.

* **CODE**
* **DATA** - globalne staticke inicializovane (ma nastavenu hodnotu)
* **BSS** - globalne staticke neinicializovane (nema nastavenu hodnotu)
* **HEAP** - halda - dynamicky alokovana pamät
* **STACK** - zasobnik - ukladanie lokalnych premennych

## Referencovanie premennych

Pomocou &premenna ziskame adresu premennej. 
Dereferencovanie .......

Ukazovatel je neaka kvazi premenna (nezaujima ziadne miesto, je to vec kompilatora)

* **&premenna** - adresa premennej
* **premenna** - hodnota premennej
* **int *premenna** - len smerovka na premennu (neinicializuje za tym ziadnu premnnu! len adresa na nu)
* ** *premenna ** - dereferencovanie smerovky na premennu (tj dostaneme obsah premennej)

## Operatory

* +, -, /, *
* & | - bitove operatory (sucin, sucet)
* ^ xor
* % modulo

## Komentare

* jednoriadkovy - pred komentarom treba dve lomky //
* viac riadkovy - text obaleny /* */

## Podmienky

Jednoducha podmienka

	if( /* podmienky */ ) {
		// splnene podmienky
	}

Podmienka s else vetvou

	if( /* podmienky */ ) {
		// splnene podmienky
	} else {
		// nesplnene
	}

Viacnasobna podmienka

	if( /* podmienky */ ) {
		// splnene podmienky
	} else if( /* dalsie podmienky */ ) {
		// splnene dalsie podmienky, nesplnene podmienky z prvej vetvy
	} else {
		// nesplnene ani z prvej ani z druhej
	}
	
Podmienky typu switch

	switch(i) {
		case 1: /* prikazdy ak i = 1 */ break;
		case 2: /* prikazdy ak i = 2 */ break;
		case 3: /* prikazdy ak i = 3 */ break;
		default: /* prikazdy ak i bolo ine ako 1,2,3 */
	}
	
V pripade ak break nebudeme vyuzivat tak bude kod postupovat od splneneho case az po koniec switchu
	
## Cyklus

	// 1. moznost
	int i;
	for(i = 0; i < 10; i++) {
		// program opakovany 10 krat
	}
	// 2. moznost (tento sa vzdy vykona aspon raz)
	int i = 0;
	do {
		i++;
		// program opakovany 10 krat
	} while (i < 10);
	// 3. moznost
	int i = 0;
	while(i < 10) {
		i++;
		// program opakovany 10 krat
	}
	
Priklady nekonecneho cyklu:

	// 1. moznost
	for(;;) {
		// program opakovany dookola
	}
	// 2. moznost
	while(1) {
		// program opakovany dookola
	}
	// 3. moznost
	do {
		// program opakovany dookola
	} while(1);

Moznosti ukoncenia vykonavania cyklu:

* **break;** ukonci cyklus a program pokracuje dalej
* **continue;** ukonci aktualne vykonavany program v cykle a pokracuje na dalsiu iteraciu cyklu

### Example

Ulozit ako program01.c

	main()
	{
		int i = 10;
		
		if(i == 10) {
			// pravda
			int i = 20; // rozsha platnosti (teraz sa nedostanem k prvej i
			// resp. iba ak poznam jej adresu)
		} else {
			// nepravda
		}
		
		
		return 0;
	}
	
Kompilacia

	gcc program01.c -o program01


## Volania

* System calls (systemove volania) - Funkcie ktorymi vieme komunikovat s operacnym systemom
* Library calls - rozsiruju moznosti systemovych volani

## Retazce

	char retazec[20];
	
Poznamka: kazdy retazec musi obsahovat nulovy znak. Tj. AHOJ\0........

## Priorita operácií

* zatvorky
* nasobenie, delenie (postupuje sa zlava)
* scitanie, odcitanie (postupuje sa zlava)

Zdroj: http://en.cppreference.com/w/c/language/operator_precedence

