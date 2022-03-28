# 前言

- 笔记中涉及的 Java 规约大多是阿里巴巴 Java 开发手册(嵩山版)中的规约
  - 以下简称(**嵩山版规约**)

---

## 实验环境

- 软件:
  - IDEAU2020.2
- 编码方案
  - 没有特殊声明的情况下都是 UTF-8

---

# 第 8 周 生产者消费者

- 第 4 次第 8 周作业
- 编写代码完成生产者消费者程序，要求：
  - 1、有多个生产者和多个消费者
  - 2、每一次的生产和消费的数量都要能够显示

## 随笔

### Math.random()

- 依赖包:
  ```Java
  import java.util.Random;
  ```
- 功能
  - 默认产生大于等于 0.0 且小于 1.0 之间的随机 double 型随机数
    - $0.0<=Math.random()<1.0$

---

### Thread.sleep()

- Thread.sleep()是 Thread 类的一个静态方法，使当前线程休眠，进入阻塞状态（暂停执行）
  - 如果线程在睡眠状态被中断，将会抛出 IterruptedException 中断异常。
- 主要方法如下：
  ```Java
  sleep(long millis)  线程睡眠 millis 毫秒
  sleep(long millis, int nanos)  线程睡眠 millis 毫秒 + nanos 纳秒
  ```

---

### 导入包

- 导入所处包同级目录下包的类
  ```Java
  import 包名.类名
  ```
- 包名(嵩山版规约)
  - 【强制】包名统一使用**小写**，点分隔符之间有且仅有一个自然语义的英语单词。包名统一使用单数形式，但是类名如果有复数含义，类名可以使用复数形式。
    - 正例：
      ```Java
      // 应用工具类包名为:
      com.alibaba.ei.kunlun.aap.util
      //类名为 :
      MessageUtils  //（此规则参考 spring 的框架结构）
      ```
- 类名(嵩山版规约)
  - 【强制】类名使用 UpperCamelCase 风格，但以下情形例外：DO / BO / DTO / VO / AO / PO / UID 等。
    - 正例：  
      ForceCode / UserDO / HtmlDTO / XmlService / TcpUdpDeal / TaPromotion
    - 反例：  
      forcecode / UserDo / HTMLDto / XMLService / TCPUDPDeal / TAPromotion
- 方法名(嵩山版规约)
  - 【强制】方法名、参数名、成员变量、局部变量都统一使用 lowerCamelCase 风格。
    - 正例:  
      localValue / getHttpMessage() / inputUserId
- 常量名(嵩山版规约)
  - 【强制】常量命名全部大写，单词间用下划线隔开，力求语义表达完整清楚，不要嫌名字长。
    - 正例：  
      MAX_STOCK_COUNT / CACHE_EXPIRED_TIME
    - 反例：  
      MAX_COUNT / EXPIRED_TIME
- 抽象/异常/测试类名
  - 【强制】抽象类命名使用 Abstract 或 Base 开头；
  - 异常类命名使用 Exception 结尾；
  - 测试类命名以它要测试的类的名称开始，以 Test 结尾。
- 数组定义
  - 【强制】类型与中括号紧挨相连来表示数组。
    - 正例：
      ```Java
      //定义整形数组
      int[] arrayDemo。
      ```
    - 反例：  
      在 main 参数中，使用 String args[]来定义。

---

### 两数较大值/较小值

```Java
Math.min(num1, num2);
Math.max(num1, num2);
```

---

### @Override

