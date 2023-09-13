#include "ecran.h"

uint32_t cur_lig = 8;
uint32_t cur_col = 0;

uint16_t *ptr_mem(uint32_t lig, uint32_t col)
{
    return (uint16_t *)FIRST_ADDR + lig * WIDTH + col;
}

void ecrit_car(uint32_t lig, uint32_t col, char c, color txt_col, color bg_col, bool blink)
{
    uint16_t *ptr = ptr_mem(lig, col);
    *ptr = c;
    *ptr |= txt_col << 8;
    *ptr |= bg_col << 12;
    *ptr |= blink << 15;
}

void efface_ecran(void)
{
    for (uint32_t lig = 0; lig < HEIGHT; lig++) {
        for (uint32_t col = 0; col < WIDTH; col++) {
            ecrit_car(lig, col, ' ', white, black, false);
        }
    }
}

void place_curseur(uint32_t lig, uint32_t col)
{
    uint16_t pos = col + lig * WIDTH;
    outb(LOW, CMD_PORT);
    outb(pos & 0xFF, DATA_PORT);
    outb(HIGH, CMD_PORT);
    outb(pos >> 8, DATA_PORT);

    cur_lig = lig;
    cur_col = col;
}

void traite_car(char c)
{
    if (32 <= c && c <= 126) {
        ecrit_car(cur_lig, cur_col, c, white, black, false);

        if (++cur_col < WIDTH) {
            place_curseur(cur_lig, cur_col);
        } else {
            cur_col = 0;
            place_curseur(++cur_lig, cur_col);
        }
    } else if (8 <= c && c <= 13) {
        switch (c) {
        case '\b':
            if (cur_col != 0) {
                place_curseur(cur_lig, --cur_col);
            }

            break;
            
        case '\t':
            cur_col += TAB_SIZE - cur_col % TAB_SIZE;

            if (cur_col < WIDTH) {
                place_curseur(cur_lig, cur_col);
            } else {
                cur_col = 0;
                place_curseur(++cur_lig, cur_col);
            }

            break;

        case '\n':
            cur_col = 0;
            place_curseur(++cur_lig, cur_col);
            break;

        case '\f':
            efface_ecran();
            cur_lig = 0;
            cur_col = 0;
            place_curseur(cur_lig, cur_col);
            break;

        case '\r':
            cur_col = 0;
            place_curseur(cur_lig, cur_col);
            break;

        default:
            break;
        }
    }
}

void defilement(void)
{
    memmove((void *)FIRST_ADDR, ptr_mem(1, 0), 2 * (NB_CASES - WIDTH));

    for (uint32_t col = 0; col < WIDTH; col++) {
        ecrit_car(HEIGHT - 1, col, ' ', white, black, false);
    }

    if (cur_lig != 0) {
        place_curseur(--cur_lig, cur_col);
    }
}
