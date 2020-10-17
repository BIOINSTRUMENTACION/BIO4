close all; clear all; clc                   % Clear varaibles and stuff
vid = VideoReader('videos\Alejandro9.mp4'); % Open video
vid.CurrentTime = 0;                        % Set current time to 0
figure;                                     % Create a figure
ax = axes;                                  % Create axis 
th = 0.5;                                   % Set threshold for binarization
se1 = strel("disk",20);                     % Set kernel for morpholgical operation
T = [];                                     % Create vector for time
A = [];                                     % Create vector for angle 
while vid.hasFrame()                        % Iterate over Frames
    %%%% PRERPOCESS IMAGE %%%
    temp = vid.readFrame();                 % Get frame
    gray = rgb2gray(temp);                  % Transform to gray
    binary = im2bw(gray,th);                % Get binary image 
    actual =   imopen(binary,se1);          % Apply erosion then dilation
    actual2 =   bwmorph(actual,'majority'); % Apply majortiy to close pixels
    
    %%% GET OBJECTS IN FRAME %%%
    [labeled,numobjects]=bwlabel(actual2);                  % Label objects 
    measurements  = regionprops(labeled,'centroid',"Area"); % Compute centroids and area
    centroids = cat(1,measurements.Centroid);               % Concatenate centroids
    area = cat(1,measurements.Area);                        % Concatenate area
    [r,c]=size(centroids); 
    % TRY AND EXCEPT (MATLAB VERSION) %
    try
    %%% SORT SHAPES BASED ON AREA %%%
    [Ar,i] = sort(area);               % Sort and get index
    % Obtaint Wrist (w), Elbow (e) and Shoulder (a)  
    % Every circle was desinged with different radius
    %(w : raduis = 1.5cm)
    %(e : raduis = 2.5cm)
    %(a : raduis = 3.5cm)
    [w,e,a] = deal(centroids(i(1),:),centroids(i(2),:),centroids(i(3),:));
    
    %%% TRANSLATE VECTORS TO ELBOW %%%
    xw = w(:,1) - e(:,1);  % transleta wrist x component to elbow x component (new x orign)
    yw = w(:,2) - e(:,2);  % transleta wrist y component to elbow y component (new y orign)
    xa = a(:,1) - e(:,1);  % transleta shoulder x component to elbow x component (new x orign)
    ya = a(:,2) - e(:,2);  % transleta shoulder y component to elbow y component (new y orign)
    v1=[xw,yw];            % Create vector 1
    v2=[xa,ya];            % Create vector 2
    nv1=norm(v1);          % Comput ecuclidian distance  of vector 1
    nv2=norm(v2);          % Comput ecuclidian distance  of vector 2
    angle = acosd(dot(v1,v2)/(nv1*nv2));      % Obtain angle 
    fprintf(' Angle: %g degrees \n', angle)   % Print angle
    
    %%% PLOT %%%
    subplot(1,2,1)                                       % Plot on first subplot
    imshow(temp);                                        % Show image
    hold on;                                             % Hold on first subplot
    plot(w(1),w(2),'r+','MarkerSize',10,'LineWidth', 1); % Plot centroids
    plot(e(1),e(2),'g+','MarkerSize',10,'LineWidth', 1); % Plot centroids
    plot(a(1),a(2),'b+','MarkerSize',10,'LineWidth', 1); % Plot centroids
    line([e(1),w(1)],[e(2),w(2)]);                       % Plot line
    line([e(1),a(1)],[e(2),a(2)]);                       % Plot line
    hold off;                                            % Hold of subplot
    
    t=vid.CurrentTime ;             % Get current Frame time
    A = [A angle];                  % Append angle to vector of angles
    T = [T t];                      % Append time to vector of time
    subplot(1,2,2)                  % Open second subplot
    plot(T,A,'b--')                 % Plot time vs angle
    axis([0 inf 0 180])             % Set y axis
    drawnow;                        % Enable draw option to make plot dynamic
    pause(1.0/vid.FrameRate);       % Pause so maltab does not get stuck      

    catch                           % In exception
    warning('Problem using function.  Assigning a value of 0.'); % Raise Warning 
    end
   
       
    %%%
  
    %%% SEE LINES %%%
    %line([0,xw],[0,yw]);
    %hold on;
    %line([0,xa],[0,ya]);
    %hold off;
    %%%%%%%%%%%%%%%%%%%%%
 
        
end