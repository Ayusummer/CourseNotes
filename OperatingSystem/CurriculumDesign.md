# 使用信息门户账密和网线使用校园网

- 打开自己座位上学校的电脑,打开命令行输入`ipconfig/all`
  - 记录下`ip`,`默认网关`,`首选DNS服务器`
- 把学校电脑的网线拔掉插到自己电脑上
- 点击右下角的网络图标,点击最上面的有线网图标,再点网络图标
  - ![](../res/img/杂项/网路图标.png)
  - ![](../res/img/杂项/有线网图标.png)
  - ![](../res/img/杂项/以太网图标.png)
- 找到`IP设置`,点击`编辑`,选择`手动`,按照刚才记录的座位上台式机的`ip`,`默认网关`,`首选DNS服务器`进行配置
  - ![](../res/img/杂项/IP设置.png)
  - ![](../res/img/杂项/IP配置.png)
- 随便打开一个浏览器网页,会弹出登录界面,用信息门户账密登录即可

---

# CentOS7 操作

---

## 进入管理员模式

```
su root
```

---

## 安装 vmware-tools

- [CentOS7 安装 VMware Tools](https://blog.csdn.net/zhujing16/article/details/88677253)
- ![](../res/img/OperatingSystem/课设-安装VMTools-1.png)
- ![](..)

---

## 分布式编译

- [CentOS 64 位系统进行 Hadoop2.3.0 本地编译及完全分布式集群的部署](https://my.oschina.net/TaoPengFeiBlog/blog/795191)

---

# 概述

- 课程设计任务有 5 个题目，每人完成一个题目，5 名完成不同题目的同学组成一组，需要联调。各自组合，班长负责协调。
- 一组 5 人：分别完成 5 个不同课题，分别编译调试通过后，再合起来编译调试。
- 时间：18 周周一 5-8 节-18 周周日 5-8 节-19 周周一 5-6 节，具体见上表

---

# PDF

---

## 提纲

- 课程目标
- 对应专业毕业要求指标点
- 可选的题目
- 课程设计要求完成的工作
- 其他要求
- 考核材料
- 考核要求及权重
- 组织方式

---

## 1.课程目标

---

### 知识方面

- 掌握操作系统功能模块的设计与实现方法

---

### 能力与素质方面

- 能够在阅读和分析开源操作系统的基础上，对其进行功能模块划分；能够指出现有功能模块的不足，并能够通过文献的研究给出解决方案。
- 能够完成操作系统功能模块的设计、实现与测试，同时在设计操作系统功能模块中，能体现**优化**和**创新**意识。
- 能够制定合理的实验方案及对实验结果进行分析并得出结论，针对实验结果分析解决过程的影响因素，论证解决方案的合理性，以获得有效结论。
- 能够根据设计任务和要求**组成团队**，分工协作，并能承担个体、团队成员以及负责人的角色。
- 能够用口头和书面方式清晰表述设计原理及相关概念与原理，包括陈述发言，清晰表达和回应指令。
- 能够撰写比较规范的课程设计报告

---

## 2.对应专业毕业要求指标点

- `毕业要求3.4`：能够借助文献研究，分析计算机领域复杂工程问题的解决过程的影响因素，论证解决方案的合理性，以获得有效结论。
- `毕业要求4.2`：根据计算机专业技术知识，能够有效地实施单体设计，并具有创新意识。
- `毕业要求9.2`：理解团队管理模式，能够承担承担个体、团队成员以及负责人的角色
- `毕业要求10.3`：能够就计算机领域复杂工程问题与社会公众和同行进行有效交流和沟通，包括陈述发言、清晰表达和回应指令。

---

## 3.可选的题目

- 基础
  - 安装虚拟机：Vmware、Vmware palyer (free)（推荐）、Virtualbox（推荐）、VMLite、Xen、Virtuozzo、KVM
  - 安装和使用 Linux（推荐 Centos 或 SUSE）（注意包含`内核源码`和`内核开发工具`等）
  - Linux 内核重编和配置
- 使用环境
  - 自己的笔记本
  - 学院的云计算系统：chrome 浏览器 202.195.167.230 test testest
    > 这个用不了,用户被锁定了

---

### 题目 1:新增 Linux 系统调用

- 采用编译内核法，在 Linux 中增加一个系统调用。
- 要求
  - （1）系统调用实现的功能：计算一个数字的三次方，并打印出来。
  - （2）另外写一个程序进行调用。

---

### 题目 2:实现基于模块的文件系统

- 修改 ext3 或 ext4 的源代码，实现新的文件系统。
- 要求：
  - （1）复制 ext3 或 ext4 的源代码，修改 Makefile 文件，使用模块编译方式，需要重新编译 Linux 内核
  - （2）可以动态加载和卸载新的文件系统
  - （3）至少需要修改文件系统的名称，最好能对文件写操作向系统后台打印出信息。

---

### 题目 3:新增 Linux 驱动程序

- 增加一个驱动程序（使用内存模拟设备），使用模块编译方式。
- 要求：
  - （1）可以动态加载和卸载新的驱动。
  - （2）通过程序或命令行使用该驱动。
  - （3）至少能通过该驱动保存 256MB 的数据，还能将这些数据读取出来。
  - （4）要重新编译 Linux 内核，可模仿 ramdisk 的实现方式。

---

### 题目 4:统计 Linux 系统缺页的次数

- 通过在 Linux 内核中自建变量，并利用/proc 文件系统作为中介的方法，统计系统缺页的次数
- 要求：
  - （1）在内核中实现缺页次数统计；
  - （2）编译并安装新内核；
  - （3）新建内核模块，并加载到新内核，通过/proc 实现用户态下查看缺页次数

---

### 题目 5:进程/线程通信

- 利用进程/线程间通信编写程序实现阅览室问题，实现多个读者进程注册、阅读、注销的过程，假设阅览室共有 5 个座位。
- 要求
  - （1）使用信号量机制和共享存储区机制来实现多个进程/线程之间的通信，同时实现注册与注销的互斥操作。
  - （2）注册操作要求读者进程填写个人手机或其他身份信息；注销操作要求读者撤销填写的个人信息。

---

## 4.课程设计要求完成的工作

- 要求
  - 文献查阅、自学与操作系统课程设计有关的资料、源码等内容，能够应用并试图改进。
  - 剖析开源操作系统的功能模块，并试图改进。
  - 通过对课程设计任务的综合分析完成给定设计任务的设计工作。
  - 完成课程设计任务的实现、调试与测试工作，并得到测试结果。
  - 根据设计要求综合现有实验环境，制定合理的实验方案。
  - 完成对实验结果的分析，并就设计的有效性和相关性能指标得出结论。
  - 用口头和书面方式对与设计内容相关的概念、原理和设计方法进行表述。
  - 正确回答与课程设计相关的概念、原理和设计方法等方面的问题。
  - 完成设计报告的整理与撰写工作。

---

## 5.其他要求

- 加强过程监控，考勤和平时表现将纳入考核指标。
- 鼓励交流、合作，但每位同学要独立完成自己承担的工作。
- 通过答辩方式检查学生设计情况，考核学生基本概念、基本原理和设计方法掌握情况，以及交流和口头表达能力。
- 按照规范撰写课程设计报告，课程设计报告包括封面、设计目的与要求、设计内容、设备与环境、设计思想、主要数据结构和流程，实验测试结果及结果分析，课程设计总结，并附源程序清单和课程设计答辩记录

---

## 6.考核材料

- 现场检查
  - 陈述
  - 交流
  - 回答问题
  - 程序演示
- 程序
- 课程设计报告

---

## 7.考核要求及权重

- ![](../res/img/OperatingSystem/课设-考核要求及权重.png)

---

## 8.组织方式

- 分组进行
- 选择不同题目的 5 名同学组成一组
- 定期交流每人进展
- 互相了解各自任务
- 融合构成大题目

---

## 9.作业提交方式

`程序检查结束后`：

- 每位同学提交一个压缩文件，里面包含 2 个文档：`源代码`和课程设计`报告的电子文档`。
  - 文件命名规则：`班级+姓名+学号.rar`
- 同时提交报告纸质版。

---

## 额外

```
        自信
        积极
       多思考
      多问度娘
  如果可以问google
       勤动手
```

---

# 随笔

---

## VSCode 连接虚拟机失败

- 因为我原本连接过以前的机子且虚拟机 IP 相同,已经生成了密钥,所以再次连接时默认使用该 ip 对应密钥,自然就失败了
- 解决方法:删除`C:\Users\233\.ssh\known_hosts`中对应 ip 所在行

---

## 更新内核至 4.14.160

- 安装`wget`

```
yum -y install wget
```

- 下载内核

```
cd /usr/src
wget https://mirrors.edge.kernel.org/pub/linux/kernel/v4.x/linux-4.14.160.tar.xz
```

```
cd /usr/src
wget https://mirrors.tuna.tsinghua.edu.cn/kernel/v3.x/linux-3.2.58.tar.xz
```

---

- 解压内核源码

```
tar -xvf linux-4.14.160.tar.xz
```

```
tar -xvf linux-3.2.58.tar.xz
```

---

- 安装依赖软件包

```
yum -y install gcc ncurses-devel bison flex bc elfutils-libelf-devel openssl-devel
```

---

- 编写系统调用入口表
- 4.打开该文件增添该行

```
333 common  mycall          sys_mycall
```

![](../res/img/OperatingSystem/课设-增加个人命令.png)

---

- 5.编写系统调用函数声明

```
asmlinkage long sys_mycall(int number);
```

![](../res/img/OperatingSystem/课设-编写系统调用函数声明.png)

---

- 6.实现系统调用函数

```
SYSCALL_DEFINE1(mycall,int,number){
		int result=number*number*number;
		printk("The result is %d\n",result);
		return 0;
    }
```

![](../res/img/OperatingSystem/课设-实现系统调用函数.png)

---

- 7.重新编译内核

```
cd linux-4.14.160/        #进入内核文件夹
chmod +x ./scripts/gcc-version.sh    #增加文件可执行权限
make mrproper               #删除以前编译产生的垃圾文件
make clean
cp /boot/config-* .config   #*为原内核版本，可用Tab补全
make menuconfig             #上下左右键选择Load和Save保存再Exit退出。
make -j 4     #编译内核，这一步时间很长很长很长很长……
make modules_install        #安装模块
make install                #安装内核
```

---

## Github 1/3/4

- 安装`wget`

```
yum -y install wget
```

---

- 下载内核

```
cd /usr/src
wget https://mirrors.tuna.tsinghua.edu.cn/kernel/v3.x/linux-3.2.58.tar.xz
```

---

- 解压内核源码

```
tar -xvf linux-3.2.58.tar.xz
```

---

- 修改内核源码，添加全局统计变量

```
cd linux-3.2.58/
```

- `linux-3.2.58/arch/x86/mm/fault.c`

```
# 在do_page_fault函数上一行添加全局变量
// 997 行
unsigned long volatile pfcount;
```

- `linux-3.2.58/include/linux/mm.h`

```
# 声明全局变量在extern int page_cluster后
// 35行
extern unsigned long volatile pfcount;
```

- `linux-3.2.58/kernel/kallsyms.c`

```
# 文件最后一行添加
EXPORT_SYMBOL(pfcount);
```

---

### 编译新内核

```
cd /usr/src/linux-3.2.58/
make menuconfig
```

- 保证窗口足够大从而可以打开 UI
- 如果报错缺少`ncurses-devel`的话

```
yum install ncurses-devel
```

---

```
# 编译
# j后面的数字代表用几个核心来编译，根据实际情况选择。
# 这一步根据电脑情况，需要1-2小时不等
make -j8
# 模块安装
make modules_install
# 安装
make install
# 重启
reboot
```

---

## 题目 4CSDN

### 下载内核

```
cd /usr/src
wget https://mirrors.edge.kernel.org/pub/linux/kernel/v3.x/linux-3.10.11.tar.xz
```

---

### 解压内核源码

```
tar -xvf linux-3.10.11.tar.xz
```

---

### 修改源码

```
cd linux-3.10.11/
```

- `linux-3.10.11/arch/x86/mm/fault.c`

```
# 在do_page_fault函数上一行添加全局变量
// 997 行
unsigned long volatile pfcount;
```

- `linux-3.2.58/include/linux/mm.h`

```
# 声明全局变量在extern int page_cluster后
// 35行
extern unsigned long volatile pfcount;
```

- `linux-3.2.58/kernel/kallsyms.c`

```
# 文件最后一行添加
EXPORT_SYMBOL(pfcount);
```

---

```
cd /usr/src
wget https://mirrors.tuna.tsinghua.edu.cn/kernel/v3.x/linux-3.10.1.tar.xz
```
