/*
 * @Author: your name
 * @Date: 2021-04-16 08:49:05
 * @LastEditTime: 2021-04-16 08:50:00
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\EmbeddedSystem\Experiment\实验6 独立看门狗实验\流畅呼吸灯.c
 */
 while(1){       // 循环执行呼吸灯,直至按下下键跳出循环
    int breath_time_total = 1500;  // 整个周期，1500ms->1.5s->模拟呼吸,吸气呼气各1.5s
    int breath_time_left = 100;
    int i;          // 计数器
    int flag_breath=0;     // 灭灯标记
    
    // 亮->暗
    for(i=breath_time_total; i>breath_time_left; i--){
        // 若按下KEY1或者KEY1已经按下(flag_breath==1)则熄灯并跳出呼吸循环
        if(led_off(KEY_Scan(1),flag_breath))   break;  
        // 亮i us灭breath_time_total+breath_time_left-i ms
        led_blink(breath_time_total+breath_time_left,i);         
    }
    
    // 若按下KEY1或者KEY1已经按下(flag_breath==1)则熄灯并跳出呼吸循环
    if(led_off(KEY_Scan(1),flag_breath))   break;  

    for(i=breath_time_left;i<breath_time_total;i++){
        // 若按下KEY1则熄灯并跳出暗->亮循环
        if(led_off(KEY_Scan(1),flag_breath))   break;  
            // 亮i us灭breath_time_total+breath_time_left-i us
        led_blink(breath_time_total,i);        
    }
    
    // 若按下KEY1或者KEY1已经按下(flag_breath==1)则熄灯并跳出呼吸循环
    if(led_off(KEY_Scan(1),flag_breath))   break;  

}   // 呼吸灯循环