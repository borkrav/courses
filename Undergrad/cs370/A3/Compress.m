function [Y, drop] = Compress(X, tol)

dropped = 0;

[height, width] = size(X);

j=1;
while (j < height)
    
    i=1;
    while (i < width)
        
        block = X(j:j+7,i:i+7);
        
        
    
        block = fft2(block);
        
        for k = 1:numel(block)
            if(abs(block(k)) > (tol*(max(block(:)))))
          
            else
                
                if(block(k) ~= 0)
                    
                    block(k)= 0;
                    dropped = dropped + 1;
                end
                
            end
            
        end
        
        block = real(ifft2(block));
   
        Y(j:j+7,i:i+7) = block(1:8,1:8);        
        i = i + 8;
        
    
    end
  
    j = j + 8;
    
end

drop = dropped/(width*height);

end
