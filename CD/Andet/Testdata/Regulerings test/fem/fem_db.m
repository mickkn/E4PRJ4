clear;
load('fem.mat');
t = fem(:,1);
f = smooth(fem(:,3), 30);
df = smooth(diff(f)./diff(t),30);
tdf = t(2:length(t));
ddf = smooth(diff(df)./diff(tdf),30);
tddf = t(3:length(t));
plot(t(10:510), f(10:510), 'b');
hold on;
plot(tdf(9:510), df(9:510), 'r');
plot(tddf(8:510), ddf(8:510), 'g');
xlabel('Sekunder')
ylabel('blå- grader, rød- grader/sekund, grøn- grader/sekund^2')
title('Plot af barnevognskurvens position(blå), vinkelhastighed(rød) og vinkelacceleration(grøn)')
max_df = max(sqrt(df(100:500).*df(100:500)));
disp max_df;
disp(max_df);

max_ddf = max(sqrt(ddf(100:500).*ddf(100:500)));
disp max_ddf;
disp(max_ddf);
