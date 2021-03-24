function [dst]=NearestInterpolation(src,K)
% 最近邻法插值
% 输入：源图像src，放大倍数K
% 输出：目标图像矩阵dst

[srcM,srcN,srcC]=size(src);     % 读取源图像元素点的行列数及色板数
dstM=round(K*srcM);             % 该处仍要确保当放大倍数K非整数时目标图像大小为整数
dstN=round(K*srcN);
 
% 使用class将数据类型统一，目标图像初始化
dst=ones(dstM,dstN,srcC,class(src));
 
% 逐像素点赋值
for dstX=1:dstM 
    for dstY=1:dstN
        for dstC=1:srcC
            srcX=round(dstX/K);
            srcY=round(dstY/K);
            srcX(srcX>srcN)=srcN; % 防止索引源图像界外位置,该函数很耗时但简洁
            srcX(srcX<1)=1;
            srcY(srcY>srcM)=srcM ;
            srcY(srcY<1)=1;
            dst(dstX,dstY,dstC)=src(srcX,srcY,dstC);
        end
    end
end
end

