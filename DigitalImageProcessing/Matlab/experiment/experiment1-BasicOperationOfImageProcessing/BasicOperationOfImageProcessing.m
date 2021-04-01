
% 将图像读取为一个矩阵
%data = imread('E:/GithubProject/junior-lessons_second-term/DigitalImageProcessing/resource/pic/lena.jpg');
 data = imread('../resource/pic/lena.jpg');  




% 显示data当前值
data;


% 创建2行2列的子图,并将读取的图在1号位上显示
subplot(221);
imshow(data);
title("RGB图像");

% 灰度化处理
gdata = rgb2gray(data);
% 将灰度图像在2号位上显示
subplot(222);
imshow(gdata);
title("灰度图像");

% 二值化
n = graythresh(gdata);
subplot(223);
bw=im2bw(data,n);
imshow(bw);
title("二值图像-im2bw");

subplot(224);
bw1 = imbinarize(gdata); 
imshow(bw1);
title("二值图像-imbinarize");


% 添加总图标题
suptitle('灰度,二值处理');

% 保存图像
%保存当前窗口的图像
saveas(gcf,...
'E:\GithubProject\junior-lessons_second-term\DigitalImageProcessing\output\Matlab\实验1-图像处理的基本操作\灰度,二值处理.png'); 

