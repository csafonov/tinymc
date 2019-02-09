using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using OxyPlot;
using OxyPlot.Axes;
using OxyPlot.Series;
using OxyPlot.WindowsForms;

using NicPlotDll;

namespace dn_Caller
{

    public partial class FormDesPI : Form
    {
        private CbodePlot bodePlot;
        private CNicholsPlot nicholsPlot;
        private CStepRespPlot StepRespPlot;

        private double  PropGain=0;
        private double IntGain=0;
        private UInt32 FreqLen=0;
        private double [] FreqHz;
        private double [] OL_Mag;
        private double [] OL_Ph;
        private double [] CL_Mag;
        private double [] CL_Ph;
        private UInt32 RespLen=0;
        private double [] RespTime;
        private double [] Resp;
        private double R = 0.2;
        private double L = 0.002;
        private double Ts = 50e-6F;
        private double Ovs = 1.15F;


        private const UInt32  MaxFreqLen = 1000;
        private const UInt32  MaxTimeLen = 60;


        public void initPlots()
        {
            bodePlot = new CbodePlot(plotBodeMag, plotBodePh);
            this.panelMag.Controls.Add(this.plotBodeMag);
            //this.Controls.Add(this.plotBodeMag);
            this.plotBodeMag.Model = bodePlot.plotBodeMag();
            this.panelPh.Controls.Add(this.plotBodePh);
            //this.Controls.Add(this.plotBodePh);
            this.plotBodePh.Model = bodePlot.plotBodePh();
            nicholsPlot = new CNicholsPlot(this.plotNichols);
            //this.Controls.Add(this.plotNichols);
            this.panelNic.Controls.Add(this.plotNichols);
            this.plotNichols.Model = nicholsPlot.plotNichols();

            StepRespPlot = new CStepRespPlot(this.plotStepResp);
            //this.Controls.Add(this.plotStepResp);
            this.panelStep.Controls.Add(this.plotStepResp);
            this.plotStepResp.Model = StepRespPlot.plotStepResp();
            
            
        }

        public FormDesPI()
        {
         FreqHz = new double[(int)MaxFreqLen];
         OL_Mag = new double[(int)MaxFreqLen];
         OL_Ph = new double[(int)MaxFreqLen];
         CL_Mag = new double[(int)MaxFreqLen];
         CL_Ph = new double[(int)MaxFreqLen];
        RespTime=new double[(int)MaxTimeLen];
        Resp = new double[(int)MaxTimeLen];

            InitializeComponent();
            this.textBoxR.Text = Convert.ToString(R);
            this.textBoxL.Text = Convert.ToString(L);
            this.textBoxOvs.Text = Convert.ToString(100*(Ovs-1));
            initPlots();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            L=Convert.ToDouble(this.textBoxL.Text);
            R = Convert.ToDouble(this.textBoxR.Text);
            Ovs = 1+ 0.01*Convert.ToDouble(this.textBoxOvs.Text);

            //NicPlotDll.wizDll.InitDLL();
            NicPlotDll.wizDll.calccurrentctrl(out PropGain,out IntGain,out FreqLen, FreqHz,
            							   OL_Mag, OL_Ph, CL_Mag,CL_Ph,
            							   out RespLen,RespTime,Resp, MaxFreqLen, MaxTimeLen, R, L, Ts, Ovs);
           
            this.textBoxKi.Text = Convert.ToString(IntGain);
            this.textBoxKp.Text = Convert.ToString(PropGain);

            bodePlot.drawBode(FreqHz, CL_Mag, CL_Ph, FreqLen);
            nicholsPlot.drawNichols(OL_Mag, OL_Ph, FreqLen);
            StepRespPlot.drawStepResponse(RespTime, Resp, RespLen);

            //NicPlotDll.wizDll.UnInitDLL();
         }

        private void trackBarOvs_ValueChanged(object sender, EventArgs e)
        {
            Ovs = 1+ 0.01*Convert.ToDouble(this.textBoxOvs.Text);
            double Ovs2 = 1 + trackBarOvs.Value * 0.01 * (Ovs-1);
            NicPlotDll.wizDll.calccurrentctrl(out PropGain, out IntGain, out FreqLen, FreqHz,
                                           OL_Mag, OL_Ph, CL_Mag, CL_Ph,
                                           out RespLen, RespTime, Resp, MaxFreqLen, MaxTimeLen, R, L, Ts, Ovs2);

            this.textBoxKi.Text = Convert.ToString(IntGain);
            this.textBoxKp.Text = Convert.ToString(PropGain);

            bodePlot.drawBode(FreqHz, CL_Mag, CL_Ph, FreqLen);
            nicholsPlot.drawNichols(OL_Mag, OL_Ph, FreqLen);
            StepRespPlot.drawStepResponse(RespTime, Resp, RespLen);

        }
    }

