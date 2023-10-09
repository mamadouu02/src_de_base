#ifndef SCREEN_H
#define SCREEN_H

#include <inttypes.h>
#include <stdbool.h>
#include <cpu.h>
#include <string.h>
#include "colors.h"

#define HEIGHT 25
#define WIDTH 80
#define NB_CASES (HEIGHT * WIDTH)
#define FIRST_ADDR 0xB8000
#define TAB_SIZE 8

uint16_t *ptr_mem(uint32_t lig, uint32_t col);

void ecrit_car(uint32_t lig, uint32_t col, char c, Color txt_col, Color bg_col, bool blink);

void efface_ecran(void);

void place_curseur(uint32_t lig, uint32_t col);

void traite_car(char c);

void defilement(void);

#endif
