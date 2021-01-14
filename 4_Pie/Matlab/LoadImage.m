clear all; close all; clc;
root   = "..//images//";                % Root directory where images are stored
images = ["atypical","typical","mid"]; % List of names of images

%%% Load image %%%
for i=1:1:length(images) % Iterate over size of image class
    for j=1:1:6          % Iterate over image number (there are 6 images of each class)
           path = root  + images(i) + "0" + string(j) + ".PNG"; % Recunstruct path to image
           A = imread(path);                                    % Load Image
           eval(sprintf('global A ;', i,j));                   % Save image in a new variable
           eval(sprintf('A%d%d = A ;', i,j));                   % Save image in a new variable
    end
end

while true
    i =input("Sequence to animate: 1:atypical, 2:typical, 3:mid  ");
    figure                                  %Create Figure 
    grid on;
    for j=1:1:6
        eval(sprintf('global A%d%d; ',i,j));
        eval(sprintf('image = A%d%d; ',i,j));
        imshow(image);
     
        title(images(i));
        axis tight
        hold off
    end
    q = input("press 6 to quit: ");
    if q == 6
       break
    end 
end
