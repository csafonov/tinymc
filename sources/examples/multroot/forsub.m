function x = forsub(A,b)
%
% assume A is an lower triangular matrix
% forsub performs forward substitution to solve Ax=b
%
   n = size(A,1);
   x = zeros(n,1);
   
   x(1) = b(1)/A(1,1);
   for k = 2:n
       x(k) = (b(k) - A(k,1:k-1)*x(1:k-1))/A(k,k);
   end;
