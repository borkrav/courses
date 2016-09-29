function myShoot(init_pos,init_theta,init_vel)

%
% Initial position and velocity
%
x0=init_pos(1);
y0=init_pos(2);
theta0=init_theta(1);
v0=init_vel(1);




%
% Set ode options and call ode 45
%
options=odeset('Events',@events,'Refine',10,'MaxStep',0.01);
[t,z]=ode45(@motion_ode,[0:0.05:5],[x0;y0;theta0;v0],options);

%
% After the calculation, plot/animate the trajectory of the triangle
%
figure(1);
hold on;
n=length(t);
tri_h=plot(z(1,1),z(1,2),'r>','linewidth',10,'MarkerFaceColor','r');
set(tri_h,'erasemode','normal');
for s=2:n,
  set(tri_h,'XData',z(s,1),'YData',z(s,2));
  if s==2,
    dot_h=plot(z(1,1),z(1,2),'.','color',[1,0.7529,0.7961],'linewidth',4,'MarkerFaceColor','g');
  else
    dx=[get(dot_h,'XData') z(s-1,1)];
    dy=[get(dot_h,'YData') z(s-1,2)];
    set(dot_h,'XData',dx,'YData',dy);
  end
  drawnow;
  pause(0.05);
end

    %
    % Dynamics function for the triangle: Complete the missing parts
    %
    function dz = motion_ode(t,z)

       dz(1,1) = z(4)*cos(z(3));
       dz(2,1) = z(4)*sin(z(3));
       dz(3,1) = -9.81/z(4)*cos(z(3));
       dz(4,1) = -(((0.72*1.29*0.005)/2)*((z(4)*cos(z(3)))^2+(z(4)*sin(z(3)))^2))/0.2-9.81*sin(z(3));

    end
    
    %
    % Event function: Complete the missing parts
    %
    function [values,halt,direction]=events(t,z);
        
        values(1) = z(2);
        halt(1) = 1;
        direction(1) = -1;

        values(2) = 2 - z(1);
        halt(2) = 1;
        direction(2) = -1;
        
        values(3) = (abs(z(1) - 1.5) + abs(z(2) - 0.05)) - 0.05;
        halt(3) = 1;
        direction(3) = -1;



    end

end
