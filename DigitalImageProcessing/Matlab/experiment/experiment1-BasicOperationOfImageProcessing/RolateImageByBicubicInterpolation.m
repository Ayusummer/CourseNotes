close all;      % 关闭所有的Figure窗口
clc;                % 清除命令窗口的内容，对工作环境中的全部变量无任何影响
clear all;       % 清除工作空间的所有变量，函数，和MEX文件


lena=imread('E:/GithubProject/junior-lessons_second-term/DigitalImageProcessing/resource/pic/lena.jpg');

figure;
imshow(rotate(lena,45));
title("双三次插值旋转图像");