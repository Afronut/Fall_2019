p=[0.01 0.1 1 10 100];
bandw=zeros(6,1);

figure (1);
hold on
for i=1:length(p)
    G=tf(1,conv([1/p(i) 1],[1 1 1]));    
    bode(G)
    bandw(i+1,1)=bandwidth(G);
    hold on
end

G=tf(1,[1 1 1]);  
bode(G,'--');
bandw(1,1)=bandwidth(G)
%T=array2table(peaks_step,'VariableNames',{'a','Mr','Mp'})
legend('a=0.01','a=0.1','a=01','a=10', 'a=100', 'a=0')