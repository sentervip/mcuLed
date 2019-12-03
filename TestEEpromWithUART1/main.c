
/*------------------------------------------------------------------*/
/* --- STC MCU International Limited -------------------------------*/
/* --- STC 1T Series MCU RC Demo -----------------------------------*/
/* --- Mobile: (86)13922805190 -------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ---------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ---------------------*/
/* --- Web: www.GXWMCU.com -----------------------------------------*/
/* --- QQ:  800003751 ----------------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/


/*------------------------------------------------------------------*/
/* --- STC MCU International Limited -------------------------------*/
/* --- STC 1T Series MCU Programme Demo ----------------------------*/
/* --- Fax: 86-755-82944243 ----------------------------------------*/
/* --- Tel: 86-755-82948412 ----------------------------------------*/
/* --- Web: www.STCMCU.com -----------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/

/*      本程序经过测试完全正常, 不提供电话技术支持, 如不能理解, 请自行补充相关基础.  */


/*************	本程序功能说明	**************

对EEPROM做扇区擦除、写入64字节、读出64字节的操作。

EEPROM通用测试程序。可以在配置文件"config.h"中选择MCU类型。

波特率:  9600,8,N,1. 可以在配置文件"config.h"中修改.

命令例子:
E 0
     对EEPROM进行扇区擦除操作，E表示擦除, 数字0为0扇区(十进制, 0~126, 看具体IC).
W 0
     对EEPROM进行写入操作，W表示写入, 数字0为0扇区(十进制, 0~126, 看具体IC). 从扇区的开始地址连续写64字节.
R 0
     对EEPROM进行读出操作，R表示读出, 数字0为0扇区(十进制, 0~126, 看具体IC). 从扇区的开始地址连续读64字节.

E 0x1A34
          对EEPROM进行扇区擦除操作，E表示擦除, 数字0x1A34为扇区内的字节地址，十六进制.
W 0x1A34
          对EEPROM进行写入操作，W表示写入, 数字0x1A34为开始地址，十六进制, 从这个地址连续写64个字节. 
R 0x1A34
          对EEPROM进行读出操作，R表示读出, 数字0x1A34为开始地址，十六进制, 从这个地址连续读64个字节. 

注意：为了通用，程序不识别扇区是否有效，用户自己根据具体的型号来决定。

工程文件:
STC_EEPROM.c
test_EEPROM.c

日期: 2013-5-10

******************************************/

#include	"config.H"
#include	"EEPROM.h"


#define		Baudrate1			115200L
#define		UART1_BUF_LENGTH	10




/*************	本地常量声明	**************/
u8	code	T_Strings[]={"去年今日此门中，人面桃花相映红。人面不知何处去，桃花依旧笑春风。"};


/*************	本地变量声明	**************/
u8	idata	tmp[70];
u8	idata	RX1_Buffer[UART1_BUF_LENGTH];
u8	RX1_Cnt;
u8	RX1_TimeOut;
bit	B_TX1_Busy;
#define	TimeOutSet1		5


/*************	本地函数声明	**************/
void	UART1_config(void);
void 	TX1_write2buff(u8 dat);	//写入发送缓冲
void 	PrintString1(u8 *puts);	//发送一个字符串


/*************  外部函数和变量声明 *****************/




/**********************************************/

u8	CheckData(u8 dat)
{
	if((dat >= '0') && (dat <= '9'))		return (dat-'0');
	if((dat >= 'A') && (dat <= 'F'))		return (dat-'A'+10);
	if((dat >= 'a') && (dat <= 'f'))		return (dat-'a'+10);
	return 0xff;
}

u16	GetAddress(void)
{
	u16	address;
	u8	i;
	
	address = 0;
	if(RX1_Cnt <  3)	return 65535;	//error
	if(RX1_Cnt <= 5)	//5个字节以内是扇区操作，十进制, 支持命令: 	E 0, E 12, E 120
						//											W 0, W 12, W 120
						//											R 0, R 12, R 120
	{
		for(i=2; i<RX1_Cnt; i++)
		{
			if(CheckData(RX1_Buffer[i]) > 9)	return 65535;	//error
			address = address * 10 + CheckData(RX1_Buffer[i]);
		}
		if(address < 124)	//限制在0~123扇区
		{
			address <<= 9;
			return (address);
		}
	}
	else if(RX1_Cnt == 8)	//8个字节直接地址操作，十六进制, 支持命令: E 0x1234, W 0x12b3, R 0x0A00
	{
		if((RX1_Buffer[2] == '0') && ((RX1_Buffer[3] == 'x') || (RX1_Buffer[3] == 'X')))
		{
			for(i=4; i<8; i++)
			{
				if(CheckData(RX1_Buffer[i]) > 0x0F)		return 65535;	//error
				address = (address << 4) + CheckData(RX1_Buffer[i]);
			}
			if(address < 63488)	return (address);	//限制在0~123扇区
		}
	}
	
	 return	65535;	//error
}

//========================================================================
// 函数: void  delay_ms(u8 ms)
// 描述: 延时函数。
// 参数: ms,要延时的ms数, 这里只支持1~255ms. 自动适应主时钟.
// 返回: none.
// 版本: VER1.0
// 日期: 2013-4-1
// 备注: 
//========================================================================
void  delay_ms(u8 ms)
{
	u16 i;
	do
	{
		i = MAIN_Fosc / 13000;
		while(--i)	;
	}while(--ms);
}


