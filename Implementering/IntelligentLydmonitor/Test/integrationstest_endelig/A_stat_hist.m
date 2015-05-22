clc, clear, close all
%**** RECBUF TEST *********************************
load Fuglefloejt1.dat;
x = Fuglefloejt1;

N = length(x);

%**** Plot sample ***********************************************
figure(1)
plot(x,'o')
xlabel('buf[num]')
ylabel('Babycon')
title('Statistician buffer')
grid on
axis([0 N 0 3])

%**** Plot histogram ***********************************************

% for i = 1 : 3
%     x(i)=i;
% end

edges = [1 2 3];
figure(2), hist(x, edges)
xlabel('BABYCON')
ylabel('Count')
title('Fuglefloejt1: Histogram over 100 målinger')