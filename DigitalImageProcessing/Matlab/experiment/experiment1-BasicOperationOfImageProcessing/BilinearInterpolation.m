function [output] = BilinearInterpolation(src,K)
% 双线性插值插值
% 输入：源图像src，放大倍数K
% 输出：目标图像矩阵dst
 
[srcM,srcN,srcC]=size(src);             % 源图像元素点的行列数及色板数
dstM=round(K*srcM);                     % 该处仍要确保当放大倍数K非整数时目标图像大小为整数
dstN=round(K*srcN);
 
% 使用class将数据类型统一，目标图像初始化
dst=ones(dstM,dstN,srcC,class(src));
 
% 逐像素点赋值
for dstX=1:dstM
    for dstY=1:dstN
        for dstC=1:srcC
            srcX=floor(dstX/K);             % 最近邻左上方像素点位置
            srcY=floor(dstY/K);
            u=dstX/K-srcX;
            v=dstY/K-srcY;
            a=(1-u)*(1-v);                         % 最近邻四点的加权系数
            b=u*(1-v);      
            c=(1-u)*v;
            d=u*v;
            srcX(srcX+1>srcN)=srcN-1;       % 防止索引源图像界外位置
            srcX(srcX<1)=1;                             % 这种函数对比if_else耗时较长但简洁
            srcY(srcY+1>srcM)=srcM-1;
            srcY(srcY<1)=1;
                        dst(dstX,dstY,dstC)=a*src(srcX,srcY,dstC)+b*src(srcX+1,srcY,dstC)+c*src(srcX,srcY+1,dstC)+d*src(srcX+1,srcY+1,dstC);
        end
    end
end
output=dst;
end

