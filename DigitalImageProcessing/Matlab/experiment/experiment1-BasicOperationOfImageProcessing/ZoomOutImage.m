close all;      % 关闭所有的Figure窗口
clc;                % 清除命令窗口的内容，对工作环境中的全部变量无任何影响
clear all;       % 清除工作空间的所有变量，函数，和MEX文件

lena=imread('E:/GithubProject/junior-lessons_second-term/DigitalImageProcessing/resource/pic/lena.jpg');

% 显示原图
figure;
imshow(lena);
title("lena原图");


% 自定义最邻近插值缩小一半
figure;
py.print("自定义最邻近插值:")
tic
imshow(NearestInterpolation(lena,0.5));
toc
title("自定义最邻近插值缩小一半");


% Matlab的imresize函数
figure;
py.print("Matlab的imresize函数:")
tic
imshow(imresize(lena,0.5,'nearest'));
toc
title("Matlab的imresize函数")

% 自定义的双线性插值算法
figure;
py.print("自定义的双线性插值:");
tic
imshow(BilinearInterpolation(lena,0.5));
toc
title("自定义的双线性插值")

% 自定义的双三次插值
figure;
py.print("自定义的双三次插值:");
tic
imshow(BicubicInterpolation(lena,0.5));
toc
title("自定义的双三次插值")



