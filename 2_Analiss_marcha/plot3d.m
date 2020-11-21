clc; clear all; close all;
path =  "position_vectors\Victor.xlsx"
Data = xlsread(path);
MassX	   = Data(:,1);
MassY	   = Data(:,2);
MassZ	   = Data(:,3);
RightHipX  = Data(:,4);
RightHipY  = Data(:,5);	
RightHipZ  = Data(:,6);
RightKneeX = Data(:,7);	
RightKneeY = Data(:,8);	
RightKneeZ = Data(:,9);	
RightAnkleX= Data(:,10);
RightAnkleY= Data(:,11);
RightAnkleZ= Data(:,12);	
LeftHipX   = Data(:,13);
LeftHipY   = Data(:,14);
LeftHipZ   = Data(:,15);
LeftKneeX  = Data(:,16);
LeftKneeY  = Data(:,17);
LeftKneeZ  = Data(:,18);	
LeftAnkleX = Data(:,19);
LeftAnkleY = Data(:,20);
LeftAnkleZ = Data(:,21);

%%%% 3D plot %%%%

for i=1:length(MassZ)
    cla(gca);
    %%% Right %%%
    plot3([MassX(i), RightHipX(i)], [MassY(i), RightHipY(i)], [MassZ(i), RightHipZ(i)], 'b-');
    hold on 
    plot3([RightHipX(i), RightKneeX(i)], [RightHipY(i), RightKneeY(i)], [RightHipZ(i), RightKneeZ(i)], 'b-');
    hold on 
    plot3([RightKneeX(i), RightAnkleX(i)], [RightKneeY(i), RightAnkleY(i)], [RightKneeZ(i), RightAnkleZ(i)], 'b-');
    
    %%% Left %%%
    plot3([MassX(i), LeftHipX(i)], [MassY(i), LeftHipY(i)], [MassZ(i), LeftHipZ(i)], 'r-');
    hold on 
    plot3([LeftHipX(i),LeftKneeX(i)], [LeftHipY(i), LeftKneeY(i)], [LeftHipZ(i),LeftKneeZ(i)], 'r-');
    hold on 
    plot3([LeftKneeX(i), LeftAnkleX(i)], [LeftKneeY(i), LeftAnkleY(i)], [LeftKneeZ(i), LeftAnkleZ(i)], 'r-');
    set(gca,'XLim',[0,1000],'YLim',[0,1000],'ZLim',[0,1000])
    xlabel("X");
    ylabel("Y");
    zlabel("Z");
    view(0,80);
    grid on;
    drawnow
    pause(0.1);
    

end

