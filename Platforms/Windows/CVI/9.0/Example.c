/*
 * FPGA Interface C API example for CVI 9.0 or later for computers running
 * Microsoft Windows.
 *
 * NOTE: In order to run this example, you must compile a LabVIEW FPGA bitfile
 *       and generate a C API for it. For more information about using this
 *       example, refer to the Examples topic of the FPGA Interface C API Help,
 *       located under
 *       Start>>All Programs>>National Instruments>>FPGA Interface C API.
 */

#include "Example.h"
#include "NiFpga_ExampleRSeries.h"
#include <stdio.h> 
#include <windows.h>
 
int main(int argc, char* argv[])
{
   int panel;
   if (InitCVIRTE(0, argv, 0) == 0)
   {
      /* out of memory */
      return -1;
   }
   panel = LoadPanel(0, "Example.uir", PANEL);
   if (panel < 0)
   {
      return -1;
   }
   DisplayPanel(panel);
   RunUserInterface();
   DiscardPanel(panel);
   return 0;
}

int CVICALLBACK PanelCallback(int   panel,
                              int   event,
                              void* callbackData,
                              int   eventData1,
                              int   eventData2)
{
   if (event == EVENT_CLOSE)
   {
      QuitUserInterface(0);
   }
   return 0;
}


int CVICALLBACK AcquireCallback(int   panel,
                                int   control,
                                int   event,
                                void* callbackData,
                                int   eventData1,
                                int   eventData2)
{
   if (event == EVENT_COMMIT)
   {
      NiFpga_Status status = NiFpga_Status_Success;
      /* setup the graph */
      SetCtrlAttribute(panel,
                       PANEL_GRAPH,
                       ATTR_XAXIS_GAIN,
                       1.0);
      DeleteGraphPlot(panel,
                      PANEL_GRAPH,
                      -1,
                      VAL_IMMEDIATE_DRAW);
      /* must be called before any other calls */
      NiFpga_MergeStatus(&status, NiFpga_Initialize());
      if (NiFpga_IsNotError(status))
      {
         NiFpga_Session session;
         /* opens a session, downloads the bitstream, and runs the FPGA */
         NiFpga_MergeStatus(&status, NiFpga_Open(NiFpga_ExampleRSeries_Bitfile,
                                                 NiFpga_ExampleRSeries_Signature,
                                                 "RIO0",
                                                 NiFpga_OpenAttribute_NoRun,
                                                 &session));
         if (NiFpga_IsNotError(status))
         {
            #define points 50
            int16_t rawTemperature = 0;
            double fahrenheit[points];
            int i;
            /* run the FPGA application */
            NiFpga_MergeStatus(&status, NiFpga_Run(session, 0));
            for (i = 0; i < points; i++)
            {
               /* read the current temperature */
               NiFpga_MergeStatus(&status, NiFpga_ReadI16(session,
                                                          NiFpga_ExampleRSeries_IndicatorI16_DeviceTemperature,
                                                          &rawTemperature));
               /* convert to Fahrenheit */
               fahrenheit[i] = (rawTemperature / 4.0) * (9.0 / 5.0) + 32;
            }
            /* plot the data */
            PlotY(panel,
                  PANEL_GRAPH,
                  fahrenheit,
                  points,
                  VAL_DOUBLE,
                  VAL_THIN_LINE,
                  VAL_EMPTY_SQUARE,
                  VAL_SOLID,
                  1,
                  VAL_RED);
            SetCtrlAttribute(panel, PANEL_ACQUIRE, ATTR_DIMMED, 1);
            ProcessDrawEvents();
            /* set the toggle rate to half a second */
            NiFpga_MergeStatus(&status, NiFpga_WriteU32(session,
                                                        NiFpga_ExampleRSeries_ControlU32_WaitMilliseconds,
                                                        500));
            /* wait for a while */
            Sleep(5000);
            /* stop the FPGA loops */
            NiFpga_MergeStatus(&status, NiFpga_WriteBool(session,
                                                         NiFpga_ExampleRSeries_ControlBool_Stop,
                                                         1));
            /* close the session now that we're done */
            NiFpga_MergeStatus(&status, NiFpga_Close(session, 0));
         }
         /* must be called after all other calls */
         NiFpga_MergeStatus(&status, NiFpga_Finalize());
      }
      /* check if anything went wrong */
      if (NiFpga_IsError(status))
      {
         char error[32];
         sprintf(error, "Error %d!", status);
         MessagePopup("Error", error);
      }
   }
   SetCtrlAttribute(panel, PANEL_ACQUIRE, ATTR_DIMMED, 0);
   ProcessDrawEvents();
   return 0;
}
