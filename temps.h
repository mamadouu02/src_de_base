#ifndef TEMPS_H
#define TEMPS_H

#include <stdio.h>
#include <segment.h>
#include "ecran.h"

#define IDT_ADDR 0x1000
#define QUARTZ 0x1234DD
#define CLOCKFREQ 50

extern void ecrit_temps(const char *s, int len);

extern void tic_PIT(void);

extern void init_traitant_IT(uint32_t num_IT, void (*traitant)(void));

extern void traitant_IT_32(void);

extern void set_clockfreq(void);

extern void masque_IRQ(uint32_t num_IRQ, bool masque);

#endif
