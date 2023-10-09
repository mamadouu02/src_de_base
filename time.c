#include "time.h"

uint8_t tic = CLOCKFREQ;
Time t = { 0, 0, 0 };

void ecrit_temps(const char *s, int len)
{
    uint32_t col = WIDTH - len + 1;
    
    for (const char *c = s; *c; c++, col++) {
        ecrit_car(0, col, *c, white, black, false);
    }
}

void tic_PIT(void)
{
    char s[12];
    outb(0x20, 0x20);

    if (tic++ == CLOCKFREQ) {
        tic = 0;

        sprintf(s, "%02u:%02u:%02u", t.h, t.m, t.s);
        ecrit_temps(s, 9);

        t.h += ((t.m == 59) && (t.s == 59)) % 100;
        t.m = (t.m + (t.s == 59)) % 60;
        t.s = (t.s + 1) % 60;
    }
}

void init_traitant_IT(uint32_t num_IT, void (*traitant)(void))
{
    uint32_t *IDT = (uint32_t *)IDT_ADDR;
    IDT[2 * num_IT] = KERNEL_CS << 16 | ((uint32_t)traitant & 0xFFFF);
    IDT[2 * num_IT + 1] = ((uint32_t)traitant & 0xFFFF0000) | 0x8E00;
}

void set_clockfreq(void)
{
    outb(0x34, 0x43);
    outb((QUARTZ / CLOCKFREQ) & 0xFF, 0x40);
    outb((QUARTZ / CLOCKFREQ) >> 8, 0x40);
}

void masque_IRQ(uint32_t num_IRQ, bool masque)
{
    uint8_t mask = inb(0x21);

    if (masque) {
        mask |= 1 << num_IRQ;
    } else {
        mask &= ~(1 << num_IRQ);
    }

    outb(mask, 0x21);
}
