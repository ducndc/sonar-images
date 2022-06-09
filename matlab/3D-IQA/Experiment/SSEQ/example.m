
%1. Load the image, for example
    image        = imread('/home/duc/workspace/sonar-images/matlab/3D-SIR/map.stl');
    
%2. Call this function to calculate the quality score:
    qualityscore = SSEQ(image)