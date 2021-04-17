/*
 * @Author: your name
 * @Date: 2021-04-15 19:21:36
 * @LastEditTime: 2021-04-15 19:24:08
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\EmbeddedSystem\Experiment\实验5-第4次实验-外部中断实验\temp.c
 */

// 上
	if(WK_UP==1){
		if(isBling==0) isBling++;
		else isBling=0;
	}		 


// 左
	if(KEY2==0){				 
		if(isBling<5) isBling++;
		else isBling=0;
	}


// 下
	if(KEY1==0){
		if(isBling<7) isBling++;
		else isBling=0;
	}		 


// 右
	if(KEY0==0){				 
		if(isBling==6) LED0=!LED0;
		else isBling=0;
	}		 
