%******************************************************************%
% Project: Forundersøgelse for E4PRJ4 BABY WATCH                   %
% Authors: Hedegaard, Lukas. & Boye, Kristian                      %
% Task: Forundersoegelse af seks udvalgte lydfiler:                %
% Hoejlydt babygraad, Moderat babygraad, Fuglefloejt               %
% Trafik, Latter, Kat                                              %
%******************************************************************%
clc, clear, close all

%**** EXTRACT SAMPLES *********************************************%
[rec1, f_s1] = wavread('Hoejlydt_babygraad1');
[rec2, f_s2] = wavread('Hoejlydt_babygraad2');
[rec3, f_s3] = wavread('Hoejlydt_babygraad3');
% [rec1, f_s1] = wavread('Moderat_babygraad1');
% [rec2, f_s2] = wavread('Moderat_babygraad2'); 
% [rec3, f_s3] = wavread('Moderat_babygraad3'); 
% [rec1, f_s1] = wavread('Fuglefloejt1');
% [rec2, f_s2] = wavread('Fuglefloejt2');
% [rec3, f_s3] = wavread('Fuglefloejt3');
% [rec1, f_s1] = wavread('Trafik1');  
% [rec2, f_s2] = wavread('Trafik2'); 
% [rec3, f_s3] = wavread('Trafik3'); 
% [rec1, f_s1] = wavread('Latter1');  
% [rec2, f_s2] = wavread('Latter2'); 
% [rec3, f_s3] = wavread('Latter3'); 
% [rec1, f_s1] = wavread('Cat1');
% [rec2, f_s2] = wavread('Cat2');
% [rec3, f_s3] = wavread('Cat3');

r1 = rec1(:,1)';  %extract left channel'
r2 = rec2(:,1)'; 
r3 = rec3(:,1)';  

%**** Check f_s ***************************************************%
if (f_s1 == f_s2  || f_s1 == f_s3)
     f_s = f_s2;
else
    Disp('ERROR: Samples do not have same f_s')
    exit
end

%**** Set sample window *******************************************%
frame_sec = 1.0;          %Set frame size from recordning length
                        %0 for full recording
space_sec = 0.1;        %Set space between recordings

if frame_sec == 0 
    N1 = length(r1);
    N2 = length(r2);
    N3 = length(r3);
    shift_N = 1;
else
    frame_N = frame_sec*f_s;
    shift_sec = 0.1;              %Set time shift
    shift_N = shift_sec*f_s;
end

Nspace = space_sec*f_s;
rSpace = zeros(1,Nspace);

%Extract framed sample
r1_win = r1(shift_N:frame_N-1+shift_N);             
r2_win = r2(shift_N:frame_N-1+shift_N);     
r3_win = r3(shift_N:frame_N-1+shift_N);     

%Window with hamming
r1_win = r1_win .* hanning(length(r1_win))';    
r2_win = r2_win .* hanning(length(r2_win))';   
r3_win = r3_win .* hanning(length(r3_win))';   

%Concatenate samples
x = [r1_win, rSpace, r2_win, rSpace, r3_win];
N = length(x);


%**** Bandpass prefiltrering **************************************%
n = 4;                                      % Order
bs_low_cutoff = 100;                        % Cut off freq (Hz)
bs_low_cutoff_rad = bs_low_cutoff/(0.5*f_s);% Cut off freq (rad/sample)
bs_high_cutoff = 10000; 
bs_high_cutoff_rad = bs_high_cutoff/(0.5*f_s); 
[b,a] = butter(n, [bs_low_cutoff_rad bs_high_cutoff_rad]); % Butter BP

x = filter(b,a,x);

%**** Play sample *************************************************%
sound(x, f_s)

%**** Plot sample *************************************************%
offset = 0;
x = x + offset;     %use offset to fit both sampleplot and TPR

figure(1)
subplot(3,1,1)
plot(x)
xlabel('Samples')
ylabel('Amplitude')
title('Rec: Sample-plot')
grid on

%**** FAST FOURIER TRANSFORM *********************************** 
NFFT = 2^nextpow2(N);       %Find next power of 2
X = fft(x,NFFT);

