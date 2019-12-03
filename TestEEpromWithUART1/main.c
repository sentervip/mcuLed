
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

/*      �����򾭹�������ȫ����, ���ṩ�绰����֧��, �粻������, �����в�����ػ���.  */


/*************	��������˵��	**************

��EEPROM������������д��64�ֽڡ�����64�ֽڵĲ�����

EEPROMͨ�ò��Գ��򡣿����������ļ�"config.h"��ѡ��MCU���͡�

������:  9600,8,N,1. �����������ļ�"config.h"���޸�.

��������:
E 0
     ��EEPROM������������������E��ʾ����, ����0Ϊ0����(ʮ����, 0~126, ������IC).
W 0
     ��EEPROM����д�������W��ʾд��, ����0Ϊ0����(ʮ����, 0~126, ������IC). �������Ŀ�ʼ��ַ����д64�ֽ�.
R 0
     ��EEPROM���ж���������R��ʾ����, ����0Ϊ0����(ʮ����, 0~126, ������IC). �������Ŀ�ʼ��ַ������64�ֽ�.

E 0x1A34
          ��EEPROM������������������E��ʾ����, ����0x1A34Ϊ�����ڵ��ֽڵ�ַ��ʮ������.
W 0x1A34
          ��EEPROM����д�������W��ʾд��, ����0x1A34Ϊ��ʼ��ַ��ʮ������, �������ַ����д64���ֽ�. 
R 0x1A34
          ��EEPROM���ж���������R��ʾ����, ����0x1A34Ϊ��ʼ��ַ��ʮ������, �������ַ������64���ֽ�. 

ע�⣺Ϊ��ͨ�ã�����ʶ�������Ƿ���Ч���û��Լ����ݾ�����ͺ���������

�����ļ�:
STC_EEPROM.c
test_EEPROM.c

����: 2013-5-10

******************************************/

#include	"config.H"
#include	"EEPROM.h"


#define		Baudrate1			115200L
#define		UART1_BUF_LENGTH	10




/*************	���س�������	**************/
u8	code	T_Strings[]={"ȥ����մ����У������һ���ӳ�졣���治֪�δ�ȥ���һ�����Ц���硣"};


/*************	���ر�������	**************/
u8	idata	tmp[70];
u8	idata	RX1_Buffer[UART1_BUF_LENGTH];
u8	RX1_Cnt;
u8	RX1_TimeOut;
bit	B_TX1_Busy;
#define	TimeOutSet1		5


/*************	���غ�������	**************/
void	UART1_config(void);
void 	TX1_write2buff(u8 dat);	//д�뷢�ͻ���
void 	PrintString1(u8 *puts);	//����һ���ַ���


/*************  �ⲿ�����ͱ������� *****************/




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
	if(RX1_Cnt <= 5)	//5���ֽ�����������������ʮ����, ֧������: 	E 0, E 12, E 120
						//											W 0, W 12, W 120
						//											R 0, R 12, R 120
	{
		for(i=2; i<RX1_Cnt; i++)
		{
			if(CheckData(RX1_Buffer[i]) > 9)	return 65535;	//error
			address = address * 10 + CheckData(RX1_Buffer[i]);
		}
		if(address < 124)	//������0~123����
		{
			address <<= 9;
			return (address);
		}
	}
	else if(RX1_Cnt == 8)	//8���ֽ�ֱ�ӵ�ַ������ʮ������, ֧������: E 0x1234, W 0x12b3, R 0x0A00
	{
		if((RX1_Buffer[2] == '0') && ((RX1_Buffer[3] == 'x') || (RX1_Buffer[3] == 'X')))
		{
			for(i=4; i<8; i++)
			{
				if(CheckData(RX1_Buffer[i]) > 0x0F)		return 65535;	//error
				address = (address << 4) + CheckData(RX1_Buffer[i]);
			}
			if(address < 63488)	return (address);	//������0~123����
		}
	}
	
	 return	65535;	//error
}

//========================================================================
// ����: void  delay_ms(u8 ms)
// ����: ��ʱ������
// ����: ms,Ҫ��ʱ��ms��, ����ֻ֧��1~255ms. �Զ���Ӧ��ʱ��.
// ����: none.
// �汾: VER1.0
// ����: 2013-4-1
// ��ע: 
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


