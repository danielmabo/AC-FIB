#include "CacheSim.h"

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */
 typedef struct {
   int v0; //TAG via 0
   int validez0;
   int v1; //TAG via 1
   int validez1;
   int LRU; //Nº via mes recent
 } asociativa2;


 asociativa2 cache[64]; //Vector que simula la ocupació de mem cache de 64 linies ja que (64*2vies)*32Byte = 4KB guardarem el tag de cada via.



/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al comen�ar cada un dels tests.
 * */
void init_cache ()
{
    totaltime=0.0;
	/* Escriu aqui el teu codi */
    int i;
    for (i = 0; i < 64; i++) {
        cache[i].validez0 = 0; //Via 0 inicialment buida
        cache[i].validez1 = 0; //Via 1 inicialment buida
        cache[i].LRU = -1; //Via usada més recentment buida
    }
}

/* La rutina reference es cridada per cada referencia a simular */
void reference (unsigned int address)
{
	unsigned int byte;
	unsigned int bloque_m;
	unsigned int conj_mc;
	unsigned int via_mc;
	unsigned int tag;
	unsigned int miss;	   // boolea que ens indica si es miss
	unsigned int replacement;  // boolea que indica si es reempla�a una linia valida
	unsigned int tag_out;	   // TAG de la linia reempla�ada
	float t1,t2;		// Variables per mesurar el temps (NO modificar)

	t1=GetTime();
	/* Escriu aqui el teu codi */

    byte = address & 31; //Fem un AND amb 0x1F per obtenir els ultims 5 bits que indiquen el byte accedit.
	bloque_m = address/32; //Eliminem els 5 bits de menys pes
	conj_mc = bloque_m & 63; //Fem un AND del bloc amb 0x3F per obtenir els 6 bits de menys pes del bloc que indiquen la linia de mc.
	tag = bloque_m/64; //Eliminem els 6 bits de menys pes que son els de linia per obtenir el tag
	tag_out = -1; //Iniciem el tag de sortida com a -1 per defecte.
	
    miss = (cache[conj_mc].validez0 == 0 || cache[conj_mc].v0 != tag) && (cache[conj_mc].validez1 == 0 || cache[conj_mc].v1 != tag);
    replacement = (cache[conj_mc].validez0 == 1 && cache[conj_mc].v0 != tag && cache[conj_mc].validez1 == 1 && cache[conj_mc].v1 != tag);
	
	if (cache[conj_mc].validez0 == 0) { //Via 0 buida i per defecte s'omple primer
        cache[conj_mc].v0 = tag;
        cache[conj_mc].LRU = 0;
        cache[conj_mc].validez0 = 1;
        via_mc = 0;
	}
	else if (cache[conj_mc].v0 != tag) { //Via 0 no té aquest tag
        //Hem d'estudiar quin es l'estat de la via 1
        if (cache[conj_mc].validez1 == 0) { //Via 1 buida, omplim la via 1
            cache[conj_mc].v1 = tag;
            cache[conj_mc].LRU = 1;
            cache[conj_mc].validez1 = 1;
            via_mc = 1;
        }
        else if (cache[conj_mc].v1 != tag) { //Via 1 tampoc té aquest tag.
            if (cache[conj_mc].LRU == 0) {
              tag_out = cache[conj_mc].v1;
              cache[conj_mc].v1 = tag;
              cache[conj_mc].LRU = 1;
              via_mc = 1;
            }
            else { // LRU = 1
                tag_out = cache[conj_mc].v0;
                cache[conj_mc].v0 = tag;
                cache[conj_mc].LRU = 0;
                via_mc = 0;
           }
       }
        else { //Hit a la via 1
            via_mc = 1;
            cache[conj_mc].LRU = 1;
        }
	}
	else { // Hit a la via 0
        via_mc = 0;
        cache[conj_mc].LRU = 0;
	}

	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual. Tamb� mesurem el temps d'execuci�
	 * */
	t2=GetTime();
	totaltime+=t2-t1;
	test_and_print2 (address, byte, bloque_m, conj_mc, via_mc, tag,
			miss, replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */
void final ()
{
 	/* Escriu aqui el teu codi */


}
