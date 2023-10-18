#include <cpu.h>
#include <inttypes.h>
#include "console.h"
#include "screen.h"
#include "time.h"
#include "process.h"

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
    
    // efface_ecran();
    // place_curseur(HEIGHT - 1, WIDTH - 7);
    // console_putbytes("Hello, world!\n", 15);
    // ecrit_temps("14:45:00", 9);
    
    traite_car('\f');
    init_traitant_IT(32, traitant_IT_32);
    set_clockfreq();
    masque_IRQ(0, false);
    // sti();

    // initialisation des structures de processus
    cree_idle();
    cree_processus(proc1, "proc1");
    cree_processus(proc1, "proc2");
    cree_processus(proc1, "proc3");
    cree_processus(proc1, "proc4");
    cree_processus(proc1, "proc5");
    cree_processus(proc1, "proc6");
    cree_processus(proc1, "proc7");

    // demarrage du processus par defaut
    idle();
    
    // on ne doit jamais sortir de kernel_start
    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}
