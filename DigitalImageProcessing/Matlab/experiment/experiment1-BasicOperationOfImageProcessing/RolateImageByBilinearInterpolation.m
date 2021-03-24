% 以图像中心为中心旋转
theta=30;                              % 自定义旋转角度，顺时针
angle=theta*pi/180;
a= cos(angle);
b= sin(angle);
rotation=[a,-b;b,a];            % 顺时针旋转矩阵
% rotation=[a,b;-b,a];       % 逆时针旋转矩阵
 
A=imread('E:/GithubProject/junior-lessons_second-term/DigitalImageProcessing/resource/pic/lena.jpg');      
h=size(A,1);
w=size(A,2);
A= double(A);                     % 为了便于后面的计算，这里强制转换为double型，原图像为uint8型
newh=round(h*a+w*b);    % 重新计算旋转以后的窗口的长和宽
neww=round(h*b+w*a);
 
for x = 1 : neww
   for y = 1 : newh
        t = rotation * [ y - newh / 2; x - neww / 2 ] + [ h / 2; w / 2 ];%t是一个两行一列的坐标矩阵，记录旋转后图像返回到原图中所在的位置
        %继续上行的注释：等式后面的是我已经计算简化后的表示，中间过程大家可参考我那篇博文，动动笔计算一下就是我的结果
        if( t(1) >= 1 && t(2) >= 1 && t(1) <= h && t(2) <= w )%保证点落在原图内
            m = floor( t(1) );%m,n表示位置t最近且最小的点的下标
            n = floor( t(2) );%由于邻近像素点在x,y方向上的距离均为1，显然邻近的其余三个点分别为（m,n+1）,(m+1,n),(m+1,n+1)
         
            d1 = A( m + 1, n, : ) * ( t(1) - m ) + A(m, n, : ) * ( 1 +m - t(1) );%d1,d2分别表示两次加权和
            %这里的加权大家注意下，我们用的是某个点的颜色值乘以离它更远的那段距离，这样交错相乘，可以把P点如果有整数坐标的情况都包含进来，程序更具一般性
            d2 = A( m + 1,n + 1, : ) * ( t(1) - m) + A(m, n + 1, : ) * ( 1 + m - t(1) );
            d = d2 * ( t(2) - n ) + d1 * ( 1 + n - t(2) );%根据新算出来的d1,d2再做一次加权，得到最终四个点的加权和d
            B( y, x, : ) = round(d);%把d的最近整数赋给B的RGB值,B是我们旋转后的图
       
        end
    end
end
 
B= uint8(B);
imshow(B);
title("双线性插值旋转图像")
