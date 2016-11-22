s = serial('COM6')
fopen(s)

%time_array = {};
%setpoint_array = {};
%input_array = {};
%output_array = {};

set = animatedline('Color','r','LineWidth',1,'Marker','None','MaximumNumPoints',100);
in = animatedline('Color','b','LineWidth',1,'Marker','None','MaximumNumPoints',100);
out = animatedline('Color','g','LineWidth',1,'Marker','None','MaximumNumPoints',100);

try
    while true
        data = fscanf(s);
        C = textscan(data, '%f%f%f%f','delimiter','\t')
        [time, setpoint, input, output] = deal(C{:});
        output = output*100/255/2;
        addpoints(set,time,setpoint);
        addpoints(in,time,input);
        addpoints(out,time,output);
        drawnow
        %time_array(end+1) = {time};
        %setpoint_array(end+1) = {setpoint};
        %input_array(end+1) = {input};
        %output_array(end+1) = {output};
    end
catch e
    display('ctrl + c')
    display(e)
    fclose(s)
    %clearpoints(set);
    %clearpoints(in);
    %clearpoints(out);
end

fclose(s)