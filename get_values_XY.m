clc
clear
delete(instrfind);
dat = serial('COM8', 'BaudRate', 115200);
dat.InputBufferSize = 4096;
fopen(dat)
fwrite(dat, 1, 'uint8');
m = 250;
ADC = [];
for i = 1:m
    
    current_value = fread(dat, 1, 'uint16');
    ADC = [ ADC ; current_value];

    
    
end
fwrite(dat, 2, 'uint8');
fclose(dat)
save('znach_ADC.mat', 'ADC')
fclose(dat)