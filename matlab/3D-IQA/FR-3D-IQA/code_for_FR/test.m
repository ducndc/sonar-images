img1 = imread('/home/duc/workspace/sonar-images/images/result/model_mine.png');
img2 = imread('/home/duc/workspace/sonar-images/images/result/mine1.png');

K = [0.05 0.05];
window = ones(8);
L = 100;
[mssim, ssim_map] = ssim (img1, img2);
mssim
imshow(ssim_map)