clear
close all
clc

n = 200;
xs = linspace(-2,4,n);
ys = linspace(-4,4,n);

% Surface
s  = @(x,y) (x.*y'.^4);
f = s(xs,ys);

sf  = @(x,y) (x.*y.^4); % surface function with output vector

% Path & Parametrization
xa = @(t) (4*cos(t));
ya = @(t) (4*sin(t));

t = linspace(-pi/2,pi/2,n);

a = [xa(t);ya(t)]';

g = sf(a(:,1),a(:,2)); % surface function along the path 'a'

% Plot surface
surf(xs,ys,f,"edgecolor","none"); hold on
xlabel('x'); ylabel('y')

plot3(a(:,1),a(:,2),g,'r')

%% Integral
aux = 0;
for in = 2:numel(t)
    aux = t(in)-t(in-1) + aux;
end
h = aux/(numel(t)-1);

dx = gradient(a(:,1))./h;
dy = gradient(a(:,2))./h;
j = sqrt(dx.^2+dy.^2);

itg = trapz(t,g.*j)             % numerical result
res = 8192/5                    % analytical solution
dif = abs(itg-res)/res * 100    % relative difference between the two