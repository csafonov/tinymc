function [M,ind2]=tmcreaddataelm(M,buf,ind)
% read matrix from data element

% recognize data type
[dtype,dsz,Idat,bCompess]=matfgetsube(buf,ind);
if dtype ~= 14
    [M,ind2]=tmcreadnumelm(M,buf,dtype,dsz,bCompess,Idat); %read  numeric element
else
    [M,ind2]=tmcreadmatrixelm(M,buf,dtype,dsz,bCompess,Idat); %read  matrix element
end
