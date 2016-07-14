#include <LiquidCrystal.h>
LiquidCrystal lcd(11, 10, 8, 7, 6, 5);
#define output_pulse1 12
#define output_pulse2 13
#define read_alpha    A0

volatile int en=LOW;
volatile long int alpha=0;
long int previous_alpha=0;
volatile float t1=0;
volatile int led=LOW;
volatile bool internal_state1=LOW;
volatile bool internal_state2=LOW;

unsigned long previous_time=0;
unsigned long pulse_width=1000; //1=1us
unsigned long current_time=0;

int error =1-0.2;
int error_pos=error;
int error_neg=error;

void edge(void);
void pin_mode_setup(void);
void setup_negative_edge(void);
void setup_positive_edge(void);
void lcd_(void);

void setup() {
attachInterrupt(digitalPinToInterrupt(3),edge,CHANGE); 
pin_mode_setup();
lcd.begin(16, 2);
lcd.setCursor(0, 0);
lcd.print("Firing Angle");
lcd.setCursor(7, 1);
lcd.print("Degrees");
}

void loop()
{
setup_negative_edge();
setup_positive_edge();
//lcd.print(alpha);
}
void lcd_(void)
{
if(alpha>=previous_alpha+2 || alpha<=previous_alpha-2)
{
previous_alpha=alpha;
lcd.setCursor(2, 1);
lcd.print(alpha/2);
lcd.print(" ");
}
}

 void edge(void)
{
 internal_state2==LOW;
 internal_state1==LOW;
 digitalWrite(output_pulse2,LOW);
 digitalWrite(output_pulse1,LOW);
 en=HIGH;
 alpha = analogRead(read_alpha);
 alpha=alpha/2.845;
 t1=alpha*20/360;
t1=t1/2;
}
void pin_mode_setup(void)
{
pinMode(output_pulse1,OUTPUT);
pinMode(output_pulse2,OUTPUT);
pinMode(read_alpha ,INPUT);
}

void setup_negative_edge(void)
{
if(en==HIGH && digitalRead(3)==LOW)
{
  if(internal_state2==LOW)
  {
  previous_time=micros();  
  internal_state2=HIGH;
  }
  if((micros() - previous_time)>((t1*1000)-500) & internal_state2==HIGH)
  {
  digitalWrite(output_pulse2,HIGH);
      if((micros()-previous_time)>=(t1*1000+pulse_width))
      {digitalWrite(output_pulse2,LOW);
      internal_state2=LOW;
      en=LOW;
      
      }
}   
}     
}
void setup_positive_edge(void)
{
if(en==HIGH && digitalRead(3)==HIGH)
{
  if(internal_state1==LOW)
  {
    
  previous_time=micros();  
  internal_state1=HIGH;
                 if(t1*1000>4000)
                  {lcd_();} 
  }
  if((micros() - previous_time)>((t1*1000)+300) & internal_state1==HIGH)
  {
  digitalWrite(output_pulse1,HIGH);
  
     if((micros()-previous_time)>=(t1*1000+pulse_width))
     {
     digitalWrite(output_pulse1,LOW);
   
     internal_state1=LOW;
      en=LOW;
      if((micros() - previous_time)<=5500)
      {
        lcd_();
        }
     }
    
  }
}
}

