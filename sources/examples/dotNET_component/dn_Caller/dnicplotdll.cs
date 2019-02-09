
using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace NicPlotDll
{

    /*
[StructLayout(LayoutKind.Sequential)]
public unsafe struct tagDesignerData
{
	public Int32 nSize;
	public Int32 nErrCode;
// internal data for designer (may be converted to internal array)
	public Int32 TF_length;
	public Int32 TF_dim;
	public Int32 DataArray_length;

    [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)(TUNER_CONSTS.MAX_IDENT_FREQS_NUM))]
	public double[] TF1_Freqs;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)(TUNER_CONSTS.MAX_IDENT_FREQS_NUM))]
    public double[] TF1_re;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)(TUNER_CONSTS.MAX_IDENT_FREQS_NUM))]
    public double[] TF1_im;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)(TUNER_CONSTS.MAX_IDENT_FREQS_NUM))]
    public double[] TF2_re;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)(TUNER_CONSTS.MAX_IDENT_FREQS_NUM))]
    public double[] TF2_im;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)(TUNER_CONSTS.MAX_DATAARRAY_LEN))]
    public double[] DataArray; //[MAX_DATAARRAY_LEN];

    public tagDesignerData(short x)
    {
        nSize = 0;
        nErrCode = 0;
        TF_length = 0;
        TF_dim = 0;
        DataArray_length = 0;
        TF1_Freqs = new double[(int)(TUNER_CONSTS.MAX_IDENT_FREQS_NUM)];
        TF1_re = new double[(int)(TUNER_CONSTS.MAX_IDENT_FREQS_NUM)];
        TF1_im = new double[(int)(TUNER_CONSTS.MAX_IDENT_FREQS_NUM)];
        TF2_re = new double[(int)(TUNER_CONSTS.MAX_IDENT_FREQS_NUM)];
        TF2_im = new double[(int)(TUNER_CONSTS.MAX_IDENT_FREQS_NUM)];
        DataArray = new double[(int)(TUNER_CONSTS.MAX_DATAARRAY_LEN)];
    }
};

    


[StructLayout(LayoutKind.Sequential)]
public struct tagPlotCollection
{
	public Int32   nSize;
	public Int32   nErrCode;
	public Int32   NumPlots;
	public Int32   MustRedraw;
    // for selected data
	//tagPlotData[]  PlotData;// array for all idents
    public Int32 NumFreqs;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)(TUNER_CONSTS.MAX_IDENT_FREQS_NUM))]
    public double[] Freqs;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)(TUNER_CONSTS.MAX_IDENT_FREQS_NUM))]
    public double[] Phases;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = (int)(TUNER_CONSTS.MAX_IDENT_FREQS_NUM))]
    public double[] Magnitudes;

    public tagPlotCollection(short x)
    {
        nSize = 0;
        nErrCode = 0;
        NumPlots=0;
        MustRedraw=0;

        NumFreqs = 0;
        Freqs = new double[(int)(TUNER_CONSTS.MAX_IDENT_FREQS_NUM)];
        Phases = new double[(int)(TUNER_CONSTS.MAX_IDENT_FREQS_NUM)];
        Magnitudes = new double[(int)(TUNER_CONSTS.MAX_IDENT_FREQS_NUM)];

    }
};
    */


    //void __stdcall InitDLL(void)
    //void __stdcall UnInitDLL(void)
//void __stdcall calccurrentctrl(double *PropGain,double *IntGain,long *FreqLen,double *FreqHz,
//							   double *OL_Mag,double *OL_Ph,double *CL_Mag,double *CL_Ph,
//							   long *RespLen,double *RespTime,double *Resp,long MaxFreqLen,long MaxTimeLen,double R,double L,double Ts,double Ovs)

    class wizDll
    {
        [System.Runtime.InteropServices.DllImport("dll_getcurloop.dll", EntryPoint = "calccurrentctrl", SetLastError = true,
            CharSet = CharSet.Unicode, ExactSpelling = true,
             CallingConvention = CallingConvention.StdCall)]
        public static extern void calccurrentctrl(
          out  double  PropGain, out double IntGain, out UInt32 FreqLen, double[] FreqHz,
            							   double [] OL_Mag,double [] OL_Ph,double [] CL_Mag,double [] CL_Ph,
                                           out UInt32 RespLen, double[] RespTime, double[] Resp, UInt32 MaxFreqLen, UInt32 MaxTimeLen, double R, double L, double Ts, double Ovs);

        [DllImport("dll_getcurloop.dll", EntryPoint = "InitDLL", SetLastError = true,
            CharSet = CharSet.Unicode, ExactSpelling = true,
             CallingConvention = CallingConvention.StdCall)]
        public static extern void InitDLL();

        [DllImport("dll_getcurloop.dll", EntryPoint = "UnInitDLL", SetLastError = true,
            CharSet = CharSet.Unicode, ExactSpelling = true,
             CallingConvention = CallingConvention.StdCall)]
        public static extern void UnInitDLL();

        public wizDll()
        {
        }
        ~wizDll()
        {
        }
    }
}