    /// plots
    public class CbodePlot
    {
        private OxyPlot.Series.LineSeries seriesBodeMag;
        private OxyPlot.Series.LineSeries seriesBodePh;

        private OxyPlot.WindowsForms.PlotView m_plotBodeMag;
        private OxyPlot.PlotModel m_PlotModelBodeMag;

        private OxyPlot.WindowsForms.PlotView m_plotBodePh;
        private OxyPlot.PlotModel m_PlotModelBodePh;

        public PlotModel plotBodeMag() { return m_PlotModelBodeMag; }
        public PlotModel plotBodePh() { return m_PlotModelBodePh; }

        public CbodePlot(PlotView _plotBodeMag, PlotView _plotBodePh)
        {
            m_plotBodeMag = _plotBodeMag;
            m_plotBodePh = _plotBodePh;
            // Mag
            m_plotBodeMag.Dock = System.Windows.Forms.DockStyle.Bottom;
            m_plotBodeMag.Location = new System.Drawing.Point(0, 0);
            m_plotBodeMag.Name = "BodeMag";
            m_plotBodeMag.PanCursor = System.Windows.Forms.Cursors.Hand;
            m_plotBodeMag.Size = new System.Drawing.Size(100, 120);
            m_plotBodeMag.TabIndex = 0;
            m_plotBodeMag.Text = "BodeMag";
            m_plotBodeMag.ZoomHorizontalCursor = System.Windows.Forms.Cursors.SizeWE;
            m_plotBodeMag.ZoomRectangleCursor = System.Windows.Forms.Cursors.SizeNWSE;
            m_plotBodeMag.ZoomVerticalCursor = System.Windows.Forms.Cursors.SizeNS;

            m_PlotModelBodeMag = new OxyPlot.PlotModel();
            //m_PlotModelBodeMag.Title = "Magnitude";

            m_PlotModelBodeMag.Axes.Add(new OxyPlot.Axes.LogarithmicAxis { Position = AxisPosition.Bottom, Maximum = 100, Minimum = 0 });//X
            m_PlotModelBodeMag.Axes.Add(new LinearAxis { Position = AxisPosition.Left, Maximum = 40, Minimum = 0 });//Y

            seriesBodeMag = new LineSeries();
            seriesBodeMag.Title = "dB";// legend
            seriesBodeMag.MarkerType = MarkerType.None;
            seriesBodeMag.Points.Add(new DataPoint(0, 0));
            seriesBodeMag.Points.Add(new DataPoint(1, 10));
            seriesBodeMag.Background = OxyColors.White;

            m_PlotModelBodeMag.Series.Add(seriesBodeMag);
            // Phase
            m_plotBodePh.Dock = System.Windows.Forms.DockStyle.Bottom;
            m_plotBodePh.Location = new System.Drawing.Point(0, 0);
            m_plotBodePh.Name = "BodePh";
            m_plotBodePh.PanCursor = System.Windows.Forms.Cursors.Hand;
            m_plotBodePh.Size = new System.Drawing.Size(100, 120);
            m_plotBodePh.TabIndex = 0;
            m_plotBodePh.Text = "BodePh";
            m_plotBodePh.ZoomHorizontalCursor = System.Windows.Forms.Cursors.SizeWE;
            m_plotBodePh.ZoomRectangleCursor = System.Windows.Forms.Cursors.SizeNWSE;
            m_plotBodePh.ZoomVerticalCursor = System.Windows.Forms.Cursors.SizeNS;


            m_PlotModelBodePh = new OxyPlot.PlotModel();
            //m_PlotModelBodePh.Title = "Phase";

            m_PlotModelBodePh.Axes.Add(new OxyPlot.Axes.LogarithmicAxis { Position = AxisPosition.Bottom, Maximum = 100, Minimum = 0 });//X
            m_PlotModelBodePh.Axes.Add(new LinearAxis { Position = AxisPosition.Left, Maximum = 40, Minimum = 0 });//Y

            seriesBodePh = new LineSeries();
            seriesBodePh.Title = "Deg";// legend
            seriesBodePh.MarkerType = MarkerType.None;
            //seriesBodePh.Points.Add(new DataPoint(0, -0.5));
            //seriesBodePh.Points.Add(new DataPoint(1, -10));
            seriesBodePh.Background = OxyColors.White;

            m_PlotModelBodePh.Series.Add(seriesBodePh);
        }
        public void drawBode(double[] FreqHz, double[] CL_Mag, double[] CL_Ph, UInt32 FreqLen)
        {
            //Mag
            seriesBodeMag.Points.Clear();
            for (int k = 0; k < FreqLen; k++)
            {
                seriesBodeMag.Points.Add(new DataPoint(FreqHz[k], CL_Mag[k]));
            }
            m_PlotModelBodeMag.Axes[0].Minimum = 0; m_PlotModelBodeMag.Axes[0].Maximum = FreqHz[FreqLen - 1];
            m_PlotModelBodeMag.Axes[1].Minimum = -20; m_PlotModelBodeMag.Axes[1].Maximum = 10;

            m_PlotModelBodeMag.Axes[0].MajorGridlineStyle = LineStyle.Dash;
            m_PlotModelBodeMag.Axes[0].MinorGridlineStyle = LineStyle.Dash;
            m_PlotModelBodeMag.Axes[1].MajorGridlineStyle = LineStyle.Dash;
            m_PlotModelBodeMag.Axes[1].MinorGridlineStyle = LineStyle.Dash;

            m_PlotModelBodeMag.Series.Clear();
            m_PlotModelBodeMag.Series.Add(seriesBodeMag);
            m_PlotModelBodeMag.InvalidatePlot(true);

            //Phase
            seriesBodePh.Points.Clear();
            for (int k = 0; k < FreqLen; k++)
            {
                seriesBodePh.Points.Add(new DataPoint(FreqHz[k], CL_Ph[k]));
            }
            m_PlotModelBodePh.Axes[0].Minimum = 0; m_PlotModelBodePh.Axes[0].Maximum = FreqHz[FreqLen - 1];
            m_PlotModelBodePh.Axes[1].Minimum = -360; m_PlotModelBodePh.Axes[1].Maximum = 360;
            m_PlotModelBodePh.Axes[0].MajorGridlineStyle = LineStyle.Dash;
            m_PlotModelBodePh.Axes[0].MinorGridlineStyle = LineStyle.Dash;
            m_PlotModelBodePh.Axes[1].MajorGridlineStyle = LineStyle.Dash;
            m_PlotModelBodePh.Axes[1].MinorGridlineStyle = LineStyle.Dash;
            m_PlotModelBodePh.Series.Clear();
            m_PlotModelBodePh.Series.Add(seriesBodePh);
            m_PlotModelBodePh.InvalidatePlot(true);
        }
    }
    public class CNicholsPlot
    {
        private OxyPlot.Series.LineSeries seriesBodeMag;
        private OxyPlot.WindowsForms.PlotView m_plotBodeMag;
        private OxyPlot.PlotModel m_PlotModelBodeMag;

