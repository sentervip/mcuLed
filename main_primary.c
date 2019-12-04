
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
#define us5 7
#define us15 7
#define rnb1 16
//sfr IAP_DATA =0xC2;
//sfr IAP_ADDRH =0xC3;
//fr IAP_ADDRL =0xC4;
//sfr IAP_CMD =0xC5;
//sfr IAP_TRIG =0xC6;
//sfr IAP_CONTR =0xC7;


#include    "config.h"
//#include  "reg51.h"
#include    "GPIO.h"
#include <intrins.h>
//#include "eeprom.h"

//#include  "delay.h"
//#include  "datzbbw.h"

//# define PI 3.14

 
unsigned char code  cr[]={63,0x00,0x00,63,63,0x00,63};
unsigned char code  cg[]={0x00,63,0x00,63,0x00,63,63};
unsigned char code  cb[]={0x00,0x00,63,0x00,63,63,63};
 
   
//unsigned char     code    Tstr[]={0x4,0x4,0x4,0x4};    
//unsigned char  data_epr [4];  
//unsigned int addr;

 
void    GPIO_config(void);
void delay_us(unsigned char t);
//void del_ms(unsigned char t)  ;

 void read_rem( void );
void add_rgb(unsigned  char a0,unsigned  char a1,unsigned  char r,unsigned  char g,unsigned  char b, u16 n);
void md1();
void md0();
void md2();
void md22();
void md3();
void md4();
void md5();
void md6();
void md7();
void md8();
void play1();

/*
void mode1();
  void mode2();
  void mode3();
  void mode30();
  void mode40();
  void mode50();
  void mode60();
  void mode70();
 void mode80();
 // void mode80();
void ww_gold(unsigned char x);
void gold_pink(unsigned char x);
void pink_red(unsigned char x);
void red_purple(unsigned char x);
void purple_blue(unsigned char x);
void blue_green(unsigned char x);
void green_6color();
void red_green();
void red_green_multi();
void multi_W_shine();
void WW_multi();
void pr(unsigned int addr,u8 dat  );
void IapIdle();
unsigned char  rd(unsigned int addr);
void er(unsigned int addr);
*/
//  void mode7();
//unsigned long sum;
unsigned char j,p,r,g,b,r1,g1,b1,mode,br,mode_old,res;
unsigned char r2,g2,b2;
unsigned char  i,k;
 unsigned char  temp;
void delay_us(unsigned char t)
{
unsigned char i;
for (i=0;i<t;i++)
{
}

}
/*
void del_ms(unsigned char t)    
{
unsigned char i;
for (i=0;i<t;i++)
{
 delay_us(200);
}

}
 */
void    GPIO_config(void)
{
    GPIO_InitTypeDef    GPIO_InitStructure;     
    GPIO_InitStructure.Pin  = GPIO_Pin_3;   
    GPIO_InitStructure.Mode = GPIO_OUT_PP;      
    GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);  

//  GPIO_InitTypeDef    GPIO_InitStructure;     
    GPIO_InitStructure.Pin  = GPIO_Pin_0;   
    GPIO_InitStructure.Mode = GPIO_OUT_PP;      
    GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);   ///clk

    
    GPIO_InitStructure.Pin  = GPIO_Pin_3;   
    GPIO_InitStructure.Mode = GPIO_PullUp;      
    GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);
    
    P10=1;  
}
/*
void IapIdle()
{
IAP_CONTR=0;
    IAP_CMD=0;
    IAP_TRIG=0;
    IAP_ADDRH=0x80;
    IAP_ADDRL=0;
}

void pr(unsigned int addr,unsigned char dat  )
{
IAP_CONTR =ENABLE_IAP;
IAP_CMD=CMD_PROGRAM;
IAP_ADDRL=addr;
IAP_ADDRH=addr>>8;
IAP_TRIG=0x5a;
IAP_TRIG=0xa5;
_nop_();    
    IapIdle();
}
unsigned char  rd(unsigned int addr)
{
unsigned char dat;
IAP_CONTR =ENABLE_IAP;
IAP_CMD=CMD_READ;
IAP_ADDRL=addr;
IAP_ADDRH=addr>>8;
IAP_TRIG=0x5a;
IAP_TRIG=0xa5;
_nop_();    
    dat=IAP_DATA;
    IapIdle();
    return dat; 
}
void er(unsigned int addr)
{
IAP_CONTR =ENABLE_IAP;
IAP_CMD=CMD_ERASE;
IAP_ADDRL=addr;
IAP_ADDRH=addr>>8;
IAP_TRIG=0x5a;
IAP_TRIG=0xa5;
_nop_();    
    IapIdle();
}

*/


