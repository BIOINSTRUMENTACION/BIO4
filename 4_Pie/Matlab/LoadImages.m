clear all; close all; clc;

%%% METADATA %%%%
root   = "..//imagenes//";                % Root directory where images are stored
images = ["atypical","typical","mid"];  % List of names of images
NumPhotos = 6;                          % Number of Original images for each Class
Height    = 320;                        % Desired Height
Width     = 240;                        % Desired Width 

%%% LOAD IMAGES IN A TENOSR %%%%
for i=1:1:length(images)                % Iterate over size of image class
    eval(sprintf('A%d = zeros(%d,%d,3,%d);;', i,Height,Width,NumPhotos )); % Create Tensor to store images
    for j=1:1:6                                                            % Iterate over image number 
           path = root  + images(i) + "0" + string(j) + ".jpeg";            % Recunstruct image path
           A = imread(path);                                               % Load Image
           A = imresize(A,[Height, Width]);                                      % Resize image 
           eval(sprintf('A%d(:,:,:,%d)= uint8(A) ;', i,j));                      % Save image in tensor
    end
end


%%%% Interpolation of Images %%%%
Time = [0,0.01,0.02,0.03,0.04,0.05];  % Time stamp for original Images 
ti=0:0.001:0.05;                      % Interpolation Time 

for i=1:Height       % Iterate over image size
    for j=1:Width    % Iterate over width
        for c=1:3    % Iterate over Channel
            aux2=[A1(i,j,c,1),A1(i,j,c,2),A1(i,j,c,3),A1(i,j,c,4),A1(i,j,c,5),A1(i,j,c,6)];
            A1_inter(i,j,c,:)= uint8(interp1(Time,double(aux2),ti,'pchip'));
        end
    end
end

for i=1:Height
    for j=1:Width  
        for c=1:3
            aux2=[A2(i,j,c,1),A2(i,j,c,2),A2(i,j,c,3),A2(i,j,c,4),A2(i,j,c,5),A2(i,j,c,6)];
            A2_inter(i,j,c,:)= uint8(interp1(Time,double(aux2),ti,'pchip'));
        end
    end
end

for i=1:Height
    for j=1:Width  
        for c=1:3
            aux2=[A3(i,j,c,1),A3(i,j,c,2),A3(i,j,c,3),A3(i,j,c,4),A3(i,j,c,5),A3(i,j,c,6)];
            A3_inter(i,j,c,:)= uint8(interp1(Time,double(aux2),ti,'pchip'));
        end
    end
end


figure(1)
for k=1:51
imshow(uint8(A1_inter(:,:,:,k))) % muestra la imagen
end


figure(2)
for k=1:51
imshow(uint8(A2_inter(:,:,:,k))) % muestra la imagen
end


figure(3)
for k=1:51
imshow(uint8(A3_inter(:,:,:,k))) % muestra la imagen
end
