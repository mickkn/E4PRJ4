
clear
load('sek.mat');
t = sek(:,1);
f = smooth(sek(:,3), 40)-2;
figure(1)
plot(t, f, 'b');
title('Testens fulde forløb');
xlabel('sekunder');
ylabel('grader');

figure(2)
i1 = 1;
i2 = find(t>17);
i2 = i2(1);
A1 = f(i1:i2);
t1 = t(i1:i2);
t1 = t1-t1(1)+0.5;

i1 = find(t>57); 
i1 = i1(1);
i2 = find(t>77);
i2 = i2(1);
A2 = f(i1:i2);
t2 = t(i1:i2);
t2 = t2-t2(1);

s = 10* sin(2*pi*0.08*(t2+3.5));
plot(t1, A1, 'b');
hold on;
plot(t2, A2, 'g');
plot(t2, s, 'r');
title('Vuggetilstand A');
xlabel('sekunder');
ylabel('grader');

figure(3)
i1 = find(t>17);
i2 = find(t>37);
i2 = i2(1);
B1 = f(i1:i2);
t1 = t(i1:i2);
t1 = t1-t1(1);

i1 = find(t>77); 
i1 = i1(1);
i2 = find(t>97);
i2 = i2(1);
B2 = f(i1:i2);
t2 = t(i1:i2);
t2 = t2-t2(1)+0.8;

s = 6 * sin(2*pi*0.16*(t2+4));
plot(t1, B1, 'b');
hold on;
plot(t2, B2, 'g');
plot(t2, s, 'r');
title('Vuggetilstand B');
xlabel('sekunder');
ylabel('grader');

figure(4)
i1 = find(t>37);
i2 = find(t>53);
i2 = i2(1);
B1 = f(i1:i2);
t1 = t(i1:i2);
t1 = t1-t1(1);

i1 = find(t>97); 
i1 = i1(1);
i2 = length(t);
B2 = f(i1:i2);
t2 = t(i1:i2);
t2 = t2-t2(1);

s = 4 * sin(2*pi*0.32*(t1-0.75));
plot(t1, B1, 'b');
hold on;
plot(t2, B2, 'g');
plot(t1, s, 'r');
title('Vuggetilstand C');
xlabel('sekunder');
ylabel('grader');


