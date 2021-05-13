/*
 * @Author: your name
 * @Date: 2021-05-13 19:29:38
 * @LastEditTime: 2021-05-13 19:42:12
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \JuniorLesson_SecondTerm\EmbeddedSystem\Experiment\实验4-第8次实验-串口(usart)实验\tmp2.c
 */
char C[12]={'1','2','3','a','4','5','6','b','7','8','9','c'};  //D¨°¨¢D¨ºy¡Á¨¦
u8 index=0;
void USART1_IRQHandler(void)                	
{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		
	OSIntEnter();    
#endif

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){
		Res = USART_ReceiveData(USART1);     // (USART1->DR);
		USART_SendData(USART1,Res);
		if(Res==C[index])
			index++;
    else 
		{
			if(Res=='1')  //¡¤¨¤?1¨º?¨¨??¨¤??1¨º¡Àindex=0
			  index=1;
		  else
			  index=0;
		}
		if(index==12)  //¨º?¨¨??y¨¨¡¤D¨°¨¢D¡ê??¨¬2a¦Ì?c
		{ 
			LED0=0;    
			index=0;   //¨ºy¡Á¨¦?¡Â¨°y??0
		}
		else
		 LED0=1;
	}
		 
#if SYSTEM_SUPPORT_OS 	//¨¨?1?SYSTEM_SUPPORT_OS?a??¡ê??¨°D¨¨¨°a?¡ì3?OS.
	OSIntExit();  											 
#endif
} 