/********************* ������ *************************/
void main(void)
{
	u8	i;
	u16 addr;

	P0M1 = 0;	P0M0 = 0;	//����Ϊ׼˫���
	P1M1 = 0;	P1M0 = 0;	//����Ϊ׼˫���
	P2M1 = 0;	P2M0 = 0;	//����Ϊ׼˫���
	P3M1 = 0;	P3M0 = 0;	//����Ϊ׼˫���
	P4M1 = 0;	P4M0 = 0;	//����Ϊ׼˫���
	P5M1 = 0;	P5M0 = 0;	//����Ϊ׼˫���
	P6M1 = 0;	P6M0 = 0;	//����Ϊ׼˫���
	P7M1 = 0;	P7M0 = 0;	//����Ϊ׼˫���

	UART1_config();	// ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer1��������.
	EA = 1;	//�������ж�

	PrintString1("STC15ϵ�д�����1����EEPROM����!\r\n");	//UART1����һ���ַ���

	while(1)
	{
		delay_ms(1);
		if(RX1_TimeOut > 0)		//��ʱ����
		{
			if(--RX1_TimeOut == 0)
			{
				if(RX1_Buffer[1] == ' ')
				{
					addr = GetAddress();
					if(addr < 63488)	//������0~123����
					{
						if(RX1_Buffer[0] == 'E')	//PC�������һ������
						{
							EEPROM_SectorErase(addr);
							PrintString1("�����������!\r\n");
						}

						else if(RX1_Buffer[0] == 'W')	//PC����д��EEPROM 64�ֽ�����
						{
							EEPROM_write_n(addr,T_Strings,64);
							PrintString1("д��������!\r\n");
						}

						else if(RX1_Buffer[0] == 'R')	//PC���󷵻�64�ֽ�EEPROM����
						{
							PrintString1("�������������£�\r\n");
							EEPROM_read_n(addr,tmp,64);
							for(i=0; i<64; i++)	TX1_write2buff(tmp[i]);	//�����ݷ��ظ�����
							TX1_write2buff(0x0d);
							TX1_write2buff(0x0a);
						}
						else	PrintString1("�������!\r\n");
					}
					else	PrintString1("�������!\r\n");
				}

				RX1_Cnt = 0;
			}
		}
	}
} 
/**********************************************/


/*************** ����һ���ֽ� *******************************/
void TX1_write2buff(u8 dat)	//д�뷢�ͻ���
{
	B_TX1_Busy = 1;		//��־����æ
	SBUF = dat;			//����һ���ֽ�
	while(B_TX1_Busy);	//�ȴ��������
}


//========================================================================
// ����: void PrintString1(u8 *puts)
// ����: ����1�����ַ���������
// ����: puts:  �ַ���ָ��.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void PrintString1(u8 *puts)	//����һ���ַ���
{
    for (; *puts != 0;	puts++)   	//����ֹͣ��0����
	{
		TX1_write2buff(*puts);
	}
}

//========================================================================
// ����: SetTimer2Baudrate(u16 dat)
// ����: ����Timer2�������ʷ�������
// ����: dat: Timer2����װֵ.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void	SetTimer2Baudrate(u16 dat)
{
	AUXR &= ~(1<<4);	//Timer stop
	AUXR &= ~(1<<3);	//Timer2 set As Timer
	AUXR |=  (1<<2);	//Timer2 set as 1T mode
	TH2 = dat / 256;
	TL2 = dat % 256;
	IE2  &= ~(1<<2);	//��ֹ�ж�
	AUXR |=  (1<<4);	//Timer run enable
}

//========================================================================
// ����: void	UART1_config(void)
// ����: UART1��ʼ��������
// ����: none.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void	UART1_config(void)
{
	AUXR |= 0x01;		//S1 BRT Use Timer2;
	SetTimer2Baudrate(65536UL - (MAIN_Fosc / 4) / Baudrate1);


	SCON = (SCON & 0x3f) | 0x40;	//UART1ģʽ, 0x00: ͬ����λ���, 0x40: 8λ����,�ɱ䲨����, 0x80: 9λ����,�̶�������, 0xc0: 9λ����,�ɱ䲨����
//	PS  = 1;	//�����ȼ��ж�
	ES  = 1;	//�����ж�
	REN = 1;	//��������
	P_SW1 = (P_SW1 & 0x3f) | 0x00;		//UART1 switch to, 0x00: P3.0 P3.1, 0x40: P3.6 P3.7, 0x80: P1.6 P1.7 (����ʹ���ڲ�ʱ��)
//	PCON2 |=  (1<<4);	//�ڲ���·RXD��TXD, ���м�, ENABLE,DISABLE

	B_TX1_Busy = 0;
	RX1_Cnt = 0;
}

//========================================================================
// ����: void UART1_int (void) interrupt UART1_VECTOR
// ����: UART1�жϺ�����
// ����: nine.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void UART1_int (void) interrupt 4
{
	if(RI)
	{
		RI = 0;
		if(RX1_Cnt >= UART1_BUF_LENGTH)	RX1_Cnt = 0;	//�����
		RX1_Buffer[RX1_Cnt++] = SBUF;
		RX1_TimeOut = TimeOutSet1;
	}

	if(TI)
	{
		TI = 0;
		B_TX1_Busy = 0;
	}
}

