/*
 * FPGA Interface C API example for Wind River Workbench 2.3 or later for
 * controllers running VxWorks.
 *
 * NOTE: In order to run this example, you must compile a LabVIEW FPGA bitfile
 *       and generate a C API for it. For more information about using this
 *       example, refer to the Examples topic of the FPGA Interface C API Help,
 *       located under
 *       Start>>All Programs>>National Instruments>>FPGA Interface C API.
 */

#include "NiFpga_ExampleCompactRIO.h"
#include <stdio.h>
#include <tasklib.h>

int NiFpga_ExampleCompactRIO_Main(int mainFunction,
                                  int clientContext,
                                  int thread,
                                  int reserved1,
                                  int reserved2,
                                  int reserved3,
                                  int reserved4,
                                  int reserved5,
                                  int reserved6,
                                  int reserved7)
{
   /* must be called before any other calls */
   printf("Initializing...\n");
   NiFpga_Status status = NiFpga_Initialize();
   if (NiFpga_IsNotError(status))
   {
      NiFpga_Session session;
      /* opens a session, downloads the bitstream, and runs the FPGA */
      printf("Opening a session...\n");
      NiFpga_MergeStatus(&status, NiFpga_Open(NiFpga_ExampleCompactRIO_Bitfile,
                                              NiFpga_ExampleCompactRIO_Signature,
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
                                                    NiFpga_ExampleCompactRIO_IndicatorI16_DeviceTemperature,
                                                    &rawTemperature));
         fahrenheit = (rawTemperature / 4.0) * (9.0 / 5.0) + 32;
         printf("Current temperature in Fahrenheit: %.1f\n", fahrenheit);
         /* stop the FPGA loop */
         printf("Stopping the FPGA...\n");
         NiFpga_MergeStatus(&status, NiFpga_WriteBool(session,
                                                      NiFpga_ExampleCompactRIO_ControlBool_Stop,
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
      printf("Error %ld!\n", status);
   else
      printf("Succeeded.\n");
   return status;
}

int NiFpga_ExampleCompactRIO_DllMain()
{
   /* spawn a thread to run our application */
   return taskSpawn("Example",
                    100,
                    VX_FP_TASK,
                    0x8000,
                    (FUNCPTR)NiFpga_ExampleCompactRIO_Main,
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

/* forces the main function to be called */
const int runDllMain = NiFpga_ExampleCompactRIO_DllMain();
