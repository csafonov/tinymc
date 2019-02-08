
function A = sylmat(g,u,v)
%
%  sylmat generates the Sylvester resultant matrix
%    of polynomial g, u, v
%
   mg = length(g)-1; 
   mu = length(u)-1; 
   mv = length(v)-1; 
   np = mg + mu;
   nq = mg + mv;
   
   m = mg + mu + mv;
   n = np + nq;
      
   A = zeros(n, m);  
   
   for j_ = 1:mg
       A(j_:j_+mu,j_) = u';
       A(np+j_:np+j_+mv,j_) = v';
   end;
   
   for j_ = 1:mu
       A(j_:j_+mg,j_+mg) = g';
   end;
   
   for j_ = 1:mv
       A(np+j_:np+j_+mg, j_+mg+mu) = g';
   end