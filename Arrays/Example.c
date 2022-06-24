/*
 * FPGA Interface C API example demonstrating usage of array indicators and
 * controls.
 *
 * NOTE: This code is merely an example and not ready to run. For more
 *       information about using these examples, refer to the Examples topic of
 *       the FPGA Interface C API Help, located under
 *       Start>>All Programs>>National Instruments>>FPGA Interface C API.
 */

#include "NiFpga_Example.h"

int main()
{
   NiFpga_Session session;
   /* must be called before any other calls */
   NiFpga_Status status = NiFpga_Initialize();
   if (NiFpga_IsNotError(status))
   {
      /* opens a session, downloads the bitstream, and runs the FPGA */
      NiFpga_MergeStatus(&status, NiFpga_Open("C:\\" NiFpga_Example_Bitfile,
                                              NiFpga_Example_Signature,
                                              "RIO0",
                                              0,
                                              &session));
      if (NiFpga_IsNotError(status))
      {
         uint8_t output[NiFpga_Example_ControlArrayU8Size_Output] = {0};
         NiFpga_Bool input[NiFpga_Example_IndicatorArrayBoolSize_Input];
         /* write data to the "Output" control on the FPGA */
         NiFpga_MergeStatus(&status,
            NiFpga_WriteArrayU8(session,
                                NiFpga_Example_ControlArrayU8_Output,
                                output,
                                NiFpga_Example_ControlArrayU8Size_Output));
         /* read data from the "Input" indicator on the FPGA */
         NiFpga_MergeStatus(&status,
            NiFpga_ReadArrayBool(session,
                                 NiFpga_Example_IndicatorArrayBool_Input,
                                 input,
                                 NiFpga_Example_IndicatorArrayBoolSize_Input));
         /* must close if we successfully opened */
         NiFpga_MergeStatus(&status, NiFpga_Close(session, 0));
      }
      /* must be called after all other calls */
      NiFpga_MergeStatus(&status, NiFpga_Finalize());
   }
   return status;
}
