#ifndef DIAG_TYPES_H
#define DIAG_TYPES_H

#ifdef DIAG_THIS_IS_UBOOT
/*
 * This is used by U-Boot only as a work-around since std[int/bool].h
 * does not exist in U-Boot
 */
#include <common.h>
#else
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#endif

#endif //DIAG_TYPES_H
