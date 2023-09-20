#include <cpu.h>
#include <inttypes.h>
#include "console.h"
#include "ecran.h"
#include "temps.h"

void kernel_start(void)
{
    // traite_car('\f');
    // ecrit_car(0, 0, 'A', black, green, false);
    // place_curseur(0, 1);
    // traite_car('\t');
    // traite_car('B');
    // traite_car('\b');
    // traite_car('C');
    // traite_car('\n');
    // traite_car('D');
    // traite_car('\r');
    // place_curseur(HEIGHT, 0);
    // traite_car('E');
    // defilement();
    
    efface_ecran();
    place_curseur(HEIGHT - 1, WIDTH - 7);
    console_putbytes("Hello, world!\n", 15);
    
    ecrit_temps("14:45:00", 9);
    init_traitant_IT(32, traitant_IT_32);

    // on ne doit jamais sortir de kernel_start
    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}
