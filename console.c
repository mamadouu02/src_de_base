#include "console.h"

extern uint32_t cur_lig;

void console_putbytes(const char *s, int len)
{
    for (const char *c = s; *c; c++) {
        traite_car(*c);

        if (cur_lig == HEIGHT) {
            defilement();
        }
    }
}