/********************* 主函数 *************************/
void main(void)
{
	u8	i;
	u16 addr;

	P0M1 = 0;	P0M0 = 0;	//设置为准双向口
	P1M1 = 0;	P1M0 = 0;	//设置为准双向口
	P2M1 = 0;	P2M0 = 0;	//设置为准双向口
	P3M1 = 0;	P3M0 = 0;	//设置为准双向口
	P4M1 = 0;	P4M0 = 0;	//设置为准双向口
	P5M1 = 0;	P5M0 = 0;	//设置为准双向口
	P6M1 = 0;	P6M0 = 0;	//设置为准双向口
	P7M1 = 0;	P7M0 = 0;	//设置为准双向口

	UART1_config();	// 选择波特率, 2: 使用Timer2做波特率, 其它值: 使用Timer1做波特率.
	EA = 1;	//允许总中断

	PrintString1("STC15系列带串口1测试EEPROM程序!\r\n");	//UART1发送一个字符串

	while(1)
	{
		delay_ms(1);
		if(RX1_TimeOut > 0)		//超时计数
		{
			if(--RX1_TimeOut == 0)
			{
				if(RX1_Buffer[1] == ' ')
				{
					addr = GetAddress();
					if(addr < 63488)	//限制在0~123扇区
					{
						if(RX1_Buffer[0] == 'E')	//PC请求擦除一个扇区
						{
							EEPROM_SectorErase(addr);
							PrintString1("扇区擦除完成!\r\n");
						}

						else if(RX1_Buffer[0] == 'W')	//PC请求写入EEPROM 64字节数据
						{
							EEPROM_write_n(addr,T_Strings,64);
							PrintString1("写入操作完成!\r\n");
						}

						else if(RX1_Buffer[0] == 'R')	//PC请求返回64字节EEPROM数据
						{
							PrintString1("读出的数据如下：\r\n");
							EEPROM_read_n(addr,tmp,64);
							for(i=0; i<64; i++)	TX1_write2buff(tmp[i]);	//将数据返回给串口
							TX1_write2buff(0x0d);
							TX1_write2buff(0x0a);
						}
						else	PrintString1("命令错误!\r\n");
					}
					else	PrintString1("命令错误!\r\n");
				}

				RX1_Cnt = 0;
			}
		}
	}
} 
/**********************************************/


/*************** 发送一个字节 *******************************/
void TX1_write2buff(u8 dat)	//写入发送缓冲
{
	B_TX1_Busy = 1;		//标志发送忙
	SBUF = dat;			//发送一个字节
	while(B_TX1_Busy);	//等待发送完毕
}


//========================================================================
// 函数: void PrintString1(u8 *puts)
// 描述: 串口1发送字符串函数。
// 参数: puts:  字符串指针.
// 返回: none.
// 版本: VER1.0
// 日期: 2014-11-28
// 备注: 
//========================================================================
void PrintString1(u8 *puts)	//发送一个字符串
{
    for (; *puts != 0;	puts++)   	//遇到停止符0结束
	{
		TX1_write2buff(*puts);
	}
}

//========================================================================
// 函数: SetTimer2Baudrate(u16 dat)
// 描述: 设置Timer2做波特率发生器。
// 参数: dat: Timer2的重装值.
// 返回: none.
// 版本: VER1.0
// 日期: 2014-11-28
// 备注: 
//========================================================================
void	SetTimer2Baudrate(u16 dat)
{
	AUXR &= ~(1<<4);	//Timer stop
	AUXR &= ~(1<<3);	//Timer2 set As Timer
	AUXR |=  (1<<2);	//Timer2 set as 1T mode
	TH2 = dat / 256;
	TL2 = dat % 256;
	IE2  &= ~(1<<2);	//禁止中断
	AUXR |=  (1<<4);	//Timer run enable
}

//========================================================================
// 函数: void	UART1_config(void)
// 描述: UART1初始化函数。
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2014-11-28
// 备注: 
//========================================================================
void	UART1_config(void)
{
	AUXR |= 0x01;		//S1 BRT Use Timer2;
	SetTimer2Baudrate(65536UL - (MAIN_Fosc / 4) / Baudrate1);


	SCON = (SCON & 0x3f) | 0x40;	//UART1模式, 0x00: 同步移位输出, 0x40: 8位数据,可变波特率, 0x80: 9位数据,固定波特率, 0xc0: 9位数据,可变波特率
//	PS  = 1;	//高优先级中断
	ES  = 1;	//允许中断
	REN = 1;	//允许接收
	P_SW1 = (P_SW1 & 0x3f) | 0x00;		//UART1 switch to, 0x00: P3.0 P3.1, 0x40: P3.6 P3.7, 0x80: P1.6 P1.7 (必须使用内部时钟)
//	PCON2 |=  (1<<4);	//内部短路RXD与TXD, 做中继, ENABLE,DISABLE

	B_TX1_Busy = 0;
	RX1_Cnt = 0;
}

//========================================================================
// 函数: void UART1_int (void) interrupt UART1_VECTOR
// 描述: UART1中断函数。
// 参数: nine.
// 返回: none.
// 版本: VER1.0
// 日期: 2014-11-28
// 备注: 
//========================================================================
void UART1_int (void) interrupt 4
{
	if(RI)
	{
		RI = 0;
		if(RX1_Cnt >= UART1_BUF_LENGTH)	RX1_Cnt = 0;	//防溢出
		RX1_Buffer[RX1_Cnt++] = SBUF;
		RX1_TimeOut = TimeOutSet1;
	}

	if(TI)
	{
		TI = 0;
		B_TX1_Busy = 0;
	}
}


