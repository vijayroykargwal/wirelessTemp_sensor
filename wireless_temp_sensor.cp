#line 1 "C:/Users/vijay kargwal/Desktop/New folder/wireless_temp_sensor.c"

sbit LCD_D7 at RB2_bit;
sbit LCD_D6 at RB3_bit;
sbit LCD_D5 at RB4_bit;
sbit LCD_D4 at RB5_bit;
sbit LCD_EN at RB6_bit;
sbit LCD_RS at RB7_bit;
sbit LCD_D7_Direction at TRISB2_bit;
sbit LCD_D6_Direction at TRISB3_bit;
sbit LCD_D5_Direction at TRISB4_bit;
sbit LCD_D4_Direction at TRISB5_bit;
sbit LCD_EN_Direction at TRISB6_bit;
sbit LCD_RS_Direction at TRISB7_bit;

int temp;
char txt [7];


char AT[]= "AT";
char noecho[]="ATE0";
char mode_text[]="AT+CMGF=1";
char mobile_no[]="AT+CMGS=\”+917877023341\”";
char terminator=0x1A;
char text1[]="temperature=";

void READ_temp(void)
{
temp = ADC_Read(0);
temp = temp * 0.4887;
}
void data_converstion(void)
{
inttostr(temp,txt);
}
void display(void)
{
lcd_out(1,1,"TEMPERATURE=");
lcd_out(1,13, Ltrim(txt));
Lcd_Chr_Cp(0xdf);
Lcd_Chr_Cp('C');
Lcd_Chr_Cp(' ');
}

void send_to_modem(char *s)
{
while(*s)
{
UART1_WRITE(*s++);
}
UART1_WRITE(0X0D);
}
void send_to_modem1(char *s)
{
while(*s)
UART1_WRITE(*s++);
}
void send_sms()
{
send_to_modem1(text1);
delay_ms(1000);
send_to_modem1(txt);
delay_ms(1000);
uart1_write(terminator);
delay_ms(1000);
}
void main()
{
lcd_init();
ADC_Init();
Uart1_Init(9600);
while(1)
{ READ_temp();
delay_ms(100);
data_converstion();
delay_ms(100);
display();
delay_ms(100);
send_to_modem(AT);
delay_ms(1000);
send_to_modem(noecho);
delay_ms(1000);
send_to_modem(mode_text);
delay_ms(1000);
send_to_modem(mobile_no);
delay_ms(1000);
send_sms();
delay_ms(10000);
}
}
