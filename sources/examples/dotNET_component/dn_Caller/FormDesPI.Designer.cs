namespace dn_Caller
{
    using System;

    using OxyPlot;
    using OxyPlot.Axes;
    using OxyPlot.Series;

    partial class FormDesPI
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.plotBodeMag = new OxyPlot.WindowsForms.PlotView();
            this.plotBodePh = new OxyPlot.WindowsForms.PlotView();
            this.plotNichols = new OxyPlot.WindowsForms.PlotView();
            this.plotStepResp = new OxyPlot.WindowsForms.PlotView();
            this.buttonRun = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.trackBarOvs = new System.Windows.Forms.TrackBar();
            this.labelKi = new System.Windows.Forms.Label();
            this.textBoxKi = new System.Windows.Forms.TextBox();
            this.labelKp = new System.Windows.Forms.Label();
            this.textBoxKp = new System.Windows.Forms.TextBox();
            this.labelOvs = new System.Windows.Forms.Label();
            this.textBoxOvs = new System.Windows.Forms.TextBox();
            this.labelL = new System.Windows.Forms.Label();
            this.textBoxL = new System.Windows.Forms.TextBox();
            this.labelR = new System.Windows.Forms.Label();
            this.textBoxR = new System.Windows.Forms.TextBox();
            this.panelMag = new System.Windows.Forms.Panel();
            this.panelPh = new System.Windows.Forms.Panel();
            this.panelStep = new System.Windows.Forms.Panel();
            this.panelNic = new System.Windows.Forms.Panel();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarOvs)).BeginInit();
            this.SuspendLayout();
            // 
            // plotBodeMag
            // 
            this.plotBodeMag.Location = new System.Drawing.Point(0, 0);
            this.plotBodeMag.Name = "plotBodeMag";
            this.plotBodeMag.PanCursor = System.Windows.Forms.Cursors.Hand;
            this.plotBodeMag.Size = new System.Drawing.Size(0, 0);
            this.plotBodeMag.TabIndex = 0;
            this.plotBodeMag.ZoomHorizontalCursor = System.Windows.Forms.Cursors.SizeWE;
            this.plotBodeMag.ZoomRectangleCursor = System.Windows.Forms.Cursors.SizeNWSE;
            this.plotBodeMag.ZoomVerticalCursor = System.Windows.Forms.Cursors.SizeNS;
            // 
            // plotBodePh
            // 
            this.plotBodePh.Location = new System.Drawing.Point(0, 0);
            this.plotBodePh.Name = "plotBodePh";
            this.plotBodePh.PanCursor = System.Windows.Forms.Cursors.Hand;
            this.plotBodePh.Size = new System.Drawing.Size(0, 0);
            this.plotBodePh.TabIndex = 0;
            this.plotBodePh.ZoomHorizontalCursor = System.Windows.Forms.Cursors.SizeWE;
            this.plotBodePh.ZoomRectangleCursor = System.Windows.Forms.Cursors.SizeNWSE;
            this.plotBodePh.ZoomVerticalCursor = System.Windows.Forms.Cursors.SizeNS;
            // 
            // plotNichols
            // 
            this.plotNichols.Location = new System.Drawing.Point(0, 0);
            this.plotNichols.Name = "plotNichols";
            this.plotNichols.PanCursor = System.Windows.Forms.Cursors.Hand;
            this.plotNichols.Size = new System.Drawing.Size(0, 0);
            this.plotNichols.TabIndex = 0;
            this.plotNichols.ZoomHorizontalCursor = System.Windows.Forms.Cursors.SizeWE;
            this.plotNichols.ZoomRectangleCursor = System.Windows.Forms.Cursors.SizeNWSE;
            this.plotNichols.ZoomVerticalCursor = System.Windows.Forms.Cursors.SizeNS;
            // 
            // plotStepResp
            // 
            this.plotStepResp.Location = new System.Drawing.Point(0, 0);
            this.plotStepResp.Name = "plotStepResp";
            this.plotStepResp.PanCursor = System.Windows.Forms.Cursors.Hand;
            this.plotStepResp.Size = new System.Drawing.Size(0, 0);
            this.plotStepResp.TabIndex = 0;
            this.plotStepResp.ZoomHorizontalCursor = System.Windows.Forms.Cursors.SizeWE;
            this.plotStepResp.ZoomRectangleCursor = System.Windows.Forms.Cursors.SizeNWSE;
            this.plotStepResp.ZoomVerticalCursor = System.Windows.Forms.Cursors.SizeNS;
            // 
            // buttonRun
            // 
            this.buttonRun.Location = new System.Drawing.Point(302, 79);
            this.buttonRun.Name = "buttonRun";
            this.buttonRun.Size = new System.Drawing.Size(120, 36);
            this.buttonRun.TabIndex = 0;
            this.buttonRun.Text = "Calculate";
            this.buttonRun.UseVisualStyleBackColor = true;
            this.buttonRun.Click += new System.EventHandler(this.button1_Click);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.trackBarOvs);
            this.panel1.Controls.Add(this.labelKi);
            this.panel1.Controls.Add(this.textBoxKi);
            this.panel1.Controls.Add(this.labelKp);
            this.panel1.Controls.Add(this.textBoxKp);
            this.panel1.Controls.Add(this.labelOvs);
            this.panel1.Controls.Add(this.textBoxOvs);
            this.panel1.Controls.Add(this.labelL);
            this.panel1.Controls.Add(this.textBoxL);
            this.panel1.Controls.Add(this.labelR);
            this.panel1.Controls.Add(this.textBoxR);
            this.panel1.Controls.Add(this.buttonRun);
            this.panel1.Location = new System.Drawing.Point(519, 454);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(440, 160);
            this.panel1.TabIndex = 1;
            // 
            // trackBarOvs
            // 
            this.trackBarOvs.Location = new System.Drawing.Point(79, 116);
            this.trackBarOvs.Maximum = 100;
            this.trackBarOvs.Name = "trackBarOvs";
            this.trackBarOvs.Size = new System.Drawing.Size(325, 69);
            this.trackBarOvs.TabIndex = 11;
            this.trackBarOvs.ValueChanged += new System.EventHandler(this.trackBarOvs_ValueChanged);
            // 
            // labelKi
            // 
            this.labelKi.AutoSize = true;
            this.labelKi.Location = new System.Drawing.Point(234, 50);
            this.labelKi.Name = "labelKi";
            this.labelKi.Size = new System.Drawing.Size(84, 20);
            this.labelKi.TabIndex = 10;
            this.labelKi.Text = "Integ Gain";
            // 
            // textBoxKi
            // 
            this.textBoxKi.Location = new System.Drawing.Point(322, 46);
            this.textBoxKi.Name = "textBoxKi";
            this.textBoxKi.Size = new System.Drawing.Size(100, 26);
            this.textBoxKi.TabIndex = 9;
            // 
            // labelKp
            // 
            this.labelKp.AutoSize = true;
            this.labelKp.Location = new System.Drawing.Point(232, 16);
            this.labelKp.Name = "labelKp";
            this.labelKp.Size = new System.Drawing.Size(80, 20);
            this.labelKp.TabIndex = 8;
            this.labelKp.Text = "Prop Gain";
            // 
            // textBoxKp
            // 
            this.textBoxKp.Location = new System.Drawing.Point(320, 13);
            this.textBoxKp.Name = "textBoxKp";
            this.textBoxKp.Size = new System.Drawing.Size(100, 26);
            this.textBoxKp.TabIndex = 7;
            // 
            // labelOvs
            // 
            this.labelOvs.AutoSize = true;
            this.labelOvs.Location = new System.Drawing.Point(12, 84);
            this.labelOvs.Name = "labelOvs";
            this.labelOvs.Size = new System.Drawing.Size(108, 20);
            this.labelOvs.TabIndex = 6;
            this.labelOvs.Text = "Overshoot [%]";
            // 
            // textBoxOvs
            // 
            this.textBoxOvs.Location = new System.Drawing.Point(124, 84);
            this.textBoxOvs.Name = "textBoxOvs";
            this.textBoxOvs.Size = new System.Drawing.Size(100, 26);
            this.textBoxOvs.TabIndex = 5;
            // 
            // labelL
            // 
            this.labelL.AutoSize = true;
            this.labelL.Location = new System.Drawing.Point(14, 46);
            this.labelL.Name = "labelL";
            this.labelL.Size = new System.Drawing.Size(51, 20);
            this.labelL.TabIndex = 4;
            this.labelL.Text = "L [Hn]";
            // 
            // textBoxL
            // 
            this.textBoxL.Location = new System.Drawing.Point(126, 46);
            this.textBoxL.Name = "textBoxL";
            this.textBoxL.Size = new System.Drawing.Size(100, 26);
            this.textBoxL.TabIndex = 3;
            // 
            // labelR
            // 
            this.labelR.AutoSize = true;
            this.labelR.Location = new System.Drawing.Point(12, 12);
            this.labelR.Name = "labelR";
            this.labelR.Size = new System.Drawing.Size(67, 20);
            this.labelR.TabIndex = 2;
            this.labelR.Text = "R [Ohm]";
            // 
            // textBoxR
            // 
            this.textBoxR.Location = new System.Drawing.Point(124, 12);
            this.textBoxR.Name = "textBoxR";
            this.textBoxR.Size = new System.Drawing.Size(100, 26);
            this.textBoxR.TabIndex = 1;
            // 
            // panelMag
            // 
            this.panelMag.Location = new System.Drawing.Point(22, 62);
            this.panelMag.Name = "panelMag";
            this.panelMag.Size = new System.Drawing.Size(459, 206);
            this.panelMag.TabIndex = 2;
            // 
            // panelPh
            // 
            this.panelPh.Location = new System.Drawing.Point(22, 286);
            this.panelPh.Name = "panelPh";
            this.panelPh.Size = new System.Drawing.Size(459, 183);
            this.panelPh.TabIndex = 3;
            // 
            // panelStep
            // 
            this.panelStep.Location = new System.Drawing.Point(22, 487);
            this.panelStep.Name = "panelStep";
            this.panelStep.Size = new System.Drawing.Size(459, 129);
            this.panelStep.TabIndex = 4;
            // 
            // panelNic
            // 
            this.panelNic.Location = new System.Drawing.Point(519, 62);
            this.panelNic.Name = "panelNic";
            this.panelNic.Size = new System.Drawing.Size(440, 386);
            this.panelNic.TabIndex = 5;
            // 
            // FormDesPI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(971, 626);
            this.Controls.Add(this.panelNic);
            this.Controls.Add(this.panelStep);
            this.Controls.Add(this.panelPh);
            this.Controls.Add(this.panelMag);
            this.Controls.Add(this.panel1);
            this.Name = "FormDesPI";
            this.Text = "Bode Plot";
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarOvs)).EndInit();
            this.ResumeLayout(false);

        }
        private OxyPlot.WindowsForms.PlotView plotBodeMag;
        private OxyPlot.WindowsForms.PlotView plotBodePh;
        private OxyPlot.WindowsForms.PlotView plotNichols;
        private OxyPlot.WindowsForms.PlotView plotStepResp;
        #endregion

  
        private System.Windows.Forms.Button buttonRun;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label labelR;
        private System.Windows.Forms.TextBox textBoxR;
        private System.Windows.Forms.Label labelOvs;
        private System.Windows.Forms.TextBox textBoxOvs;
        private System.Windows.Forms.Label labelL;
        private System.Windows.Forms.TextBox textBoxL;
        private System.Windows.Forms.Label labelKi;
        private System.Windows.Forms.TextBox textBoxKi;
        private System.Windows.Forms.Label labelKp;
        private System.Windows.Forms.TextBox textBoxKp;
        private System.Windows.Forms.Panel panelMag;
        private System.Windows.Forms.Panel panelPh;
        private System.Windows.Forms.Panel panelStep;
        private System.Windows.Forms.Panel panelNic;
        private System.Windows.Forms.TrackBar trackBarOvs;
    }
}

