clear;
t = 0:4*pi/10000:4*pi;
s = square(t);
s_n = s * -1;
d = square(t-(4*pi*0.025), 45);
d_n = -1* square(t, 55);

subplot(2, 1, 1);
hold on;
plot(t, s);
plot(t, s_n, 'r');
axis([0 4*pi -1.5 1.5]);
hold off;
subplot(2, 1, 2);
hold on;
plot(t, d);
plot(t, d_n, 'r');
axis([0 4*pi -1.5 1.5]);
hold off;


