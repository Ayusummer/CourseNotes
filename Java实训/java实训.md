# Java 实训

## 环境配置

- [jdk-8u91-windows-x64](https://ayusummer-my.sharepoint.com/:u:/g/personal/233_ayusummer_onmicrosoft_com/EVQVmGs2AvJKpL1V8yupW6wB-V-XlmlmQRpMVrcbA_CC8g?e=qDKvjb)
- IDEA
  - [官网下载-IntelliJ IDEA：JetBrains 功能强大、符合人体工程学的 Java IDE](https://www.jetbrains.com/zh-cn/idea/)
  - [ideaU-2021.2.3](https://ayusummer-my.sharepoint.com/:u:/g/personal/233_ayusummer_onmicrosoft_com/ETCBYPPlJNtIhU1e4F_QQs8BoTJMP3Rvy3V_XogGIRcI_Q?e=PQQI8s)
  - [Jetbrains 学生包](https://www.jetbrains.com/community/education/#students)

---

## java学习路线

- javaSE (java基础部分)
  面向对象、集合、反射、多线程、设计模式、IO流
- javaWeb
  Servlet、jsp、Jdbc
- 高级框架SSM spring springMVC mybatis
  ssm的项目(自己独立完成一个管理系统)
- 分布式相关的内容springCloud . dubbo + zookeeper

---

## Spring

---

### 概述

`Spring` 是分层的 `Java SE/EE` 应用 `full-stack` 轻量级开源框架, 以 `IoC (Inverse Of Control:反转控制)` 和 `AOP (Aspect
Oriented Programming:面向切面编程)` 为内核，提供了展现层 `Spring MVC` 和持久层 `Spring JDBC` 以及业务层事务管理等众多的企业级应用技术,还能整合开源世界众多著名的第三方框架和类库,逐渐成为使用最多的 `Java EE` 企业应用开源框架

----

### Spring 的优势

**方便解耦，简化开发**
通过 `Spring` 提供的 `IoC` 容器，可以将对象间的依赖关系交由 `Spring` 进行控制，避免硬编码所造成的过度程序耦合。用户也不必再为单例模式类、属性文件解析等这些很底层的需求编写代码,可以更专注于上层的应用。

---

### 体系结构

<img src="http://cdn.ayusummer233.top/img/202112281141384.png" alt="image-20211228114144100" style="zoom: 67%;" />

---

### 程序间的耦合

耦合性(Coupling)，也叫耦合度,是对模块间关联程度的度量。耦合的强弱取决于模块间接口的复杂性、调用模块的方式以及通过界面传送数据的多少。模块间的耦合度是指模块之间的依赖关系,包括控制关系、调用关系、数据传递关系。模块间联系越多，其耦合性越强，同时表明其独立性越差(降低耦合性,可以提高其独立性)。耦合性存在于各个领域,而非软件设计中独有的,但是我们只讨论软件工程中的耦合。

---

#### 工厂模式解耦
在实际开发中我们可以把三层的对象都使用配置文件配置起来，当启动服务器应用加载的时候,让一个类中的方法通过读取配置文件，把这些对象创建出来并存起来。在接下来的使用的时候,直接拿过来用就好了。那么，这个读取配置文件，创建和获取三层对象的类就是工厂。

---

### 控制反转
`控制反转（Inversion of Control,缩写为IoC）`，是面向对象编程中的一种设计原则,可以用来减低计算机代码之间的耦合度。其中最常见的方式叫做依赖注入(公Dependency Injection，简称DI），还有一种方式叫“依赖查找”（Dependency Lookup）。通过控制反转,对象在被创建的时候,由一个调控系统内所有对象的外界实体将其所依赖的对象的引用传递给它。也可以说，依赖被注入到对象中明确ioc的作用:削减计算机程序的耦合(解除代码中的依赖关系)。

---

### ApplicationContext接口的实现类

- `ClassPathXmlApplicationContext`
  从类的根路径下加载配置文件  推荐使用这种

- `FileSystemXmlApplicationContext`

  从磁盘路径上加载配置文件  配置文件可以在磁盘的任意位置

- `AnnotationConfigApplicationContext`
  
  当我们使用注解配置容器对象时，需要使用此类来创建 spring 容器。它用来读取注解。

---

### Spring 示例项目步骤

#### 新建 java 项目

#### 配置 package 层级

- src
  - com
    - lib
    - team_name
      - beans
      - demo
      - utils
  - xml

#### 写 xml 配置

`src/xml/beans.xml`

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
        http://www.springframework.org/schema/beans/spring-beans.xsd">
</beans>
```

将需要的 jar 包添加到库

- commons-logging-1.2.jar
- spring-beans-5.0.2.RELEASE.jar
- spring-context-5.0.2.RELEASE.jar
- spring-core-5.0.2.RELEASE.jar
- spring-expression-5.0.2.RELEASE.jar

创建 Spring facet 并配置应用程序上下文(全默认即可)

<img src="http://cdn.ayusummer233.top/img/202112281302510.png" alt="image-20211228130213260" style="zoom: 67%;" />

---

#### 封装学生类

`com.ayusummer.beans.Student.java`

```java
package com.ayusummer.beans;

public class Student {
    private String name;
    private int age;
    private String sex;
    private String birthday;
    private String address;

    public Student(String name, int age, String sex, String birthday, String address) {
        this.name = name;
        this.age = age;
        this.sex = sex;
        this.birthday = birthday;
        this.address = address;
    }

    public Student() {
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }

    public String getSex() {
        return sex;
    }

    public String getBirthday() {
        return birthday;
    }

    public String getAddress() {
        return address;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public void setSex(String sex) {
        this.sex = sex;
    }

    public void setBirthday(String birthday) {
        this.birthday = birthday;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    @Override
    public String  toString() {
        return "Student{" +
                "name='" + name + '\'' +
                ", age=" + age +
                ", sex='" + sex + '\'' +
                ", birthday='" + birthday + '\'' +
                ", address='" + address + '\'' +
                '}';
    }
}

```

---

#### 测试

`com.ayusummer.demo/Demo01.java`

```java
package com.ayusummer.demo;

import com.ayusummer.beans.Student;

public class Demo01 {
    public static void main(String[] args) throws Exception {
        Student student1 = new Student("张三",23,"男","1997-10-8","江苏省");
        Student student2 = new Student("李四",24,"男","1997-10-8","江苏省");

        System.out.println(student1);
        System.out.println(student2);


        // 不适用 new 关键字, 使用反射创建对象
        Class<?> aclass = Class.forName("com.ayusummer.beans.Student");

        // 实例化对象
        Student student3 = (Student)aclass.newInstance();

        // 给属性赋值
        student3.setName("王五");
        student3.setAge(25);
        student3.setAddress("江苏省");
        student3.setBirthday("1995-1-8");
        student3.setSex("男");

        System.out.println(student3);
    }
}
```

---

#### 写 Spring 程序

先把 Student 类写入配置文件 `src/xml/beans.xml`

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
        http://www.springframework.org/schema/beans/spring-beans.xsd">
    <!--
        bean标签作用：spring程序在启动的时候会去读取核心配置文件，解析配置
        文件的内容，bean标签的作用就是根据反射创建实例添加到核心容器中！！
    -->
    <bean id="stu" class="com.ayusummer.beans.Student">
    </bean>
</beans>
```

`com.ayusummer.demo/SpringTest01.java`

```java
package com.ayusummer.demo;

import com.ayusummer.beans.Student;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class SpringTest01 {
    public static void main(String[] args)throws Exception {
        // 获取 Spring 核心容器对象
        ClassPathXmlApplicationContext applicationContext
                = new ClassPathXmlApplicationContext("xml/beans.xml");
        // 从核心容器对象中取出学生实例
        Student stu = (Student)applicationContext.getBean("stu");
        System.out.println(stu);
    }
}

```

在配置文件中通过 set 方法给 student 赋值

`xml/beans.xml`

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
        http://www.springframework.org/schema/beans/spring-beans.xsd">
    <!--
        bean标签作用：spring程序在启动的时候会去读取核心配置文件，解析配置
        文件的内容，bean标签的作用就是根据反射创建实例添加到核心容器中！！

        通过配置的方式给属性赋值
            set注入: 通过 set 方法给属性赋值
    -->
    <bean id="stu" class="com.ayusummer.beans.Student">
        <!--给属性赋值-->
        <property name="name" value="jack"/>
        <property name="age" value="15"/>
        <property name="sex" value="男"/>
        <property name="birthday" value="1998-10-19"/>
        <property name="address" value="南京市"/>
    </bean>
</beans>
```

---

#### 测试一个含复杂数据类型的类

`com.ayusummer.beans/Person.java`

```java
package com.ayusummer.beans;

import java.util.Date;

public class Person {
    private String name;
    private Date date;

    public Person(String name, Date date) {
        this.name = name;
        this.date = date;
    }

    public Person() {
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    @Override
    public String toString() {
        return "Person{" +
                "name='" + name + '\'' +
                ", date=" + date +
                '}';
    }
}

```
---

### 控制反转示例项目步骤

---

#### 新建 Java 项目并配置软件包层级

```java
- src
  - com
    - lib		              // 用于存放 jar 包
    - ayusummer
      - account            
        - controller        // 表现层(前端视觉)
        - mapper            // 持久层(与数据库交互)
        - service           // 业务层(业务逻辑)
      - pojo
      - demo
      - utils
- xml
```

表现层获取前端反馈数据送业务层处理逻辑, 调用持久层操作数据库

---

#### 定义保存账户方法

- 表现层 `com/ayusummer/account/controller/AccountController.java`

  ```java
  package com.ayusummer.account.controller;
  
  import com.ayusummer.account.service.AccountService;
  
  public class AccountController {
      private AccountService accountService = new AccountService();
      // 保存账户方法
      public void saveAccount(){
          accountService.saveAccount();
      }
  }
  
  ```

- 业务层 `com/ayusummer/account/service/AccountService.java`

  ```java
  package com.ayusummer.account.service;
  
  import com.ayusummer.account.mapper.AccountMapper;
  
  public class AccountService {
      private AccountMapper accountMapper= new AccountMapper();
  
      // 保存账户方法
      public void saveAccount(){
          accountMapper.saveAccount();
      }
  }
  
  ```

- 持久层 `com/ayusummer/account/mapper/AccountMapper.java`

  ```java
  package com.ayusummer.account.mapper;
  
  
  public class AccountMapper {
  
      // 保存账户方法
      public void saveAccount(){
          System.out.println("账户已保存");
      }
  }
  
  ```

---

#### 创建测试 demo 

`com/ayusummer/demo/AccountTest01.java`

```java
package com.ayusummer.demo;

import com.ayusummer.account.controller.AccountController;

public class AccountTest01 {
    public static void main(String[] args) {
        // 创建表现层实例
        AccountController accountController = new AccountController();
        // 调用保存账户方法
        accountController.saveAccount();
    }
}

```

运行后会回显 账户已保存 字样

![image-20211228160054599](http://cdn.ayusummer233.top/img/202112281600040.png)

---

#### 耦合分析

表现层创建了业务层实例, 产生了耦合

----

#### 解耦

表现层不使用 new 关键词创建业务层实例, 在构造函数中引入业务层对象作为参数, 由开发人员主动创建对象变为被动接收对象

对象的控制权发生了转换, 这种思想称为控制反转

控制反转的核心思想是解耦

`com/ayusummer/account/controller/AccountController.java`

```java
package com.ayusummer.account.controller;

import com.ayusummer.account.service.AccountService;

public class AccountController {
    private AccountService accountService;

    public AccountController(AccountService accountService){
        this.accountService = accountService;
    }

    // 保存账户方法
    public void saveAccount(){
        accountService.saveAccount();
    }
}

```

---

#### 写配置文件注册三层实例并注入相关实例

`xml/bean.xml`

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
        http://www.springframework.org/schema/beans/spring-beans.xsd">

    <!-- 注册表现层实例-->
    <bean id="controller" class="com.ayusummer.account.controller.AccountController">
        <!-- 注入业务层实例 -->
        <property name="accountService" ref="service"/>
    </bean>
    <!-- 注册业务层实例 -->
    <bean id="service" class="com.ayusummer.account.service.AccountService">
        <!-- 注入持久层实例 -->
        <property name="accountMapper" ref="mapper"/>
    </bean>
    <!-- 注册持久层实例 -->
    <bean id="mapper" class="com.ayusummer.account.mapper.AccountMapper"/>


</beans>
```

`com/ayusummer/account/controller/AccountController.java`

```java
package com.ayusummer.account.controller;

import com.ayusummer.account.service.AccountService;

public class AccountController {
    private AccountService accountService;

    public void setAccountService(AccountService accountService) {
        this.accountService = accountService;
    }

    public AccountController() {
    }

    // 保存账户方法
    public void saveAccount(){
        accountService.saveAccount();
    }
}

```

`com/ayusummer/account/service/AccountService.java`

```java
package com.ayusummer.account.service;

import com.ayusummer.account.mapper.AccountMapper;

public class AccountService {
    private AccountMapper accountMapper;

    public void setAccountMapper(AccountMapper accountMapper) {
        this.accountMapper = accountMapper;
    }

    // 保存账户方法
    public void saveAccount(){
        accountMapper.saveAccount();
    }
}

```


---

### 基于注解的 IOC 配置

- `@Component`: 把资源让 spring 来管理。相当于在 xml 中配置一个 bean.
  
- `@Controller`: 一般用于表现层的注解。

- `@Service`: 一般用于业务层的注解。

- `@Repository`: 一般用于持久层的注解。

注解起到标识作用, 不影响程序运行结果

Spring 程序在运行的时候，首先会扫描包( com.ayusummer), 检测指定包下面所有的类，查看类上面有无注解(@service 等)，若有注解，则 Spring 会将当前类的实例添加到容器中(也是通过反射的反射来创建实例)，以后项目开发中，注解的方式会使用的多一点

---

### 用于注入数据的注解
- `@Autowired`: 根据类型注入
- `@Qualifier`: 不能单独使用
- `@Resource`: 根据 id 注入的
- `@Value`: 用于注入基本数据类型和 String 类型

---

### 基于注解的 Spring 开发示例

#### 新建 Java 项目并配置软件包层级

同[控制反转示例项目](#控制反转示例项目步骤), 需要重配 xml 并加一个 jar 包

`spring-aop-5.0.2.RELEASE.jar`

`xml/beans.xml`

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
        xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
        xmlns:context="http://www.springframework.org/schema/context"
        xsi:schemaLocation="http://www.springframework.org/schema/beans
        http://www.springframework.org/schema/beans/spring-beans.xsd
        http://www.springframework.org/schema/context
        http://www.springframework.org/schema/context/spring-context.xsd">

    <!-- 开启扫描包 -->
    <context:component-scan base-package="com.ayusummer"/>
</beans>
```

---

#### 新建一个类用于测试自动配置

`com/ayusummer/pojo/Student.java`

```java
package com.ayusummer.pojo;

import org.springframework.stereotype.Component;

@Component("stu")	// 不带("stu") 的话默认name为首字母小写即 student
public class Student {
}
```

`com/ayusummer/demo/Demo01.java`

```java
package com.ayusummer.demo;

import com.ayusummer.pojo.Student;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class Demo01 {
    public static void main(String[] args) {
        // 创建核心容器对象
        ClassPathXmlApplicationContext applicationContext
                = new ClassPathXmlApplicationContext("xml/beans.xml");
        Student student = applicationContext.getBean("stu", Student.class);

        System.out.println(student);
    }
}

```

后面按照不同的层级添加不同的注解即可

---

### 代理模式

在不修改目标类的前提下，完成对目标类的增强

- 静态代理必须要满足两个条件
  - 有代理对象和目标对象
  - 代理对象和目标对象要去继承相同的父类，或者是实现相同的接口
- 动态代理
  - 分类
    - `jdk 动态代理`: 当目标类实现接口的时候
    - `cglib 动态代理`: 当目标类没有实现任何接口的时候
  - 场景:
    - 代理对象, 被代理对象(目标对象), 目标发起点
    - 租房子-中介相当于代理对象, 房东相当于被代理对象, 目标发起点就是有找房需求的客户

----

