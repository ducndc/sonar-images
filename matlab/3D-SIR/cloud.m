data = importdata ("../../map/xyz.txt", ' ', 0);
x = data(:,1);
y = data(:,2);
% 
z = data(:,3);

value = data(:,4); 
ptCloud = pointCloud([x(:),y(:),z(:)],'Intensity',value(:));
% 
pcshow(ptCloud);

% P = [x, y, z];
% P = unique(P,'rows');
% shp = alphaShape(P, 4);
% zlim([-500 -490]);
% h = plot(shp);
% [T, R] =  boundaryFacets(shp);
% stlwrite(triangulation(T,R),'map.stl')
