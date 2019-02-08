function [y,tmcdefs]=readtmcmat(buf)
% read matrix data

tmcdefs=struct;

ofs_m_type=0; 
% 	TYPE_NOTHING=-1,
% 	TYPE_MATRIX=0, // simple matrix
% 	TYPE_STRUCT=1,
% 	TYPE_STRING=2,
% 	TYPE_CELL_ARRAY=3,
% 	TYPE_MAGIC_COLON=4,
% 	TYPE_REF=5,
% 	TYPE_ITERATOR=7,
% 	TYPE_FNC_HANDLE=9,
    
ofs_m_modifier=4;
ofs_m_nRows=8;
ofs_m_nCols=12;

% Matrix (0) or string (2)
ofs_rData=16;
ofs_iData=20;

% Cell type (3)
ofs_m_cells=16;

% Struct type (1)
ofs_hcFields=16;
ofs_m_fields=20;
ofs_m_nFields=24;

LongIndean_A=[1,2^8,2^16,2^24]';
LongInd =[1:4];
ShortIndean_A=[1,2^8]';
ShortInd =[1:2];

I = find(buf<0);
buf(I) = buf(I) + 256;
y.m_type = buf(ofs_m_type+LongInd) * LongIndean_A ;

switch y.m_type
    case {0,2} % TYPE_MATRIX,TYPE_STRING
        y.rData = buf(ofs_rData+LongInd) * LongIndean_A ;
        y.iData = buf(ofs_iData+LongInd) * LongIndean_A ;
    case {3} %TYPE_CELL_ARRAY
        y.m_cells = buf(ofs_m_cells+LongInd) * LongIndean_A ;
        
end

y.m_nRows = buf(ofs_m_nRows+LongInd) * LongIndean_A ;
y.m_nCols = buf(ofs_m_nCols+LongInd) * LongIndean_A ;
y.m_modifier = buf(ofs_m_modifier+ShortInd) * ShortIndean_A ;



