classdef util
    % This is a module to do some operations 
    methods(Static) % Static method
          function [e] = p_norm(v,p)
              % Computes the euclidian distance (Norm 2) of a row vector %
              [r,c] = size(v);       % Get shape
              e = 0;                 % Start temp variable
              for i = 1:1:r          % Iterate over vector 
                  e = e + v(i,1)^p;  % Apply p exponentiation
              end
              e = e^(1/p);           % apply 1/p exponentiation 
          end
          
          function [angle] = angle(v1,v2)
              % Returns the angle between 2 vectors %
              nv1=util.p_norm(v1,2);         % Computes eculidian norm in v1
              nv2=util.p_norm(v2,2);         % Computes eculidian norm in v2
              angle = acosd(dot(v1,v2)/(nv1*nv2)); % Gets angle
          end
    end
end