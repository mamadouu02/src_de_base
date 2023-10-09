#include "process.h"

Process process_tab[PROCESS_TAB_SIZE];

void idle(void)
{
    for (int i = 0; i < 3; i++) {
        printf("[idle] je tente de passer la main a proc1...\n");
        ctx_sw(process_tab[0].regs, process_tab[1].regs);
        printf("[idle] proc1 m'a redonne la main\n");
    }

    printf("[idle] je bloque le systeme\n");
    hlt();
}

void proc1(void)
{
    for (;;) {
        printf("[proc1] idle m'a donne la main\n");
        printf("[proc1] je tente de lui la redonner...\n");
        ctx_sw(process_tab[1].regs, process_tab[0].regs);
    }
}
