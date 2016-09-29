function [ y ] = myErf( x0,xfinal, N, y0 )

h = (xfinal-x0)/N;
xn = y0;
y = xn;
for i=1:N
   
    xn1 = xn + (2/sqrt(pi)*exp(-xn^2))*h;
    y = [y xn1];
    xn = xn1;
    
end
    
end

