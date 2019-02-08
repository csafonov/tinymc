function z = multroot( p, tol )
%  
%  Finds all roots of a real or complex polynomial p,
% 
%        p(x) = a_1 x^n + a_2 x^n-1 + ... + a_n x + a_n+1,
%
%  given by an (n+1)-row vector p = (a_1, ..., a_n+1) 
%
%  METHOD : for details, contact the author 
%
%             Zhonggang Zeng
%             Department of Mathematics
%             Northeastern Illinois University
%             Chicago, IL 60625
%          
%             email: zzeng@neiu.edu
%
% This code is freely released for research exchange only. The author 
% is not responsible for any demage caused by using this code.
%
%  INPUT :  p = polynomial coefficients. 
%           
%  OUTPUT : z = roots of polynomial p and multiplicities:
%                  z(:,1) = all distinct roots
%                  z(:,2) = corresponding multiplicities
%  CALL :   
%               >> z = multroot(p). 
%
   if nargin == 1, tol = 1.0d-10; end;
   %
   % transpose if p is a column vector
   %
   [m,n] = size(p);            
   if m > n, p = p'; end;
   %
   % clear leading/trailing zeros
   %
   n = length(p);
   q = p;
   if q(1) == 0 | q(n) == 0 
       jj = find(p); 
       j1 = min(jj); j2 = max(jj);
       q = p(j1:j2);
   else
       j1 = 1; j2 = n;
   end;
   q = q/q(1); c = 1;
   %
   % scaling
   %
   m = length(q)-1;
   c = 1/(abs(q(m+1)))^(1/m);
   q = q.*(c.^[0:m]);
   %
   [y,bke] = gcdroot(q, tol);
   
   if bke < 1.0d-2
       [z,bkerr,pjcnd,job] = pejroot(q,y(:,1).',y(:,2)');
       if j2 < n
           z = [z;0,n-j2];
       end;
       if job == 1
           %
           % show off results
           %
           z(:,1) = z(:,1)/c;
           fprintf('\n');
           fprintf('    !!!THE COMPUTATION IS SUCCESSFUL!!!\n');
           fprintf('\n');
           fprintf('THE PEJORATIVE CONDITION NUMBER:     \t\t\t\t  %g \n',pjcnd);
           fprintf('THE BACKWARD ERROR:                    %6.2e \n',bkerr);
           fprintf('THE ESTIMATED FORWARD ROOT ERROR:      %6.2e \n',...
               2*bkerr*pjcnd);
           fprintf('\n');
           if norm(imag(z(:,1))) == 0 
               fprintf('        computed roots         multiplicities\n');
               fprintf('\n');
               fprintf('%25.15f \t \t \t %3g \n', z');
           else
               fprintf('        computed roots ')
               fprintf('   \t\t\t\t\t\t     multiplicities\n');
               fprintf('\n');
               fprintf('%22.15f + %22.15f i \t \t %3g \n', ...
                   [real(z(:,1)),imag(z(:,1)),z(:,2)]');
           end;
       else
           z = [roots(p),ones(length(p)-1,1)];
       end;
   else
       z = [roots(p),ones(length(p)-1,1)];
   end;
   