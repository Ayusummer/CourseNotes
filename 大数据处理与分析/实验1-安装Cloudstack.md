# Cloudstack

[CloudStack 简介 - Jamin Zhang](https://jaminzhang.github.io/cloud-computing/CloudStack-Introduction/)

---

## 云计算

基本上，云计算只是一种把 IT 资源当作服务来提供的手段。

几乎所有 IT 资源都可以作为云服务来提供：应用程序、计算能力、存储容量、联网、编程工具，以至于通信服务和协作工具。

就最终用户而言，云计算意味着没有硬件购置成本、没有需要管理的软件许可证或升级、不需要雇佣新的员工或咨询人员、不需要租赁设施、没有任何种类的基建投资， 而且还没有隐性成本。只是一种用仪表测量出来的、根据使用情况支付的订购费或固定的订购费。只是用您所需的量，而且只按使用量付费。

![Cloud-Computing-Architecture](http://jaminzhang.github.io/images/Cloud-Computing/Cloud-Computing-Architecture.png)

---

## IaaS

[IaaS、PaaS、SaaS的区别 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/276054509)

[[技术深度\]云服务器IaaS的资源虚拟化 - 简书 (jianshu.com)](https://www.jianshu.com/p/55b03f2fea45)

---

IaaS、PaaS、SaaS 是云计算的三种主要类型;

|      |                         功能概述                         |                            示例                             |                      全称                       |
| :--: | :------------------------------------------------------: | :---------------------------------------------------------: | :---------------------------------------------: |
| IaaS | 基于云的服务，按需付费，<br> 用于存储，网络和虚拟化等服务 |                 AWS，阿里云，腾讯云，华为云                 | Infrastructure as a Service <br> 基础设施即服务 |
| PaaS |              Internet上可用的硬件和软件工具              | Microsoft Windows Azure，百度BAE、<br/> 新浪SAE、京东云擎JAE |      Platform as a Service <br> 平台即服务      |
| SaaS |             可通过互联网通过第三方获得的软件             |                       钉钉，企业微信                        |      Software as a Service <br> 软件即服务      |

![image-20210915091928167](http://cdn.ayusummer233.top/img/20210915091935.png)

IaaS 为用户提供了基于云的本地基础结构替代品，因此企业可以避免对昂贵的现场资源进行投资

![image-20210915092657640](http://cdn.ayusummer233.top/img/202109150926786.png)

IaaS 软件通常用于管理大规模的物理硬件(IaaS 可以管理小到一台物理主机，多到成千上万的物理服务器)并把客户所需的软硬件资源(CPU，内存，网络，存储等)以“主机”的形式提供;

IaaS 的根本就是将计算资源进行池化(不限于cpu,内存，网络), 这些资源被逻辑切割成更小的可管理单元,然后根据客户需要被灵活的组装成可运作的主机,很明显这里的主机并不是一台真的物理主机,而是虚拟机.这个虚拟机通常都会包含一个可以连上网络的操作系统,用户可以通过网络连接上虚拟主机并且能灵活的进行资源配置以及按照配置及时间来付费.而用户操作这台虚拟主机就像操作一台物理服务器一样,可以在上面安装软件,搭建数据库以及应用服务器,部署web应用.由于这些提供给用户的功能都是最基础的计算功能,所以这种服务形式也被称作基础架构及服务(IaaS)

---

## CloudStack 概述

[关于cloudstack，openstack，kubernetes三个开源云平台的架构演进思考 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/49523193)

[Kubernetes（k8s）中文文档 Kubernetes概述_Kubernetes中文社区](https://www.kubernetes.org.cn/k8s)

[CloudStack 简介 - Jamin Zhang](https://jaminzhang.github.io/cloud-computing/CloudStack-Introduction/)

---

CloudStack 是一个 IaaS 级的服务，IaaS 提供了对资源的自动化管理能力。 例如用界面、脚本甚至 Web Service API 实现对大量硬件、大量虚拟机的生命周期管理。
IaaS 产品面对的是大规模、可伸缩的云环境，这是与用手工管理有限资源的方式完全不同的一类系统。

- CloudStack 是一个开源的具有高可用性及扩展性的云计算平台。
- CloudStack 是一个开源的云操作系统，它可以帮助用户利用自己的硬件提供类似于 Amazon EC2 那样的公共云服务。
- CloudStack 可以通过组织和协调用户的虚拟化资源，构建一个和谐的环境。
- Cloudstack 支持管理大部分主流的 hypervisors(管理程序)，如 KVM，XenServer，VMware，Oracle VM，Xen 等。

> KVM(Kernel-based Virtual Machine 的简称，是一个开源的[系统虚拟化](https://baike.baidu.com/item/系统虚拟化)模块，自 Linux 2.6.20 之后集成在 Linux 的各个主要发行版本中。它使用 [Linux](https://baike.baidu.com/item/Linux/27050) 自身的调度器进行管理，所以相对于 [Xen](https://baike.baidu.com/item/Xen)，其核心源码很少。KVM 已成为学术界的主流 [VMM](https://baike.baidu.com/item/VMM) 之一。)

Cloudstack 部署架构:

![CloudStack-Architecture-and-Concepts](http://cdn.ayusummer233.top/img/202109150948407.png)

![region-overview](http://cdn.ayusummer233.top/img/202109150949283.png)

- `Zone`

  Zone 对应于现实中的一个数据中心，它是 CloudStack 中最大的一个单元。
  即从包含关系上来说，一个 Zone 包含多个 Pod，一个 Pod 包含多个 Cluster，一个 Cluster 包含多个 Host。

- `Pod` 提供点

  一个提供点通常代表一个机柜，机柜里面的主机在同一个子网，每个区域中必须包含一个或多个提供点，提供点中包含主机和主存储服务器，CloudStack 的内部管理通信配置一个预留 IP 地址范围。预留的 IP 范围对云中的每个区域来说必须唯一。

- `Cluster` 集群

  Cluster 是多个主机组成的一个集群。
  同一个 Cluster 中的主机有相同的硬件，相同的 Hypervisor(管理程序/管理员)，和共用同样的存储。
  同一个 Cluster 中的虚拟机，可以实现无中断服务地从一个主机迁移到另外一个上。
  集群由一个或多个宿主机和一个或多个主要存储服务器构成。
  集群的大小取决于下层虚拟机软件。大多数情况下基本无建议。
  当使用 VMware 时，每个 VMware 集群都被 vCenter 服务器管理。
  管理员必须在本产品中登记 vCenter。每个 Zone 下可以有多个 vCenter 服务器。每个 vCenter 服务器可能管理多个 VMware 集群。

- `Host` 主机

  Host 就是运行的虚拟机（VM）主机。

  宿主机就是个独立的计算机。宿主机运行来宾虚拟机并提供其相应的计算资源。
  每个宿主机都装有虚拟机软件来运行来宾虚拟机。
  比如一个开启了 kvm 支持的服务器，一个思杰 XenServer 服务器，或者一个 ESXi 服务器都可以作为宿主机。
  宿主机在 CloudStack 部署中属于最小的组织单元。
  宿主机包含于集群中，集群又属于提供点，而区域中包含提供点（就是在逻辑概念上 Zone>Pod>Cluster>Host ），
  新增的宿主机可以随时添加以提供更多资源给来宾虚拟机，CloudStack 自动探测宿主机的 CPU 数量和内存资源。
  宿主机对终端用户不可见。终端用户不能决定他们的虚拟机被分配到哪台宿主机。

- `Primary Storage` 一级存储

  一级存储与 Cluster 关联，它为该 Cluster 中的主机的全部虚拟机提供磁盘卷。一个 Cluster 至少有一个一级存储，且在部署时位置要临近主机以提供高性能。

- `Secondary Storage` 二级存储

  二级存储与 Zone 关联，它存储模板文件，ISO 镜像和磁盘卷快照。

---

# Linux 

---

## Ubuntu

### 查看版本信息

1. 方法1：使用命令： `cat /proc/version` 查看
2. 方法2：使用命令： `uname -a` 查看
3. 方法3：使用命令： `lsb_release -a` 查看

---

## CentOS

---

### 查看某软件包是否安装

[centos系统如何查看指定软件是否已安装-CentOS-PHP中文网](https://www.php.cn/centos/445574.html)

`yum` 方法安装的，可以用 `yum list installed` 查找，如果是查找指定包，命令后加 `| grep "软件名或者包名"`, 没有返回值就是没安装

> `grep`: Linux 系统中 grep 命令是一种强大的文本搜索工具，它能使用正则表达式搜索文本，并把匹配的行打印出来。grep全称是Global Regular Expression Print，表示全局正则表达式版本，它的使用权限是所有用户。
>
> [教你使用CentOS yum-CentOS-PHP中文网](https://www.php.cn/centos/465530.html)
>
> `yum install -y xxx` 中的 `-y` 用于默认 yes, 省略 yes 确认步骤

---

### 常用软件包

#### screen

[CentOS下screen 命令详解 - 用代码书写人生 - 博客园 (cnblogs.com)](https://www.cnblogs.com/webnote/p/5749675.html)

GNU Screen可以看作是窗口管理器的命令行界面版本。它提供了统一的管理多个会话的界面和相应的功能。

```shell
yum install screen -y
```



---

### Debug log

---

#### yum 命令报错: `Could not resolve host: mirrors.tencentyun.com; Unknown error`

[Could not resolve host: mirrors.tencentyun.com_user2025的博客-CSDN博客](https://blog.csdn.net/user2025/article/details/107733068)

原因：腾讯云服务器内网 yum 源的域名 mirrors.tencentyun.com 需要有内网的 DNS 才能访问，但是实际情况下，我们会根据需要修改 DNS，为了使用腾讯云内网快速稳定的内网源，我们需要把 DNS 恢复为内网 DNS，下面为各地区服务器 DNS 地址
解决办法：
（1）修改服务器的 DNS 配置文件：`/etc/resolv.conf` ，请参阅如下文档添加对应地区的内网 DNS 服务器

​          [云服务器 内网服务 - 产品简介 - 文档中心 - 腾讯云 (tencent.com)](https://cloud.tencent.com/document/product/213/5225)

> 我用的上海地域的轻量, 配上海或者上海金融的 DNS 都不对, 最后无奈重置实例才发现原来是配最后一个所有地域的那个 DNS
>
> ![image-20210916203841882](http://cdn.ayusummer233.top/img/202109162038974.png)

（2）重启网络服务

```shell
# 重启方式1：
/etc/init.d/network restart
#重启方式2：
systemctl restart network
```

>
>
>![image-20210916185305965](http://cdn.ayusummer233.top/img/202109161853077.png)
>
>部署 Cloudstack 前做网络桥接的时候把 DNS 改成了谷歌的这个所以重启网络后上图自动生成的配置中 DNS 就成这样了
>
>直接在上图这个文件中改的话重启网络后又会变回谷歌的这两个, 因此要在当初配网桥时候的配置里改:
>
>![image-20210916190504657](http://cdn.ayusummer233.top/img/202109161905823.png)
>
>这里需要注意的是最多支持三个 DNS, 一个首选两个备选, 因此这里将腾讯云的两个内网 DNS 设为首选, 谷歌的那个座位备选
>
>重启网络后可以看到配置自动更新了
>
>> PS: 图里的两个DNS对我的上海轻量不管用, 详见上文(应当配置适用于所有地域的内网DNS)
>
>---
>
>[linux 的/etc/resolv.conf文件最多支持多少DNS - Linux系统管理-Chinaunix](http://bbs.chinaunix.net/thread-3714518-1-1.html)

---

# CloudStack 部署

---

## CentOS 7.6 下的 Cloudstack 部署

[Quick Installation Guide — Apache CloudStack 4.15.1.0 documentation](http://docs.cloudstack.apache.org/en/4.15.1.0/quickinstallationguide/qig.html)

---

由于个人手头只有一台主力计算机且已经升级了 Windows11, 使用 WSL2 并由 Hyper-V 提供硬件虚拟化并且没有官方提供支持的 CentOS 分发, 为了减少变数, 降低安装成本, 减轻初次部署难度, 因此选择购买了一个轻量云应用服务器来配置官方部署教程中的环境并进行 Cloudstack 的部署

由于腾讯云的公有云镜像中 CentOS 只支持 CentOS8 与 CentOS7.6, 而官网的快速部署教程以 CentOS7.7 为例, 因此要先确定这份教程是适用于 CentOS7.6

CentOS 发行注记: [zh/Manuals/ReleaseNotes - CentOS Wiki](https://wiki.centos.org/zh/Manuals/ReleaseNotes)

CentOS7.6 发行注记: [zh/Manuals/ReleaseNotes/CentOS7.1810 - CentOS Wiki](https://wiki.centos.org/zh/Manuals/ReleaseNotes/CentOS7.1810)

![image-20210915110807525](http://cdn.ayusummer233.top/img/202109151108678.png)

CentOS7.7 发行注记: [zh/Manuals/ReleaseNotes/CentOS7.1908 - CentOS Wiki](https://wiki.centos.org/zh/Manuals/ReleaseNotes/CentOS7.1908)\

![image-20210915110824979](http://cdn.ayusummer233.top/img/202109151108077.png)

可以看到两个版本间的变动部分为 python3.6 的支持及 bind 和 chrony 的改版

由于 Cloudstack 的开发语言为 Java, 因此可以暂且认为 python3.6 的支持不会影响此次部署

bind 用于将域名翻译成 IP, 暂且认为不会影响到此次部署

chrony 用于做时间同步, 暂且认为不会影响到此次部署

综上, 只考虑更新不考虑降级的情况下 CentOS7.6 应该可以使用官网的快速部署教程部署 Cloudstack

> [openstack 和cloudstack之间的比较_从菜鸟到菜菜鸟-CSDN博客_cloudstack和openstack](https://blog.csdn.net/carolzhang8406/article/details/56480024)
>
> [BIND Installation On CentOS (howtoforge.com)](https://www.howtoforge.com/bind-installation-on-centos)
>
> [Centos使用chrony做时间同步 - 驴得水 - 博客园 (cnblogs.com)](https://www.cnblogs.com/lizhaoxian/p/11260041.html)

---

### 轻量服务器配置

![image-20210915111842049](http://cdn.ayusummer233.top/img/202109151118137.png)

![image-20210915111853994](http://cdn.ayusummer233.top/img/202109151118067.png)

![image-20210915113140602](http://cdn.ayusummer233.top/img/202109151131828.png)

---

### 先决条件

- [x] 至少一台计算机支持并启用了硬件虚拟化

  > 已经上了云服务器, 故满足要求

- [x] CentOS7.6 x86_64

  > ![image-20210915153357943](http://cdn.ayusummer233.top/img/202109151533049.png)

- [x] 一个网关位于 `xxx.xxx.xxx.1`  的 `/24` 网络，，该网络上不应有DHCP，并且任何运行 CloudStack 的计算机都不会具有动态地址。同样，这也是为了简单。

  > 云轻量有固定 ip, 故此项满足

---

### 环境

CentOS 7.6  

---

更新系统:

```shell
yum -y upgrade
```

![image-20210915155241846](http://cdn.ayusummer233.top/img/202109151552042.png)

---

#### 配置网络

安装 `brctl` 与 `net-tools`

```shell
yum install bridge-utils net-tools -y
```

> 先检查下是否已经安装了
>
> ![image-20210915204418620](http://cdn.ayusummer233.top/img/202109152044700.png)

![image-20210915204828274](http://cdn.ayusummer233.top/img/202109152048388.png)

- `brctl`

  [brctl命令 – 以太网网桥管理 – Linux命令大全(手册) (linuxcool.com)](https://www.linuxcool.com/brctl)

  brctl 命令用于设置、维护和检查 linux 内核中的以太网网桥配置。

  以太网网桥是一种设备，通常用于将以太网的不同网络连接在一起，以便这些以太网对参与者显示为一个以太网。所连接的每个以太网对应于网桥中的一个物理接口。这些单独的以太网被聚集成一个更大的（“逻辑”）以太网，这个更大的以太网对应于网桥网络接口

- `net-tools`

  Net-Tools 是一个 Linux 系统中基本的网络工具集，其集成了常用的网络管理命令“`ifconfig`、`netstat`、`arp`、`route` 等”

---

你应当以 root 身份登入控制台, 下面首先创建 Cloudstack 用于联网的桥

创建并打开 `/etc/sysconfig/network-scripts/ifcfg-cloudbr0`

> ip 寻址 - 在整个本文档中, 我们假设您有一个 `/24` 网络用于实现 Cloudstack; 这可以使任何 [RFC 1918](https://baike.baidu.com/item/RFC%201918/1528155) 网络; 但是我们料想到你可能会使用我们的机器地址来配置网络, 所以在这里声明我们在本篇中会使用 `172.16.10.2` 作为网络地址, 如果您的网络为 `192.168.55.0/24` 的话你应当使用 `192.168.55.2` 作为您的网络地址
>
> > RFC 1918私有网络地址分配 (Address Allocation for Private Internets)
> >
> > [局域网使用的IP地址范围_张小帅的专栏-CSDN博客](https://blog.csdn.net/qinghezhen/article/details/27882951)
> >
> > 局域网可用的IP地址范围为: 
> >
> > ```shell
> > A类地址：10.0.0.0 - 10.255.255.255 
> > B类地址：172.16.0.0 - 172.31.255.255 
> > C类地址：192.168.0.0 -192.168.255.255 
> > ```
> >
> > 以上IP是都是属于局域网，但不一定是同一个局域网。要检测两台电脑是否在同一个局域网，可以再一台电脑上ping另外一台电脑的IP.能ping通的就是在同一个局域网中。
> >
> > PS: 个人实验中使用了云服务器, 边使用了相应的内网地址 `10.x.x.x`

```shell
#【ifcfg-cloudbr0】，原本没有这个文件
DEVICE=cloudbr0     # 网卡设备名称   
TYPE=Bridge         # 网卡类型为网桥
ONBOOT=yes          # 启动时是否激活 yes | no  
BOOTPROTO=static    # 协议类型为静态协议   (dhcp bootp none)
IPV6INIT=no
IPV6_AUTOCONF=no
DELAY=5
IPADDR=172.16.10.2  # 网络IP地址(这里写的是官方的示例, 需要根据个人设备网络 ip 填写同网段地址)
GATEWAY=172.16.10.1 # 网关地址(上一条的第 4 段改成 1 即可)
NETMASK=255.255.255.0
DNS1=8.8.8.8
DNS2=8.8.4.4
STP=yes
USERCTL=no
NM_CONTROLLED=no
```

> [linux 网络配置 (配置/etc/sysconfig/network-scripts/ifcfg-ethx) - blue鹰 - 博客园 (cnblogs.com)](https://www.cnblogs.com/blueying/p/3976502.html)
>
> 8.8.8.8是一个[IP地址](https://baike.baidu.com/item/IP地址)，是Google提供的免费[DNS服务器](https://baike.baidu.com/item/DNS服务器)的IP地址，Google提供的另外一个免费DNS服务器的IP地址是：8.8.4.4 。用户可以使用Google提供的[DNS](https://baike.baidu.com/item/DNS/427444)服务器上网。
>
> > 关于 BOOTPROTO: 
> >
> > [centos设置BOOTPROTO none和dhcp有什么区别_周二也被占用-CSDN博客](https://blog.csdn.net/u011350541/article/details/78224872)
> >
> > ```shell
> > none表示使用静态IP，自行配置; 
> > dhcp表示使用动态IP，自行生成
> > ```
> >
> > 如果自己有内网的IP地址，最好设置成dhcp自己指定ip地址
> >
> > 还有个onboot=yes或onboot=no的配置
> > 意思是是否系统启动是自动激活网卡，一般设置为yes

保存配置并退出.

打开接口配置文件 `/etc/sysconfig/network-scripts/ifcfg-eth0` 并按照如下配置

```shell
TYPE=Ethernet
BOOTPROTO=none
DEFROUTE=yes
NAME=eth0
DEVICE=eth0
ONBOOT=yes
BRIDGE=cloudbr0
# HWADDR(又名 MAC 地址或 UUID) 不用改
```

> 接口名仅为用例, 请使用默认的以太网口名称替换上述配置项中的 etho
>
> > 也即你的配置项文件名称不一定为 `ifcfg-eth0`
>  
> [网卡配置文件里DEFROUTE="yes"是什么东西？ - Linux新手园地-Chinaunix](http://bbs.chinaunix.net/thread-4185395-1-1.html)
>
> ```shell
> DEFROUTE=answer, 这里answer取下列值之一：
> yes -- 将该接口设置为默认路由。
> no -- 不要将该接口设置为默认路由
> ```

现在已经正确设置了配置文件, 我们需要运行几个命令来启动网络

```shell
systemctl enable network

systemctl restart network
```

需要注意的是,如果通过 SSH 连接到虚拟机, 那么重启网络会您短暂地断开连接, 如果断开时间过久那么则说明您的配置项出现了错误

可以通过如下命令查看系统网络的桥接情况

```shell
brctl show
```

![image-20210915220516351](http://cdn.ayusummer233.top/img/202109152205450.png)

> [多网卡绑定实例 - 遥远的绿洲 - 博客园 (cnblogs.com)](https://www.cnblogs.com/zjd2626/p/6555198.html)

> 如果是本地虚拟机的话可以通过 ping baidu.com 来试试有没有网
>
> 有网的话记得把前面的 yum 命令执行了
>
> ```shell
> yum -y upgrade	# 升级所有包，不改变软件设置和系统设置，系统版本升级，内核不改变
> yum install bridge-utils net-tools -y
> 
> 
> # PS:
> yum -y update：升级所有包，改变软件设置和系统设置,系统版本内核都升级
> 
> ```

---

#### `Hostname`

Cloudstack 要求正确配置主机名; 若您在安装中使用了默认选项,则主机名当前设置为本地主机, 为了测试这一点, 我们运行如下命令

```shell
hostname --fqdn    # 或 hostname -f

# PS:
hostname          # 查看主机名
hostname -f       # 查看FQDN
```

> [FQDN 是什么_ez scope-CSDN博客_fqdn](https://blog.csdn.net/u012842205/article/details/51931017)
>
> FQDN是完全合格域名/全程域名缩写，Fully Qualified Domain Name，即是域名，访问时将由DNS进行解析，得到IP。
>
> `FQDN = Hostname + DomainName`

在当前情况下返回的应当是

```shell
localhost
```

为了纠正这种情况, 我们将通过编辑 `/etc/hosts` 来设置 `hostname` , 请按照类似如下格式进行配置

```shell
127.0.0.1 localhost localhost.localdomain localhost4 localhost4.localdomain4
::1 localhost localhost.localdomain localhost6 localhost6.localdomain6
172.16.10.2 srvr1.cloud.priv    # ip 记得改成自己之前配网时的 ip
```

修改完文件后使用如下命令重启网络

```shell
systemctl restart network
```

并使用 `hostname --fqdn` 命令;来看看是否返回的是 `srvr1.cloud.priv`

> 很遗憾我这里不管怎么配置都还是原本的默认值 `VM-4-11-centos`
>
> 索性直接 `hostname srvr1.cloud.priv` 改了, 重启网络重连后使用 `hostname --fqdn` 命令确实可以回显 `srvr1.cloud.priv`
>
> 虽然不清楚是否可以这么做, 但是遍寻磁盘文件, 我是用 hostname 命令改完主机名后只有 `/etc/hosts` 中有这个名字, 故不了了之

---

#### SELinux

> [一文彻底明白linux中的selinux到底是什么_yanjun821126的博客-CSDN博客_selinux](https://blog.csdn.net/yanjun821126/article/details/80828908)
>
> [2.4 SELinux](https://blog.csdn.net/qq_44714521/article/details/109145500#24_SELinux_123)
>
> 安全增强型 Linux（Security-Enhanced Linux）简称 SELinux，它是一个 Linux 内核模块，也是 Linux 的一个安全子系统。
> SELinux 主要作用就是最大限度地减小系统中服务进程可访问的资源（最小权限原则）

要使 Cloudstack 正常工作, 必须将 SELinux 设置为 Permissive

> [SELinux 宽容模式(permissive) 强制模式(enforcing) 关闭(disabled) 几种模式之间的转换_tangsilian的博客-CSDN博客_permissive](https://blog.csdn.net/tangsilian/article/details/80144112)
>
> permissive：宽容模式：代表 SELinux 运作中，不过仅会有警告讯息并不会实际限制 domain/type 的存取。这种模式可以运来作为 SELinux 的 debug 之用

使用 `getenforce` 命令可以在 Linux 下查看是否开启了 SELinux

```shell
getenforce
```



![image-20210916100835642](http://cdn.ayusummer233.top/img/202109161008748.png)

> [getenforce命令_Linux getenforce命令使用详解：查看是否开启了SELinux (ywnz.com)](https://www.ywnz.com/linux/getenforce/)

可以使用如下命令将 SELinux 配置为 Permissive

```shell
setenforce 0
```

![image-20210916101218105](http://cdn.ayusummer233.top/img/202109161012171.png)

> 我服务器中的 SELinux 处于未使能的状态, 不过反正 SELinux 设置为 Permissive 的话也是不会有实际上的操作限制, 直接关闭应该也不成问题

---

#### NTP

NTP 是保证 cloud servers 中所有时钟同步的必要条件。但是 NTP 不是默认安装的;

> [centos7 查看启动ntp服务命令_夫君子之行,静以修身,俭以养德,非淡泊无以明志,非宁静无以致远.-CSDN博客_启动ntp服务](https://blog.csdn.net/qq_33468857/article/details/91345107)
>
> 可以使用如下命令查看 NTP 是否启用
>
> ```shell
> systemctl status ntpd
> ```
>
> ![image-20210916101947609](http://cdn.ayusummer233.top/img/202109161019723.png)
>
> 可以看到我这里是 `active(running)` (毕竟本就是云服务器), 所以就不用再配置了

使用如下命令安装并启用 ntpd:

```shell
yum -y install ntp
systemctl enable ntpd
systemctl start ntpd
```

---

#### 配置 Cloudstack Package Repository

我们需要配置机器使用 Cloudstack package repository

> Apache Cloudstack 的官方 Release 都是 source code 以至于并不存在可用的"官方"二进制文件
>
> [完整的安装指南](http://docs.cloudstack.apache.org/en/4.15.1.0/installguide/index.html)描述了如何获取 source release 并生成 RPMs and  yum repository
>
> > [RPM（Red-Hat Package Manager 软件包管理器）_百度百科 (baidu.com)](https://baike.baidu.com/item/RPM/3794648)
> >
> > [Yum Repository详解_weixin_34055910的博客-CSDN博客](https://blog.csdn.net/weixin_34055910/article/details/92964753)
> > [YUM](http://yum.baseurl.org/)(Yellowdog Updater Modified)是 Fedora、CentOS、RedHat 中的软件包管理器。基于 RPM 包管理，YUM 通过分析 RPM header数据，自动处理依赖关系，从指定服务器自动下载安装所有依赖的软件包。
>
> [快速部署指南](http://docs.cloudstack.apache.org/en/4.15.1.0/quickinstallationguide/qig.html#selinux)试图让配置越简单越好, 因此这里不进行过多描述, 因此这里使用一款 community-provided 的 yum repository
>
> 此外, 本次以安装 Cloudstack 4.15.1.0 为例 - 具体到个人安装参阅如下内容时请按照相应版本适当变更设置

要添加 CLoudstack repository, 需要创建 `/etc/yum.repos.d/cloudstack.repo` 并输入如下信息:

```shell
[cloudstack]
name=cloudstack    # yum仓库名字
baseurl=http://download.cloudstack.org/centos/$releasever/4.15/    # 仓库的位置
enabled=1     # 开启yum功能
gpgcheck=0    # 关闭完整性检查
```

---

#### NFS

> 网络文件系统，Network File System, 是一种使用于分散式文件协定，功能是通过网络让不同的机器、不同的操作系统能够分享个人数据，让应用程序通过网络可以访问位于服务器磁盘中的数据的系统
>
> [Linux下部署NFS服务 (*￣︶￣)_Ever~z 的博客！-CSDN博客_nfs](https://blog.csdn.net/sinat_41075146/article/details/80800812)

我们的配置将 NFS 用于 主存储 与 二级存储 (前文 [Cloudstack 概述](#Cloudstack 概述)时有提到)

使用如下命令安装 `nfs-utils`

```shell
yum -y install nfs-utils
```

> 大失败, 到这里的时候我突然 ping 不同腾讯云的内网 DNS了, 导致后面 yum 操作全崩
>
> 备份完修改文件重置实例了, 这次要好好看看怎么回事
>
> > 答案是上海云轻量不适用上海或上海金融的DNS,  应当使用所有地域的DNS, 详见 [此处](# yum 命令报错: `Could not resolve host: mirrors.tencentyun.com; Unknown error`)

配置 NFS 提供两个不同的 share

```shell
# 打开配置文件
vi /etc/exports

# 填入如下内容
/export/secondary *(rw,async,no_root_squash,no_subtree_check)
/export/primary *(rw,async,no_root_squash,no_subtree_check)
```

你应该会注意到这两个路径目前并不存在, 因此我们将继续创建这些目录并用如下命令为它们配置适当的权限

```
mkdir -p /export/primary
mkdir /export/secondary
```

> [Linux mkdir 命令 | 菜鸟教程 (runoob.com)](https://www.runoob.com/linux/linux-comm-mkdir.html)
>
> ---
>
> `-p` 确保目录名称存在, 不存在就创建一个
>
> ![image-20210916212430637](http://cdn.ayusummer233.top/img/202109162124784.png)

默认情况下, CentOS 7.x  release 使用 NFSv4; NFSv4 要求在所有客户端上都设置匹配的域; 在本例中 domain 是 `cloud.priv` ; 所以请确保 `/etc/idmapd.conf` 目录下 `Domain = cloud.priv`

```shell
vi /etc/idmapd.conf

# 修改如下配置:
Domain = cloud.priv
```



> ![image-20210916213927112](http://cdn.ayusummer233.top/img/202109162139208.png)
>
> 这里我没取消注释并修改而是直接在原有注释下加了一行, 主要是我看到后面有两处用到了原有注释里的 `local.domain.edu`
>
> ![image-20210916214044901](http://cdn.ayusummer233.top/img/202109162140989.png)

在 `/etc/sysconfig/nfs` 中添加如下配置, 或者取消原本的注释并进行设置

```shell
vi /etc/sysconfig/nfs
```

```shell
LOCKD_TCPPORT=32803
LOCKD_UDPPORT=32769
MOUNTD_PORT=892
RQUOTAD_PORT=875
STATD_PORT=662
STATD_OUTGOING_PORT=2020
```

> 有一说一这个 nfs 是个隐藏文件, 差点误修改 nfs.conf 去了
>
> ![image-20210916214813349](http://cdn.ayusummer233.top/img/202109162148482.png)
>
> 如下图所示, 原文件中几处配置隔开了
>
> ![image-20210916214935117](http://cdn.ayusummer233.top/img/202109162149261.png)
>
> 所以我索性讲配置加在文件末尾了
>
> ![image-20210916215100821](http://cdn.ayusummer233.top/img/202109162151915.png)

接下来关掉防火墙以防止其阻断连接

```shell
systemctl stop firewalld
systemctl disable firewalld
```

> [iptables、firewall和SELinux的区别及CentOS6.5、7关闭/开启防火墙的方法_theworldofxiej的专栏-CSDN博客](https://blog.csdn.net/theworldofxiej/article/details/103652136)
>
> [CentOS查看端口防火墙状态 - 刀锋93 - 博客园 (cnblogs.com)](https://www.cnblogs.com/hebiao/p/12966000.html)

用如下命令查看下防火墙状态

```shell
firewall-cmd --state
```

> ![image-20210916215701825](http://cdn.ayusummer233.top/img/202109162157968.png)

现在开始配置 nfs 服务在主机启动时启用并实际启用 nfs

```shell
systemctl enable rpcbind
systemctl enable nfs
systemctl start rpcbind
systemctl start nfs
```

> - [2.7 NFS](https://blog.csdn.net/qq_44714521/article/details/109145500#27_NFS_180)
>
> rpcbind 是一个 RPC 服务，主要是在 nfs 共享时候负责通知客户端服务器的 nfs 端口号的。简单理解 rpc 就是一个中介服务。
>
> ![image-20210916220118599](http://cdn.ayusummer233.top/img/202109162201695.png)
>
> 这里我遇到了一处比较奇怪的地方

使用 `showmount` 命令查看共享目录

```shell
showmount -e srvr1.cloud.priv
```



> [Linux showmount命令查看NFS共享目录信息-Linux实验室 (wanyunshuju.com)](https://idc.wanyunshuju.com/cym/1728.html)
>
> 使用showmount命令可以显示NFS服务器的挂载信息。比如查看NFS服务器上有哪些共享目录，这些共享目录可以被哪些客户端访问，以及哪些共享目录已经被客户端挂载了。
>
> `showmount [选项] [NFS服务器]`
>
> `-e` 显示 NFS 服务器的导出列表
>
> ---
>
> 由于之前在 [hostname 设置](#Hostname)时 `hostname --fqdn` 始终无法回显 `srvr1.cloud.priv` 因此这次部署 Cloudstack 时就没配 hostname 所以这里也是无法识别 host
>
> ![image-20210916221453014](http://cdn.ayusummer233.top/img/202109162214100.png)
>
> 不过将 hostname 换成内网 ip 又查了下发现有用
>
> ![image-20210916222222868](http://cdn.ayusummer233.top/img/202109162222951.png)
>
> 那么说明 NFS 已经配置好了, 因此又返回  [hostname 设置](#Hostname) 步骤修改了下 hosts 文件将下面这行又加上了
>
> ```shell
> 172.16.10.2 srvr1.cloud.priv	
> ```
>
> 然后又用 hostname 试了下结果成功了
>
> ![image-20210916222517900](http://cdn.ayusummer233.top/img/202109162225999.png)
>
> 不过 `hostname --fqdn` 回显仍然没变, 那么说明这里 `hostname` 访问的名字可能是我公网的 hostname, 毕竟云服务器不同于本地虚拟机, 同时有公网 ip 和内网 ip
>
> 不过这种解释是否真的成立暂时按下不表, 下面继续部署时美出问题就是没事

---

### 安装 Management Server

### 数据库的安装与配置

安装并配置 MySQL

首先, CentOS 7 不再提供 MySQL 二进制文件, 我们需要添加一个 MySQL 社区仓库, 其可提供 MySQL Server(以及 Python MySQL connector)

```shell
wget http://repo.mysql.com/mysql-community-release-el7-5.noarch.rpm
rpm -ivh mysql-community-release-el7-5.noarch.rpm
```

> ![image-20210918104710063](http://cdn.ayusummer233.top/img/202109181047325.png)
>
> ![image-20210918104743300](http://cdn.ayusummer233.top/img/202109181047463.png)
>
> [Linux rpm命令 | 菜鸟教程 (runoob.com)](https://www.runoob.com/linux/linux-comm-rpm.html)
>
> ```shell
> -i 　显示套件的相关信息。
> -v 　显示指令执行过程。
> -h或--hash 　套件安装时列出标记。
> ```

使用如下命令安装 MySQL:

```shell
yum -y install mysql-server
```

> ![image-20210918105200080](http://cdn.ayusummer233.top/img/202109181052287.png)
>
> 可以使用如下命令查看安装的 MySQL 版本
>
> ```shell
> mysql -V
> ```
>
> ![image-20210918105331967](http://cdn.ayusummer233.top/img/202109181053123.png)
>
> ```shell
> rpm -qa | grep mysql
> ```
>
> ![image-20210918110222751](http://cdn.ayusummer233.top/img/202109181102916.png)
>
> ```shell
> -q 　使用询问模式，当遇到任何问题时，rpm指令会先询问用户。
> -a 　查询所有套件。
> ```
>
> 

修改 `/etc/my.cnf`, 在 [mysqld] 部分添加如下配置

```shell
# 编辑 /etc/my.cnf
vi /etc/my.cnf

# 添加配置
innodb_rollback_on_timeout=1
innodb_lock_wait_timeout=600
max_connections=350
log-bin=mysql-bin
binlog-format = 'ROW'
```

> 需要注意的是, 如果使用 `Ubuntu 16.04` 及更高版本, 那么请指定一个 `server-id`: 在 `my.cnf` 的 [mysqld] 中多加一句
>
> ```shell
> server-id=master-01
> ```
>
> 
>
> ---
>
> [MySQL my.cnf配置文件详解 (biancheng.net)](http://c.biancheng.net/view/7618.html#:~:text=Linux 操作系统中 MySQL 的配置文件是 my.cnf，一般会放在 %2Fetc%2Fmy.cnf 或 %2Fetc%2Fmysql%2Fmy.cnf,rpm 包安装 MySQL 找不到 my.cnf 文件，可参考《 在linux下通过rpm安装的mysql找不到my.cnf解决方法 》。)
>
> [mysql之my.cnf详解 - 百衲本 - 博客园 (cnblogs.com)](https://www.cnblogs.com/panwenbin-logs/p/8360703.html)
>
> - `innodb_rollback_on_timeout`
> 	
> 	[MySQL数据库innodb_rollback_on_timeout参数 - 云+社区 - 腾讯云 (tencent.com)](https://cloud.tencent.com/developer/article/1579417)
> 	
> - `innodb_lock_wait_timeout`  
> 	InnoDB 事务在被回滚之前可以等待一个锁定的超时秒数。InnoDB 在它自己的 锁定表中自动检测事务死锁并且回滚事务。 InnoDB 用 LOCK TABLES 语句注意到锁定设置。默认值是 50 秒
>
> 	> [innodb_百度百科 (baidu.com)](https://baike.baidu.com/item/Innodb/8970025)
> 	>
> 	> InnoDB，是MySQL的数据库引擎之一，现为MySQL的默认存储引擎
>
> - `max_connections`  
>    指定 MySQL 允许的最大连接进程数。如果在访问数据库时经常出现"Too Many Connections"的错误提 示，则需要增大该参数值。
>
> - `log-bin = mysql-bin`  
>   打开二进制日志功能.在复制(replication)配置中,作为 MASTER 主服务器必须打开此项.如果你需要从你最后的备份中做基于时间点的恢复,你也同样需要二进制日志.这些路径相对于 datadir>	
>
> - `binlog-format = 'ROW'`
>
>   [关于binary log那些事——认真码了好长一篇 - 苏家小萝卜 - 博客园 (cnblogs.com)](https://www.cnblogs.com/xinysu/p/6607658.html#_lab2_2_1)
>
> ![image-20210918113037715](http://cdn.ayusummer233.top/img/202109181130992.png)



