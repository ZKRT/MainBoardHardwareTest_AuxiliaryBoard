#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include "can.h"
//ALIENTEK ̽����STM32F407������ ʵ��27
//CANͨ��ʵ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

int main(void)
{ 
	u8 key=0,key2=0;
	u8 i=0;
	int t=0;
	u8 canbuf[8] = {0};
	u8 canbuf2[8] = {0};
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);    //��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED 
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_3tq,CAN_BS1_8tq,7,CAN_Mode_Normal);//CAN��ʼ������ģʽ,������500Kbps    
	CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS2_3tq,CAN_BS1_8tq,7,CAN_Mode_Normal);//CAN��ʼ������ģʽ,������500Kbps    
// 									  
	while(1)
	{
		key=CAN1_Receive_Msg(canbuf);
		if(key)//���յ�������
		{
			CAN1_Send_Msg(canbuf,8);//����8���ֽ� 
			for(i=0; i<8; i++)
			{
				canbuf[i] = 0;
			}
		}
		key2=CAN2_Receive_Msg(canbuf2);
		if(key2)//���յ�������
		{			
			CAN2_Send_Msg(canbuf2,8);//����8���ֽ� 
			for(i=0; i<8; i++)
			{
				canbuf2[i] = 0;
			}
		}
		t++; 
		if(t==500000)
		{
			LED0=!LED0;//��ʾϵͳ��������	
			t=0;
		}		   
	} 
}
//int main(void)
//{ 
//	u8 key;
//	u8 i=0,t=0;
//	u8 cnt=0;
//	u8 canbuf[8];
//	u8 res;
//	u8 mode=1;//CAN����ģʽ;0,��ͨģʽ;1,����ģʽ
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
//	delay_init(168);    //��ʼ����ʱ����
//	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
//	LED_Init();					//��ʼ��LED 
//// 	LCD_Init();					//LCD��ʼ�� 
//	KEY_Init(); 				//������ʼ��  
//	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_3tq,CAN_BS1_8tq,7,CAN_Mode_Normal);//CAN��ʼ������ģʽ,������500Kbps   
////CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_3tq,CAN_BS1_8tq,4,CAN_Mode_Normal);	
////	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
////	LCD_ShowString(30,70,200,16,16,"CAN TEST");	
////	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
////	LCD_ShowString(30,110,200,16,16,"2014/5/7");
////	LCD_ShowString(30,130,200,16,16,"LoopBack Mode");	 
////	LCD_ShowString(30,150,200,16,16,"KEY0:Send WK_UP:Mode");//��ʾ��ʾ��Ϣ		
////  POINT_COLOR=BLUE;//��������Ϊ��ɫ	   
////	LCD_ShowString(30,170,200,16,16,"Count:");		  	//��ʾ��ǰ����ֵ	
////	LCD_ShowString(30,190,200,16,16,"Send Data:");		//��ʾ���͵�����	
////	LCD_ShowString(30,250,200,16,16,"Receive Data:");	//��ʾ���յ�������		
//// 									  
//while(1)
//{
////		key=KEY_Scan(0);
////		if(key==KEY0_PRES)//KEY0����,����һ������
////		{
////			for(i=0;i<8;i++)
////			{
////				canbuf[i]=cnt+i;//��䷢�ͻ�����
////				if(i<4)LCD_ShowxNum(30+i*32,210,canbuf[i],3,16,0X80);	  //��ʾ����
////				else LCD_ShowxNum(30+(i-4)*32,230,canbuf[i],3,16,0X80);	//��ʾ����
//// 			}
////			res=CAN1_Send_Msg(canbuf,8);//����8���ֽ� 
////			if(res)
////				printf("Failed\n");		//��ʾ����ʧ��
////			else 
////				printf("OK\n");	 		//��ʾ���ͳɹ�								   
////		}
////		else if(key==WKUP_PRES)//WK_UP���£��ı�CAN�Ĺ���ģʽ
////		{	   
////			mode=!mode;
////			CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,mode);	//CAN��ͨģʽ��ʼ��,��ͨģʽ,������500Kbps
////			if(mode==0)//��ͨģʽ����Ҫ2��������
////			{
////				printf("Nnormal Mode\n");	    
////			}
////			else //�ػ�ģʽ,һ��������Ϳ��Բ�����.
////			{
//// 				printf("LoopBack Mode\n");
////			}
////		}		 
//		for(i=0; i<8; i++)
//		{
//			canbuf[i] = 0;
//		}
//		
//		key=CAN1_Receive_Msg(canbuf);
//		if(key)//���յ�������
//		{			
// 			for(i=0;i<key;i++)
//			{
//				printf("%x ", canbuf[i]);
// 			}
////			printf("\nOK\n");	
////			res=CAN1_Send_Msg(canbuf,8);//����8���ֽ� 
////			if(res)
////				printf("Failed\n");		//��ʾ����ʧ��
////			else 
////				printf("OK\n");	 		//��ʾ���ͳɹ�				
//		}
//		t++; 
////		delay_ms(10);
//		if(t==200)
//		{
//			LED0=!LED0;//��ʾϵͳ��������	
//			t=0;
//			cnt++;
////			printf("cnt=%d\n", cnt);
//		}		   
//	} 
//}
