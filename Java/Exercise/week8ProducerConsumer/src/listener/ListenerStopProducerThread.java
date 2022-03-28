package listener;
// 导入自定义类
import static main.MainFrameProducerConsumer.basket;
import macrovalue.MacroValue;
import main.MainFrameProducerConsumer;
import thread.ProducerThread;

// 导入Java类库
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;




// 线程生产开关(实现方式是循环调用生产线成中的开关函数,因此会有一定延迟)
public class ListenerStopProducerThread implements ActionListener {
    static ProducerThread[] threadsProducer = null;
    static JFrame frame = null;

    public ListenerStopProducerThread(ProducerThread[] t, JFrame f) {
        super();
        threadsProducer = t;
        frame = f;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        synchronized (basket) {
            System.out.println("当前生产者开关值为:" + MainFrameProducerConsumer.switchProducerNum);
            if (MainFrameProducerConsumer.switchProducerNum % 2 == 0) {
                MainFrameProducerConsumer.buttonP.setText("生产 关");
                JOptionPane.showMessageDialog(frame, "生产者线程正在逐一关闭,这需要一定的时间......");
                for (int i = 0; i < MacroValue.MAX_PRODUCER_NUM; i++)
                    threadsProducer[i].switchOffProducer();
                JOptionPane.showMessageDialog(frame, "生产者线程均已关闭");
                MainFrameProducerConsumer.switchProducerNum = MainFrameProducerConsumer.switchProducerNum + 1;
                System.out.println("生产者开关已关闭.当前生产者开关值为:" + MainFrameProducerConsumer.switchProducerNum);
            } else {
                MainFrameProducerConsumer.buttonP.setText("生产 开");
                JOptionPane.showMessageDialog(frame, "生产者线程正在逐一开启,这需要一定的时间......");
                for (int i = 0; i < MacroValue.MAX_PRODUCER_NUM; i++)
                    threadsProducer[i].switchOnProducer();
                JOptionPane.showMessageDialog(frame, "生产者线程均已开启");
                MainFrameProducerConsumer.switchProducerNum = MainFrameProducerConsumer.switchProducerNum + 1;
                System.out.println("生产者开关已开启.当前生产者开关值为:" + MainFrameProducerConsumer.switchProducerNum);
            }

            if (basket.putNum == 0 || basket.getNum == 0) {
                System.out.println("生产开关监听器提醒您:资源已临界,正在尝试进行唤醒操作");
                System.out.println("当前可放置空间为:"+basket.putNum + "  可取资源数为:" + basket.getNum);
                basket.notifyAll();
                System.out.println("已执行唤醒操作");
            }
        }
    }
}

