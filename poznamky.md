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

	for(int i =0; i < 10; i++) {
		// program opakovany 10 krat
	}
	
Priklad nekonecneho cyklu

	for(;;) {
		// program opakovany dookola
	}
