#include <reg51.h>

#define LCD P2

sbit RS = P3^0;
sbit RW = P3^1;
sbit EN = P3^2;

sbit C1 = P1^0;
sbit C2 = P1^1;
sbit C3 = P1^2;
sbit C4 = P1^3;
sbit RESULT = P1^4;

unsigned char vote1=0;
unsigned char vote2=0;
unsigned char vote3=0;
unsigned char vote4=0;

void delay()
{
    unsigned int i,j;
    for(i=0;i<300;i++)
        for(j=0;j<1275;j++);
}
void lcd_cmd(unsigned char cmd)
{
    LCD = cmd;
    RS = 0;
    RW = 0;
    EN = 1;
    delay();
    EN = 0;
}
void lcd_data(unsigned char dat)
{
    LCD = dat;
    RS = 1;
    RW = 0;
    EN = 1;
    delay();
    EN = 0;
}

void lcd_string(char *str)
{
    while(*str)
    {
        lcd_data(*str++);
    }
}
void lcd_init()
{
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}
void lcd_number(unsigned char num)
{
    lcd_data(num + '0');
}
void check_vote()
{
    if(C1 == 0)
    {
        vote1++;
        lcd_cmd(0x01);
        lcd_string("Vote Recorded");
        delay();
        while(C1 == 0);
    }

    if(C2 == 0)
    {
        vote2++;
        lcd_cmd(0x01);
        lcd_string("Vote Recorded");
        delay();
        while(C2 == 0);
    }

    if(C3 == 0)
    {
        vote3++;
        lcd_cmd(0x01);
        lcd_string("Vote Recorded");
        delay();
        while(C3 == 0);
    }

    if(C4 == 0)
    {
        vote4++;
        lcd_cmd(0x01);
        lcd_string("Vote Recorded");
        delay();
        while(C4 == 0);
    }
}
void show_result()
{
    lcd_cmd(0x01);
    lcd_string("C1=");
    lcd_number(vote1);

    lcd_cmd(0xC0);
    lcd_string("C2=");
    lcd_number(vote2);

    delay();

    lcd_cmd(0x01);
    lcd_string("C3=");
    lcd_number(vote3);

    lcd_cmd(0xC0);
    lcd_string("C4=");
    lcd_number(vote4);

    delay();

    while(RESULT == 0);
}
void main()
{
    lcd_init();

    lcd_string("Electronic");
    lcd_cmd(0xC0);
    lcd_string("Voting Machine");

    delay();
    lcd_cmd(0x01);

    while(1)
    {
        lcd_string("Press Button");

        check_vote();

        if(RESULT == 0)
        {
            show_result();
            lcd_cmd(0x01);
        }
    }
}