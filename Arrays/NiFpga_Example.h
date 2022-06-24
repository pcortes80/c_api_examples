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
static const char* const NiFpga_Example_Signature = "D4D53FA41D50D2E2A242B343835BA673";

typedef enum
{
   NiFpga_Example_IndicatorArrayBool_Input = 0x810E,
} NiFpga_Example_IndicatorArrayBool;

typedef enum
{
   NiFpga_Example_IndicatorArrayBoolSize_Input = 8,
} NiFpga_Example_IndicatorArrayBoolSize;

typedef enum
{
   NiFpga_Example_ControlArrayU8_Output = 0x8110,
} NiFpga_Example_ControlArrayU8;

typedef enum
{
   NiFpga_Example_ControlArrayU8Size_Output = 8,
} NiFpga_Example_ControlArrayU8Size;

#endif
