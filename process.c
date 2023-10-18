#include "process.h"
#include "tinyalloc.h"

Process *process_tab[NB_PROC];
int32_t pid_active = 0;
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
    int32_t pid_old = pid_active++;
    pid_active %= NB_PROC;
    process_tab[pid_old]->state = ready;
    process_tab[pid_active]->state = running;
    ctx_sw(process_tab[pid_old]->regs, process_tab[pid_active]->regs);
}

int32_t mon_pid(void)
{
    return pid_active;
}

char *mon_nom(void)
{
    return process_tab[pid_active]->name;
}

void cree_idle(void)
{
    process_tab[0] = malloc(sizeof(Process));
    process_tab[0]->pid = 0;
    strcpy(process_tab[0]->name, "idle");
    process_tab[0]->state = running;
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
    process_tab[id]->regs[1] = (uint32_t)(process_tab[id]->stack + (STACK_SIZE - 1));
    process_tab[id]->stack[STACK_SIZE - 1] = (uint32_t)code;
    return id++;
}
