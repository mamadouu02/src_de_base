#ifndef ECRAN_H
#define ECRAN_H

#include <inttypes.h>
#include <stdbool.h>
#include <cpu.h>
#include <string.h>
#include "colors.h"

#define HEIGHT 25
#define WIDTH 80
#define NB_CASES (HEIGHT * WIDTH)
#define FIRST_ADDR 0xB8000
#define CMD_PORT 0x3D4
#define DATA_PORT 0x3D5
#define LOW 0x0F
#define HIGH 0x0E
#define TAB_SIZE 8

extern uint16_t *ptr_mem(uint32_t lig, uint32_t col);

extern void ecrit_car(uint32_t lig, uint32_t col, char c, color txt_col, color bg_col, bool blink);

extern void efface_ecran(void);

extern void place_curseur(uint32_t lig, uint32_t col);

extern void traite_car(char c);

extern void defilement(void);

#endif
