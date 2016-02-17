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
* **float** - min 16bit
* **double** - min 32bit

#### Znamienkove / neznamienkove typy

Pred typ zadame definovanie:

* **unsigned** - neznamienkovy typ
* **signed** - znamienkovy typ - nemusime zadavat je to defaultny typ

### Princip zavedenia programu do pamäte

Toto je vsetko v operacnej pamati, v rámci.

* **CODE**
* **DATA** - globalne staticke inicializovane (ma nastavenu hodnotu)
* **BSS** - globalne staticke neinicializovane (nema nastavenu hodnotu)
* **HEAP** - halda - dynamicky alokovana pamät
* **STACK** - zasobnik - ukladanie lokalnych premennych


### Referencovanie premennych

Pomocou &premenna ziskame adresu premennej. Dereferencovanie .......

### Operatory

* +, -, /, *
* & | - bitove operatory (sucin, sucet)
* ^ xor
* % modulo

### Komentare

* jednoriadkovy - pred komentarom treba dve lomky //
* viac riadkovy - text obaleny /* */

### Podmienky

	if( /* podmienky */ ) {
		// splnene
	} else {
		// nesplnene
	}
	
### Cyklus

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
	
Kopilacia

	gcc program01.c -o program01

