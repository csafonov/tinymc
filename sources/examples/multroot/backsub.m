function x = backsub(A,b)
%
% assume A is an upper triangular matrix
% backsub performs backward substitution to solve Ax=b
%
   n = size(A,1);
   s = max(abs(diag(A)))*1.0d-16;
   x = zeros(n,1);
   if A(n,n) == 0, A(n,n) = s; end;
   x(n) = b(n)/A(n,n);
   for k = (n-1):-1:1
       if A(k,k) == 0, A(k,k) = s; end;
       x(k) = (b(k) - A(k,k+1:n)*x(k+1:n))/A(k,k);
   end;
