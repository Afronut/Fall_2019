
%% Problem 11
a=[0.01 0.1 1 10 100];
peaks_step=zeros(5,3);

figure (1);
hold on
for i=1:length(a)
    G=tf([1/a(i) 1],[1 1 1]);
    step(G)
    m=stepinfo(G);
    peaks_step(i,1)=a(i);
    peaks_step(i,2)=m.Peak;
    
    hold on 
    clear G
    
end
figure (2);
hold on
i=0;
for i=1:length(a)
    G=tf([1/a(i) 1],[1 1 1]);
    bode(G)
    m=stepinfo(G);
    peaks_step(i,3)=20*log10(getPeakGain(G));
    hold on
end
T=array2table(peaks_step,'VariableNames',{'a','Mr','Mp'})
% The values are corolated as showed in the table bellow
%% Problem 12

p=[0.01 0.1 1 10 100];
bandw=zeros(6,2);

figure (3);
hold on
for i=1:length(p)
    G=tf(1,conv([1/p(i) 1],[1 1 1]));    
    bode(G)
    bandw(i+1,1)=p(i);
    bandw(i+1,2)=bandwidth(G);
    hold on
end

G=tf(1,[1 1 1]);  
bode(G,'--');
bandw(1,1)=0;
bandw(1,2)=bandwidth(G);
B=array2table(bandw,'VariableNames',{'a','Band'})
% As the value of the P increases the Band get close to the zero P value.
% We can say that as  P increases the new pole has less effect on the
% system
legend('a=0.01','a=0.1','a=01','a=10', 'a=100', 'a=0')

%% Problem 16
G1=tf([1 2], [1 20]);
G2=tf(1, conv([1 10],[1 2 1]));
G3=tf(conv([1 10],[1 1]),conv([1 100], conv([1 10 25],[1 5])));

figure(4)
margin(G1)
figure(5)
margin(G2)
figure(6)
margin(G3)
% The K values for wich each system is stable accure at the phase of -180.
% For G1 and G3 the values are inf because the phase never cross the 180
% degrees, and for the G2 the value is finite and diaplay on the graph
%% Problem 19
G1=tf([1 2], [1 20]);
G2=tf(1, conv([1 10],[1 2 1]));
G3=tf(conv([1 10],[1 1]),conv([1 100], conv([1 10 25],[1 5])));

figure(7)
nyquist(G1)
figure(8)
nyquist(G2)
figure(9)
nyquist(G3)