/**************************************/
void main(void)
{
//del_ms(500);  
    GPIO_config();
//EA = 1;
//  del_ms(500);
//  add_rgb(0,0,0,0x00,0x00,0xff,1);
    //read_rem();
    //  del_ms(5);
    //read_rem();
  br=0;
 // if ((mode>0)&&(mode<20)) mode=mode;else mode=2;
  res=0;
 //  speed=1;
    mode=2;
  mode_old=mode;
//  on_off=1;
    //sum=0;
    //timer=0;
    //  add_rgb(0,0,0,0,0,0,10);
//  sum=0;
//  addr=0x0;
    //er (IAP_ADDRESS);         
//  er (IAP_ADDRESS);           
//  pr (IAP_ADDRESS,10);
    //pr (IAP_ADDRESS,10);
    //mode=rd (IAP_ADDRESS);
    //mode=rd (IAP_ADDRESS);
//EEPROM_SectorErase(IAP_ADDRESS);
//EEPROM_write_n(IAP_ADDRESS,Tstr,4);
//EEPROM_read_n(IAP_ADDRESS,data_epr,4);
//mode=data_epr[0];
//mode=10;
// mode_old=mode;
//speed=data_epr[1];
//br=data_epr[2];
r2=0;g2=0;b2=0;
add_rgb(0,0,0,0,0,10); 
while (1)
{
//if ((P1&0x2)==0x0 )
//{
// read_rem();
//}


  
if (mode==1) { md1();}
if (mode==2) { md3();}
if (mode==3) {r1=0x00;g1=32;b1=0x00;md0(); md5();}
if (mode==3) {r1=32;g1=32;b1=0x00;md0(); md5();}
if (mode==3) {r1=16;g1=16;b1=16;md0(); md4();}
if (mode==3) {r1=32;g1=0x00;b1=16;md0(); md5();}
if (mode==4) { md6();}
if (mode==5) { md2();}
if (mode==6) {r1=32;g1=0;b1=0;md0(); md7();}
if (mode==6) {r1=0;g1=32;b1=0;md0(); md7();}
if (mode==6) {r1=32;g1=32;b1=0;md0(); md7();}
if (mode==6) {r1=32;g1=0;b1=16;md0(); md7();}
if (mode==8) { md8();}
if (mode==9) { md22();}
if (mode==10) { play1();}


if (mode==7) { 
    

    if (mode==7) { md1();}
if (mode==7) { md3();}
if (mode==7) {r1=0x00;g1=32;b1=0x00;md0(); md5();}
if (mode==7) {r1=32;g1=32;b1=0x00;md0(); md5();}
if (mode==7) {r1=16;g1=16;b1=16;md0(); md4();}
if (mode==7) {r1=32;g1=0x00;b1=16;md0(); md5();}
if (mode==7) { md6();}
if (mode==7) { md2();}
if (mode==7) {r1=32;g1=0;b1=0;md0(); md7();}
if (mode==7) {r1=0;g1=32;b1=0;md0(); md7();}
if (mode==7) {r1=32;g1=32;b1=0;md0(); md7();}
if (mode==7) {r1=32;g1=0;b1=16;md0(); md7();}

}   
/*
if (mode==8) 
{ 
if (mode==8)    md1();
if (mode==8)    md2();
if (mode==8)    md3();
if (mode==8)    md4();
if (mode==8)    md5();
if (mode==8)    md6();
if (mode==8)    md7();

}
*/
//if (on_off==1)
/*
{
 if (mode==2) ww_gold(1);
 if (mode==3) gold_pink(1);
 if (mode==4) pink_red(1);
 if (mode==5) red_purple(1);
 if (mode==6) purple_blue(1);
 if (mode==7) blue_green(1);
 if (mode==8) green_6color();
// if (mode==12) red_green();
// if (mode==13) red_green_multi();
 if (mode==9) multi_W_shine();
// if (mode==15) WW_multi();
if (mode==10) { r=0xff;g=0x00;b=0xff;  mode30();}
if (mode==11) {r1=0x0;g1=0xff;b1=0xff; 
if (mode==11)   mode40();r1=0x0;g1=0xff;b1=0;r=0xff;g=0xff;b=0xff;
if (mode==11)   mode40();
}
if (mode==12) {r1=0x0;g1=0x0;b1=0;r=0xff;g=0xff;b=0xff; mode50();}
if (mode==13) {r1=0x0;g1=0xf;b1=0;r=0xff;g=0xff;b=0xff; mode50();}
//if (mode==20) {r1=0xf;g1=0xf;b1=0;r=0xff;g=0xff;b=0xff; mode50();}
if (mode==14) { mode60();}
if (mode==15) { mode70();}
if (mode==16) { mode80();}
if (mode==17) 
    
{
 //if (mode==21) mode1();
 //if (mode==21) mode2();
 //if (mode==21) mode3();
 if (mode==17) ww_gold(0);
 if (mode==17) gold_pink(0);
 if (mode==17) pink_red(0);
 if (mode==17) red_purple(0);
 if (mode=17) purple_blue(0);
 if (mode==17) blue_green(0);
 if (mode==17) green_6color();  
 //if (mode==21)    red_green();
 //if (mode==21) red_green_multi();
 //if (mode==21) multi_W_shine();
//  if (mode==21) WW_multi();
  if (mode==17) {r=0xff;g=0x00;b=0xff; 
 if (mode==17)  mode30();r=0xff;g=0xff;b=0x00; 
     if (mode==17) mode30();    }
    
 if (mode==17)  {mode40();r1=0x0;g1=0xff;b1=0;r=0xff;g=0xff;b=0xff;
     if (mode==17) mode40();
 r1=0xff;g1=0xff;b1=0;r=0x0;g=0x0;b=0xff; 
  if (mode==17) mode40();}
 
 
  if (mode==17) 
    {r1=0x0;g1=0x0;b1=0;r=0xff;g=0xff;b=0xff; mode50();}
  if (mode==17) 
    {r1=0x0;g1=0xf;b1=0;r=0xff;g=0xff;b=0xff; mode50();}
 // if (mode==21) 
//  {r1=0xf;g1=0xf;b1=0;r=0xff;g=0xff;b=0xff; mode50();}
 if (mode==17)  mode60();
 if (mode==17)  mode70();
//if (mode==21)     mode80();
    
}



}
*/

}
 ///////////////////////////////
}


 void read_rem( void )
 {
// unsigned char i;
     mode++;
     if (mode>10) mode=1;
     if (mode!=mode_old)    {res=1;mode_old=mode;}
     /*
  unsigned char bb[57];
  for (i=0;i<56;i++)
  {
 P10=0;
 delay_us(150);
  bb[i]=((P1&0x2)>>1);
  P10=1;
 delay_us(150);

 }
 res=0;
br=((bb[48-8]<<7)|(bb[49-8]<<6)|(bb[50-8]<<5)|(bb[51-8]<<4)|(bb[52-8]<<3)|(bb[53-8]<<2)|(bb[54-8]<<1)|(bb[55-8]<<0));
speed=((bb[48-16]<<7)|(bb[49-16]<<6)|(bb[50-16]<<5)|(bb[51-16]<<4)|(bb[52-16]<<3)|(bb[53-16]<<2)|(bb[54-16]<<1)|(bb[55-16]<<0));
mode=((bb[48-24]<<7)|(bb[49-24]<<6)|(bb[50-24]<<5)|(bb[51-24]<<4)|(bb[52-24]<<3)|(bb[53-24]<<2)|(bb[54-24]<<1)|(bb[55-24]<<0));
func=((bb[48]<<7)|(bb[49]<<6)|(bb[50]<<5)|(bb[51]<<4)|(bb[52]<<3)|(bb[53]<<2)|(bb[54]<<1)|(bb[55]<<0));
//if (func==1)
//{
//if (timer==0) {timer=1;sum=0;} //else {timer=0;sum=0;}
//} else timer=0;
//br=10-br;
//speed=8-((speed-30)/10);
if (mode!=mode_old) {res=1;mode_old=mode;}
if ((mode==1)&&(on_off==1)) on_off=0; else on_off=1;
*/


 }

