function [y, bkerr, pjcnd, job ] = ...
              pejroot( f, y0, l, noi, tol, style, prtsty )
%
% PEJROOT calculates (multiple) roots of polynomial using an iterative
% method developed by Z. Zeng. For details, you can request the paper
%
%     "Conputing Multiple roots of polynomials: pejorative condition and accurate
%     computation", by Zhonggang Zeng 
%
% This code is dated Dec. 4, 2002. Please sent bug/failure report to
%           
%             Prof. Zhonggang Zeng
%             Department of Mathematics
%             Northeastern Illinois University
%             Chicago, IL 60625
%
%             email: zzeng@neiu.edu
%
% This code is freely released for research exchange only. The author 
% is not responsible for any demage caused by using this code.
%
% Calling syntax: The simplest way to call is
%  
%   » pejroot(f,y,m)
%
% where the input items are
%          f --- (row vector) the target polynomial
%          y --- (row vector) the initial iterate (of the roots)
%          m --- (row vector) the multiplicity structure
%
% For more advanced usage:
%
%	» [z, e, c] = pejroot(f, y, l, noi, tol, style, prtsty)
%
% The output 
%          z --- (matrix) distinct roots (1st column) and corresponding
%                         multiplicities (2nd column)
%          e --- (scalar) the backward error of the roots
%          c --- (scalar) the pejorative condition number
%
%
%  Additional input parameters
%  
%        noi --- (integer)    the number of iteration allowed
%                               (default: 10)
%        tol --- (numeric)    the error tolerance
%                               (default: 1.0d-8)
%      style --- (integer)    backward error minimization style:
%                               1 : overall (absolute)
%                               2 : coefficientwise (relative,default)
%     prtsty --- (integer)    intermediate results showing style
%                               0: minimal (default)
%                               1: plus intermediate backward error and 
%                                     root corrections
%                               2: plus intemediate root approximations
%  Example:
%
% » f = polyr2p([ones(1,20),2*ones(1,10),3*ones(1,5)]); % construct the test 
%                 % polynomial with multiple roots
% » y = [0.95,2.05,2.95];           % prepare initial iterate
% » m = [20, 10, 5];                % prepare the multiplicity structure
% » pejroot(f,y,m)                  % running the program
% ans =
%
%   3.00000000000000   5.00000000000000
%   2.00000000000000  10.00000000000000
%   1.00000000000000  20.00000000000000
%
%
%

%HSKOST
y=[];bkerr=[]; pjcnd=[];

   if nargin == 3, noi = 10; tol = 1.e-6; style = 2; prtsty = 0; end;
   
   m = length(l);    % number of variables
   n = sum(l);       % number of equations
   
   if abs(f(1)) ~= 0     % make the polynomial monic
       f = f / f(1);
   else, jj = find(f);  j_ = min(jj); f = f(j_:length(f));
   end;
   
   if length(f) ~= n+1   % exit if the input is wrong
       fprintf('In put error');  return;
   end;
       
   % sort initial values to enhance accuracy
   % it is interesting, sorting really improves accuracy
   [yy,jj] = sort(1./abs(y0));   y0 = y0(jj); l = l(jj);

   job = 0;               % initialze job
   y = conj(y0');         % pass the initial iterate
   h = conj(f(2:n+1)');   % make the RHS
   delta = zeros(1,noi);  % space for sizes of the correction
   bcker = zeros(1,noi);  % space for backward errors

   w = ones(n,1);         % set weight
   if style == 2
      for j_ = 1:n
         if abs(f(j_+1)) >= 1.0 
            w(j_) = abs(1.0/f(j_+1));
         end
      end
   end;

   if prtsty == 1 
      disp('  ');  disp(' step   bcker         delta')
   end

   for k = 1:noi

      % evaluate the coefficient operator and its Jacobian
      Df = zeros(n,m);       % open the space for A
      
      ff = [1];  ll = l - ones(1,m);    % form the base polynomial
      mm = max(ll); lll = ll;
      for kk = 1:mm
          id = find(lll>0);
          ff = conv(ff,polyr2p(y(id)));
          lll = lll - 1;
      end;
       
      for j_ = 1:m               % remaining polynomial multiplication
         if m > 1
            id = [1:(j_-1),(j_+1):m]; g = polyr2p(y(id));
         else
            g = [1];
         end;
         g = conv(-l(j_)*g,ff);  Df(:,j_) = conj(g');
      end
      g = conv(-g/l(m), [1,-y(m)]);   % evalulate the coef. operator
      c = conj(g(2:n+1)');
      
      
      b = c - h;   % RHS of the polyn. system
    
      if style == 2   % scale
         b = b.*w; for j_ = 1:n,  Df(j_,:) = Df(j_,:)*w(j_); end
      end

      d = Df\b;               % least squares 
      delta(k) = norm(d,2);   bcker(k) = norm(b,inf);

      if delta(k) < tol, job = 1; end     % convergence criterion 1
      if k > 1 
         if delta(k) > delta(k-1) & bcker(k) > bcker(k-1)
            if job == 1, bkerr = bcker(k-1);   break; end;
         elseif delta(k) < delta(k-1)                 % criterion 2
            if delta(k)^2/(delta(k-1)-delta(k)) < tol, 
                job = 1; 
            end
         end
      end
      
      y = y - d;    % correct the roots

      if prtsty == 1       % intermediate show style 1
         disp(sprintf(' %2.0f    %10.2e    %10.2e', ...
                   k, bcker(k),delta(k)))
      elseif prtsty == 2   % intermediate show style 2
         [k, bcker(k),delta(k)]
         y
      end;
  
      bkerr = bcker(k); A = Df;
   end

   if job == 1
      s = svd(A); pjcnd = 1/s(m);               % get pej. cond. number
      [ll,jj] = sort(l);  y = [y(jj),l(jj)'];   % sort by multiplicities
      %
      % show off results
      %
      %fprintf('\n');
      %fprintf('    !!!THE COMPUTATION IS SUCCESSFUL!!!\n');
      %fprintf('\n');
      %fprintf('THE PEJORATIVE CONDITION NUMBER:     \t\t\t\t  %g \n',pjcnd);
      %fprintf('THE BACKWARD ERROR:                    %6.2e \n',bkerr);
      %fprintf('THE ESTIMATED FORWARD ROOT ERROR:      %6.2e \n',...
      %    2*bkerr*pjcnd);
      %fprintf('\n');
      %if norm(imag(y(:,1))) == 0 
      %   fprintf('        computed roots         multiplicities\n');
      %   fprintf('\n');
      %   fprintf('%25.15f \t \t \t %3g \n', y');
      %else
      %   fprintf('        computed roots ')
      %   fprintf('   \t\t\t\t\t\t     multiplicities\n');
      %   fprintf('\n');
      %   fprintf('%22.15f + %22.15f i \t \t %3g \n', ...
      %             [real(y(:,1)),imag(y(:,1)),y(:,2)]');
      %end;
   %else
       %fprintf('\n');
       %fprintf('The computation in pejroot is unsuccessful, you can try to\n');
       %fprintf('   1. use better initial iterate, and/or \n');
       %fprintf('   2. use a better multiplicity strucuture, and/or \n');
       %fprintf('   3. allow the iteration to run more steps ');
       %fprintf(' (default: 10 steps)\n');
       %fprintf('\n');
       %fprintf('The method may fails when the polynomial is pejoratively\n');
       %fprintf('ill-conditioned.\n');
   end;
