function c = polyr2p(x)
%POLY Convert roots to polynomial.
%   POLY(A), when A is an N by N matrix, is a row vector with
%   N+1 elements which are the coefficients of the
%   characteristic polynomial, DET(lambda*EYE(SIZE(A)) - A) .
%
%   POLY(V), when V is a vector, is a vector whose elements are
%   the coefficients of the polynomial whose roots are the
%   elements of V . For vectors, ROOTS and POLY are inverse
%   functions of each other, up to ordering, scaling, and
%   roundoff error.
%
%   ROOTS(POLY(1:20)) generates Wilkinson's famous example.
%
%   See also ROOTS, CONV, RESIDUE, POLYVAL.

%   Original by J.N. Little 4-21-85.
%   Copyright 1984-2002 The MathWorks, Inc.
%   $Revision: 5.14 $  $Date: 2002/04/09 00:14:24 $

[m,n] = size(x);
if m == n
   % Characteristic polynomial (square x)
   e = eig(x);
elseif (m==1) | (n==1)
   e = x;
else
   error('Argument must be a vector or a square matrix.')
end

% Strip out infinities
%TMC:e = e( isfinite(e) );
e = e(find( isfinite(e) ));

% Expand recursion formula
n = length(e);
c = [1 zeros(1,n)];
for j_=1:n
    c(2:(j_+1)) = c(2:(j_+1)) - e(j_).*c(1:j_);
end

% The result should be real if the roots are complex conjugates.
%TMC: if isequal(sort(e(imag(e)>0)),sort(conj(e(imag(e)<0))))
if isequal(sort(e(find(imag(e)>0))),sort(conj(e(find(imag(e)<0)))))
    c = real(c);
end
