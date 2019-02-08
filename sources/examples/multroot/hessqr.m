
function [B,t] = hessqr(A)
%
%  hessqr performs QR decomposition on an upper
%      Hessenberg matrix
%
%  assume A is a Hessenberg matrix
%  output  B -- upper triangular
%          c -- rotation used
%
   [m,n] = size(A);
   if m < n, return; end;
   
   B = A;
   
   for j_ = 1:n
       if j_ < m
           d = sqrt(B(j_,j_)^2+B(j_+1,j_)^2);
           if d ~= 0
               c = B(j_,j_)/d; s = B(j_+1,j_)/d;
               T = [c,s;-s,c];
               B(j_:j_+1,j_:n) = T*B(j_:j_+1,j_:n);
               t(1,j_) = c; t(2,j_) = s;
           else
               t(1,j_) = 1; t(2,j_) = 0;
           end;
       end;
   end;