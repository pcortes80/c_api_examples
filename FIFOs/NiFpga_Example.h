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
static const char* const NiFpga_Example_Signature = "820E7A3566B44A5A4392CFB4832F251F";

typedef enum
{
   NiFpga_Example_TargetToHostFifoI16_Input = 0,
} NiFpga_Example_TargetToHostFifoI16;

typedef enum
{
   NiFpga_Example_HostToTargetFifoI16_Output = 1,
} NiFpga_Example_HostToTargetFifoI16;

#endif
