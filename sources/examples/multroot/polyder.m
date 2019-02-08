function [a,b] = polyder(u,v)
%POLYDER Differentiate polynomial.
%   POLYDER(P) returns the derivative of the polynomial whose
%   coefficients are the elements of vector P.
%
%   POLYDER(A,B) returns the derivative of polynomial A*B.
%
%   [Q,D] = POLYDER(B,A) returns the derivative of the
%   polynomial ratio B/A, represented as Q/D.
%
%   See also POLYINT, CONV, DECONV.

%   Charles R. Denham, MathWorks, 1988.
%   Copyright 1984-2002 The MathWorks, Inc.
%   $Revision: 5.11 $  $Date: 2002/04/09 00:14:25 $

if nargin < 2, v = 1; end

u = u(:).'; v = v(:).';
nu = length(u); nv = length(v);
if nu < 2, up = 0; else, up = u(1:nu-1) .* (nu-1:-1:1); end
if nv < 2, vp = 0; else, vp = v(1:nv-1) .* (nv-1:-1:1); end
a1 = conv(up,v); a2 = conv(u,vp);
i_ = length(a1); j_ = length(a2); z = zeros(1,abs(i_-j_));
if i_ > j_, a2 = [z a2]; elseif i_ < j_, a1 = [z a1]; end
if nargout < 2, a = a1 + a2; else, a = a1 - a2; end
f = find(a ~= 0);
if ~isempty(f), a = a(f(1):end); else, a = 0; end
b = conv(v,v);
f = find(b ~= 0);
if ~isempty(f), b = b(f(1):end); else, b = 0; end
