function bOk=matdiff(S1,S2)
% This file is a part of TMC converter.
% Shmuel Safonov (C) 2012-2013 All rights reserved.
% S1 is template matrix
format long
tol = 1e-6;
bOk=1; % Ok
if isstruct(S1)
    if isstruct(S2)
        S1n = orderfields(S1);
        S2n = orderfields(S2);
        fn1 = fieldnames(S1);
        for cnt=1:length(fn1)
            
            if isfield(S2n,fn1{cnt})
                bOk=matdiff(getfield(S1,fn1{cnt}),getfield(S2,fn1{cnt}));
                if ~bOk
                    disp(['<--In ',fn1{cnt}]);    
                end
            else
                disp(['Left only:', fn1{cnt}]);bOk=0;
            end
            
            
        end
    else
        disp(['Left only is struct:']);bOk=0;
    end
end
if iscell(S1)
    if iscell(S2)
        [m1,n1,k1,l1]=size(S1);
        [m2,n2,k2,l2]=size(S2);
        if m1~=m2
            disp(['Cell m: left=',num2str(m1),' right=',num2str(m2)]);bOk=0;
        end
         if n1~=n2
            disp(['Cell n: left=',num2str(n1),' right=',num2str(n2)]);bOk=0;
        end
        if k1~=k2
            disp(['Cell k: left=',num2str(k1),' right=',num2str(k2)]);bOk=0;
        end
        if l1~=l2
            disp(['Cell l: left=',num2str(l1),' right=',num2str(l2)]);bOk=0;
        end
        m=min(m1,m2);n=min(n1,n2);k=min(k1,k2);l=min(l1,l2);
        for cnt4=1:l
            for cnt3=1:k
                for cnt2=1:n
                    for cnt1=1:m
                        bOk=matdiff(S1{cnt1,cnt2,cnt3,cnt4},S2{cnt1,cnt2,cnt3,cnt4});
                        if ~bOk
                            disp(sprintf('<--in {%d,%d,%d,%d}}',cnt1,cnt2,cnt3,cnt4));
                        end
                    end
                end
            end
        end
                        
        
    else
        if ~isempty(S2) ||   ~isempty(S1)
            disp(['Left only is cell:']);bOk=0;
        end
    end
end

if isnumeric(S1) 
   if isnumeric(S2)

        [m1,n1,k1,l1]=size(S1);
        [m2,n2,k2,l2]=size(S2);
        if m1~=m2
            disp(['m: left=',num2str(m1),' right=',num2str(m2)]);bOk=0;
        end
         if n1~=n2
            disp(['n: left=',num2str(n1),' right=',num2str(n2)]);bOk=0;
        end
        if k1~=k2
            disp(['k: left=',num2str(k1),' right=',num2str(k2)]);bOk=0;
        end
        if l1~=l2
            disp(['l: left=',num2str(l1),' right=',num2str(l2)]);bOk=0;
        end
        m=min(m1,m2);n=min(n1,n2);k=min(k1,k2);l=min(l1,l2);
        for cnt4=1:l
            for cnt3=1:k
                for cnt2=1:n
                    for cnt1=1:m
                        x1=S1(cnt1,cnt2,cnt3,cnt4);
                        x2=S2(cnt1,cnt2,cnt3,cnt4);
                        
                        if abs(x1-x2)>tol
                                disp(sprintf(['(%d,%d,%d,%d): left=',num2str(x1),' right=',num2str(x2),'   diff=',num2str(x1-x2)],cnt1,cnt2,cnt3,cnt4));
                        bOk=0;        
                        end
                        
                        
                    end
                end
            end
        end
        
    else
            disp(['Left only is numeric.']);bOk=0;
       
   end
    
end