void add_rgb(unsigned  char a0,unsigned  char a1,unsigned  char r,unsigned  char g,unsigned  char b, u16 n)
 {
unsigned char j,tmp,i;
 u16 ii;


//  a0=0xff;
tmp=0x1;
for(j=0;j<6;j++)
{
P1=P1&0xF7;
delay_us(us5);
if ((a0&tmp)==0) {P1=(P1|0x8);} else {P1=P1&0xF7;}delay_us(us15);
tmp=tmp<<1;
P1=(P1|0x8); 
delay_us(10);
}

tmp=0x1;
for(j=0;j<4;j++)
{
P1=P1&0xF7;
delay_us(us5);
if ((a1&tmp)==0) {P1=(P1|0x8);} else {P1=P1&0xF7;}delay_us(us15);
tmp=tmp<<1;
P1=(P1|0x8); 
delay_us(10);
}
tmp=0x1;
for(j=0;j<6;j++)
{
P1=P1&0xF7;
delay_us(us5);
if ((r&tmp)==0) {P1=(P1|0x8);} else {P1=P1&0xF7;}delay_us(us15);
tmp=tmp<<1;
P1=(P1|0x8); 
delay_us(10);
}

tmp=0x1;
for(j=0;j<6;j++)
{
P1=P1&0xF7;
delay_us(us5);
if ((g&tmp)==0) {P1=(P1|0x8);} else {P1=P1&0xF7;}delay_us(us15);
tmp=tmp<<1;
P1=(P1|0x8); 
delay_us(10);
}

tmp=0x1;
for(j=0;j<6;j++)
{
P1=P1&0xF7;
delay_us(us5);
if ((b&tmp)==0) {P1=(P1|0x8);} else {P1=P1&0xF7;}delay_us(us15);
tmp=tmp<<1;
P1=(P1|0x8); 
delay_us(10);
}

//delay_us(us5);
P1=P1&0xF7; 
 delay_us(36);
P1=(P1|0x8); 
delay_us(36);   
/*
if ((P3&0x8)==0x0 )
{
i=0;
while(((P3&0x8)==0x0 )&&(i<200))
{
delay_us(200);
i++;
}   
if (i>190)
{
    while((P3&0x8)==0x0 );
 read_rem();}
}
*/
/////////////////////////////////////
for (ii=0;ii<n;ii++)
{
delay_us(200);
if ((P3&0x8)==0x0 )
{
i=0;
while(((P3&0x8)==0x0 )&&(i<200))
{
delay_us(200);
i++;
}   
if (i>190)
{
    while((P3&0x8)==0x0 );
 read_rem();break;}
}
}

} 
 void md0()//
 {
for(k=0;k<64;k++)   
{    
  if (r2>r1) r2--; else {if (r2<r1) r2++;}
  if (g2>g1) g2--; else {if (g2<g1) g2++;}
  if (b2>b1) b2--; else {if (b2<b1) b2++;}
     add_rgb(0,0,r2,g2,b2,200); if (res==1) goto m_end;
    if ((r1==r2)&&(g1==g2)&&(b1==b2)) break;
}
 r2=r1;g2=g1;b2=b1;
m_end:
 res=0;

 }
 
 void md1()//
 {
 unsigned char k,j,i,t;
for (k=0;k<7;k++)
{
r=cr[k];g=cg[k];b=cb[k];    
i=1; 
while(i<64)
{   
add_rgb(i,0,r,g,b,200); if (res==1) goto m_end;
 i+=1;
}//i
add_rgb(i-1,0,r,g,b,6000); if (res==1) goto m_end;

}
m_end:
 res=0;
 
 }
 void md2()//shine
 {
 
unsigned char k,j,i,t,r2,g2,b2;
for (k=0;k<2;k++)
{
i=1; 
while(i<64)
{   
j=0;
        r1=cr[i%6]>>2;g1=cg[i%6]>>2;b1=cb[i%6]>>2;
    r=r1;g=g1;b=b1;r2=63;g2=63;b2=63;
 while(j<64)
 {   
j+=1;
if (r<63) r++;if (g<63) g++;if (b<63) b++;
add_rgb(i,0,r,g,b,10); if (res==1) goto m_end;
if (r2>r1) r2--;if (g2>g1) g2--;if (b2>b1) b2--;
if (i==1) t=63; else t=i-1;
add_rgb(t,0,r2,g2,b2,10); if (res==1) goto m_end;
//j
}
 i+=1;
}//i
} //k
////////////////////////////////

 m_end:
 res=0;

}
void md22()//shine
 {
 
unsigned char k,j,i,t,r2,g2,b2,r3,g3,b3;
//unsigned char cr1[6],cg1[6],cb1[6];
//for (t=0;t<6;t++)
{
//  cr1[t]=cr[t];cg1[t]=cg[t];cb1[t]=cb[t];
}   

     for (k=0;k<6;k++)
{
i=0; 
while(i<6)
{   
j=0;
        r1=cr[(i+2+k)%6];g1=cg[(i+2+k)%6];b1=cb[(i+2+k)%6];
      r=cr[(i+1+k)%6];g=cg[(i+1+k)%6];b=cb[(i+1+k)%6];
      r3=cr[(i+0)%6]>>0;g3=cg[(i+0)%6]>>0;b3=cb[(i+0)%6]>>0;
      r2=r;g2=g;b2=b;
 while(j<64)
 {   
j+=1;
if (r<r1) r++;if (g<g1) g++;if (b<b1) b++;
if (r>r1) r--;if (g>g1) g--;if (b>b1) b--;
//add_rgb((1*i+1)%63+1,0,r,g,b,130); if (res==1) goto m_end;
add_rgb(0,(i+1)%6+1,r,g,b,60); if (res==1) goto m_end;
     
if (r2>r3) r2--;if (g2>g3) g2--;if (b2>b3) b2--;
if (r2<r3) r2++;if (g2<g3) g2++;if (b2<b3) b2++;
//add_rgb((1*i)%63+1,0,r2,g2,b2,130); if (res==1) goto m_end;
//add_rgb(0,(i%6)+1,r2,g2,b2,330); if (res==1) goto m_end;
//j
}
 i+=1;
}//i
} //k
////////////////////////////////

 m_end:
 res=0;

}

