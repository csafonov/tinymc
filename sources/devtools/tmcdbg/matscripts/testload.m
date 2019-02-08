%testload
if 1
     FileName='C:\Data_D\HSKOST\Borisenko\tinyMcc\tmcdbg\Z.mat';
    fp=fopen(FileName,'rb');
    [A, COUNT] = fread(fp);
    fclose(fp);
end
A=A(:)';
Descr=A(1:128);
ind0=129;
% while ind0<length(A)
M=struct; % returned workspace
ind2=ind0;
while ind2<length(A)
    [M,ind2]=tmcreaddataelm(M,A,ind0);
    ind0=ind2;
end
return;


% 
% 
% 
% 
% 
% [dtype,dsz,Idat,bCompess]=matfgetsube(A,ind0);
% if dtype==14
%     [dtype1,dsz1,Idat1,bCompess]=matfgetsube(A,Idat(1));% ArrayFlags
%     ArrayFlags = A([Idat1(1):Idat1(2)]);
%     
%     [dtype2,dsz2,Idat2,bCompess]=matfgetsube(A,Idat1(2)+1);% DimsArr
%     DimsArr = A([Idat2(1):Idat2(2)]);
%     
%     [dtype3,dsz3,Idat3,bCompess]=matfgetsube(A,Idat2(2)+1);% ArrName
%     ArrName=char(A([Idat3(1)+[0:dsz3-1]]));
%     
%     
%     if ArrayFlags(1)==2
%         % structure
%         [dtype4,dsz4,Idat4,bCompess]=matfgetsube(A,Idat3(2)+1); % FnLen
%         FnLen=A([Idat4(1)+[0:dsz4-1]])*[1;256;256^2;256^3];
%         [dtype5,dsz5,Idat5,bCompess]=matfgetsube(A,Idat4(2)+1); % Fnames
%         Fnames=char(A([Idat5(1)+[0:dsz5-1]]));
%         NumFd=length(Fnames) /  FnLen;
%         Fd={};
%         X=struct;
%         for k=1:NumFd
%             [dtype5,dsz5,Idat5,bCompess]=matfgetsube(A,Idat5(2)+1); % Fd
%             Fd{k}=A([Idat5(1)+[0:dsz5-1]]);
%             II=(k-1)*FnLen+[1:FnLen-1];
%             X=setfield(X,Fnames(II),Fd{k});
%         end
%         MATF=setfield(MATF,ArrName,X);
%     end
%     if   ArrayFlags(1)==6  
%         [dtype4,dsz4,Idat4,bCompess]=matfgetsube(A,Idat3(2)+1);% Re
%         xRe=A([Idat4(1)+[0:dsz4-1]]);
%         if mod(floor(ArrayFlags(2)/8),2)==1 
%             [dtype5,dsz5,Idat5,bCompess]=matfgetsube(A,Idat4(2)+1);% Im
%             xIm=A([Idat5(1)+[0:dsz5-1]]);
%         else
%             xIm=[];
%         end
%         MATF=setfield(MATF,ArrName,{xRe ; xIm});
% 
%     end
% end
%     dt=A(ind0+[0:3])*[1;256;256^2;256^3];
%     ind0=ind0+4;
%     len=A(ind0+[0:3])*[1;256;256^2;256^3];
%     ind0=ind0+4;
%     dat=A(ind0+[0:len-1]);
%     
%     if dt==14
%         TagFlags=dat(1+[0:7]);
%         ArrayFlags=dat(9+[0:7]);
%         flags=ArrayFlags(3);
%     end

% end
