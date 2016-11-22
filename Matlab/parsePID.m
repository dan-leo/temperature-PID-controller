s = serial('COM5')
fopen(s)

time_array = {};
setpoint_array = {};
input_array = {};
output_array = {};

try
    while true
        data = fscanf(s);
        C = textscan(data, '%d%f%f%f','delimiter','\t')
        [time, setpoint, input, output] = deal(C{:});
        time_array(end+1) = {time};
        setpoint_array(end+1) = {setpoint};
        input_array(end+1) = {input};
        output_array(end+1) = {output};
    end
catch e
    display('ctrl + c')
    fclose(s)
end

fclose(s)