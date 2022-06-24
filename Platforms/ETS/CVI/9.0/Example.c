/*
 * FPGA Interface C API example for CVI Real-Time Module 9.0 or later for
 * controllers running Phar Lap ETS.
 *
 * NOTE: In order to run this example, you must compile a LabVIEW FPGA bitfile
 *       and generate a C API for it. For more information about using this
 *       example, refer to the Examples topic of the FPGA Interface C API Help,
 *       located under
 *       Start>>All Programs>>National Instruments>>FPGA Interface C API.
 */

#include "NiFpga_ExampleRSeries.h"
#include <stdio.h>
#include <cvirte.h>
#include <rtutil.h>

void CVIFUNC_C RTmain(void)
{
   /* initialize the CVI Run-Time Engine */
   if (!InitCVIRTE(0, 0, 0))
   {
      /* out of memory */
      printf("Error initializing the CVI Run-Time Engine!\n");
      return;
   }
   /* must be called before any other calls */
   printf("Initializing...\n");
   NiFpga_Status status = NiFpga_Initialize();
   if (NiFpga_IsNotError(status))
   {
      NiFpga_Session session;
      /* opens a session, downloads the bitstream, and runs the FPGA */
      printf("Opening a session...\n");
      NiFpga_MergeStatus(&status, NiFpga_Open("C:\\ni-rt\\cvi\\" NiFpga_ExampleRSeries_Bitfile,
                                              NiFpga_ExampleRSeries_Signature,
                                              "RIO0",
                                              NiFpga_OpenAttribute_NoRun,
                                              &session));
      if (NiFpga_IsNotError(status))
      {
         int16_t rawTemperature = 0;
         double fahrenheit;
         /* run the FPGA application */
         printf("Running the FPGA...\n");
         NiFpga_MergeStatus(&status, NiFpga_Run(session, 0));
         /* read the current temperature */
         NiFpga_MergeStatus(&status, NiFpga_ReadI16(session,
                                                    NiFpga_ExampleRSeries_IndicatorI16_DeviceTemperature,
                                                    &rawTemperature));
         fahrenheit = (rawTemperature / 4.0) * (9.0 / 5.0) + 32;
         printf("Current temperature in Fahrenheit: %.1f\n", fahrenheit);
         /* set the toggle rate to half a second */
         printf("Setting the toggle rate to half a second...\n");
         NiFpga_MergeStatus(&status, NiFpga_WriteU32(session,
                                                     NiFpga_ExampleRSeries_ControlU32_WaitMilliseconds,
                                                     500));
         printf("Waiting 10 seconds...\n");
         SleepUS(10000000);
         /* stop the FPGA loops */
         printf("Stopping the FPGA...\n");
         NiFpga_MergeStatus(&status, NiFpga_WriteBool(session,
                                                      NiFpga_ExampleRSeries_ControlBool_Stop,
                                                      1));
         /* close the session now that we're done */
         printf("Closing the session...\n");
         NiFpga_MergeStatus(&status, NiFpga_Close(session, 0));
      }
      /* must be called after all other calls */
      printf("Finalizing...\n");
      NiFpga_MergeStatus(&status, NiFpga_Finalize());
   }
   /* check if anything went wrong */
   if (NiFpga_IsError(status))
      printf("Error %d!\n", status);
   else
      printf("Succeeded.\n");
   /* close the CVI Run-Time Engine */
   CloseCVIRTE();
}
