

// SMART ELECTRIC METER 
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int ledPin = 13; // choose the pin for the LED
int switchPin = 8; // choose the input pin (for a pushbutton)
int val = 0; // variable for reading the pin status
int counter = 0;
int currentState = 0;
int previousState = 0;
int temp = 0;
int i = 0;
int led = 13;
char str[15];

void setup() {
  pinMode(ledPin, OUTPUT); // declare LED as output
  pinMode(switchPin, INPUT); // declare pushbutton as input
  lcd.begin(16, 2);
  lcd.print("SRG Automation");
  delay(1000);
  lcd.clear();

  Serial.begin(9600);
  delay(500);
  Serial.println("AT+CNMI=2,2,0,0,0");
  delay(500);
  Serial.println("AT+CMGF=1");
  delay(1000);

  lcd.print("METER START.....   ");
  digitalWrite(13, HIGH);
  Serial
  .println("AT+CMGF=1\r");
  delay(1000);
  Serial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r");
  delay(1000);
  Serial.println("METER START");
  delay(1000);
  Serial.write((char)26); //ctrl+z
  delay(1000);
  Serial.println("AT+CLTS=1");
  Serial.println("AT+CCLK?");
   lcd.clear();
  digitalWrite(13, 0);
}
void loop() {
   if (temp == 1)
  {
    check();
    temp = 0;
    i = 0;
    delay(1000);
  }
  val = digitalRead(switchPin); // read input value
  if (val == HIGH) { // check if the input is HIGH (button released)
    digitalWrite(ledPin, HIGH); // turn LED on
    currentState = 1;
  }
  else {
    digitalWrite(ledPin, LOW);
    currentState = 0;
  }
  if (currentState != previousState) {
    if (currentState == 1) {
      counter = counter + 1;
      lcd.setCursor(1, 0);
      lcd.print("   ABS METER");
      lcd.setCursor(0, 1);
      lcd.print("UNIT = ");
      lcd.println(counter  );
    }
  }
  previousState = currentState;
  delay(250);
 

}
void serialEvent()
{
  while (Serial.available())
  {
     if (Serial.find("#A."))
    {
      digitalWrite(led, HIGH);
      delay(1000);
      digitalWrite(led, LOW);
      while (Serial.available())
      {
        char inChar = Serial.read();
        str[i++] = inChar;
        if (inChar == '*')
        {
          temp = 1;
          return;
        }
      }
    }
      
}
}
void check()
{
  if (!(strncmp(str, "send data", 9)))
  {
    Serial.print("UNIT SENDING.....   ");
    lcd.clear();
    lcd.println(counter);
    delay(1000);
    lcd.clear();
    lcd.print("UNIT SENDING.....   ");
    digitalWrite(13, HIGH);
    Serial.println("AT+CMGF=1\r");
    delay(1000);
    Serial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r");
    delay(1000);
    Serial.print("UNIT =");
    Serial.print(counter);
    Serial.println("THANK YOU");
    delay(1000);
    Serial.write((char)26); //ctrl+z
    delay(1000);
    Serial.println("AT+CLTS=1");
    Serial.println("AT+CCLK?");
    digitalWrite(13, 0);
    counter =0;
    lcd.clear();
     lcd.print("SENDING ok ");
  }


}
