function myAngryTriangle

f=figure(1);
clf;
aH=axes('Xlim',[0,2],'Ylim',[0,1]);

line([0.2 0.2],[0 0.2],'color',[0.5451,0.2706,0.0745],'linewidth',5);
line([1.5 1.5],[0.05 0.05],'color','g','linewidth',21,'Marker','o','MarkerFaceColor','g');
line([1.47 1.47],[0.08 0.08],'color',[0.1961,0.8039,0.1961],'linewidth',3,'Marker','^','MarkerFaceColor',[0.1961,0.8039,0.1961]);
line([1.53 1.53],[0.08 0.08],'color',[0.1961,0.8039,0.1961],'linewidth',3,'Marker','^','MarkerFaceColor',[0.1961,0.8039,0.1961]);
rectangle('Position',[1.487,0.026,0.028,0.025],'Curvature',[1,1],'FaceColor',[0.1961,0.8039,0.1961]);
tri=line([0.2 0.2],[0.2 0.2],'color','red','linewidth',10,'Marker','>','MarkerFaceColor','r','ButtonDownFcn', @startDragFcn);
sling=line([0.2 0.2],[0.2 0.2],'color',[0.6275,0.3216,0.1765],'linewidth',2);
pos=text(1.56,0.96,'');

set(f,'WindowButtonUpFcn',@stopDragFcn);

  function startDragFcn(varargin)
    set(f,'WindowButtonMotionFcn',@draggingFcn)
  end

  function draggingFcn(varargin)
    pt = get(aH,'CurrentPoint'); 
    dist = norm([pt(1),pt(3)]-[0.2,0.2]);
    if pt(1)<=0.2
      if dist<=0.15
        set(tri,'XData',pt(1)*[1 1],'YData',pt(3)*[1 1]);
        set(sling,'XData',[0.2 pt(1)],'YData',[0.2 pt(3)]);
        set(pos,'String',['x0 = ' num2str(pt(1)) ', y0 = ' num2str(pt(3))]);
      else
        newx=pt(1)+(dist-0.15)/dist*(0.2-pt(1));
        newy=pt(3)+(dist-0.15)/dist*(0.2-pt(3));
        set(tri,'XData',newx*[1 1],'YData',newy*[1 1]);
        set(sling,'XData',[0.2 newx],'YData',[0.2 newy]);
        set(pos,'String',['x0 = ' num2str(newx) ', y0 = ' num2str(newy)]);
      end
    end
  end

  function stopDragFcn(varargin)
    set(f,'WindowButtonMotionFcn','');
    sx=get(sling,'XData');
    sy=get(sling,'YData');
    dist = norm([sx(1)-sx(2),sy(1)-sy(2)]);
    if dist>0
      set(sling,'XData',[0.2 0.2],'YData',[0.2 0.2]);
      set(tri,'color','w','MarkerFaceColor','w');
      x0=sx(2); y0=sy(2);
    
      speed=dist/0.15*4;
      myShoot([x0;y0],atan((sy(2)-sy(1))/(sx(2)-sx(1))),speed);

   
      set(tri,'XData',[0.2 0.2],'YData',[0.2 0.2],'color','red','MarkerFaceColor','r');
      position=get(pos,'Position');
      pos=text(1.56,position(2)-0.06,'');
    end
  end

end
