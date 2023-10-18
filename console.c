#include "console.h"

extern uint32_t cur_lig;

void console_putbytes(const char *s, int len)
{
    for (int i = 0; i < len; i++) {
        traite_car(s[i]);

        if (cur_lig == HEIGHT) {
            defilement();
        }
    }
}
