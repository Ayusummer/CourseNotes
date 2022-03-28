package listener;

import macrovalue.MacroValue;
import main.MainFrameProducerConsumer;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ListenerValueSet implements ActionListener {
    JTextField textFieldBufferVolume = null;
    JTextField textFieldProducerNum = null;
    JTextField textFieldConsumerNum = null;
    JFrame frameValueSet = null;
    boolean signR = false;

    public ListenerValueSet(JTextField textFieldBufferVolume, JTextField textFieldProducerNum,
                            JTextField textFieldConsumerNum, JFrame frameValueSet, boolean signR) {
        this.textFieldBufferVolume = textFieldBufferVolume;
        this.textFieldProducerNum = textFieldProducerNum;
        this.textFieldConsumerNum = textFieldConsumerNum;
        this.frameValueSet = frameValueSet;
        this.signR = signR;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        try{
            MacroValue.BUFFER_VOLUME = Integer.parseInt(textFieldBufferVolume.getText());
            MacroValue.MAX_PRODUCER_NUM = Integer.parseInt(textFieldProducerNum.getText());
            MacroValue.MAX_CUSTOMER_NUM = Integer.parseInt(textFieldConsumerNum.getText());
        }   catch(Exception ee){
            if(textFieldBufferVolume.getText().equals("")){
                JOptionPane.showMessageDialog(frameValueSet, "请输入缓冲区容量");
            }
            else if(textFieldProducerNum.getText().equals("")){
                JOptionPane.showMessageDialog(frameValueSet, "请输入生产者线程数目");
            }
            else if(textFieldConsumerNum.getText().equals("")){
                JOptionPane.showMessageDialog(frameValueSet, "请输入消费者线程数目");
            }
            else{
                JOptionPane.showMessageDialog(frameValueSet, "请检查输入数据是否为正整数");
            }
        }
        MainFrameProducerConsumer.setSignR(true);
    }
}