        public PlotModel plotNichols() { return m_PlotModelBodeMag; }

        public CNicholsPlot(PlotView _plotBodeMag)
        {
            m_plotBodeMag = _plotBodeMag;
            // nic
            m_plotBodeMag.Dock = System.Windows.Forms.DockStyle.Bottom;
            m_plotBodeMag.Location = new System.Drawing.Point(0, 0);
            m_plotBodeMag.Name = "NicholsPlot";
            m_plotBodeMag.PanCursor = System.Windows.Forms.Cursors.Hand;
            m_plotBodeMag.Size = new System.Drawing.Size(200, 220);
            m_plotBodeMag.TabIndex = 0;
            m_plotBodeMag.Text = "NicholsPlot";
            m_plotBodeMag.ZoomHorizontalCursor = System.Windows.Forms.Cursors.SizeWE;
            m_plotBodeMag.ZoomRectangleCursor = System.Windows.Forms.Cursors.SizeNWSE;
            m_plotBodeMag.ZoomVerticalCursor = System.Windows.Forms.Cursors.SizeNS;

            m_PlotModelBodeMag = new OxyPlot.PlotModel();
            //m_PlotModelBodeMag.Title = "Nichols";

            m_PlotModelBodeMag.Axes.Add(new OxyPlot.Axes.LinearAxis { Position = AxisPosition.Bottom, Maximum = 360, Minimum = -360 });//X
            m_PlotModelBodeMag.Axes.Add(new LinearAxis { Position = AxisPosition.Left, Maximum = 10, Minimum = -30 });//Y

            seriesBodeMag = new LineSeries();
            seriesBodeMag.Title = "(Deg,dB)";// legend
            seriesBodeMag.MarkerType = MarkerType.None;
            //seriesBodeMag.Points.Add(new DataPoint(0, 0));
            //seriesBodeMag.Points.Add(new DataPoint(1, 10));
            seriesBodeMag.Background = OxyColors.White;

            m_PlotModelBodeMag.Series.Add(seriesBodeMag);
         }
        public void drawNichols(double[] OL_Mag, double[] OL_Ph, UInt32 FreqLen)
        {
            //nic
            seriesBodeMag.Points.Clear();
            for (int k = 0; k < FreqLen; k++)
            {
                seriesBodeMag.Points.Add(new DataPoint(OL_Ph[k], OL_Mag[k]));
            }
            m_PlotModelBodeMag.Axes[0].Minimum = -360; m_PlotModelBodeMag.Axes[0].Maximum = 0;
            m_PlotModelBodeMag.Axes[1].Minimum = -30; m_PlotModelBodeMag.Axes[1].Maximum = 10;

            m_PlotModelBodeMag.Axes[0].MajorGridlineStyle = LineStyle.Dash;
            m_PlotModelBodeMag.Axes[0].MinorGridlineStyle = LineStyle.Dash;
            m_PlotModelBodeMag.Axes[1].MajorGridlineStyle = LineStyle.Dash;
            m_PlotModelBodeMag.Axes[1].MinorGridlineStyle = LineStyle.Dash;

            m_PlotModelBodeMag.Series.Clear();
            m_PlotModelBodeMag.Series.Add(seriesBodeMag);
            m_PlotModelBodeMag.InvalidatePlot(true);
        }
    }
    public class CStepRespPlot
    {
        private OxyPlot.Series.LineSeries seriesBodeMag;
        private OxyPlot.WindowsForms.PlotView m_plotBodeMag;
        private OxyPlot.PlotModel m_PlotModelBodeMag;

