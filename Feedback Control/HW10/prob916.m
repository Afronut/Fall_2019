G3=tf(conv([1 10],[1 1]),conv([1 100], conv([1 10 25],[1 5])));

figure(1)
bode(G1)
figure(2)
bode(G2)
figure(3)
bode(G3)
