
function z = hqrt(t,b)
%
%  transformation using the t from hessqr
%
   [m,n] = size(b);
   z = b;
   k = size(t,2);
   for j_ = 1:k
       T = [t(1,j_),t(2,j_); -t(2,j_), t(1,j_)];
       z(j_:j_+1,:)=T*z(j_:j_+1,:);
   end;