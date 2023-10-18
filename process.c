#include "process.h"
#include "tinyalloc.h"

Process *process_tab[NB_PROC];
int32_t active = 0;
int32_t id = 1;

void idle(void)
{
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}

void proc1(void)
{
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}

void ordonnance(void)
{
    int32_t old = active++;
    active %= NB_PROC;
    process_tab[old]->state = ready;
    process_tab[active]->state = running;
    ctx_sw(process_tab[old]->regs, process_tab[active]->regs);
}

int32_t mon_pid(void)
{
    return active;
}

char *mon_nom(void)
{
    return process_tab[active]->name;
}

int32_t cree_processus(void (*code)(void), char *nom)
{
    if (id >= NB_PROC) {
        return -1;
    }

    process_tab[id] = malloc(sizeof(Process));
    process_tab[id]->pid = id;
    strcpy(process_tab[id]->name, nom);
    process_tab[id]->state = ready;
    process_tab[id]->regs[id] = (uint32_t)(process_tab[id]->stack + (STACK_SIZE - 1));
    process_tab[id]->stack[STACK_SIZE - 1] = (uint32_t)code;
    return id++;
}
