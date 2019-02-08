function [M,ind2]=tmcreadmatrixelm(M,A,dtype,dsz,bCompess,Idat)
% read matrix element
% always dtype=14

[dtype1,dsz1,Idat1,bCompess]=matfgetsube(A,Idat(1));% ArrayFlags
ArrayFlags = A([Idat1(1):Idat1(2)]); % elmdata2double(A,dtype1,dsz1,Idat1,bCompess); %A([Idat1(1):Idat1(2)]);

[dtype2,dsz2,Idat2,bCompess]=matfgetsube(A,Idat1(2)+1);% DimsArr
DimsArr=elmdata2double(A,dtype2,dsz2,Idat2,bCompess);

[dtype3,dsz3,Idat3,bCompess]=matfgetsube(A,Idat2(2)+1);% ArrName
ArrName=char(elmdata2double(A,dtype3,dsz3,Idat3,bCompess)); %  (A([Idat3(1)+[0:dsz3-1]]));

matcls=ArrayFlags(1); % matrix class
hasIm=mod(floor(ArrayFlags(2)/8),2);
switch matcls
    case 1 % mxCELL_CLASS
        Idat5=Idat3;
        len = prod(DimsArr);
        
        m = DimsArr(1);
        if len >0 && m > 0
            n = len / m;
            X=cell(m,n);
            for cntn=1:n
                for cntm=1:m
                    [dtype5,dsz5,Idat5,bCompess]=matfgetsube(A,Idat5(2)+1); % cell
                    Mx=[];
                    [Mx,indx]=tmcreadmatrixelm(Mx,A,dtype5,dsz5,bCompess,Idat5); 
                    X{cntm,cntn}=Mx;
                end
            end
        else
            X=[];
        end
        if ~isempty(ArrName)
            M=setfield(M,ArrName,X);
        else
            M=    X;
        end
        ind2=Idat5(2)+1;

    case 2 % mxSTRUCT_CLASS
        [dtype4,dsz4,Idat4,bCompess]=matfgetsube(A,Idat3(2)+1); % FnLen
        %FnLen=A([Idat4(1)+[0:dsz4-1]])*[1;256;256^2;256^3];
        FnLen= elmdata2double(A,dtype4,dsz4,Idat4,bCompess);
        [dtype5,dsz5,Idat5,bCompess]=matfgetsube(A,Idat4(2)+1); % Fnames
        
        %Fnames=char(A([Idat5(1)+[0:dsz5-1]]));
        Fnames=char(  elmdata2double(A,dtype5,dsz5,Idat5,bCompess)  );
        NumFd=length(Fnames) /  FnLen;
        
                    len = prod(DimsArr);
                    m = DimsArr(1);
                    if len >0 && m > 0 
                        n = len / m;
                    end    
                    X=struct;%('xuxu',cell(m,n));
                    
                    for cntn=1:n
                        for cntm=1:m
                            %X0=struct;
                            for k=1:NumFd
                                II=(k-1)*FnLen+[1:FnLen-1];
                                
                                [dtype5,dsz5,Idat5,bCompess]=matfgetsube(A,Idat5(2)+1); % Fd
                                Mx=[];
                                [Mx,indx]=tmcreadmatrixelm(Mx,A,dtype5,dsz5,bCompess,Idat5); 
                                %X{cntm,cntn}=Mx;
                                X=setfield(X,{cntm,cntn},Fnames(II),Mx);
                            end
                            %X(cntm,cntn)=X0;
                        end
                    end

            
            
            
            
%             [dtype5,dsz5,Idat5,bCompess]=matfgetsube(A,Idat5(2)+1); % Fd
%             Mx=[];
%             [Mx,indx]=tmcreadmatrixelm(Mx,A,dtype5,dsz5,bCompess,Idat5); %tmcreaddataelm(Mx,A,Idat5(1));
%             
%             Fd{k}= Mx ;%A([Idat5(1)+[0:dsz5-1]]);
%             II=(k-1)*FnLen+[1:FnLen-1];
%             X=setfield(X,Fnames(II),Fd{k});
%         end
        if ~isempty(ArrName)
            M=setfield(M,ArrName,X);
        else
            M=    X;
        end
        ind2=Idat5(2)+1;

        
        
    case 4 % mxCHAR_CLASS
        [dtype4,dsz4,Idat4,bCompess]=matfgetsube(A,Idat3(2)+1);% Re
        xRe=elmdata2double(A,dtype4,dsz4,Idat4,bCompess);
        %xRe=A([Idat4(1)+[0:dsz4-1]]);
        x=xRe;
        if hasIm 
            [dtype5,dsz5,Idat5,bCompess]=matfgetsube(A,Idat4(2)+1);% Im
            %xIm=A([Idat5(1)+[0:dsz5-1]]);
            xIm=elmdata2double(A,dtype5,dsz5,Idat5,bCompess);
            x=x+j*xIm;
        else
             Idat5=Idat4;
        end
        x =char(x);
        if ~isempty(ArrName)
            M=setfield(M,ArrName,x);
        else
            M=    x;
        end
        ind2=Idat5(2)+1;
        
    case {6,7,8,9,10,11,12,13} % mxDOUBLE_CLASS
        [dtype4,dsz4,Idat4,bCompess]=matfgetsube(A,Idat3(2)+1);% Re
        xRe=elmdata2double(A,dtype4,dsz4,Idat4,bCompess);
        %xRe=A([Idat4(1)+[0:dsz4-1]]);
        x=xRe;
        if hasIm 
            [dtype5,dsz5,Idat5,bCompess]=matfgetsube(A,Idat4(2)+1);% Im
            %xIm=A([Idat5(1)+[0:dsz5-1]]);
            xIm=elmdata2double(A,dtype5,dsz5,Idat5,bCompess);
            x=x+j*xIm;
        else
             Idat5=Idat4;
        end
        if ~isempty(ArrName)
            M=setfield(M,ArrName,x);
        else
            M=    x;
        end
        ind2=Idat5(2)+1;
%     case 7 % mxSINGLE_CLASS
%     case 8 % mxINT8_CLASS
%     case 9 % mxUINT8_CLASS
%     case 10 % mxINT16_CLASS
%     case 11 % mxUINT16_CLASS
%     case 12 % mxINT32_CLASS
%     case 13 % mxUINT32_CLASS
    otherwise
        error('TMC unsupported matrix class')
end

