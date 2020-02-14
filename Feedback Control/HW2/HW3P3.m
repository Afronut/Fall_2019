clear
clc
close all
% Constant 
m=1;
l=1;
g=9.81;
k=1;
deta=5*(pi/180);
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