- [参考文章](https://www.cnblogs.com/ttzz/p/8455325.html)
- 作用
  - 作为注释，帮助自己检查是否正确的复写了父类中已有的方法
  - 便于别人理解代码
  - 编译器可以给你验证@Override 下面的方法名是否是你父类中所有的，如果没有则报错．
    - 自己重写接口方法或者父类方法时写错方法名的话编译的时候会报错
      - 相应的,不加@Override 的话若是实例的接口的方法写错的话编译时还能报没有实例化使用接口中的所有方法
        - 但是若是重写父类方法写错方法名的话编译时会被认为是该子类定义的新的方法而不报错

---

### JFrame

```Java
baseFrame = new JFrame("棋盘");
baseFrame.setVisible(true);    // 容器可见
baseFrame.setSize(600,700);    // 设置容器大小
// 设置容器居中显示
baseFrame.setLocationRelativeTo(null);
// 按X关闭窗口
baseFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
```

- ```Java
  JFrame.pack()
  ```
  - [参考链接](https://blog.csdn.net/sherlocksy/article/details/80110773)
  - pack() 调整此窗口的大小，以适合其子组件的首选大小和布局
  - 单独使用 setSize()时，不能使用 pack()，否则按照 pack()自动适配
  - 单独使用 pack()时，是按照组件的大小自动适配的
  - 单独使用 setPreferredSize()时，设置的大小无效，必须在后面添加 pack()配合显示，否则设置效果不生效
    - ```Java
      setPreferredSize()
      ```
      - 所属类
        ```Java
        java.awt.Component
        ```
      - 函数声明
        ```Java
        public void setPreferredSize(Dimension preferredSize)
        ```
        - 将此组件的首选大小设置为常量值。 随后电话 getPreferredSize 总是返回此值。 将首选大小设置为 null 可恢复默认行为。
        - preferredSize - 新的首选大小，或 null

---

### 滚动窗格 JScrollPane

- 创建一个水平与垂直滚动条在需要时才显示的,以一个文本域为视口的滚动窗格
  ```Java
  import javax.swing.JTextArea;
  import javax.swing.JScrollPane;
  import static javax.swing.ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED;
  import static javax.swing.ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED;
  static JTextArea textArea = null;
  static JScrollPane jScrollPane = null;
  textArea = new JTextArea();
  jScrollPane = new JScrollPane(textArea,VERTICAL_SCROLLBAR_AS_NEEDED,HORIZONTAL_SCROLLBAR_AS_NEEDED);
  ```

---

### Synchronized

- [原文链接](https://blog.csdn.net/zjy15203167987/article/details/82531772)

---

#### 为什么要使用 synchronized

- 在并发编程中存在线程安全问题，主要原因有：
  - 1.存在共享数据
  - 2.多线程共同操作共享数据。
- 关键字 synchronized 可以保证在同一时刻，只有一个线程可以执行某个方法或某个代码块，同时 synchronized 可以保证一个线程的变化可见（可见性），即可以代替 volatile。

---

#### 实现原理

- synchronized 可以保证方法或者代码块在运行时，同一时刻只有一个方法可以进入到临界区，同时它还可以保证共享变量的内存可见性

---

#### 临界区

- 交往的进程会产生错误的原因：  
  两个进程交叉访问的共享变量 count 或 X。
- 我们把并发进程中与共享变量有关的程序段称为“**临界区**”（Critical section)。
- 一次只允许一个进程使用的资源称**临界资源**。
- 为保证临界资源的正确使用，可把临界资源的访问过程分成四个部分：  
  进入区->临界区->退出区->剩余区
- 进程中访问临界资源的那段代码称临界区。

---

#### synchronized 的三种应用方式

Java 中每一个对象都可以作为锁，这是 synchronized 实现同步的基础：

- 普通同步方法（实例方法）
  - 锁是当前实例对象
  - 进入同步代码前要获得当前实例的锁
- 静态同步方法
  - 锁是当前类的 class 对象
  - 进入同步代码前要获得当前类对象的锁
- 同步方法块
  - 锁是括号里面的对象
  - 对给定对象加锁，进入同步代码库前要获得给定对象的锁。

---

#### synchronized 的作用

- Synchronized 是 Java 中解决并发问题的一种最常用最简单的方法
  - 他可以确保线程互斥的访问同步代码

---

#### 举栗子

- 一.synchronized 作用于实例方法

  - 多个线程访问同一个对象的同一个方法

    ```Java
    public class synchronizedTest implements Runnable {
      //共享资源
      static int i =0;
      /**
       * synchronized 修饰实例方法
      */
      public synchronized void increase(){
        i++;
      }
      @Override
      public void run(){
        for (int j =0 ; j<10000;j++){
            increase();
        }
      }

      public static void main(String[] args) throws InterruptedException {
        synchronizedTest test = new synchronizedTest();
        Thread t1 = new Thread(test);
        Thread t2 = new Thread(test);
        t1.start();
        t2.start();
        t1.join();
        t2.join();
        System.out.println(i);
      }
    }
    ```

    - ```Java
      public final void join()
                throws InterruptedException
      ```
      - 等待这个线程死亡。
      - 调用此方法的行为方式与调用完全相同
        - join (0)
      - 异常
        - InterruptedException
          - 如果任何线程中断当前线程。
          - 当抛出此异常时，当前线程的中断状态将被清除。
    - 运行结果:20000
    - 分析：
      - 当两个线程同时对一个对象的一个方法进行操作，只有一个线程能够抢到锁。
      - 因为一个对象只有一把锁，一个线程获取了该对象的锁之后，其他线程无法获取该对象的锁，就不能访问该对象的其他 synchronized 实例方法，需要等到对象被释放后才能获取，但是在对象没有被释放前，其他线程可以访问非 synchronized 修饰的方法

  - 一个线程获取了该对象的锁之后，其他线程来访问其他 synchronized 实例方法现象

    ```Java
    public class SynchronizedTest {
      public synchronized void method1() {
        System.out.println("Method 1 start");
        try {
            System.out.println("Method 1 execute");
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
          }
        System.out.println("Method 1 end");
     }

      public synchronized void method2() {
        System.out.println("Method 2 start");
        try {
            System.out.println("Method 2 execute");
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
          }
        System.out.println("Method 2 end");
      }


      public static void main(String[] args) {
        final SynchronizedTest test = new SynchronizedTest();

        new Thread(test::method1).start();

        new Thread(test::method2).start();
      }
    }
    ```

    - 运行结果:
      ```Java
      Method 1 start
      Method 1 execute
      Method 1 end
      Method 2 start
      Method 2 execute
      Method 2 end
      ```
    - 分析：
      - 可以看出其他线程来访问 synchronized 修饰的其他方法时需要等待线程 1 先把锁释放

  - 一个线程获取了该对象的锁之后，其他线程来访问其他非 synchronized 实例方法现象

    - 去掉上一个例子中方法二的 synchronized

    ```Java
    public class SynchronizedTest {
      public synchronized void method1() {
        System.out.println("Method 1 start");
        try {
            System.out.println("Method 1 execute");
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Method 1 end");
      }

      public void method2() {
        System.out.println("Method 2 start");
        try {
            System.out.println("Method 2 execute");
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Method 2 end");
      }


      public static void main(String[] args) {
        final SynchronizedTest test = new SynchronizedTest();

        new Thread(test::method1).start();
        new Thread(test::method2).start();
      }
    }
    ```

    - 运行结果:
      ```Java
      Method 1 start
      Method 2 start
      Method 1 execute
      Method 2 execute
      Method 2 end
      Method 1 end
      ```
    - 分析：
      - 当线程 1 还在执行时，线程 2 也执行了
      - 所以当其他线程来访问非 synchronized 修饰的方法时是可以访问的

  - 当多个线程作用于不同的对象

    ```Java
    public class SynchronizedTest {
      public synchronized void method1() {
        System.out.println("Method 1 start");
        try {
            System.out.println("Method 1 execute");
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Method 1 end");
      }

      public synchronized void method2() {
        System.out.println("Method 2 start");
        try {
            System.out.println("Method 2 execute");
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Method 2 end");
      }


      public static void main(String[] args) {
        final SynchronizedTest test1 = new SynchronizedTest();
        final SynchronizedTest test2 = new SynchronizedTest();

        new Thread(test1::method1).start();

        new Thread(test2::method2).start();
      }
    }
    ```

    - 结果
      ```Java
      Method 1 start
      Method 1 execute
      Method 2 start
      Method 2 execute
      Method 2 end
      Method 1 end
      ```
      - 分析：
        - 因为两个线程作用于不同的对象，获得的是不同的锁，
        - 所以互相并不影响
      - **此处思考一个问题：为什么分布式环境下 synchronized 失效？如何解决这种情况？**

---

- 二.synchronized 作用于静态方法

```Java
public class synchronizedTest implements Runnable {
    //共享资源
    static int i =0;
    /**
     * synchronized 修饰实例方法
     */
    public static synchronized void increase(){
        i++;
    }
    @Override
    public void run(){
        for (int j =0 ; j<10000;j++){
            increase();
        }
    }

    public static void main(String[] args) throws InterruptedException{
        Thread t1 = new Thread(new synchronizedTest());
        Thread t2 = new Thread(new synchronizedTest());
        t1.start();
        t2.start();
        t1.join();
        t2.join();
        System.out.println(i);
    }
}
```

- 执行结果:20000
  - 分析：
    - 由例子可知，两个线程实例化两个不同的对象，但是访问的方法是静态的
    - 两个线程发生了互斥（即一个线程访问，另一个线程只能等着）
      - 因为静态方法是依附于类而不是对象的，当 synchronized 修饰静态方法时，锁是 class 对象。

---

- 三、synchronized 作用于同步代码块

  - 为什么要同步代码块呢？
    - 在某些情况下，我们编写的方法体可能比较大，同时存在一些比较耗时的操作，而需要同步的代码又只有一小部分，如果直接对整个方法进行同步操作，可能会得不偿失，
    - 此时我们可以使用同步代码块的方式对需要同步的代码进行包裹，这样就无需对整个方法进行同步操作了。

  ```Java
  public class synchronizedTest implements Runnable {
    static synchronizedTest instance=new synchronizedTest();
    static int i=0;
    @Override
    public void run() {
        //省略其他耗时操作....
        //使用同步代码块对变量i进行同步操作,锁对象为instance
        synchronized(instance){
            for(int j=0;j<10000;j++){
                i++;
            }
        }
    }
    public static void main(String[] args) throws InterruptedException {
        Thread t1=new Thread(instance);
        Thread t2=new Thread(instance);
        t1.start();
        t2.start();
        t1.join();
        t2.join();
        System.out.println(i);
    }
  }
  ```

  - 运行结果:20000
  - 分析

    - 将 synchronized 作用于一个给定的实例对象 instance，

      - 即当前实例对象就是锁对象，每次当线程进入 synchronized 包裹的代码块时就会要求当前线程持有 instance 实例对象锁，

        - 如果当前有其他线程正持有该对象锁，那么新到的线程就必须等待，这样也就保证了每次只有一个线程执行 i++;操作。
        - 当然除了 instance 作为对象外，我们还可以使用 this 对象(代表当前实例)或者当前类的 class 对象作为锁，如下代码：

          ```Java
          //this,当前实例对象锁
          synchronized(this){
            for(int j=0;j<1000000;j++){
              i++;
            }
          }

          //class对象锁
          synchronized(AccountingSync.class){
            for(int j=0;j<1000000;j++){
              i++;
            }
          }
          ```

---

### wait()

- [原文链接](https://blog.csdn.net/qq_40550018/article/details/87859399)
- wait()是 Object 里面的方法，而不是 Thread 里面的，这一点很容易搞错。
  - 它的作用是将当前线程置于预执行队列，并在 wait()所在的代码处停止，等待唤醒通知。
- wait()只能在同步代码块或者同步方法中执行，如果调用 wait()方法，而没有持有适当的锁，就会抛出异常。
- wait()方法调用后会释放出锁，线程与其他线程竞争重新获取锁。

#### 例子

```Java
public class TestWait implements Runnable {
    private final Object object=new Object();
    @Override
    public void run() {
        synchronized (object){
            System.out.println("线程执行开始。。。");
            try {
                object.wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("线程执行结束。。。");
        }
    }

    public static void main(String[] args) {
        TestWait testWait=new TestWait();
        Thread thread=new Thread(testWait);
        thread.start();
    }
}
```

- 执行结果:线程执行开始。。。
- 从结果中我们可以看出线程调用了 wait()方法后一直在等待，不会继续往下执行。
  - 这也就能解释上面说的 wait()一旦执行，除非接收到唤醒操作或者是异常中断，否则不会继续往下执行。

---

### notify()

- notify()方法也是要在同步代码块或者同步方法中调用的
  - 它的作用是使停止的线程继续执行
  - 调用 notify()方法后，会通知那些等待当前线程对象锁的线程，并使它们重新获取该线程的对象锁，如果等待线程比较多的时候，则有线程规划器随机挑选出一个呈 wait 状态的线程。
- notify()调用之后不会立即释放锁，而是当执行 notify()的线程执行完成，即退出同步代码块或同步方法时，才会释放对象锁。

---

#### 例子

还是上面的例子，刚才我们调用了 wait()方法后，线程便一直在等待，接下来我们给线程一个唤醒的信号，代码如下：

```Java
public class TestWait implements Runnable {
    private final Object object=new Object();

    public void setFlag(boolean flag) {
        this.flag = flag;
    }

    private boolean flag=true;
    @Override
    public void run() {
        if(flag){
            this.testwait();
        }
        else {
            this.testnotify();
        }

    }
    public void testwait(){
        synchronized (object){
            try {
            System.out.println("线程开始执行。。。");
                Thread.sleep(1000);
            object.wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("线程执行结束。。。");
        }
    }
    public void testnotify(){
        synchronized (object){
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            object.notify();
        }
    }

    public static void main(String[] args) {
        TestWait testWait=new TestWait();
        Thread thread=new Thread(testWait);
        thread.start();
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        testWait.setFlag(false);
        Thread thread1=new Thread(testWait);
        thread1.start();
    }
}

```

- 运行结果
  ```Java
  线程开始执行。。。
  线程执行结束。。。
  ```
- 我们看到在调用 notify()方法之后，线程又继续了。

---

### notifyAll()

- 从字面意思就可以看出 notifyAll 是唤醒所有等待的线程。

---

### 出现阻塞的情况

- 出现阻塞的情况大体分为如下 5 种:
  - 线程调用 sleep 方法,主动放弃占用的处理器资源。
  - 线程调用了阻塞式 IO 方法,在该方法返回前,该线程被阻塞。
  - 线程试图获得一个同步监视器,但该同步监视器正被其他线程所持有。
  - 线程等待某个通知。
  - 程序调用了 suspend 方法将该线程挂起。此方法容易导致死锁,尽量避免使用该方法。
- run()方法运行结束后进入销毁阶段,整个线程执行完毕。
  - 每个锁对象都有两个队列,一个是就绪队列,一个是阻塞队列。
  - 就绪队列存储了将要获得锁的线程,阻塞队列存储了被阻塞的线程。
    - 一个线程被唤醒后,才会进入就绪队列,等待 CPU 的调度;
    - 反之,一个线程被 wait 后,就会进入阻塞队列,等待下一次被唤醒。

### 断点记录

- 10.29.7:24

  - 基本完成了整体设计
  - 缺陷设计
    - 开关用了循环实现,有一定延迟
  - 下一步设计
    - 重写 Basket 类
      - 信号量从 1 个改成 2 个
        - 生产者消费者使用两个不同的信号量

- 10.31.22:56
  - 完成了基本设计要求
    - 有一个 bug
      - 消费者线程开关无法关闭所有消费者线程
        - 原因是实现功能的监听器是采用切换开关状态来完成的
          - 但是实际上消费者这么多,很可能存在消费者从运行开始到点开关的时候都没有抢到资源使用权
      - 解决 bug 的方案:
        - 在主进程中设置两个计数变量用于记录当前生产/消费者线程开关该打开/关闭所有生产/消费者线程
        - 修改两个线程类的开关函数定义
          - 从原来的切换开关状态扩展到两个函数
            - 分别为至非与至是
        - 修改两个监听器的功能函数体
          - 从原来的执行开关切换函数改成根据主进程中对应计数变量确定是调用相应线程类中的置非还是置是函数

### bug&debug

#### 11.1 缓冲区空或满时通过按钮无法唤醒线程

- 原因分析:
  - 事件监听器设计时采用了 for 循环将开关置是置非的方式来实现线程的开关,实际上应该还需要线程的唤醒操作
- 解决方案思路流程:
  - 在循环置位后唤醒全部线程
    - (new Basket()).notifyAll()
  - 上面方案实测不可取
    - 因为锁是加在当前对象上的,new 一个对象就不是原来的锁了
    - 拟定解决方案:
      ```Java
      if()
      MainFrameProducerConsumerTest.basket.notifyAll();
      ```

---

# 第 9 周 聊天室

- 大方向拟定从 Java 从入门到精通中最后的 Java 编程实例为蓝本构建一个仿 QQ 的即时通信软件

---

## 系统功能分析

- 完整的客户端和服务器端
- 只具备基本的通信功能
  - 多人点对点聊天
  - 密码管理
  - 好友管理
  - 有人上线自动提示
  - 头像显示

---

- 在客户端，它由 3 个主要模块组成：
  - 登录模块
  - 注册模块
  - 主模块
    - 发送信息
    - 添加好友
    - 查找其他用户
    - 删除好友
    - 查看好友信息
    - 更改个人信息
    - 上线提示
    - 下线提示

---

- 服务器端，需要为客户端的功能提供相应的服务
  - 所以它提供了下列功能：
    - 处理注册新用户
    - 处理用户登录
    - 处理用户查找其他用户
    - 处理用户添加好友
    - 处理用户删除好友
    - 处理用户更新信息
    - 处理用户上、下线

---

## 数据库设计

- 本软件的服务器端需要用到数据库
  - 而用户端无需安装任何数据库。
- 这里选择的数据库平台仍然是 Access
  - 数据库文件为 MyQQ.mdb
- 采用 JDBC-ODBC 桥连接
  - ODBC 数据源名称为 myqq。
- 在数据库中，共有 3 张表
  - （1）friend 表
    - 记录了每个用户所拥有的好友号码
      | 字段名 | 类型 | 长度 | 含义 | 主键否 |
      | ----- | --- | -- | -- | -- |
      | QQNUM | int | 自动 | 用户账号 | 是 |
      | FRIEND | int | 自动 | 这个账户拥有的好友 | 否 |
      - 小体量故而账号使用 int 类型就够用了
  - qqnum 表
    - 记录了所有合法的账号
      | 字段名 | 类型 | 长度 | 含义 | 主键否 |
      | ----- | --- | -- | -- | -- |
      | ID | int | 自动 | 用户唯一编码 | 是 |
      | QQNUM | int | 自动 | 用户申请的账号 | 否 |
  - user_info 表
    - 记录了用户的基本信息

| 字段名   | 类型    | 长度 | 含义                   | 主键否 |
| -------- | ------- | ---- | ---------------------- | ------ |
| QQNUM    | int     | 自动 | 用户申请的账号         | 是     |
| Name     | varchar | 16   | 用户名                 | 否     |
| PASSWORD | varchar | 16   | 密码                   | 否     |
| STATUS   | int     | 自动 | 用户目前状态           | 否     |
| IP       | 文本    | 16   | 用户 IP 地址           | 否     |
| INFO     | 文本    | 100  | 用户自己留下的描述信息 | 否     |
| PIC      | 文本    | 50   | 所选头像文件名         | 否     |
| SEX      | 文本    | 2    | 性别                   | 否     |
| EMAIL    | 文本    | 50   | EMAIL 地址             | 否     |
| Name     | 文本    | 16   | 用户名                 | 否     |
| Name     | 文本    | 16   | 用户名                 | 否     |
| FRIEND   | 长整型  | 自动 | 这个账户拥有的好友     | 否     |

---

## 系统总体设计

- 本系统
  - 基于网络的三层 C/S 模式
  - 程序采用 JDK1.5 开发
  - 后台数据库采用 Access
  - 客户端之间的通信采用 UDP 协议
  - 客户端与服务器之间的通信采用 TCP/IP 协议
- 整个系统体系结构如下图所示
  ![](../res/img/Java/聊天室-系统体系结构.png)

---

## 随笔

### IDEA 导入 jar 包

- File -> Project Structure(Ctrl + Alt + Shift + s) -> Modules -> Dependencies -> add Jar...

---

### 安装 MySQL

- [原文链接](https://www.cnblogs.com/winton-nfs/p/11524007.html)

- 下载[MySQL 免安装版](https://dev.mysql.com/get/Downloads/MySQL-8.0/mysql-8.0.22-winx64.zip)

  > 该链接指向的是截止 2020.12.2 最新版的 MySQL 社区版最新下载链接

- 下载完成后解压到你想把 MySQL 安装在的目录

  > 该目录不可有中文与空格

- 安装 MySQL 的服务
  - 打开解压后的文件夹中的 bin 文件夹,单击 Windows 文件资源管理器左上角的`文件`->`打开Windows Powershell`->`以管理员身份打开Windows Powershell`
    > Win11 的话 `win+X` 选择 `Windows Powershell(管理员)` 打开, 使用
    ```powershell
    cd 当前文件夹路径
    ```
    转到当前文件夹路径
  - 输入
    ```powershell
    .\mysqld --install
    ```
    并回车
  - 之后会显示安装成功的提示:`Service successfully installed.`
- 初始化 mysql
  - 输入
    ```powershell
    .\mysqld --initialize --console
    ```
    并回车
  - 将会显示几行文字,复制最后一行`root@localhost:`字样后面的字符串`o?0yxuffh?E.`

    > 这串字符串是初始化生成的随机密码
- 开启 mysql 的服务

  - 输入

    ```powershell
    net start mysql
    ```

    并回车

  - 将会显示`MySQL 服务已经启动成功`的字样

- 登录验证 MySQL 是否安装成功
  - 输入

    ```powershell
    .\mysql -u root -p
    ```

    并回车,将会让你输入密码

    > 密码就是刚才生成的临时密码,输入并回车即可
    >
    > 这里需要注意的是: 若刚才生成临时密码的时候最后有个`.`的话注意这里的`.` 不是句号,而是密码的一部分

  - 登陆成功后当前光标前面会有`mysql>`
- 修改密码

  - 登录成功后输入

    ```powershell
    alter user 'root'@'localhost' identified by 'root';
    ```

    - 这样即可将密码改为`root`

    - 同理,将最后 by 后面的`root`改成你自己想修改成的密码吧

    - 修改成功后将会显示`Query OK, 0 rows affected`字样

    - 输入

      ```powershell
      exit
      ```

      并回车以退出 MySQL

    - 验证密码

      - 输入

        ```powershell
        .\mysql -u root -p
        ```

        并回车,将会让你输入密码

      - 输入你刚才修改好的密码

      - 能够再次成功进入则修改成功

- 设置系统的全局变量：

  - `桌面`->`右键"此电脑"`->`属性`->左侧`高级系统设置`->`环境变量`

    > Win 11 的话 `设置 -> 系统 -> 关于 -> 高级系统设置 -> 环境变量`
    >
    > ![image-20220327122623794](http://cdn.ayusummer233.top/img/202203271226203.png)

  - 进入后上面是`用户变量`,下面是`系统变量`
    - 点击 `下面的新建按钮`, 新建一个`系统变量`
      - 变量名填`mysql`
      - 变量值填你将 MySQL 安装的位置
        - 例如我填的是`C:\Database\MySQL\mysql-8.0.22-winx64`
      - 单击`确定`以完成新建
    - 进入`系统变量`的`Path`变量
      - 单击`新建`
      - 输入`%mysql%\bin`
    - 完成后逐级确定以完成配置

- 配置完系统变量之后要登录 MySQL 只需

  - `Win + R`输入`cmd`并回车打开命令行窗口

  - 输入

    ```shell
    mysql -u root -p
    ```

    并回车即可

- 在 mysql 目录下创建一个 ini 或 cnf 配置文件，在这里我创建的是 ini 配置文件，里面写的代码是 mysql 的一些基本配置
  - mysql 目录就是刚才配置环境变量时的 MySQL 安装位置
    - 我的就是`C:\Database\MySQL\mysql-8.0.22-winx64`
    - 打开该文件夹新建一个文本文档并**连同文件扩展名**一同改为`my.ini`
      - 打开`my.ini`,键入以下配置并保存退出
        ```
        [mysqld]
        character-set-server=utf8mb4
        bind-address=0.0.0.0
        port=3306
        default-storage-engine=INNODB
        [mysql]
        default-character-set=utf8mb4
        [client]
        default-character-set=utf8mb4
        ```
- 到这里就已经配置完成了

- 你可以在 Navicat 中连接配置好的 MySQL
  - 打开 Navicat
  - 左上`连接`->`MySQL`
    - 连接名自拟
    - 主机:`localhost`
    - 端口:`3306`
    - 用户名:`root`
    - 密码:你刚才配置好的 MySQL 的密码
  - 输入完成并单击`确定`后会在当前窗口左栏出现一个你自拟的链接名,双击它,若它变绿了就说明连接上你配置的 MySQL 了
- 到这里 MySQL 的安装,配置与连接就已经完成了,更详细的步骤以及**可能出现的问题**可以移步原博主的[博客链接](https://www.cnblogs.com/winton-nfs/p/11524007.html)查看
  - 如果有空的话别忘了给博主点个`推荐`哦

    > 若忘记密码可以参考[这篇文章](https://www.cnblogs.com/syq816/p/12241136.html)

---

### MySQL 数据类型

- [原文链接](https://www.runoob.com/mysql/mysql-data-types.html)

---

- MySQL 中定义数据字段的类型对你数据库的优化是非常重要的。
- MySQL 支持多种类型，大致可以分为三类：
  - 数值
  - 日期/时间
  - 字符串(字符)类型。

---

#### 数值类型

- MySQL 支持所有标准 SQL 数值数据类型。
  - 这些类型包括
    - 严格数值数据类型(INTEGER、SMALLINT、DECIMAL 和 NUMERIC)
    - 近似数值数据类型(FLOAT、REAL 和 DOUBLE PRECISION)。
- 关键字 INT 是 INTEGER 的同义词，关键字 DEC 是 DECIMAL 的同义词。
- BIT 数据类型保存位字段值，并且支持 MyISAM、MEMORY、InnoDB 和 BDB 表。
- 作为 SQL 标准的扩展，MySQL 也支持整数类型 TINYINT、MEDIUMINT 和 BIGINT。

---

- 下面的表显示了需要的每个整数类型的存储和范围。
  ![](../res/img/Java/MySQL-数值类型.png)

---

- Navicat 中设计表时,数值类型数据的长度设置与字符类型的长度设置是不一样的
  - [原文链接](https://blog.csdn.net/guaiguaiknl/article/details/105813770)
  - **char**类型数据的长度为字符(字母或汉字)的**个数**
  - **varchar**类型数据的长度为字符(字母或汉字)的**最大个数**
  - **int**类型的长度指的是**显示宽度**
    - 长度的设定值范围 1~255
      - 设置 0 时自动转为 11
      - 不设置时自动转为默认的 11
      - 在此范围内任意长度值的字段值范围都是
        - -2147483648~2147483647
          - 即$-2³¹-1$ ~ $2³¹-1$

            > 也就是说：int(1)、int(4)、int(11)和 int(110)表示意思是一样的
  - 要查看出不同效果记得在创建类型的时候加 zerofill 这个值（INT(M) ZEROFILL），表示用 0 填充，否则看不出效果的

---

#### 日期和时间类型

- 表示时间值的日期和时间类型为 DATETIME、DATE、TIMESTAMP、TIME 和 YEAR。
- 每个时间类型有一个有效值范围和一个"零"值，当指定不合法的 MySQL 不能表示的值时使用"零"值。
- TIMESTAMP 类型有专有的自动更新特性，将在后面描述。

---

![](../res/img/Java/MySQL-日期和时间类型.png)

---

#### 字符串类型

- 字符串类型指 CHAR、VARCHAR、BINARY、VARBINARY、BLOB、TEXT、ENUM 和 SET。
- 该节描述了这些类型如何工作以及如何在查询中使用这些类型。

---

![](../res/img/Java/MySQL-字符串类型.png)

---

- 注意:
  - char(n) 和 varchar(n) 中括号中 n 代表字符的个数，并不代表字节个数，比如 CHAR(30) 就可以存储 30 个字符。
  - CHAR 和 VARCHAR 类型类似，但它们保存和检索的方式不同。它们的最大长度和是否尾部空格被保留等方面也不同。在存储或检索过程中不进行大小写转换。
  - BINARY 和 VARBINARY 类似于 CHAR 和 VARCHAR，不同的是它们包含二进制字符串而不要非二进制字符串。也就是说，它们包含字节字符串而不是字符字符串。这说明它们没有字符集，并且排序和比较基于列值字节的数值值。
  - BLOB 是一个二进制大对象，可以容纳可变数量的数据。
    - 有 4 种 BLOB 类型：TINYBLOB、BLOB、MEDIUMBLOB 和 LONGBLOB。
      - 它们区别在于可容纳存储范围不同。
    - 有 4 种 TEXT 类型：TINYTEXT、TEXT、MEDIUMTEXT 和 LONGTEXT。
      - 对应的这 4 种 BLOB 类型，可存储的最大长度不同，可根据实际情况选择。

---

---

# 大作业

- 遇到问题及解决方案
- HTTP500 服务器内部错误
  - 仔细排查源码与示例,发现有一个变量使用错了;
- SyntaxError: “JSON.parse: unexpected character at line 1 column 1 of the JSON data”
  - 在调用的方法上加上注解@ResponseBoby
- An internal error occurred during: “Initializing Java Tooling”.
  - 清空项目缓存,重启 Eclipse
- org.apache.ibatis.binding.BindingException: Invalid bound statement (not found)
  - Service 层的类上方添加了@Service 注解
  - 报错的类上方添加@Component 等注解
