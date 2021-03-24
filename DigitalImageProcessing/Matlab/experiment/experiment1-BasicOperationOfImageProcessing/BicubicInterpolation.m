function [output]=BicubicInterpolation(src,K)

% 输入：源图像src，放大倍数K
% 输出：目标图像矩阵dst
 
[srcM,srcN,srcC]=size(src);         % 源图像元素点的行列数及色板数
dstM=round(K*srcM);                 % 该处仍要确保当放大倍数K非整数时目标图像大小为整数
dstN=round(K*srcN);
 
% 使用class将数据类型统一，目标图像初始化
dst=ones(dstM,dstN,srcC,class(src));
 
% 逐像素点赋值
for dstX=1:dstM
    for dstY=1:dstN
            X=dstX/K;
            Y=dstY/K;
            if X<2||X>srcN-2||Y<2||Y>srcM-2     % 在边界采用最近邻插值
                for dstC=1:srcC
            srcX=round(dstX/K);
            srcY=round(dstY/K);
            srcX(srcX>srcN)=srcN;                       % 防止索引源图像界外位置,该函数很耗时但简洁
            srcX(srcX<1)=1;
            srcY(srcY>srcM)=srcM ;
            srcY(srcY<1)=1;
            dst(dstX,dstY,dstC)=src(srcX,srcY,dstC);
                end
            else            %非边界位置采用双三次插值
                srcX=floor(X);%最近邻左上方像素点位置
                srcY=floor(Y);
                v=X-srcX;
                u=Y-srcY;
                X1=zeros(4,4);  X2=zeros(4,4);  %距离矩阵
                W1=ones(4,4); W2=ones(4,4);    %系数矩阵
                for i=1:4
                    for j=1:4
                        X1(i,j)=abs(v-i+2);
                        X2(i,j)=abs(u-j+2);
                        if X1(i,j)<=1
                            W1(i,j)=1.5*(X1(i,j))^3-2.5*(X1(i,j))^2+1;
                        else
                            if  X1(i,j)<2
                                W1(i,j)=(-0.5)*(X1(i,j))^3+2.5*(X1(i,j))^2-4*X1(i,j)+2;
                            else
                                W1(i,j)=0;
                            end
                        end
                        if X2(i,j)<=1
                            W2(i,j)=1.5*(X2(i,j))^3-2.5*(X2(i,j))^2+1;
                        else
                            if  X2(i,j)<2
                                W2(i,j)=(-0.5)*(X2(i,j))^3+2.5*(X2(i,j))^2-4*X2(i,j)+2;
                            else
                                W2(i,j)=0;
                            end
                        end
                    end
                end
                W=W1.*W2;
                Z=ones(4,4);  %16个源像素点矩阵
                O=ones(4,4);  %16个加权后的源像素点矩阵
                for dstC=1:srcC
                    for i=1:4
                        for j=1:4
                            Z(i,j)=src(srcX-1+i-1,srcY-1+j-1,dstC);
                            O(i,j)=W(i,j).*Z(i,j);
                        end
                    end
                    O1=sum(sum(O));
                    dst(dstX,dstY,dstC)=O1;
                end
            end
    end
end
output=dst;
end

