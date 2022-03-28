package listener;
// 导入自定义类
import static main.MainFrameProducerConsumer.basket;
import macrovalue.MacroValue;
import main.MainFrameProducerConsumer;
import thread.ConsumerThread;

// 导入Java类库
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;




public class ListenerStopConsumerThread implements ActionListener {
    ConsumerThread[] threadsConsumer = null;
    JFrame frame = null;

    public ListenerStopConsumerThread(ConsumerThread[] t, JFrame f) {
        super();
        threadsConsumer = t;
        frame = f;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        System.out.println("当前消费者开关值为:" + MainFrameProducerConsumer.switchConsumerNum);
        if (MainFrameProducerConsumer.switchConsumerNum % 2 == 0) {
            MainFrameProducerConsumer.buttonC.setText("消费 关");
            JOptionPane.showMessageDialog(frame, "消费者线程正在逐一关闭,这需要一定的时间......");
            for (int i = 0; i < MacroValue.MAX_CUSTOMER_NUM; i++) {
                threadsConsumer[i].switchOffConsumer();
            }
            JOptionPane.showMessageDialog(frame, "消费者线程均已关闭");
            MainFrameProducerConsumer.switchConsumerNum = MainFrameProducerConsumer.switchConsumerNum + 1;
            System.out.println("消费者开关已关闭.当前消费者开关值为:" + MainFrameProducerConsumer.switchConsumerNum);
        }   else{
                MainFrameProducerConsumer.buttonC.setText("消费 开");
            JOptionPane.showMessageDialog(frame, "消费者线程正在逐一开启,这需要一定的时间......");
                for (int i = 0; i < MacroValue.MAX_CUSTOMER_NUM; i++)
                    threadsConsumer[i].switchOnConsumer();
                JOptionPane.showMessageDialog(frame, "消费者线程均已开启");
                MainFrameProducerConsumer.switchConsumerNum = MainFrameProducerConsumer.switchConsumerNum + 1;
                System.out.println("消费者开关已开启,当前消费者开关值为:" + MainFrameProducerConsumer.switchConsumerNum);
            }
        if (basket.putNum == 0 || basket.getNum == 0) {
            System.out.println("消费开关监听器提醒您:资源已临界,正在尝试进行唤醒操作");
            System.out.println("当前可放置空间为:"+basket.putNum + "  可取资源数为:" + basket.getNum);
            synchronized (basket) {
                basket.notifyAll();
            }
            System.out.println("已执行唤醒操作");
        }
    }

}
