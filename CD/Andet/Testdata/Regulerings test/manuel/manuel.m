clear
load('man.mat');
t = man(:,1);
f = smooth(man(:,3), 40);
s = 8* sin(2*pi*0.11*(t+6));
figure(1)
plot(t, f, 'b');
hold on;
plot(t, s, 'r');
xlabel('sekunder');
ylabel('grader');
title('Manuel vugge tilstand');
