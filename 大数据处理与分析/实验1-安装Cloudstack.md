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

# Linux 安装

---

## Ubuntu

### 查看版本信息

1. 方法1：使用命令： `cat /proc/version` 查看
2. 方法2：使用命令： `uname -a` 查看
3. 方法3：使用命令： `lsb_release -a` 查看

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

#### 配置网络

服务器有网, pass

---

更新系统:

```shell
yum -y upgrade
```

![image-20210915155241846](http://cdn.ayusummer233.top/img/202109151552042.png)

---

#### `Hostname`



```shell
hostname --fqdn
```