void md3()
 {
 unsigned char k;
//r=255;g=10;b=255;
//add_rgb(0,0,0,255,0,0,1); if (res==1) goto m_end;
     
     
     
 for(k=0;k<64;k++)  
{
add_rgb(0,0,k,0,0,195);if (res==1) goto m_end;  
}
 for(k=0;k<64;k++)  
{
add_rgb(0,0,63,k,0,195);if (res==1) goto m_end; 
}
 for(k=0;k<64;k++)  
{
add_rgb(0,0,63-k,63,0,195);if (res==1) goto m_end;  
}
 for(k=0;k<64;k++)  
{
add_rgb(0,0,0,63,k,195);if (res==1) goto m_end; 
}
 for(k=0;k<64;k++)  
{
add_rgb(0,0,0,63-k,63,195);if (res==1) goto m_end;  
}

 for(k=0;k<64;k++)  
{
add_rgb(0,0,k,0,63,195);if (res==1) goto m_end; 
}
 for(k=0;k<64;k++)  
{
add_rgb(0,0,63,k,63,195);if (res==1) goto m_end;    
}
 for(k=0;k<64;k++)  
{
add_rgb(0,0,63,63,63-k,195);if (res==1) goto m_end; 
}
 for(k=0;k<64;k++)  
{
add_rgb(0,0,63-k,63,0,195);if (res==1) goto m_end;  
}
 for(k=0;k<64;k++)  
{
add_rgb(0,0,0,63-k,0,195);if (res==1) goto m_end;   
}
     
//////////////////////////////////   
 for(k=0;k<64;k++)  
{
add_rgb(0,0,k,0,0,195);if (res==1) goto m_end;  
}

 for(k=0;k<64;k++)  
{
add_rgb(0,0,63-k,0x0,0,195);if (res==1) goto m_end; 
}
/////////////////////
 for(k=0;k<64;k++)  
{
add_rgb(0,0,0,k,0,195);if (res==1) goto m_end;  
}

 for(k=0;k<64;k++)  
{
add_rgb(0,0,0,63-k,0x0,195);if (res==1) goto m_end; 
}
///////////////////////////////
 for(k=0;k<64;k++)  
{
add_rgb(0,0,0,0,k,195);if (res==1) goto m_end;  
}

 for(k=0;k<64;k++)  
{
add_rgb(0,0,0,0x0,63-k,195);if (res==1) goto m_end; 
}

///////////////////////////////
 for(k=0;k<64;k++)  
{
add_rgb(0,0,k,k,k,195);if (res==1) goto m_end;  
}

 for(k=0;k<64;k++)  
{
add_rgb(0,0,63-k,63-k,63-k,195);if (res==1) goto m_end; 
}



 m_end:
 res=0;
}


