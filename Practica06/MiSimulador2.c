#include "CacheSim.h"
 #include <stdio.h>

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */

 typedef struct {
	unsigned int tag;
	unsigned int validez;
	unsigned int dirty;
 } directa;


 directa cache[128]; // Vector que simula la ocupació de mem cache de 128 linies ja que 128*32Byte = 4KB guardarem els tag.

 int n_hit;
 int n_miss;

/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al comen�ar cada un dels tests.
 * */
void init_cache ()
{
	/* Escriu aqui el teu codi */

	int i;
    for (i = 0; i < 128; i++){
        cache[i].validez = 0; //Posem els bit de validesa a 0 per indicar que aquella linia esta buida
    }
    n_hit  = 0;
    n_miss = 0;
}

/* La rutina reference es cridada per cada referencia a simular */
void reference (unsigned int address, unsigned int LE)
{
	unsigned int byte;
	unsigned int bloque_m;
	unsigned int linea_mc;
	unsigned int tag;
	unsigned int miss;
	unsigned int lec_mp;
	unsigned int mida_lec_mp;
	unsigned int esc_mp;
	unsigned int mida_esc_mp;
	unsigned int replacement;
	unsigned int tag_out;

	/* Escriu aqui el teu codi */

	//LE pren el valor 0->Lectura, 1->escriptura

	byte = address & 31; //Fem un AND amb 0x1F per obtenir els ultims 5 bits que indiquen el byte accedit.
	bloque_m = address>>5; //Eliminem els 5 bits de menys pes
	linea_mc = bloque_m & 127; //Fem un AND del bloc amb 0x7F per obtenir els 7 bits de menys pes del bloc que indiquen la linia de mc.
	tag = bloque_m>>7; //Eliminem els 7 bits de menys pes que son els de linia per obtenir el tag

    miss = (cache[linea_mc].validez == 0 || cache[linea_mc].tag != tag);
    replacement = (cache[linea_mc].validez == 1 && cache[linea_mc].tag != tag);
	esc_mp = (replacement && cache[linea_mc].dirty);
	lec_mp = (miss);

	if (esc_mp){
		mida_esc_mp = 32;
	}
	if (lec_mp){
		mida_lec_mp = 32;
	}
	if (miss && !replacement) { //Miss lectura, linia de cache buida (no reemplaçament)
		cache[linea_mc].tag = tag;
		cache[linea_mc].validez = 1;
		cache[linea_mc].dirty = 0;
	}
	else if (miss && replacement) { //Miss lectura, (si reemplaçament)
		tag_out = cache[linea_mc].tag;
		cache[linea_mc].tag = tag;
		cache[linea_mc].dirty = 0;
	}
	if (LE && !cache[linea_mc].dirty){
		cache[linea_mc].dirty = 1;
	}
	if (miss){
		n_miss++;
	}
	else {
		n_hit++;
	}

	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual
	 * */
	test_and_print (address, LE, byte, bloque_m, linea_mc, tag,
			miss, lec_mp, mida_lec_mp, esc_mp, mida_esc_mp,
			replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */
void final ()
{
 	/* Escriu aqui el teu codi */
	//printf("Miss: %d\n", n_miss);
	//printf("Hit: %d\n", n_hit);

}
