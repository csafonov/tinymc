/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_COMMANDBUTTON              2       /* control type: command, callback function: CloseUICallback */
#define  PANEL_GRAPH                      3       /* control type: graph, callback function: (none) */
#define  PANEL_NUMERICSLIDE_A5            4       /* control type: scale, callback function: SliderCallback */
#define  PANEL_NUMERICSLIDE_A4            5       /* control type: scale, callback function: SliderCallback */
#define  PANEL_NUMERICSLIDE_A3            6       /* control type: scale, callback function: SliderCallback */
#define  PANEL_NUMERICSLIDE_A2            7       /* control type: scale, callback function: SliderCallback */
#define  PANEL_NUMERICSLIDE_A1            8       /* control type: scale, callback function: SliderCallback */
#define  PANEL_NUMERICSLIDE_A0            9       /* control type: scale, callback function: SliderCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK CloseUICallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SliderCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