void md4()///shine
 {
 unsigned char j;
  i=1;
    j=0;
     while (j<2)
{
    i=1;
while (i<64)
{
add_rgb(i,0,0xff,0xff,0x0,130);if (res==1) goto m_end;
add_rgb(i,0,r1,g1,b1,1);if (res==1) goto m_end;
i++;
}//i
j++;
}
 m_end:
  res=0;
 }

 



  void md5()///blink
 {
     unsigned char j;
  i=1;
    j=0;
     while (j<2)
{
    i=1;
while (i<64)
{
add_rgb(i,0,0xff,0xff,0xff,130);if (res==1) goto m_end;
add_rgb(i,0,r1,g1,b1,1);if (res==1) goto m_end;
i++;
}//i
j++;
}
 m_end:
  res=0;

}
 
void md6()///blink_multi
 {
     unsigned char t;
     for(k=0;k<3;k++)
     {
 j=0;
 while (j<2)
 {
  i=1;
while (i<64)
{
    r1=cr[i%6];g1=cg[i%6];b1=cb[i%6];
add_rgb(i,0,0xff,0xff,0xff,130);if (res==1) goto m_end;
    
add_rgb(i,0,r1>>2,g1>>2,b1>>2,1);if (res==1) goto m_end;
i++;
}//i
j++;
} //j
 }

 m_end:
  res=0;
 }
