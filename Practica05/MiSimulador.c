#include "CacheSim.h"

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */


 typedef struct {
   int tag;
   int validez;
 } directa;


directa cache[128]; // Vector que simula la ocupació de mem cache de 128 linies ja que 128*32Byte = 4KB guardarem els tag.



/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al comen�ar cada un dels tests.
 * */
void init_cache ()
{
    totaltime=0.0;
	/* Escriu aqui el teu codi */
    int i;
    for (i = 0; i < 128; i++){
        cache[i].validez = 0; //Posem els tag a -1 per indicar que aquella linia esta buida
    }

}

/* La rutina reference es cridada per cada referencia a simular */
void reference (unsigned int address)
{
	unsigned int byte;
	unsigned int bloque_m;
	unsigned int linea_mc;
	unsigned int tag;
	unsigned int miss;	   // boolea que ens indica si es miss
	unsigned int replacement;  // boolea que indica si es reempla�a una linia valida
	unsigned int tag_out;	   // TAG de la linia reempla�ada
	float t1,t2;		// Variables per mesurar el temps (NO modificar)

	t1=GetTime();
	/* Escriu aqui el teu codi */

    byte = address & 31; //Fem un AND amb 0x1F per obtenir els ultims 5 bits que indiquen el byte accedit.
	bloque_m = address/32; //Eliminem els 5 bits de menys pes
	linea_mc = bloque_m & 127; //Fem un AND del bloc amb 0x7F per obtenir els 7 bits de menys pes del bloc que indiquen la linia de mc.
	tag = bloque_m/128; //Eliminem els 7 bits de menys pes que son els de linia per obtenir el tag
	tag_out = -1; //Iniciem el tag de sortida com a -1 per defecte.
    miss = (cache[linea_mc].validez == 0 || cache[linea_mc].tag != tag);
    replacement = (cache[linea_mc].validez == 1 && cache[linea_mc].tag != tag);

	if (cache[linea_mc].validez == 0) { //Miss lectura, linia de cache buida (no reemplaçament)
        cache[linea_mc].tag = tag;
        cache[linea_mc].validez = 1;
	}
	else if (cache[linea_mc].validez == 1 && cache[linea_mc].tag != tag) { //Miss lectura, (si reemplaçament)
        tag_out = cache[linea_mc].tag;
        cache[linea_mc].tag = tag;
	}

	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual. Tamb� mesurem el temps d'execuci�
	 * */
	t2=GetTime();
	totaltime+=t2-t1;
	test_and_print (address, byte, bloque_m, linea_mc, tag,
			miss, replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */
void final ()
{
 	/* Escriu aqui el teu codi */


}
