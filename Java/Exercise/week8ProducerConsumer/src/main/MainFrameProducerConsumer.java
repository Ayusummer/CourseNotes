package main;
// 导入自定义类
import entity.Basket;
import macrovalue.MacroValue;
import thread.*;
import listener.*;

// 导入Java类库
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;


import java.awt.BorderLayout;

import static javax.swing.ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED;
import static javax.swing.ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED;

public class MainFrameProducerConsumer {
    static JFrame frame = null;
    static JLabel label =null;
    static JTextArea textArea = null;
    public static Basket basket = null;
    public static ProducerThread[] threadsProducer = new ProducerThread[MacroValue.MAX_PRODUCER_NUM];
    public static ConsumerThread[] threadsConsumer = new ConsumerThread[MacroValue.MAX_CUSTOMER_NUM];
    static JScrollPane jScrollPane = null;
    public static int switchProducerNum = 0;
    public static int switchConsumerNum = 0;
    public static JPanel panel;
    public static JButton buttonP;
    public static JButton buttonC;

    // 全局变量设置窗口组件定义
    // 主体框架窗口
    static JFrame frameValueSet = null;
    static JPanel panelValueSet = null;
    // 提示信息面板
    static JPanel panelMessage = null;
    static JLabel labelMessage = null;
    // 缓冲区容量设置面板
    static JPanel panelBufferVolume = null;
    static JLabel labelBufferVolume = null;
    static JTextField textFieldBufferVolume = null;
    // 生产者线程数目设置面板
    static JPanel panelProducerNum = null;
    static JLabel labelProducerNum = null;
    static JTextField textFieldProducerNum = null;
    // 消费者线程数目设置面板
    static JPanel panelConsumerNum = null;
    static JLabel labelConsumerNum = null;
    static JTextField textFieldConsumerNum = null;
    // 全局变量设置确认按钮
    static JButton buttonValueSet = null;
    // 返回值
    static boolean signR = false;

    // 设置返回值函数
    public static void setSignR(boolean r){
        signR = r;
    }

    // 设置生产者消费者线程数目
    static void setMarcoValue(){
        frameValueSet = new JFrame("全局变量设定");
        panelValueSet = new JPanel();

        // 提示信息面板初始化
        panelMessage = new JPanel();
        panelMessage.setSize(400,100);
        labelMessage = new JLabel("请在此面板设置全局变量,设定完后请确认");
        panelMessage.add(labelMessage);
        panelValueSet.add(panelMessage);

        // 缓冲区大小设置面板初始化
        panelBufferVolume = new JPanel();
        panelBufferVolume.setSize(400,100);
        labelBufferVolume = new JLabel("请输入缓冲区容量(正整数):");
        textFieldBufferVolume = new JTextField("",5);
        panelBufferVolume.add(labelBufferVolume);
        panelBufferVolume.add(textFieldBufferVolume);
        panelValueSet.add(panelBufferVolume);

        // 生产者线程数目设置面板初始化
        panelProducerNum = new JPanel();
        panelProducerNum.setSize(400,100);
        labelProducerNum = new JLabel("请输入生产者线程数目(正整数):");
        textFieldProducerNum = new JTextField("",5);
        panelProducerNum.add(labelProducerNum);
        panelProducerNum.add(textFieldProducerNum);
        panelValueSet.add(panelProducerNum);

        // 消费者线程数目设置面板初始化
        panelConsumerNum = new JPanel();
        panelConsumerNum.setSize(400,100);
        labelConsumerNum = new JLabel("请输入消费者线程数目:");
        textFieldConsumerNum = new JTextField("",5);
        panelConsumerNum.add(labelConsumerNum);
        panelConsumerNum.add(textFieldConsumerNum);
        panelValueSet.add(panelConsumerNum);

        // 全局变量设定按钮初始化
        buttonValueSet = new JButton("确定");
        buttonValueSet.addActionListener(new ListenerValueSet(textFieldBufferVolume, textFieldProducerNum,
                textFieldConsumerNum, frameValueSet, signR));
        panelValueSet.add(buttonValueSet);

        frameValueSet.add(panelValueSet);
        frameValueSet.setVisible(true);
        frameValueSet.setSize(400,500);
        frameValueSet.setLocationRelativeTo(null);
        frameValueSet.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }


    // 面板初始化
    public static void init(){
        frame = new JFrame("生产和消费同步问题");
        label = new JLabel();
        label.setText("篮子中馒头的数量是： "+Basket.getNum);
        frame.add(label, BorderLayout.NORTH);

        textArea = new JTextArea();
        jScrollPane = new JScrollPane(textArea,VERTICAL_SCROLLBAR_AS_NEEDED,
                HORIZONTAL_SCROLLBAR_AS_NEEDED);
        frame.add(jScrollPane,BorderLayout.CENTER);

        basket = new Basket();
        for(int i=0; i<MacroValue.MAX_PRODUCER_NUM; i++){
            threadsProducer[i] = new ProducerThread(textArea,label,basket);
        }
        for(int i=0; i<MacroValue.MAX_CUSTOMER_NUM; i++) {
            threadsConsumer[i] = new ConsumerThread(textArea, label, basket);
        }
        panel = new JPanel();
        buttonP = new JButton("生产 开");
        buttonP.addActionListener(new ListenerStopProducerThread(threadsProducer, frame));
        buttonC = new JButton("消费 开");
        buttonC.addActionListener(new ListenerStopConsumerThread(threadsConsumer, frame));
        panel.add(buttonP);
        panel.add(buttonC);

        frame.add(panel,BorderLayout.SOUTH);
        frame.setVisible(true);
        frame.setSize(400,500);
        frame.setLocationRelativeTo(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    }



    public static void main(String[] args) {
        setMarcoValue();
        while(!signR){
            try {
                Thread.sleep(10000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("正在等待开始信号");
        }
        if(signR) {
            init();
            // 创建一个线程池
            ExecutorService eService = Executors.newCachedThreadPool();
            // 将线程加入线程池
            for (int i = 0; i < MacroValue.MAX_PRODUCER_NUM; i++) {
                eService.submit(threadsProducer[i]);
            }
            for (int i = 0; i < MacroValue.MAX_CUSTOMER_NUM; i++) {
                eService.submit(threadsConsumer[i]);
            }
            eService.shutdown();
        }
    }
}
