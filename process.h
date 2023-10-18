#ifndef PROCESS_H
#define PROCESS_H

#include <inttypes.h>
#include <stdio.h>
#include <cpu.h>
#include <string.h>

#define STACK_SIZE 512
#define NB_PROC 8

typedef enum {
    running,
    ready
} State;

typedef struct {
    int32_t pid;
    char name[32];
    State state;
    uint32_t regs[5];
    uint32_t stack[STACK_SIZE];
} Process;

void idle(void);

void proc1(void);

void ctx_sw(uint32_t *regs1, uint32_t *regs2);

void ordonnance(void);

int32_t mon_pid(void);

char *mon_nom(void);

void cree_idle(void);

int32_t cree_processus(void (*code)(void), char *nom);

#endif