/*
void md66()///blink_multi
 {
     unsigned char t;
     for(k=0;k<3;k++)
     {
 j=0;
 while (j<2)
 {
  i=1;
while (i<64)
{
    r1=cr[i%6];g1=cg[i%6];b1=cb[i%6];
add_rgb(i,0,0xff,0xff,0xff,130);if (res==1) goto m_end;
    
add_rgb(i,0,r1>>2,g1>>2,b1>>2,1);if (res==1) goto m_end;
i++;
}//i
j++;
} //j
 }

 m_end:
  res=0;
 }
*/
 
 
 
   void md7()//shine
 {
 unsigned char k,j,i,t,r2,g2,b2;
for (k=0;k<2;k++)
{
i=0; 
while(i<31)
{   
j=0;
    r=r1;g=g1;b=b1;r2=63;g2=63;b2=63;
 while(j<64)
 {   
j+=1;
if (r<63) r++;if (g<63) g++;if (b<63) b++;
add_rgb((2*i+0)%63+1,0,r,g,b,10); if (res==1) goto m_end;
add_rgb((2*i+1)%63+1,0,r,g,b,10); if (res==1) goto m_end;
if (r2>r1) r2--;if (g2>g1) g2--;if (b2>b1) b2--;
//if (i==1) t=63; else t=i-1;
add_rgb((2*i-1)%63+1,0,r2,g2,b2,10); if (res==1) goto m_end;
add_rgb((2*i-2)%63+1,0,r2,g2,b2,10); if (res==1) goto m_end;
//j
}
 i+=1;
}//i
} //k
////////////////////////////////

 m_end:
 res=0;
   ///////////////////////////////////////////
}


 
void md8()///shine
 {
 unsigned char j;
unsigned char m[14];
      char tmp,i;
    
    j=1;
     m[0]=10;m[1]=20;m[2]=30;m[3]=40;m[4]=50;m[5]=60;
     m[6]=50;m[7]=40;m[8]=30;m[9]=20;m[10]=10;m[11]=20;m[12]=30;m[13]=40;
for(k=0;k<6;k++)
{
for(j=1;j<7;j++)
{
for(i=0;i<10;i++)
{
if (m[j-1+k+1]== m[j-1+k])  tmp=0;
    add_rgb(0,j,m[j-1+k]+0-0,0x0,0x0,2);if (res==1) goto m_end;
    
    
if (m[j-1+k+1]> m[j-1+k])   //tmp=i;
//if (m[j-1+k+1]== m[j-1+k])    tmp=0;
//if (m[j-1+k+1]< m[j-1+k]) tmp=-i;

    add_rgb(0,j,m[j-1+k]+i-0,0x0,0x0,2);if (res==1) goto m_end;
if (m[j-1+k+1]< m[j-1+k])   //tmp=-i;
    add_rgb(0,j,m[j-1+k]-i-0,0x0,0x0,2);if (res==1) goto m_end;
}//i
}
}

 m_end:
  res=0;
 }

 
 
   void play1()
 {
 
 unsigned char a,r,g,b;//,t,tt;
 int k,t,tt;

  //while(1)
  {
  for (k=0;k<96;k++)
  {
 a=1;
 while(a<6)
    {
    tt=((k+a)/rnb1)%3;
    t=(k+a)%rnb1;
    if (tt==0) {r=255-(t*16);g=(t*16);b=0;}
  if (tt==1) {g=255-(t*16);b=(t*16);r=0;}
if (tt==2) {b=255-(t*16);r=(t*16);g=0;}
   add_rgb(0,a+0,r>>2,g>>2,b>>2,100);if (res==1) goto m_end;
   a++;
    } //while
  }//for
    }
   m_end:
  res=0;

 }  

 
 /*
 void mode60()///shine
 {
 j=0;
 while (j<8)
 {
  i=1;
while (i>0)
{
add_rgb(0,m1[j+1],0,i,i,i,speed);if (res==1) goto m_end;
add_rgb(0,m1[j],0,0xff-i,0xff-i,0xff-i,speed);if (res==1) goto m_end;
i++;
}//i
j++;
} //j
 m_end:
  res=0;
 }
void mode70()///shine
 {
 j=0;
 while (j<8)
 {
  i=1;
while (i<240)
{
add_rgb(0,m1[j+1],0,i,i+15,i,speed);if (res==1) goto m_end;
add_rgb(0,m1[j],0,239-i,0xff-i,239-i,speed);if (res==1) goto m_end;
i++;
}//i
j++;
} //j
 m_end:
  res=0;
 }
 void mode80()
 {
 unsigned char k,j,i,i1,tmp;
 //for (k=0;k<8;k++)
 //{
//for (j=5;j<13;j++)
 //{
for (k=0;k<7;k++)
//if  k=0; {r=0xff;g=0x0;b=0x0;}
    { r=cr2[k];
     g=cg2[k];
     b=cb2[k];
 
    for (j=6;j<14;j++)
 {
 
 i=1;
while (i<9)
{
add_rgb(m1[j-6],i,0,r>>(0+7),g>>(0+7),b>>(0+7),speed); if (res==1) goto m_end;
add_rgb(m1[j-5],i,0,r>>(0+6),g>>(0+6),b>>(0+6),speed); if (res==1) goto m_end;
add_rgb(m1[j-4],i,0,r>>(0+5),g>>(0+5),b>>(0+5),speed); if (res==1) goto m_end;
add_rgb(m1[j-3],i,0,r>>(0+4),g>>(0+4),b>>(0+4),speed); if (res==1) goto m_end;
add_rgb(m1[j-2],i,0,r>>(0+3),g>>(0+3),b>>(0+3),speed); if (res==1) goto m_end;
add_rgb(m1[j-1],i,0,r>>(0+2),g>>(0+2),b>>(0+2),speed); if (res==1) goto m_end;
add_rgb(m1[j+0],i,0,r>>(0+1),g>>(0+1),b>>(0+1),speed); if (res==1) goto m_end;
add_rgb(m1[j+1],i,0,r>>(0+0),g>>(0+0),b>>(0+0),speed); if (res==1) goto m_end;
i+=1;
}//i
 }//j
 }//k
 m_end:
 res=0;
 }
*/
 /*
 void mode70()///shine
 {
 j=0;
 while (j<9)
 {
  i=1;
while (i<240)
{
add_rgb(0,m1[j+1],0,i,i+15,i,speed);if (res==1) goto m_end;
add_rgb(0,m1[j],0,239-i,239-i,239-i,speed);if (res==1) goto m_end;
i++;
}//i
j++;
} //j
 m_end:
  res=0;
 }
void mode80()///shine
 {
 j=0;
 while (j<9)
 {
  i=1;
while (i<240)
{
add_rgb(0,m1[j+1],0,i+15,i,i+15,speed);if (res==1) goto m_end;
add_rgb(0,m1[j],0,239-i,239-i,239-i,speed);if (res==1) goto m_end;
i++;
}//i
j++;
} //j
 m_end:
  res=0;
 }
 /*
 void mode70()///shine
 {
 j=0;
 while (j<9)
 {
  i=1;
while (i<240)
{
add_rgb(0,m1[j+1],0,i,i+15,i);
add_rgb(0,m1[j],0,239-i,0xff-i,239-i);
i++;
 del_ms(30);
}//i
j++;
} //j
 }
 */
 




