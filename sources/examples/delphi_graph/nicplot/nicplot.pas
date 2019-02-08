unit nicplot;

interface

uses
  System.SysUtils, System.Types, System.UITypes, System.Classes, System.Variants,
  FMX.Types, FMX.Controls, FMX.Forms, FMX.Graphics, FMX.Dialogs,
  FMX.ExtCtrls,
  System.Math.Vectors, FMX.Controls.Presentation, FMX.StdCtrls, FMX.Edit,
  FMX.Layouts, FMX.ListBox,
  System.Math,
  TmcLib32;

type
  TMainForm = class(TForm)
    PlotGrid1: TPlotGrid;
    PanelRL: TPanel;
    ButtonCalc: TButton;
    gboxPlant: TGroupBox;
    gboxCtrl: TGroupBox;
    lbX: TLabel;
    EditW1: TEdit;
    LabelW1: TLabel;
    EditW2: TEdit;
    LabelW2: TLabel;
    ListBox1: TListBox;
    lbCtrlType: TLabel;
    LabelD1: TLabel;
    LabelD2: TLabel;
    EditD1: TEdit;
    EditD2: TEdit;
    CheckBoxInt: TCheckBox;
    EditNumInt: TEdit;
    procedure PlotGridPaint(Sender: TObject; Canvas: TCanvas;
      const ARect: TRectF);
    procedure PlotGridResize(Sender: TObject);
    procedure ButtonCalcEnter(Sender: TObject);
    procedure ButtonCalcClick(Sender: TObject);
    procedure gboxPlantClick(Sender: TObject);
  private
    { Private declarations }
    procedure CalculatePlant(w1,w2,d1,d2:double;NumInt:Integer);
    procedure SetParams;
  public
    { Public declarations }
        (* local functions *)
    procedure myFiltFreqResp(w1,d1,w2,d2:Double;NumFreqs:Integer;
    var F,Mag,Ph:array of Double;
    Fmin,Fmax: Double;NumInt:Integer);

  end;


var
  MainForm: TMainForm;
  FPoints: TPolygon;
  xPixels, yPixels: Double;
  Origin: TPointF;

implementation

{$R *.fmx}
{ TMainForm }
    (* External procedures from TMC Dll: *)
    procedure FiltFreqResp(w1,d1,w2,d2:Double;NumFreqs:Integer;F,Mag,Ph:PDouble;
    Fmin,Fmax: Double); stdcall; external 'plotdll.dll';

    // A wrapper function  tmcTestO_ex with stdcall is used here since
    // I could not export  tmcTestO as cdecl (builder cryed is as non-public symbol)
    // If the DLL was build by GCC or MSVC tmcTestO may be used instead.
    procedure  tmcTestO( nargout,nargin:Integer;F,Mag,Ph,f1,d1,f2,d2,NumFreqs,
    Fmin,Fmax,NumInt:PTmcMatrix); stdcall; external 'plotdll.dll' name 'tmcTestO_ex';

    //void tmcTestO(int nargout, int nargin,tmsMatrix *F,tmsMatrix *Mag,tmsMatrix *Ph
    //,tmsMatrix *f1,tmsMatrix *d1,tmsMatrix *f2,tmsMatrix *d2,
    //tmsMatrix *NumFreqs,tmsMatrix *Fmin,tmsMatrix *Fmax);

// Example of direct call of generated code.
procedure TMainForm.myFiltFreqResp(w1,d1,w2,d2:Double;NumFreqs:Integer;
var  F,Mag,Ph:  array of Double;
    Fmin,Fmax: Double; NumInt:Integer);
    var
    nargout,nargin:Integer;
    mF,mMag,mPh,mf1,md1,mf2,md2,mNumFreqs,mFmin,mFmax,mNumInt:PTmcMatrix;
    actNumFreqs,k: Integer;
     begin
         nargout:=3;nargin:=8;
         mF := __tmcNewMatrix;
         mMag:= __tmcNewMatrix();
        mPh:= __tmcNewMatrix();
        mf1:= __tmcNewMatrix();
        md1:= __tmcNewMatrix();
        mf2:= __tmcNewMatrix();
        md2:= __tmcNewMatrix();
        mNumFreqs:= __tmcNewMatrix();
        mFmin:= __tmcNewMatrix();
        mFmax:= __tmcNewMatrix();
        mNumInt:= __tmcNewMatrix();
        tmcScalar(mf1,w1);
        tmcScalar(md1,d1);
        tmcScalar(mf2,w2);
        tmcScalar(md2,d2);
        tmcScalar(mNumFreqs,NumFreqs);
        tmcScalar(mFmin,Fmin);
        tmcScalar(mFmax,Fmax);
        tmcScalar(mNumInt,NumInt);
         tmcTestO( nargout,nargin,mF,mMag,mPh,    // outputs
         mf1,md1,mf2,md2,mNumFreqs, mFmin,mFmax,mNumInt   // inputs
         );

         	// copy outputs
           actNumFreqs := tmcNumElem ( mF );
          if  NumFreqs < actNumFreqs then
                       actNumFreqs:= NumFreqs;

          for  k:=0 to actNumFreqs-1 do
          begin
          // Unsafe:
          //  F[k]   := mF^.complx.rData[k];
          //  Mag[k] := mMag^.complx.rData[k];
          //  Ph[k]  := mPh^.complx.rData[k];
            F[k] :=  tmcMatrixValRe(mF,0,k);
            Mag[k] := tmcMatrixValRe(mMag,0,k);
            Ph[k]  := tmcMatrixValRe(mPh,0,k);
          end;

            tmcFreeLocalVar(mNumInt);
            tmcFreeLocalVar(mFmax);
            tmcFreeLocalVar(mFmin);
            tmcFreeLocalVar(mNumFreqs);
            tmcFreeLocalVar(md2);
            tmcFreeLocalVar(mf2);
            tmcFreeLocalVar(md1);
            tmcFreeLocalVar(mf1);
            tmcFreeLocalVar(mPh);
            tmcFreeLocalVar(mMag);
            tmcFreeLocalVar(mF);
    end;

