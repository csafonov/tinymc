function [x,y]=testm1( fn)

if ~isempty(fn)
		JData = json_read(fn);
else
		fn=[];
		JData = json_read;
end;
save([fn,'.mat'], 'JData' );
x = JData;y=fn;


