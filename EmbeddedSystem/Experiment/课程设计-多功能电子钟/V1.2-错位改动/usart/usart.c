#include "sys.h"
#include "usart.h"
#include "led.h"
#include "string.h"
#include "lcd.h"
#include "rtc.h"

////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif

//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
#endif
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���
u8 USART_RX_str[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	

//��ʼ��IO ����1 
//bound:������
void uart_init(u32 bound){
   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
  USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_USART1_RX	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif
	
}

//�洢У׼��Ϣhxx mxx sxx
char str[20];

//�洢У׼��Ϣtxx:xx:xx dxx-xx-xx
char strtd[20];

//�洢�����������Ϣaxx:xx:xxwx
char stra[20];

//�洢��ǰ�����ַ�����
int i=0;

//�洢������(У׼������)
int aweek;

//�洢���ڲ���(У׼������)
int tempy,tempm,tempd;

//�洢��ǰ���ӵĸ���
int cnt;

void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;//�洢��ǰ�յ����ַ�
	RTC_TimeTypeDef RTC_Time;
	RTC_DateTypeDef RTC_Date;
	
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		//��ȡ���յ�������
		Res =USART_ReceiveData(USART1);//(USART1->DR);
		
		if(i<3) str[i]=Res;//h12 m12 s12
		if(i<9) strtd[i]=Res;//t12:12:12 d12-12-12
		if(i<11) stra[i]=Res;//a12:12:12w5
		i++;
		if(i>3){
				for(int j=1;j<3;j++){
					str[j-1]=str[j];
				}
				str[2]=Res;
		}
		if(i>9){
				for(int j=1;j<9;j++){
					strtd[j-1]=strtd[j];
				}
				strtd[8]=Res;
		}
		if(i>11){
				for(int j=1;j<11;j++){
					stra[j-1]=stra[j];
				}
				stra[10]=Res;
		}
		
		//h12 m12 s12 ��������ʱ����
		if((str[0]=='h' || str[0]=='m' || str[0]=='s') && i>=3){
			RTC_GetTime(RTC_Format_BIN,&RTC_Time);//��ȡʱ��
		  RTC_GetDate(RTC_Format_BIN,&RTC_Date);//��ȡ����
			if(str[0]=='h')   RTC_Time.RTC_Hours=(str[1]-'0')*10+(str[2]-'0');
			if(str[0]=='m')   RTC_Time.RTC_Minutes=(str[1]-'0')*10+(str[2]-'0');
			if(str[0]=='s')   RTC_Time.RTC_Seconds=(str[1]-'0')*10+(str[2]-'0');
			if(RTC_Time.RTC_Hours<24 && RTC_Time.RTC_Minutes<60 && RTC_Time.RTC_Seconds<60){
				RTC_Set_Time(RTC_Time.RTC_Hours,RTC_Time.RTC_Minutes,RTC_Time.RTC_Seconds,RTC_H12_AM);
				RTC_Set_Date(RTC_Date.RTC_Year,RTC_Date.RTC_Month,RTC_Date.RTC_Date,RTC_Date.RTC_WeekDay);
			}
		}
		
		//t12:12:12 ����ʱ��
		if(strtd[0]=='t' && strtd[3]==':' && strtd[6]==':' && i>=9){
			RTC_GetTime(RTC_Format_BIN,&RTC_Time);//��ȡʱ��
		  RTC_GetDate(RTC_Format_BIN,&RTC_Date);//��ȡ����
			RTC_Time.RTC_Hours=(strtd[1]-'0')*10+(strtd[2]-'0');
			RTC_Time.RTC_Minutes=(strtd[4]-'0')*10+(strtd[5]-'0');
			RTC_Time.RTC_Seconds=(strtd[7]-'0')*10+(strtd[8]-'0');
			//�ж�ʱ���Ƿ�Ϸ�
			if(RTC_Time.RTC_Hours<24 && RTC_Time.RTC_Minutes<60 && RTC_Time.RTC_Seconds<60){
				  //��ȡ���º������
					RTC_Date.RTC_WeekDay=RTC_Get_Week(RTC_Date.RTC_Year,RTC_Date.RTC_Month,RTC_Date.RTC_Date);
					RTC_Set_Time(RTC_Time.RTC_Hours,RTC_Time.RTC_Minutes,RTC_Time.RTC_Seconds,RTC_H12_AM);
					RTC_Set_Date(RTC_Date.RTC_Year,RTC_Date.RTC_Month,RTC_Date.RTC_Date,RTC_Date.RTC_WeekDay);
			}
		}
		
		//d12-12-12 ��������
		if(strtd[0]=='d' && strtd[3]=='-' && strtd[6]=='-' && i>=9){
			RTC_GetTime(RTC_Format_BIN,&RTC_Time);//��ȡʱ��
		  RTC_GetDate(RTC_Format_BIN,&RTC_Date);//��ȡ����
			RTC_Date.RTC_Year=(strtd[1]-'0')*10+(strtd[2]-'0');
			RTC_Date.RTC_Month=(strtd[4]-'0')*10+(strtd[5]-'0');
			RTC_Date.RTC_Date=(strtd[7]-'0')*10+(strtd[8]-'0');
			//�ձ��ж������Ƿ�Ϸ�
			if(RTC_Date.RTC_Year<=99 && RTC_Date.RTC_Month<=12 && RTC_Date.RTC_Date<=31){
				tempy=2000+RTC_Date.RTC_Year;
				tempm=RTC_Date.RTC_Month;
				tempd=RTC_Date.RTC_Date;
				//�����ж������Ƿ�Ϸ�
			  if(   (tempd<=28 && tempm==2 && !(((tempy%4==0) && (tempy%100!=0)) || tempy%400==0))//����ƽ��
					  ||(tempd<=29 && tempm==2 &&  (((tempy%4==0) && (tempy%100!=0)) || tempy%400==0))//��������
					  ||(tempd<=30 && (tempm==4 || tempm==6 || tempm==9 || tempm==11))//С��
				    ||(tempd<=31 && (tempm==1 || tempm==3 || tempm==5 || tempm==7 || tempm==8 || tempm==10 || tempm==12)))//����
				{
					  //��ȡ���º������
						RTC_Date.RTC_WeekDay=RTC_Get_Week(tempy%2000,tempm,tempd);
						RTC_Set_Time(RTC_Time.RTC_Hours,RTC_Time.RTC_Minutes,RTC_Time.RTC_Seconds,RTC_H12_AM);
						RTC_Set_Date(RTC_Date.RTC_Year,RTC_Date.RTC_Month,RTC_Date.RTC_Date,RTC_Date.RTC_WeekDay);
				}
			}
		}
		
		//a12:12:12w5 ��������
		if(stra[0]=='a' && stra[3]==':' && stra[6]==':' && stra[9]=='w' && i>=11){
			RTC_Time.RTC_Hours=(stra[1]-'0')*10+(stra[2]-'0');
			RTC_Time.RTC_Minutes=(stra[4]-'0')*10+(stra[5]-'0');
			RTC_Time.RTC_Seconds=(stra[7]-'0')*10+(stra[8]-'0');
			aweek=stra[10]-'0';
			if(RTC_Time.RTC_Hours<24 && RTC_Time.RTC_Minutes<60 && RTC_Time.RTC_Seconds<60 && aweek>=0 && aweek<=6){
				if(!RTC_isExist_Alarm(RTC_Time,aweek)){
					//�洢������Ϣ
					alarms[cnt].hour=RTC_Time.RTC_Hours;
					alarms[cnt].minute=RTC_Time.RTC_Minutes;
					alarms[cnt].second=RTC_Time.RTC_Seconds;
					alarms[cnt].week=aweek;
					cnt++;
					//���ж������ʱ��������
					if(cnt>1) RTC_Sort_Alarms();
					//������������������Ǹ�����
					RTC_Set_AlarmA(alarms[0].week,alarms[0].hour,alarms[0].minute,alarms[0].second);
					printf("\n���óɹ�,����%dʱ��Ϊ��%02d:%02d:%02dw%d\n",cnt-1,RTC_Time.RTC_Hours,RTC_Time.RTC_Minutes,RTC_Time.RTC_Seconds,aweek);
					RTC_Print_Alarms();
				}
			}
		}
	}
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
}
#endif	

 