%**** Find Maximal FFT frequency *******************************
X_max = max(abs(X));

%**** Plot FFT ************************************************* 
%Smooth (only used for plot)
X_abs = abs(X);
X_abs_log = 20*log10(2*abs(X(1:NFFT/2+1)));
X_smooth_log1 = smooth(X_abs_log,0.002,'moving');       % Smooth data
X_smooth_log1 = smooth(X_smooth_log1,0.002,'moving'); 
X_smooth_log2 = smooth(X_abs_log,0.03,'moving');       
X_smooth_log2 = smooth(X_smooth_log2,0.03,'moving');  

f_axis = f_s/2*linspace(0,1,NFFT/2+1);  % Frequency axis setup
figure(2)
hold on
plot(f_axis,20*log10(2*abs(X(1:NFFT/2+1))),'b')
plot(f_axis,X_smooth_log1,'r','linewidth',2)
plot(f_axis,X_smooth_log2,'k','linewidth',2)
hold off
axis([0.1 10000 0 inf])
xlabel('Frekvens [Hz]')
ylabel('Magnitude [dB]')
title('FFT')
grid on

%**** SHORT-TIME DFT (Spectogram) *********************************%
segmentlen = 256;
nOverlap = 60;
NFFT = 1280;

figure(1)
subplot(3,1,3)
spectrogram(x, segmentlen, nOverlap, NFFT, f_s, 'yaxis');
specMinFreq = 0;
specMaxFreq = 10000;
axis([-inf inf specMinFreq specMaxFreq])
colormap bone
%colorbar

%Repeat and save data for use in tonal analysis functions:
[s,f,t,p] = spectrogram(x, segmentlen, nOverlap, NFFT, f_s,'yaxis'); 


%**** TONAL POWER RATIO *******************************************% 
%TPR for short-time DFT
TPR = TonalPowerRatio(abs(s), f_s, 5*10^-2)';
TPR_smooth = smooth(TPR(:),0.05,'moving');   % Smooth data

%TPR for global DFT
sig = X_abs;
fSum = sum(sig);                %sum all freq bins
[afPeaks] = findpeaks(sig);     %find peaks
G_T = 5*10^-2;                  %threshhold
k_peak = find(afPeaks > G_T);   %find peak above thresh
TPR_global = sum(afPeaks(k_peak))/fSum

%**** Plot Tonal Power Ratio **************************************%
xAxis = 1:(length(x)/length(TPR)):length(x);

figure(1)
subplot(3,1,2)
plot(xAxis,TPR,'r','linewidth',1)
hold on
plot(xAxis,TPR_smooth,'k','linewidth',2)
hold off
xlabel('Samples')
ylabel('Tonal Power Ratio')
title('Tonal Power Ratio')
grid on

%**** FREQ WITH MAX POWER **************************************
%For short time DFT
[q,nd] = max(10*log10(p));  %q is used for x-axis in later plot
maxPwr_smooth = smooth(f(nd),0.1,'moving');     % Smooth data

%For "long time" DFT
[maxPwr_val, maxPwr_freq] = max(X_abs);
maxPwr_freq = maxPwr_freq*(854/18656)   
%Omregningsfaktor fundet eksperimentelt

%**** FREQUENCY ANALYSIS PLOTS ************************************%
%**** Discard values beneath Tonal Power Ratio Threshold *******
cutThresh = 0;
maxPwr_smooth_cut = maxPwr_smooth;
maxPwr_cut = f(nd);

for i = 1 : length(maxPwr_smooth)
    %determine spectral energy at freq
    if ((TPR_smooth(i) < cutThresh) || (TPR(i) == 0))
        maxPwr_smooth_cut(i) = NaN(1);
        maxPwr_cut(i) = NaN(1);
    end
end

%**** Plot frequency analysis *************************************%
figure(1)
subplot(3,1,3)

hold on
plot3(t,maxPwr_smooth_cut,q,'r','linewidth',2)  %maxPwr_smooth plot
scatter(t,maxPwr_cut,5,'b')
view(2)
hold off





    































 
