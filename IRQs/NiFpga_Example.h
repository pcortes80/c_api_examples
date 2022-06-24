/*
 * Generated with the FPGA Interface C API Generator 1.0.
 */

#ifndef __NiFpga_Example_h__
#define __NiFpga_Example_h__

#ifndef NiFpga_Version
   #define NiFpga_Version 100
#endif

#include "NiFpga.h"

/**
 * The filename of the FPGA bitfile.
 *
 * This is a #define to allow for string literal concatenation. For example:
 *
 *    static const char* const Bitfile = "C:\\" NiFpga_Example_Bitfile;
 */
#define NiFpga_Example_Bitfile "NiFpga_Example.lvbitx"

/**
 * The signature of the FPGA bitfile.
 */
static const char* const NiFpga_Example_Signature = "27E593155E48A4B4B8EFBAFC4DF9D51B";

typedef enum
{
   NiFpga_Example_IndicatorI32_Interrupts0 = 0x810C,
   NiFpga_Example_IndicatorI32_Interrupts1 = 0x8110,
} NiFpga_Example_IndicatorI32;

#endif
