#include <IRremote.h>
const int IR_RECEIVE_PIN = 2;

void setup()
{
   Serial.begin(9600);
   Serial.println("IR Receive test");
   IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop()
{
   if (IrReceiver.decode())
   {
      String ir_code = String(IrReceiver.decodedIRData.decodedRawData, HEX);
      Serial.println(ir_code);

      IrReceiver.resume();
   }
}