        public PlotModel plotStepResp() { return m_PlotModelBodeMag; }

        public CStepRespPlot(PlotView _plotBodeMag)
        {
            m_plotBodeMag = _plotBodeMag;
            // Mag
            m_plotBodeMag.Dock = System.Windows.Forms.DockStyle.Bottom;
            m_plotBodeMag.Location = new System.Drawing.Point(0, 0);
            m_plotBodeMag.Name = "StepRespPlot";
            m_plotBodeMag.PanCursor = System.Windows.Forms.Cursors.Hand;
            m_plotBodeMag.Size = new System.Drawing.Size(200, 120);
            m_plotBodeMag.TabIndex = 0;
            m_plotBodeMag.Text = "StepRespPlot";
            m_plotBodeMag.ZoomHorizontalCursor = System.Windows.Forms.Cursors.SizeWE;
            m_plotBodeMag.ZoomRectangleCursor = System.Windows.Forms.Cursors.SizeNWSE;
            m_plotBodeMag.ZoomVerticalCursor = System.Windows.Forms.Cursors.SizeNS;

            m_PlotModelBodeMag = new OxyPlot.PlotModel();
            m_PlotModelBodeMag.Title = "Step Response";

            m_PlotModelBodeMag.Axes.Add(new LinearAxis { Position = AxisPosition.Bottom, Maximum = 0, Minimum = 1e-3 });//X
            m_PlotModelBodeMag.Axes.Add(new LinearAxis { Position = AxisPosition.Left, Maximum = 5, Minimum = -5 });//Y

            seriesBodeMag = new LineSeries();
            seriesBodeMag.Title = "(output)";// legend
            seriesBodeMag.MarkerType = MarkerType.None;
            seriesBodeMag.Points.Add(new DataPoint(0, 0));
            seriesBodeMag.Points.Add(new DataPoint(1, 10));
            seriesBodeMag.Background = OxyColors.White;

            m_PlotModelBodeMag.Series.Add(seriesBodeMag);
        }
        public void drawStepResponse(double[] RespTime, double[] Resp, UInt32 RespLen)
        { 
            //Mag
            seriesBodeMag.Points.Clear();
            for (int k = 0; k < RespLen; k++)
            {
                seriesBodeMag.Points.Add(new DataPoint(RespTime[k], Resp[k]));
            }
            m_PlotModelBodeMag.Axes[0].Minimum = 0; m_PlotModelBodeMag.Axes[0].Maximum = 3e-3;
            m_PlotModelBodeMag.Axes[1].Minimum = -0.1; m_PlotModelBodeMag.Axes[1].Maximum = 3;

            m_PlotModelBodeMag.Axes[0].MajorGridlineStyle = LineStyle.Dash;
            m_PlotModelBodeMag.Axes[0].MinorGridlineStyle = LineStyle.Dash;
            m_PlotModelBodeMag.Axes[1].MajorGridlineStyle = LineStyle.Dash;
            m_PlotModelBodeMag.Axes[1].MinorGridlineStyle = LineStyle.Dash;

            m_PlotModelBodeMag.Series.Clear();
            m_PlotModelBodeMag.Series.Add(seriesBodeMag);
            m_PlotModelBodeMag.InvalidatePlot(true);
        }
    }
}