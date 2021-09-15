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
| IaaS | 基于云的服务，按需付费，<br>用于存储，网络和虚拟化等服务 |                 AWS，阿里云，腾讯云，华为云                 | Infrastructure as a Service <br> 基础设施即服务 |
| PaaS |              Internet上可用的硬件和软件工具              | Microsoft Windows Azure，百度BAE、<br/>新浪SAE、京东云擎JAE |      Platform as a Service <br> 平台即服务      |
| SaaS |             可通过互联网通过第三方获得的软件             |                       钉钉，企业微信                        |      Software as a Service <br> 软件即服务      |

![image-20210915091928167](http://cdn.ayusummer233.top/img/20210915091935.png)

IaaS 为用户提供了基于云的本地基础结构替代品，因此企业可以避免对昂贵的现场资源进行投资

![image-20210915092657640](http://cdn.ayusummer233.top/img/202109150926786.png)

IaaS 软件通常用于管理大规模的物理硬件(IaaS 可以管理小到一台物理主机，多到成千上万的物理服务器)并把客户所需的软硬件资源(CPU，内存，网络，存储等)以“主机”的形式提供;

IaaS 的根本就是将计算资源进行池化(不限于cpu,内存，网络), 这些资源被逻辑切割成更小的可管理单元,然后根据客户需要被灵活的组装成可运作的主机,很明显这里的主机并不是一台真的物理主机,而是虚拟机.这个虚拟机通常都会包含一个可以连上网络的操作系统,用户可以通过网络连接上虚拟主机并且能灵活的进行资源配置以及按照配置及时间来付费.而用户操作这台虚拟主机就像操作一台物理服务器一样,可以在上面安装软件,搭建数据库以及应用服务器,部署web应用.由于这些提供给用户的功能都是最基础的计算功能,所以这种服务形式也被称作基础架构及服务(IaaS)

---

## CloudStack 

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

---



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

----

### 环境

CentOS 7.6 

---

更新系统:

```shell
yum -y upgrade
```

![image-20210915155241846](http://cdn.ayusummer233.top/img/202109151552042.png)

----

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
> > ```
> > A类地址：10.0.0.0 - 10.255.255.255 
> > B类地址：172.16.0.0 - 172.31.255.255 
> > C类地址：192.168.0.0 -192.168.255.255 
> > ```
> >
> > 以上IP是都是属于局域网，但不一定是同一个局域网。要检测两台电脑是否在同一个局域网，可以再一台电脑上ping另外一台电脑的IP.能ping通的就是在同一个局域网中。
> >
> > PS: 个人实验中使用了云服务器, 边使用了相应的内网地址 `10.x.x.x`

```
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
> > ```
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

```
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

> [网卡配置文件里DEFROUTE="yes"是什么东西？ - Linux新手园地-Chinaunix](http://bbs.chinaunix.net/thread-4185395-1-1.html)
>
> ```
> DEFROUTE=answer, 这里answer取下列值之一：
> yes -- 将该接口设置为默认路由。
> no -- 不要将该接口设置为默认路由
> ```

现在已经正确设置了配置文件, 我们需要运行几个命令来启动网络

```
systemctl enable network

systemctl restart network
```

需要注意的是,如果通过 SSH 连接到虚拟机, 那么重启网络会您短暂地断开连接, 如果断开时间过久那么则说明您的配置项出现了错误

可以通过如下命令查看系统网络的桥接情况

```
brctl show
```

![image-20210915220516351](http://cdn.ayusummer233.top/img/202109152205450.png)

> [多网卡绑定实例 - 遥远的绿洲 - 博客园 (cnblogs.com)](https://www.cnblogs.com/zjd2626/p/6555198.html)

> 如果是本地虚拟机的话可以通过 ping baidu.com 来试试有没有网
>
> 有网的话记得把前面的 yum 命令执行了
>
> ```
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
hostname --fqdn			# 或 hostname -f

# PS:
hostname		# 查看主机名
hostname -f 	# 查看FQDN
```

> [FQDN 是什么_ez scope-CSDN博客_fqdn](https://blog.csdn.net/u012842205/article/details/51931017)
>
> FQDN是完全合格域名/全程域名缩写，Fully Qualified Domain Name，即是域名，访问时将由DNS进行解析，得到IP。
>
> `FQDN = Hostname + DomainName`

在当前情况下返回的应当是

```
localhost
```

为了纠正这种情况, 我们将通过编辑 `/etc/hosts` 来设置 `hostname` , 请按照类似如下格式进行配置

```
127.0.0.1 localhost localhost.localdomain localhost4 localhost4.localdomain4
::1 localhost localhost.localdomain localhost6 localhost6.localdomain6
172.16.10.2 srvr1.cloud.priv	# ip 记得改成自己之前配网时的 ip
```

修改完文件后使用如下命令重启网络

```
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



