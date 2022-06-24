/*
 * FPGA Interface C API example demonstrating usage of FIFOs.
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
         #define SIZE 256
         int16_t output[SIZE] = {0}; /* TODO: write to output buffer */
         int16_t input[SIZE];
         int16_t* writeElements;
         int16_t* readElements;
         size_t writeElementsAcquired;
         size_t readElementsAcquired;
         /* copy FIFO data to the FPGA */
         NiFpga_MergeStatus(&status,
            NiFpga_WriteFifoI16(session,
                                NiFpga_Example_HostToTargetFifoI16_Output,
                                output,
                                SIZE,
                                NiFpga_InfiniteTimeout,
                                NULL));
         /* copy FIFO data from the FPGA */
         NiFpga_MergeStatus(&status,
            NiFpga_ReadFifoI16(session,
                               NiFpga_Example_TargetToHostFifoI16_Input,
                               input,
                               SIZE,
                               NiFpga_InfiniteTimeout,
                               NULL));
         /* acquire elements we can write to without an additional copy */
         NiFpga_MergeStatus(&status,
            NiFpga_AcquireFifoWriteElementsI16(session,
                                NiFpga_Example_HostToTargetFifoI16_Output,
                                &writeElements,
                                SIZE,
                                NiFpga_InfiniteTimeout,
                                &writeElementsAcquired,
                                NULL));
         if (NiFpga_IsNotError(status))
         {
            /* TODO: write directly to writeElements[0] through
                     writeElements[writeElementsAcquired - 1] */
            NiFpga_MergeStatus(&status,
               NiFpga_ReleaseFifoElements(session,
                                NiFpga_Example_HostToTargetFifoI16_Output,
                                writeElementsAcquired));
         }
         /* acquire elements we can read from without an additional copy */
         NiFpga_MergeStatus(&status,
            NiFpga_AcquireFifoReadElementsI16(session,
                                NiFpga_Example_TargetToHostFifoI16_Input,
                                &readElements,
                                SIZE,
                                NiFpga_InfiniteTimeout,
                                &readElementsAcquired,
                                NULL));
         if (NiFpga_IsNotError(status))
         {
            /* TODO: read directly from readElements[0] through
                     readElements[readElementsAcquired - 1] */
            NiFpga_MergeStatus(&status,
               NiFpga_ReleaseFifoElements(session,
                                NiFpga_Example_TargetToHostFifoI16_Input,
                                readElementsAcquired));
         }
         /* must close if we successfully opened */
         NiFpga_MergeStatus(&status, NiFpga_Close(session, 0));
      }
      /* must be called after all other calls */
      NiFpga_MergeStatus(&status, NiFpga_Finalize());
   }
   return status;
}
