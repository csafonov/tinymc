package com.tmc.tunerdemo;

import android.graphics.Color;

public class PIDData {
	public static final int PIDH = 1;
	public int numFreqs;
	public int numPlants;
	public double [] Plants;
	public int nCrl;
	public int typeCrl;
	public int dimCrl;
	public double [] Crl;
	
	public PIDData(int _numFreqs)
	{
		numFreqs=_numFreqs;
	}
	public PIDData(int _numFreqs, int _numPlants,  int _nCrl, int  _typeCrl,
			double [] _Plants, double [] _Crl ) {
		
		

		
		numFreqs=_numFreqs; numPlants=_numPlants; 
		Plants = new double[ (1+_numPlants * 2) * _numFreqs]; // F,real(P),image(P)
		nCrl = _nCrl;
		typeCrl = _typeCrl;
		if (typeCrl == PIDH)
		{
			dimCrl = 4 ;// KD,KP,KI,w
			Crl    = new double [ _nCrl * dimCrl  ]; 
		}
		for (int kk=0 ; kk< (1+_numPlants * 2) * _numFreqs; kk++)
		{
			Plants[kk]=_Plants[kk];
		}
		for (int kk=0 ; kk< _nCrl * dimCrl; kk++)
		{
			Crl[kk]=_Crl[kk];
		}
	}

	private void copyPlant(double [] Fw,double [] re,double [] im,int indPlant) {
		for (int kk=0; kk< numFreqs; kk++) {
			re[kk]= Plants[ kk + numFreqs*(1 + indPlant*2)  ];
			im[kk]= Plants[ kk + numFreqs*(1 + indPlant*2 + 1)  ];		
			Fw[kk]= Plants[ kk    ];
		}
	}
	
	public void prepKarman(double[] drawbuffer, int buffer_len, int indCrl) {
		// generate drawbuffer from PIDData
		//HAZARD: temporary - only plant is drawn
		int offs = PlotNic.StartNicholsPlot(  drawbuffer);
		for (int kk=0; kk< numPlants; kk++)
		{
		final int [] colors  = { Color.RED,Color.GREEN,Color.BLUE,
				Color.CYAN,Color.BLACK,Color.MAGENTA};
		int color = colors[kk % 6];
		double [] Fw = new double[numFreqs];
		double [] re = new double[numFreqs];
		double [] im = new double[numFreqs];
		copyPlant(Fw,re,im,kk);
		
		// Kp + Kd*s + Ki/s
		double Kd=Crl[indCrl];
		double Kp=Crl[indCrl  + nCrl];
		double Ki=Crl[indCrl  + nCrl*2];
		double wPole = Crl[indCrl  + nCrl*3];
		double [] reS = new double[numFreqs];
		double [] imS = new double[numFreqs];
		
		double [] reInt = new double[numFreqs];
		double [] imInt = new double[numFreqs];
		
		CtrlHelper.j(numFreqs, reS, imS);
		CtrlHelper.mult(numFreqs, reS, imS, Fw);// s=Fw*j
		
		double [] rePole = new double[numFreqs];
		double [] imPole = new double[numFreqs];
		
		// Type=PIDH: Loop =( KP*P1 + KD*P1.*s .*  Lpole).*N  + KI .*P1./s   ;
		
		CtrlHelper.pole1(numFreqs, rePole, imPole, Fw, wPole);
		
		
		CtrlHelper.ones(numFreqs, reInt, imInt);
		CtrlHelper.div(numFreqs, reInt, imInt, reS, imS);// 1/s
		CtrlHelper.mult(numFreqs, reInt, imInt, Ki);// Ki/s
		
		CtrlHelper.mult(numFreqs, reS, imS, Kd);// Kd*s
		CtrlHelper.mult(numFreqs,  reS , imS , rePole , imPole  );// Kd*s*Lpole
		
		
		CtrlHelper.add(numFreqs, reS, imS, Kp );// Kp + Kd*s*Lpole
		CtrlHelper.add(numFreqs, reS, imS, reInt, imInt );// Kp + Kd*s*Lpole+Ki/s
		
		CtrlHelper.mult(numFreqs, re , im , reS, imS);// (Kp + Kd*s+Ki/s)*P1
		
		
		offs = PlotNic.AddNicholsPlot(drawbuffer, offs, color,numFreqs,re,im);
		}
		
		
	}
}
