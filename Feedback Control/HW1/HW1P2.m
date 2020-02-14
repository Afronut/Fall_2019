clear
close all
clc

% enter input
prompt="Enter initial value of degree: ";
x=input(prompt);
prompt="Enter initial value of torque: ";
y=input(prompt);

% gravity
g=9.8;

mass=1; % the system is independant of mass
len=1;

% Linear ode
f_lean = @(t,z) [z(2); (-g/len)*z(1)];

% Non linear ode
f_nonlean=@(t,z) [z(2); (-g/len)*sin(z(1))];

% Intial conditions
int = [x*(pi/180);y];

%ODE solver

[t,sol_lean]=ode45(f_lean,[0 100],int);
[t1,sol_nonlean]=ode45(f_nonlean,[0 100],int);


% Plot
plot(t,sol_lean(:,1),'b')
hold on
plot(t1,sol_nonlean(:,1),'*')
legend('Linearized','Non linear')
xlabel('time (s)')
ylabel('Radians')
title(['Pendulum @ ',num2str(x),' degree(s)'])
xlim([90,100])
ylim([ min(sol_lean(:,1))-.009, max(sol_lean(:,1))+.009])













