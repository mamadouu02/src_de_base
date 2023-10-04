#include "process.h"

Process process_tab[PROCESS_TAB_SIZE];

void idle(void)
{
    printf("[idle] je tente de passer la main a proc1...\n");
    ctx_sw(process_tab[0].regs, process_tab[1].regs);
}

void proc1(void)
{
    printf("[proc1] idle m'a donne la main\n");
    printf("[proc1] j'arrete le systeme\n");
    hlt();
}
