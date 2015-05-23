clc, clear, close all
%**** RECBUF TEST *********************************
load sin880_2.dat;
x = sin880_2;

%**** Play sample ***********************************************
f_s = 24000;
sound(x, f_s)
N = length(x);

%**** Plot sample ***********************************************
figure(1)
plot(x)
xlabel('Tid/Samples')
ylabel('Amplitude')
title('Rec: Sample-plot')
grid on
axis([0 N -inf inf])

%**** Window sample *********************************************
x = x .* hanning(length(x));

%**** fft ******************************************************* 
NFFT = 2^nextpow2(N);       %Find next power of 2
X = fft(x,NFFT);
X_abs = abs(X);

f_axis = f_s/2*linspace(0,1,NFFT/2+1);  % Frequency axis setup
figure(2)
plot(f_axis,20*log10(2*abs(X(1:NFFT/2+1))),'b')
axis([0.1 12000 -inf inf])
xlabel('Frekvens i Herz')
ylabel('Magnitude [dB]')
title('FFT')
grid on