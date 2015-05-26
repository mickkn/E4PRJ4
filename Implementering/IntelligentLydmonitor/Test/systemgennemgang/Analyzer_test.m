clc, clear, close all

%**** ANALYZER TEST ***************************************************

%**** Generate test-sinus *********************************************
f_s = 48000;
Ttotal = 10;        % total tid i sek.
A = 1;              % amplitude
f1 = 1000;          % tone frekvens
f2 = 4000;          % tone frekvens
Ntotal = f_s*Ttotal;% totalt antal samples

% BEREGNING
n=0:Ntotal-1;       % tidsvektor
x=A*sin(2*pi*(f1/f_s)*n)+A*sin(2*pi*(f2/f_s)*n);

sound(x, f_s)       % play sinus

%%

%**** Load FFT from BF533 *********************************************
load an_freqSpecSmooth_hoejlydt.dat;
x = an_freqSpecSmooth_hoejlydt(:,1);

NFFT = length(x);
f_s = 24000;

%**** Plot Blackfin FFT ***********************************************
f_axis = (f_s/2)*linspace(0,1,NFFT);  % Frequency axis setup

figure(1)
plot(x)
xlabel('Frekvens bin]')
ylabel('Magnitude')
title('FFT')
grid on
axis([0 NFFT -inf inf])

figure(2)
plot(f_axis,x)
xlabel('Frekvens [Hz]')
ylabel('Magnitude [gg]')
title('FFT')
grid on
axis([0 f_s/2 -inf inf])