procedure TMainForm.ButtonCalcClick(Sender: TObject);
begin
    PlotGrid1.Repaint;
end;

procedure TMainForm.ButtonCalcEnter(Sender: TObject);
begin
   PlotGrid1.Repaint;
end;

procedure TMainForm.CalculatePlant(w1,w2,d1,d2:double;NumInt:Integer);
const
  maxW        = 20000.0;//Hz
  maxNumFreqs = 500;
var
  I : Integer;
  w,Ph,Mag : Double;


  arrF,arrMag,arrPh: array[0..maxNumFreqs-1] of Double;
begin

  //FiltFreqResp(10000,d1,20000,d2,maxNumFreqs,@arrF[0],@arrMag[0],@arrPh[0],1.0,200000.0);
   myFiltFreqResp(w1,d1,w2,d2,maxNumFreqs,arrF,arrMag,arrPh,1.0,200000.0,NumInt);


  SetLength(FPoints, maxNumFreqs);                       // Alloc space for number of points to be calculated
  SetParams;
  for I := 0 to High(FPoints) do
  begin
    //w   := 2.0 * Pi * I / maxNumFreqs * maxW ;
    //Mag := 20 * System.Math.Log10 ( 1/sqrt(R*R + w*w*L*L));
    //Ph  := System.Math.ArcTan2( -w*L ,R   ) / Pi *180.0;
    w:=arrF[I];Ph:=arrPh[I];Mag:=arrMag[I];
    FPoints[I].X := Origin.x + Ph    * xPixels / 360;   // Calculate X value with scaling
    //Bode: FPoints[I].X := Origin.x + w    * xPixels / arrF[maxNumFreqs-1];
    FPoints[I].Y := Origin.y - Mag   * yPixels / 180.0; // asis OY is toward bottom
    //Radian := Radian + Interval;                        // Set next point
  end;
end;

procedure TMainForm.gboxPlantClick(Sender: TObject);
 var w1,w2,d1,d2: double;
      k,NumInt:Integer;

begin
 PlotGrid1.Canvas.StrokeThickness := 1;                  // Set stroke thickness
  try
  w1:=   StrToFloat( EditW1.Text);
  w2:=   StrToFloat( EditW2.Text);
  d1:=   StrToFloat( EditD1.Text);
  d2:=   StrToFloat( EditD2.Text);
     if CheckBoxInt.IsChecked  then
           NumInt:=StrToInt(EditNumInt.Text)
     else
           NumInt:=0;

  CalculatePlant(w1,w2,d1,d2,NumInt);
  finally
    w1:=1;w2:=1;d1:=0.5;d2:=0.5;NumInt:=0;
  end;
                                            // Calculate and scale X and sin(X) values and save them in FPoints
  PlotGrid1.Canvas.Stroke.Color := TAlphaColorRec.Red;    // Set color for sin to red
  for k := 1 to High(FPoints) do
  begin
        PlotGrid1.Canvas.DrawLine(FPoints[k-1],FPoints[k],1);
  end;
end;

procedure TMainForm.SetParams;
begin
  xPixels := PlotGrid1.Width / 4;        // Contain graph width within a quarter of the grid width (actually half because of neg values)
  yPixels := PlotGrid1.Height / 4;       // Contain graph height within a quarter of the grid height (actually half because of neg values)
  Origin := PointF(PlotGrid1.Width / 2,  // Calculate the center point of the plot grid
  PlotGrid1.Height / 2);
  PlotGrid1.Frequency := 50;
  PlotGrid1.Marks := 10;
  end;


procedure TMainForm.PlotGridPaint(Sender: TObject; Canvas: TCanvas;
  const ARect: TRectF);
  var w1,w2,d1,d2: double;
      k,NumInt:Integer;
begin
  PlotGrid1.Canvas.StrokeThickness := 1;                  // Set stroke thickness
  try
  w1:=   StrToFloat( EditW1.Text);
  w2:=   StrToFloat( EditW2.Text);
  d1:=   StrToFloat( EditD1.Text);
  d2:=   StrToFloat( EditD2.Text);
     if CheckBoxInt.IsChecked  then
           NumInt:=StrToInt(EditNumInt.Text)
     else
           NumInt:=0;

  CalculatePlant(w1,w2,d1,d2,NumInt);
  finally
    w1:=1;w2:=1;d1:=0.5;d2:=0.5;NumInt:=0;
  end;
                                            // Calculate and scale X and sin(X) values and save them in FPoints
  PlotGrid1.Canvas.Stroke.Color := TAlphaColorRec.Red;    // Set color for sin to red
  for k := 1 to High(FPoints) do
  begin
        PlotGrid1.Canvas.DrawLine(FPoints[k-1],FPoints[k],1);
  end;
  //PlotGrid1.Canvas.DrawPolygon(FPoints, 1);               // Draw sin graph

 (* CalculateCos;                                          // Calculate and scale X and cos(X) values and save them in FPoints
  PlotGrid1.Canvas.Stroke.Color := TAlphaColorRec.Blue;   // Set color for cos to blue
  PlotGrid1.Canvas.DrawPolygon(FPoints, 1);               // Draw cos graph
  *)
  end;

procedure TMainForm.PlotGridResize(Sender: TObject);
begin
  PlotGrid1.Repaint;  // Repaint grid on resize
end;

end.

