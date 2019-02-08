/*---------------------------------------------------------------------------*/
/*                                                                           */
/* FILE:    guidll.h                                                         */
/*                                                                           */
/* PURPOSE: This is the header file for guidll.dll.  This file is used in    */
/*          two ways -- it is added to the guidll.prj project to tell        */
/*          LabWindows/CVI to export the symbols contained in it.  It is     */
/*          used by the calling project to gain access to the library        */
/*          function prototypes.                                             */
/*                                                                           */
/*          Note that we explicitly specify a calling convention for our     */
/*          functions.  This is necessary to ensure that caller and callee   */
/*          agree on stack responsibilities.  You should always sepcify a    */
/*          calling convention explicitly when prototyping DLL functions.    */
/*---------------------------------------------------------------------------*/

int __stdcall RunDLLUI (void);
