
function [s,x] = zminsv(A,tol)
%
%  zminsv calculates the smallest singular value
%  of matrix A and the associated right singular vector
%  via an implicit inverse iteration in the form of the
%  Gauss-Newton iteration
%
%    input  A --- the matrix
%           tol --- the error tolerence
%
%   output  s --- the smallest singular value
%           x --- the associated right singular vector
%
   [m,n] = size(A);      % get the dimensions of A
   scale = norm(A,inf);  % get the magnitude of rows as scaler
   %TMC_DEBUG: a = 2*rand(1,n)-1;        % random initial vector
   a = 2*ones(1,n)-1;
   
   a = scale*a/norm(a);      % set the first row
   b = [scale;zeros(m,1)];
   
   [Q,R] = qr(A);              % QR decomp. of A, maybe input
  
   [T,trans] = hessqr([a;R]);  % Hessenberg QR decomp. of stacked matrix
   z = hqrt(trans,b);          % same Q on b
   
   x = backsub(T(1:n,1:n),z(1:n));  x = x/norm(x); % geting the new vector
   
   r = [scale*x';R]*x-b;
   ss_ = [norm(r(2:m+1))]; cr = [];
   
   for k = 1:3
       
       [T,trans] = hessqr([2*scale*x';R]); 
       z = hqrt(trans,r); 
       u = backsub(T(1:n,1:n),z(1:n));
       y = x - u;
       y = y / norm(y);
       r = [scale*y';R]*y-b; 
       s = norm(r(2:m+1));
       ss_ = [ss_,s];
       cr = [cr,norm(x-y)]; %disp(cr(k));
      
       if k == 1
           if cr(1) < tol, break; end;
       else
           if cr(k) < cr(k-1)
               if cr(k)^2/(cr(k-1)-cr(k))<tol 
                   break
               end;
           end;
       end;
       x = y;
       
   end;