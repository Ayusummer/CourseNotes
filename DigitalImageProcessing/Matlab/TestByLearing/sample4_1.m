% 灰度n倍增强

clc;                % 清空命令行
close all;      % 关闭所有figure

data = imread('../resource/pic/lena.jpg');  

% 将原图在1号位上显示
subplot(2,2,1);
imshow(data);
title("原始图像");

% 将二值图像在2号位上显示
subplot(222);
bw1 = imbinarize(gdata); 
imshow(bw1);                                % 二值化
title("二值图像-imbinarize");
y = bw1(141:146, 255:255);
y;

% 添加总图标题
suptitle('灰度,二值处理');