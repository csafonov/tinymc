function y=elmdata2double(A,dtype,dsz,Idat,bCompess)
% convert the data element to double

x = A([Idat(1)+[0:dsz-1]]);

switch dtype
    case 1 % miINT8
         I=find(x>=128);
         x(I)=x(I)-256;
         y = x ; 
         
    case 2 % miUINT8
         y = x ; 
    case 3 % miINT16
         len = length(x)/2;
         y=zeros(1,len);
         for k=1:len
            y(k) = [x((k-1)*2+1),x((k-1)*2+2)] * [1;256];
         end
         I=find(y>=2^15);
         y(I)=y(I)-2^16;
    case 4 % miUINT16
         len = length(x)/2;
         y=zeros(1,len);
         for k=1:len
            y(k) = [x((k-1)*2+1),x((k-1)*2+2)] * [1;256];
         end
    case 5 % miINT32
         len = length(x)/4;
         y=zeros(1,len);
         for k=1:len
            y(k) = [x((k-1)*4+1),x((k-1)*4+2),x((k-1)*4+3),x((k-1)*4+4)] * [1;256;256^2;256^3];
         end
         I=find(y>=2^31);
         y(I)=y(I)-2^32;
   case 6 % miUINT32
         len = length(x)/4;
         y=zeros(1,len);
         for k=1:len
            y(k) = [x((k-1)*4+1),x((k-1)*4+2),x((k-1)*4+3),x((k-1)*4+4)] * [1;256;256^2;256^3];
         end
    case 7 % miSINGLE
          len = length(x)/8;
         y=zeros(1,len);
         % 8 8 [7 1] [7 1]
         % mant = x((k-1)*8+1) + x((k-1)*8+2)*256 + mod(x((k-1)*8+3),128)*256^2;
         % scl  = floor( x((k-1)*8+4) / 128
         for k=1:len
            y(k) = 11111; %[x((k-1)*8+1),x((k-1)*8+2),x((k-1)*8+3),x((k-1)*8+4),x((k-1)*8+5),x((k-1)*8+6),x((k-1)*8+7),x((k-1)*8+8)] * [1;256;256^2;256^3;256^4;256^5;256^6;256^7];
         end
    case 9 % miDOUBLE
          len = length(x)/8;
         y=zeros(1,len);
         for k=1:len
            y(k) = 22222; %[x((k-1)*8+1),x((k-1)*8+2),x((k-1)*8+3),x((k-1)*8+4),x((k-1)*8+5),x((k-1)*8+6),x((k-1)*8+7),x((k-1)*8+8)] * [1;256;256^2;256^3;256^4;256^5;256^6;256^7];
         end
    case 12 %  miINT64  
          len = length(x)/8;
         y=zeros(1,len);
         for k=1:len
            y(k) = [x((k-1)*8+1),x((k-1)*8+2),x((k-1)*8+3),x((k-1)*8+4),x((k-1)*8+5),x((k-1)*8+6),x((k-1)*8+7),x((k-1)*8+8)] * [1;256;256^2;256^3;256^4;256^5;256^6;256^7];
         end
         I=find(y>=2^63);
         y(I)=y(I)-2^64;
   case 13 % miUINT64
         len = length(x)/8;
         y=zeros(1,len);
         for k=1:len
            y(k) = [x((k-1)*8+1),x((k-1)*8+2),x((k-1)*8+3),x((k-1)*8+4),x((k-1)*8+5),x((k-1)*8+6),x((k-1)*8+7),x((k-1)*8+8)] * [1;256;256^2;256^3;256^4;256^5;256^6;256^7];
         end
    otherwise
        error('TMC unsupported data type')
end
