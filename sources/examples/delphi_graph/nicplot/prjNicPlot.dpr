program prjNicPlot;

uses
  System.StartUpCopy,
  FMX.Forms,
  nicplot in 'nicplot.pas' {Form2},
  TmcLib32 in 'TmcLib32.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TMainForm, MainForm);
  Application.Run;
end.
