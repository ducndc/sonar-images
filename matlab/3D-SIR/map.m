data = importdata ("../../map/xyz.txt", ' ', 0);
x = data(:,1);
y = data(:,2);
% 
z = data(:,3);

P = [x, y, z];

P = unique(P,'rows');
shp = alphaShape(P, 0.9);
zlim([-50 -40]);
h = plot(shp);

[T, R] =  boundaryFacets(shp);
stlwrite(triangulation(T,R),'map.stl')