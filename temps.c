#include "temps.h"

uint32_t *idt = (uint32_t *)IDT_ADDR;

void ecrit_temps(const char *s, int len)
{
    uint32_t col = WIDTH - len + 1;

    for (const char *c = s; *c; c++, col++) {
        ecrit_car(0, col, *c, white, black, false);
    }
}

void tic_PIT(void)
{
    outb(0x20, 0x20);
    char s[9];
    sprintf(s, "HH:MM:SS");
    ecrit_temps(s, 9);
}

void init_traitant_IT(uint32_t num_IT, void (*traitant)(void))
{
    idt[2 * num_IT] = KERNEL_CS << 16 | (uint32_t)traitant && 0xFFFF;
    idt[2 * num_IT + 1] = (uint32_t)traitant && 0xFFFF0000 | 0x8E00;
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
