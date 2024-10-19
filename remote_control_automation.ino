#include <IRremote.h>                                  
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int relay[]={8,9,10,11};                               
bool check[]={0,0,0,0};                                
const int IR_RECEIVE_PIN = 2;                          
LiquidCrystal_I2C lcd(0x27, 16, 2);                   
void update_display();                                 
void setup()
{
   Serial.begin(9600);         
   IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
   lcd.init();         
   lcd.backlight();
   for(int i=0;i<4;i++)
   {
     pinMode(relay[i],OUTPUT);
   }
   for(int i=0;i<4;i++)
   {
     digitalWrite(relay[i],LOW);
   }
    
   lcd.print("Initializing");
   delay(1000);
   lcd.print(".");
   delay(1000);
   lcd.print(".");
   delay(1000);
   lcd.print(".");
   delay(1000);
   lcd.print(".");
   delay(1000);
   lcd.print(".");
   lcd.clear();
   lcd.print("  Ready for");
   lcd.setCursor(0,1);
   lcd.print("  operation...");
   delay(1000);
}

void loop()
{
   if (IrReceiver.decode())
   {
      String ir_code = String(IrReceiver.decodedIRData.decodedRawData, HEX);
      Serial.println(ir_code);

      if(ir_code =="ed127f80") 
      {
        digitalWrite(relay[0], HIGH); 
        check[0]=1;
      }
      else if(ir_code =="e51a7f80"||ir_code=="e11e7f80") 
      {
        digitalWrite(relay[0], LOW);
        check[0]=0;
      } 
      else if(ir_code =="fe017f80") 
      {
        digitalWrite(relay[1], HIGH);
        check[1]=1;
      }
      else if(ir_code =="fd027f80"||ir_code=="fc037f80") 
      {
        digitalWrite(relay[1], LOW);
        check[1]=0;
      }  
      else if(ir_code =="fb047f80") 
      {
        digitalWrite(relay[2], HIGH);
        check[2]=1;
      }
      else if(ir_code =="fa057f80"||ir_code=="f9067f80") 
      {
        digitalWrite(relay[2], LOW); 
        check[2]=0;

      } 
      else if(ir_code =="f8077f80") 
      {
        digitalWrite(relay[3], HIGH);
        check[3]=1;
      } 
      else if(ir_code =="f7087f80"||ir_code=="f6097f80")
      {
        digitalWrite(relay[3], LOW);
        check[3]=0;
      }
      else if(ir_code=="f50a7f80")
      {
         digitalWrite(relay[0], HIGH);
         digitalWrite(relay[1], HIGH);
         digitalWrite(relay[2], HIGH);
         digitalWrite(relay[3], HIGH);
         check[0]=1;
         check[1]=1;
         check[2]=1;
         check[3]=1;
      }
      else if(ir_code=="e41b7f80"||ir_code=="e01f7f80")
      {
         digitalWrite(relay[0], LOW);
         digitalWrite(relay[1], LOW);
         digitalWrite(relay[2], LOW);
         digitalWrite(relay[3], LOW);
         check[0]=0;
         check[1]=0;
         check[2]=0;
         check[3]=0;
      }
      else if(ir_code=="f30c7f80")
      {
         digitalWrite(relay[0], HIGH);
         digitalWrite(relay[1], HIGH);
         check[0]=1;
         check[1]=1;
      }
      else if(ir_code=="f20d7f80"||ir_code=="f10e7f80")
      {
        digitalWrite(relay[0], LOW);
        digitalWrite(relay[1], LOW);
        check[0]=0;
        check[1]=0;
      }
      else if(ir_code=="ff007f80")
      {
        digitalWrite(relay[2], HIGH);
         digitalWrite(relay[3], HIGH);
         check[2]=1;
         check[3]=1;
      }
      else if(ir_code=="f00f7f80"||ir_code=="e6197f80")
      {
        digitalWrite(relay[2], LOW);
         digitalWrite(relay[3], LOW);
         check[2]=0;
         check[3]=0;
      }
      else 
      {
        //nothing to do...
      }

      update_display();
      IrReceiver.resume();
   }
}
void update_display()
{
  lcd.clear();
  if(check[0]==0&&check[1]==0&&check[2]==0&&check[3]==0)
  {
    lcd.setCursor(0,0);
    lcd.print("Everything is");
    lcd.setCursor(0,1);
    lcd.print("turned off...");
  }
  else
  {
    lcd.setCursor(0,0);
    if(check[0]==1) lcd.print("Light ");
    if(check[1]==1) lcd.print("Fan ");
    if(check[2]==1) lcd.print("AC ");
    if(check[3]==1) lcd.print("TV ");
    lcd.setCursor(0,1);
    lcd.print("   Turned on");
  }
  
}