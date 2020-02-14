G1=tf([1 2], [1 20]);
G2=tf(1, conv([1 10],[1 2 1]));
G3=tf(conv([1 10],[1 1]),conv([1 100], conv([1 10 25],[1 5])));

figure(1)
nyquist(G1)
figure(2)
nyquist(G2)
figure(3)
nyquist(G3)
