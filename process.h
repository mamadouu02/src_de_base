#ifndef PROCESS_H
#define PROCESS_H

#include <inttypes.h>
#include <stdio.h>
#include <cpu.h>

#define STACK_SIZE 512
#define PROCESS_TAB_SIZE 2

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

#endif
