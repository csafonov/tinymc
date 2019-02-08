function [dtype,dsz,Idat,bCompess]=matfgetsube(buf,ind1)
% read sub-element from mat-file miMatrix
% returns data type, subelement size, data  index (padded)
if buf(ind1+2)~=0 || buf(ind1+3)~=0
    bCompess=1;
    dtype=buf(ind1+[0:1])*[1;256];
    dsz=buf(ind1+[2:3])*[1;256];
    Idat=[ind1+4,ind1+4+dsz-1];
else
    bCompess=0;
    dtype=buf(ind1+[0:3])*[1;256;256^2;256^3];
    dsz=buf(ind1+[4:7])*[1;256;256^2;256^3];
    Idat=[ind1+8,ind1+8+dsz-1];
end

Idat(2) = ceil(Idat(2)/8)*8;