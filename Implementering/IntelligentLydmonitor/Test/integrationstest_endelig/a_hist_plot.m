clc, clear, close all
%**** HISTOGRAM PLOTTER *****************************************
load Latter2.dat;
x = Latter2;
N = length(x);

%**** Plot sample ***********************************************
figure(1)
plot(x,'o')
xlabel('buf[num]')
ylabel('Babycon')
title('Statistician buffer')
grid on
axis([0 N 0 3])

%**** Plot histogram ********************************************
edges = [1 2 3];
figure(2), hist(x, edges)
xlabel('BABYCON')
ylabel('Count')
title('Latter: Histogram over 100 m?linger')