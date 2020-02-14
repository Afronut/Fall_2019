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
    