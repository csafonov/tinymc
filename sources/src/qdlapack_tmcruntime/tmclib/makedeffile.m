%makedeffile
fp=fopen('dll.txt','rt'); % must be terminated by one empty string
fp2=fopen('def.txt','wt');
fp3=fopen('iat.inc','wt');
fp4=fopen('fncc.inc','wt');
fp5=fopen('bdef.txt','wt');

S=0;
OrdF=1;
while (S>=0)
    S=fgets(fp);
    if (S>=0)
    I=find((S==10) );
    fn=S(1:(I(1)-1));
    fprintf(fp2,'\t%s\t\t\t\t\t\t\t@%d\n',fn,OrdF);
    fprintf(fp5,'\t_%s\t\t\t\t\t\t\t@%d\n',fn,OrdF);
    
%        dd (0x80000000+1)                             ; Import function 1 by ordinal
    fprintf(fp3,'\t dd (0x80000000+%d) \t\t ; _%s \n',OrdF,fn);
%	%define		_tmcScalar	[iat+MY_LOAD_ADDRESS+3*4]

    fprintf(fp4,'\t%%define\t_%s\t[iat+MY_LOAD_ADDRESS+%d*4]\t; @%d\n',  fn,OrdF-1,OrdF);
    
    disp(fn);
    end
    OrdF=OrdF+1;
end


fclose(fp);
fclose(fp2);
fclose(fp3);
fclose(fp4);
fclose(fp5);
