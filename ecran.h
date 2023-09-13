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

uint16_t *ptr_mem(uint32_t lig, uint32_t col);

void ecrit_car(uint32_t lig, uint32_t col, char c, color txt_col, color bg_col, bool blink);

void efface_ecran(void);

void place_curseur(uint32_t lig, uint32_t col);

void traite_car(char c);

void defilement(void);

#endif
