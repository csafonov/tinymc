call TmcSetEnv.bat

@rem %TMCLSP%  -S  -d -q  -g2  -w TestO  -r .\Stubs\TestO.m -l .\OutC3\testO3.err.log -@ woo3_rsp.txt  -o .\OutC3\ >outC3.txt

@rem C output:
@rem %TMCLSP% -c -C -S -d -q -g2   -w TestO  -r .\Stubs\TestO.m -l .\OutC3\testO3.err.log -@ woo3_rsp.txt  -o .\OutC3\ >outC3.txt
@rem move .\OutC3\*.inc	.\OutS3\
@rem move .\OutC3\*.asm	.\OutS3\


@rem ASM only:
%TMCLSP%  -c -C -S -d -q -g2   -w TestO  -r .\Stubs\TestO.m -l .\OutS3\testO3.err.log -@ woo3_rsp.txt  -o .\OutS3\ >outS3.txt

pause