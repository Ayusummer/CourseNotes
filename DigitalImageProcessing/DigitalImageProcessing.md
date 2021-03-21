<!--
 * @Author: your name
 * @Date: 2021-03-12 15:20:33
 * @LastEditTime: 2021-03-20 10:41:37
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\数字图像处理\DigitalImageProcessing.md
-->
# 资料分享(持续更新)
- [英文第四版笔记<iCloud>](https://www.icloud.com/iclouddrive/0n1hoYXE5HSN8I8yj7kkNglMw#Digital_Image_Processing_4th_Edition_%5BRafael_C._Gonzalez%5D)
- [教材笔记<OneDrive>](https://1drv.ms/u/s!Agvl5Ir7iUevllq25QUUhc0-M9MZ?e=g8vsS8)
- [课堂PPT笔记<OneDrive><PDF文件>](https://1drv.ms/b/s!Agvl5Ir7iUevlmClzv3bGbV7SRDA?e=R6BNoB)
- [[课堂PPT笔记<OneDrive><.goodnotes文件>]](https://1drv.ms/u/s!Agvl5Ir7iUevlmEZBUZP263AFXKZ?e=w9c4L4)
> - OneDrive如果实在打不开的话可能需要魔法(
> - 有意向协作编辑的话可以私信我获取编辑权限


---
# 基本概念

## 调色板(Palette)
- [参考链接@CSDN:_古怪](https://blog.csdn.net/shen_gan/article/details/8114285)

  ---
- 真彩图像虽然是目前的主流图像,但在实际应用中仍然有一些其他彩色图像在使用,这些图像的图像数据一般不是像素值,需要查颜色表才能找到真正的像素值;颜色表又称调色板或颜色查找表
- **引入调色板的目的是为早期图像节省显示缓冲区空间**
  ![20210320103108](http:qpokg4i30.hn-bkt.clouddn.com/img/20210320103108.png)
  - `假设`上图是一个长宽各为240个像素,颜色数为16色的彩色图像
    - 每个颜色都用RGB来直接表示的话,由于RGB每个分量都有256个级别,要用8位(bit)即1字节(byte)表示,每个像素用3byte,整个图像需要$240 \times 240 \times 3 \approx 168KB$显示缓存空间
    - 若用调色板的方法,就能用一个16行24位(24=8*3)的表,每行记录一种颜色的RGB值;16种状态可以用4位二进制数表示,所以一个像素用0.5byte(=4bit),整个图像用$240 \times 240 \times 0.5 \approx 28KB$,占用的字节数约为前面的1/6