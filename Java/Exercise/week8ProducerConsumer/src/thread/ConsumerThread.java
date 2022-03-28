package thread;
// 导入自定义类
import entity.Basket;
// 导入java类库
import javax.swing.JTextArea;
import javax.swing.JLabel;

public class ConsumerThread implements Runnable{
    public static boolean flag1 = true;
    public static boolean flag2 = true;
    JTextArea consumerTextArea = null;
    JLabel consumerLabel = null;
    Basket basket = null;

    public ConsumerThread(JTextArea t, JLabel l, Basket basket) {
        super();
        this.consumerTextArea = t;
        this.consumerLabel = l;
        this.basket = basket;
    }

    @Override
    public void run() {
        while (flag1) {
            if(flag2){
                int numProduce = basket.get();
                consumerLabel.setText("篮子中馒头的数量是： " + Basket.getNum);
                consumerTextArea.append("线程消费了"+ numProduce +"份食物。还剩" + Basket.getNum + "个食物\n");
            }else{
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        }

    }

    public void switchOffConsumer(){
        flag2 = false;
    }

    public void switchOnConsumer(){
        flag2 = true;
    }
}
