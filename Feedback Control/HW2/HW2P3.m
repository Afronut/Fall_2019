%% Problem 3
clear
close all
% Constant definition
m=1; M=1; k=1; b=.1; u=1; b1=.1;
% Symbolic var
syms y(t) x(t)
%generate vector field from the ode
ode=odeToVectorField(diff(x,2)==-(k/m)*(x-y)-(b/m)*(diff(x)-diff(y)),(diff(y,2)==u/M+(k/M)*(x-y)+((b/M)*diff(x)-(b1/M)*diff(y))));
%turm the field into func
func = matlabFunction(ode,'vars', {'t','Y'});
%solve ODE
[t,sol] = ode45(func,[0 50],[0 0 0 0]);
y=sol(:,1);
ydot=sol(:,2);
x=sol(:,3);
xdot=sol(:,4);
%plot velocity the mass M only
plot(t,ydot)
%% Problem 4
% Constant
l=1; g=9.81; deta=5*(pi/180);
%symbolic vars
syms y(t) x(t)
%Create verctor field
ode=odeToVectorField(diff(x,2)==(9*k/16*m)*y-(g/l-9*k/(16*m))*x, diff(y,2)==(9*k/16*m)*x-(g/l-9*k/(16*m))*y);
%Change vector field into function
func = matlabFunction(ode,'vars', {'t','Y'});
% Solve
[t,sol] = ode45(func,[0 100],[deta 0 0 0]);
y=sol(:,1);
ydot=sol(:,2);
x=sol(:,3);
xdot=sol(:,4);
%Plot the Y
plot(t,y)
hold on
% Plot X
plot(t,x)