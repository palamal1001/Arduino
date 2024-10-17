#define ledpin 13
#define buttonpin 2
int input_reading,buttonState=1;
bool check=true;
void setup() 
{
  pinMode(buttonpin,INPUT_PULLUP);
  pinMode(ledpin,OUTPUT);
  digitalWrite(ledpin,0);
  Serial.begin(9600);
}

void loop() 
{
  input_reading=digitalRead(buttonpin);
  if(input_reading==0)
  {
      if(check==true)
      {
        digitalWrite(ledpin,1);
      }
      else 
      {
        digitalWrite(ledpin,0);
      }
      buttonState=0;
  }
  else 
  {
    if(buttonState==0) check=!check;
    buttonState=1;
  }
  Serial.println(input_reading);
}
