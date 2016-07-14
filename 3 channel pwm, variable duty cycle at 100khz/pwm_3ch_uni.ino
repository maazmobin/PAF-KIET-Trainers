float max_duty=0.8; //80%
float min_duty=0.2; //20%

#include <LiquidCrystal.h>

LiquidCrystal lcd(A2, A1, A0, 13, 12, 8);

float duty=100;
float duty2=100;
float duty1=100;
void setup() {
  // put your setup code here, to run once:
//Serial.begin(9600);
 lcd.begin(20, 4);
timer0_setup();
timer2_setup();
timer1_setup();
lcd.setCursor(0, 0);
lcd.print("  DC-DC Converter");

}

void loop() {
  // put your main code here, to run repeatedly:
channel_0();
channel_2();
channel_1();
}
void timer0_setup(void)
{
TCCR0A=0b01100011; //b0 b1 a0 a1 r r w1 w0
TCCR0B=9;
TCCR0B=00001001;
pinMode(5,OUTPUT);
pinMode(A3,INPUT);  
OCR0A=159;
  }
 void channel_0(void)
 {duty=analogRead(A4);
duty=duty/1023;
if(duty<min_duty)
duty=0.2;
else if(duty>max_duty)
duty=0.8;
OCR0B=duty*159;
//Serial.println(analogRead(A0));
int d=duty*100;
lcd.setCursor(0, 2);
lcd.print("Boost - DC:");
lcd.setCursor(12, 2);
lcd.print(d);
lcd.print("%  ");
}
void timer2_setup(void)
{
TCCR2A=0b01100011; //b0 b1 a0 a1 r r w1 w0
TCCR2B=9;
//TCCR0B=00001001;
pinMode(3,OUTPUT);
pinMode(A4,INPUT);  
OCR2A=159;
  }
 void channel_2(void)
 {duty2=analogRead(A3);
duty2=duty2/1023;
if(duty2<min_duty)
duty2=0.2;
else if(duty2>max_duty)
duty2=0.8;

OCR2B=duty2*159;
//Serial.println(analogRead(A2));
int d=duty2*100;
lcd.setCursor(0, 1);
lcd.print("Buck - DC:");
lcd.setCursor(12, 1);
lcd.print(d);
lcd.print("%  ");
}

void timer1_setup(void)
{
TCCR1A=0b00100011;          //COM1A1 COM1A0 COM1B1 COM1B0 – – WGM11 WGM10 TCCR1A
//prescalar 1:TCCR1B=25   256:TCCR1B=28
TCCR1B=0b00011001;          //ICNC1 ICES1 – WGM13 WGM12 CS12 CS11 CS10 TCCR1B
//TCCR1B=25;
pinMode(10,OUTPUT);
pinMode(A5,INPUT);  
OCR1A=159;
}
 void channel_1(void)
 {duty1=analogRead(A5);
duty1=duty1/1023;
if(duty1<min_duty)
duty1=0.2;
else if(duty1>max_duty)
duty1=0.8;

OCR1B=duty1*159;
//Serial.println(analogRead(A1));
int d=duty1*100;
lcd.setCursor(0, 3);
lcd.print("Buck-Boost-DC:");
lcd.setCursor(16, 3);
lcd.print(d);
lcd.print("%  ");
}
