clear
clc
load('znach_ADC.mat', 'ADC');
time = [];
t = 0;
dt = 0.002;
for i = 1:250
    time = [time ; t];
    t = t + dt;
end
figure(1);
grid on
plot(time,ADC)
legend('Значения потенциометра'); 
title('Зависимость значений потенциометра от времени');
xlabel('Время, c');
ylabel('Значения 12-битного АЦП'); 