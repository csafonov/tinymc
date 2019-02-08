function [x,buff]=gettmcvar(addr)
% read variable from debugged application
x=[];buff=[];
if ischar(addr)
    I=findstr(addr,'x');
    if ~isempty(I)
        addr=addr((I(1)+1):end);    
    end
    addr=hex2dec(addr);
end

hWnd = findwnd('tmcdebug');
if hWnd<=0
    error('debugged appication does not running');
end
    hProcess_copy = getwndprocess( hWnd );
if hProcess_copy<=0
    error('debugged appication does not running');
end

szTmcMat=32;
szDouble=8;
szAddr = 4;

buff=readprocessmem( hProcess_copy,addr,szTmcMat );
y=readtmcmat(buff);
x=buff;
switch (y.m_type)
    case {0,2} %TYPE_MATRIX,TYPE_STRING    
        NumElem=y.m_nRows*y.m_nCols;
    	NN=szDouble*NumElem;
        buffr=readprocessmem( hProcess_copy,y.rData,NN );
%         DoubleIndean_A=[1,2^8,2^16,2^24,2^32,2^40,2^48,2^64]';
% HAZARD: please, optimize: remove dec2hex and hex2double.
        DoubleInd =[1:8];
        I = find(buffr<0);
        buffr(I) = buffr(I) + 256;
        re=[];
        for cnt=1:NumElem
            sBuf=[];
            for k=1:szDouble
                    sBuf=[dec2hex(buffr(8*(cnt-1)+DoubleInd(k)),2),sBuf];
            end
            re(cnt) = hex2double(sBuf);
        end
        x=re;
        if (bitand(y.m_modifier , 2) == 2) %MODIFIER_MASK_HAS_IM
            buffr=readprocessmem( hProcess_copy,y.iData,NN );
            I = find(buffr<0);
            buffr(I) = buffr(I) + 256;

            im=[];
            for cnt=1:NumElem
                sBuf=[];
                for k=1:szDouble
                        sBuf=[dec2hex(buffr(8*(cnt-1)+DoubleInd(k)),2),sBuf];
                end
                im(cnt) = hex2double(sBuf);
            end
            x = x + j*im;
        end
        x = reshape(x,y.m_nRows,y.m_nCols);
        if y.m_type==2
            x=char(x);
        end
	case 3  % TYPE_CELL_ARRAY://3
        NumElem=y.m_nRows*y.m_nCols;
    	NN=szAddr*NumElem;
        buffr=readprocessmem( hProcess_copy,y.m_cells,NN );
        AddrInd =[1:4];
        AddrIndean_A=[1,2^8,2^16,2^24]';

        I = find(buffr<0);
        buffr(I) = buffr(I) + 256;
        AddrCell=[];
        for cnt=1:NumElem
            AddrCell(cnt) = buffr((cnt-1)*4 + AddrInd)*AddrIndean_A ;
        end
        x={};
        for m=1:y.m_nRows
            for n=1:y.m_nCols
                cAddr=AddrCell(m+(n-1)*y.m_nRows)
                x{m,n}=gettmcvar(cAddr);        
            end
        end
    case 1 %TYPE_STRUCT
        NumElem=y.m_nRows*y.m_nCols;
    	NN=szAddr*NumElem;
        
end
