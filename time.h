#ifndef TIME_H
#define TIME_H

#include <stdio.h>
#include <segment.h>
#include "screen.h"

#define IDT_ADDR 0x1000
#define QUARTZ 0x1234DD
#define CLOCKFREQ 50

typedef struct {
    uint8_t h;
    uint8_t m;
    uint8_t s;
} Time;

void ecrit_temps(const char *s, int len);

void tic_PIT(void);

void init_traitant_IT(uint32_t num_IT, void (*traitant)(void));

void traitant_IT_32(void);

void set_clockfreq(void);

void masque_IRQ(uint32_t num_IRQ, bool masque);

#endif
