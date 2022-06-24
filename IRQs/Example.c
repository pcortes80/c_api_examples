/*
 * FPGA Interface C API example demonstrating usage of interrupts.
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
         NiFpga_IrqContext irqContext;
         /* reserve a context for this thread to wait on IRQs */
         NiFpga_MergeStatus(&status,
            NiFpga_ReserveIrqContext(session, &irqContext));
         if (NiFpga_IsNotError(status))
         {
            uint32_t irqsAsserted;
            NiFpga_Bool timedOut;
            /* wait until an IRQ is asserted */
            NiFpga_MergeStatus(&status,
               NiFpga_WaitOnIrqs(session,
                                 irqContext,
                                 NiFpga_Irq_0 | NiFpga_Irq_1,
                                 1000, /* 1 second */
                                 &irqsAsserted,
                                 &timedOut));
            /* if an IRQ was asserted */
            if (NiFpga_IsNotError(status) && !timedOut)
            {
               if (irqsAsserted & NiFpga_Irq_0)
               {
                  /* TODO: do something if IRQ0 */
               }
               if (irqsAsserted & NiFpga_Irq_1)
               {
                  /* TODO: do something if IRQ1 */
               }
               /* acknowledge the IRQ(s) when we're done */
               NiFpga_MergeStatus(&status,
                  NiFpga_AcknowledgeIrqs(session,
                                         irqsAsserted));
            }
            /* must unreserve if we successfully reserved */
            NiFpga_MergeStatus(&status,
               NiFpga_UnreserveIrqContext(session, irqContext));
         }
         /* must close if we successfully opened */
         NiFpga_MergeStatus(&status, NiFpga_Close(session, 0));
      }
      /* must be called after all other calls */
      NiFpga_MergeStatus(&status, NiFpga_Finalize());
   }
   return status;
}
