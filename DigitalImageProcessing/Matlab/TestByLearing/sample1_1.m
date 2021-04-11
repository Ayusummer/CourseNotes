% 灰度,二值处理
clc;                % 清空命令行
close all;      % 关闭所有figure

data = imread('../resource/pic/lena.jpg');  

% 将灰度图像在1号位上显示
gdata = rgb2gray(data);              % 灰度化处理
subplot(121);
imshow(gdata);
title("灰度图像");

% 将二值图像在2号位上显示
subplot(122);
bw1 = imbinarize(gdata); 
imshow(bw1);                                % 二值化
title("二值图像-imbinarize");
y = bw1(141:146, 255:255);
y;

% 添加总图标题
suptitle('灰度,二值处理');