%******************************************************************%
% Project: E4PRJ4 BABY WATCH                                       %
% Authors: Lukas Hedegaard og Kristian Boye                        %
% Task: Forundersoegelse af fire udvalgte lydfiler,                %
% Hoejlydt babygraad, Moderat babygraad, Fuglefloejt og Trafik     %
%******************************************************************%

%**** EXTRACT SAMPLES *********************************************%
[rec, f_s] = wavread('Hoejlydt_babygraad');
%[rec, f_s] = wavread('Moderat_babygraad');   
%[rec, f_s] = wavread('Fuglefloejt');
%[rec, f_s] = wavread('Trafik');  

x = rec(:,1)';  %extract left channel'

%**** Set sample window *******************************************%
frame_sec = 0;          %Set frame size from recordning length
                        %0 for full recording
if frame_sec == 0 
    N = length(x);
    shift_N = 1;
else
    N = frame_sec*f_s;
    shift_sec = 1.1;    %Set time shift
    shift_N = shift_sec*f_s;
end

x_win = x(shift_N:N-1+shift_N);             %extract framed sample
x_win = x_win .* hanning(length(x_win))';   %window with hamming

%**** Bandpass prefiltrering **************************************%
n = 4;                                      % Order
bs_low_cutoff = 100;                        % Cut off freq (Hz)
bs_low_cutoff_rad = bs_low_cutoff/(0.5*f_s);% Cut off freq (rad/sample)
bs_high_cutoff = 10000; 
bs_high_cutoff_rad = bs_high_cutoff/(0.5*f_s); 
[b,a] = butter(n, [bs_low_cutoff_rad bs_high_cutoff_rad]); % Butter BP

x_win = filter(b,a,x_win);

%**** Play sample *************************************************%
sound(x_win, f_s)

%**** Plot sample *************************************************%
offset = 0;
x = x_win + offset;     %use offset to fit both sampleplot and TPR

figure(1)
subplot(3,1,1)
plot(x)
xlabel('Tid/Samples')
ylabel('Amplitude')
title('Rec: Sample-plot')
grid on

%**** FAST FOURIER TRANSFORM **************************************% 
NFFT = 2^nextpow2(N);   %Find next power of 2
X = fft(x_win,NFFT);

%**** Find Maximal FFT frequency **********************************%
X_max = max(abs(X));


%**** SHORT-TIME DFT (Spectogram) *********************************%
segmentlen = 256;
nOverlap = 60;
NFFT = 1280;

figure(1)
subplot(3,1,3)
spectrogram(x_win, segmentlen, nOverlap, NFFT, f_s, 'yaxis');
specMinFreq = 0;
specMaxFreq = 5000;
axis([-inf inf specMinFreq specMaxFreq])
colormap bone
%colorbar

%Repeat and save data for use in tonal analysis functions:
[s,f,t,p] = spectrogram(x_win, segmentlen, nOverlap, NFFT, f_s,'yaxis'); 


%**** TONAL POWER RATIO *******************************************% 
TPR = FeatureSpectralTonalPowerRatio(abs(s), f_s, 5*10^-2)';
TPR = TPR*5;   % upscaling

TPR_smooth = smooth(TPR(:),0.1,'moving');   % Smooth data

%**** Plot Tonal Power Ratio **************************************%
xAxis = 1:(length(x_win)/length(TPR)):length(x_win);

figure(1)
subplot(3,1,2)
plot(xAxis,TPR,'r','linewidth',1)
hold on
plot(xAxis,TPR_smooth,'k','linewidth',2)
hold off
xlabel('Tid/sample')
ylabel('Tonal Power Ratio')
title('Tonal Power Ratio')
grid on

%**** FREQ WITH MAX POWER *****************************************%
[q,nd] = max(10*log10(p));  %q is used for x-axis in later plot

maxPwr_smooth = smooth(f(nd),0.1,'moving');     % Smooth data


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





    































 
