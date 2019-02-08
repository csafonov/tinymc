function A = sylves(f,g,k)
%
%  The k-th sylvester matrix of f(x), f'(x) = g(x)
%
   l = length(f);
   m = l+k-1;
   n = 2*k+1;
   A = zeros(m,n);
   for j_ = 1:k+1;
       A(j_:j_+l-2,j_) = g';
   end;
   for j_ = 1:k
       A(j_:j_+l-1,j_+k+1) = f';
   end;

   