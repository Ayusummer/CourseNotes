% 导入图片并显示原图
img = imread('E:/GithubProject/junior-lessons_second-term/DigitalImageProcessing/resource/pic/lena.jpg');
figure;
imshow(img);
title('lena原图');

% 计算原图长、宽、通道数
[row, col, ch] = size(img);  %输出目标的大小信息
d = [row, col]/2;
%求出旋转矩阵及其逆矩阵
x = pi/4;
R = [cos(x), -sin(x)
    sin(x), cos(x)];
R = R'; 
%计算显示完整图像需要的画布大小,mlnb5r 
cc = ceil(row*sin(x)+col*cos(x));     %向下取整
rr = ceil(row*cos(x)+col*sin(x));
dd = [rr cc]/2;
 
% 初始化目标画布
img2 = uint8(zeros(rr,cc,ch));
for k = 1:ch
    for i = 1:rr
       for j = 1:cc
          p = [i;j];
          pp = (R*(p-dd)+d);   %根据某点与旋转中心的距离找到原图中的位置
          mn = floor(pp);   %向下取整
          x = pp(1);
          y = pp(2);
          m = mn(1);
          n = mn(2);
          if m>=1 && m<row && n>=1 && n<col
              if x-m <= 0.5
                        x = m;
              else
                        x = m+1;
              end
              if y-n <= 0.5
                        y = n;
              else 
                        y = n+1;
              end                       %最邻近插值算法
            img2(i,j,k) = img(x,y,k);
          end
       end 
    end
end

% 显示图像
figure;
imshow(img2);
title('最邻近插值法逆时针旋转结果');
