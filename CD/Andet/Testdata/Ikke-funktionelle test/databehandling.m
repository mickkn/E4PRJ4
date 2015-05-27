clear
load('data.mat')
f = smooth(data/2^16, 40);
t = 0:1/200:(length(f)/200)-1/200;
df = smooth(200*diff(f), 20);
tdf = 0:1/200:(length(df)/200)-1/200;
ddf = smooth(200*diff(df), 20);
tddf = 0:1/200:(length(ddf)/200)-1/200;
plot(t, f, 'r');
hold on;
plot(tdf, df, 'b');
plot(tddf, ddf, 'g');
title('Unders�gelse af �nskede vuggem�nstre')
xlabel('sekunder');
ylabel('r�d- grader, bl�- grader/sekund, gr�n- grader/sekund^2');