#include <Keypad.h>
#include<LiquidCrystal.h>;
#include<EEPROM.h>;
#include <Servo.h>
Servo myservo;
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};
byte rowPins[ROWS] = {13, 12, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7,6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  pinMode(5,INPUT);//alarm button 
  pinMode(3,INPUT);//closed buton
   pinMode(4,OUTPUT);//alarm
    myservo.attach(2); 
  Serial.begin(9600);
  lcd.begin(16,2);  
  EEPROM.write(0,0);
 
}
  int k=3;int l=3;int hello=0;int z=0;
  String firstpass="";
  
void loop(){
  char kl;
ll: if(EEPROM.read(0)==0){
  EEPROM.write(2,3);
  char key = keypad.getKey();
  if(hello==0){lcd.print("set pass then'='>");lcd.setCursor(0,1);hello=1;}
    
    
     if (key=='#'){EEPROM.update(1,k);
      while(l<EEPROM.read(1)){firstpass+=EEPROM.get(l,kl);l++;}l=3;
      lcd.clear();lcd.print("  pass saved");delay(2000);lcd.clear();
EEPROM.write(0,1);
  }
  else if(key){ 
    lcd.print("*");
EEPROM.put(k,key);k++;}

}
  else{
    int counter=EEPROM.read(2);
    if(z==0){z=1;lcd.print("enter password:>");lcd.setCursor(0,1);}
       String enterdpass=""; lcd.blink();
   while(l<EEPROM.read(1)){
   char op=keypad.getKey();
    if(op){
      lcd.print("*");
      enterdpass+=op;l++;}
     if(digitalRead(3)==1){
      for (int pos = 0; pos <= 90; pos += 1) { 
    myservo.write(pos);              
    delay(7);}
      }
     
      }
   
      if(enterdpass==firstpass){lcd.clear();
            lcd.print("true");
      for (int pos = 90; pos >= 0; pos -= 1) { 
    myservo.write(pos);            
    delay(7);        }     
      //delay(1000);
      lcd.clear();lcd.print("press button ");
      lcd.setCursor(0,1);
      lcd.print("to close::>> ");
      while(true)
      {
        if(digitalRead(3)==1){ 
          for (int pos = 0; pos <= 90; pos++) { 
    myservo.write(pos);            
    delay(7);        }
    lcd.clear();lcd.setCursor(0,0);
          break;
        }

      }
      k=3;l=3;z=0;EEPROM.update(2,3);}
      else{lcd.clear();l=3;k=3;z=0;counter--;EEPROM.update(2,counter);
      lcd.print("false");
      lcd.setCursor(0,1);
      lcd.print("tria lefted: "+String(EEPROM.read(2)) );delay(2000);lcd.clear();
      if(EEPROM.read(2)==0){
        while(true)
        {lcd.setCursor(0,0);
          lcd.print("     alarm");
          digitalWrite(4,HIGH);
        if(digitalRead(5)==1){
        EEPROM.write(0,0);
        lcd.clear();
        digitalWrite(4,LOW);
        firstpass="";
        goto ll;
        }
        }
      
      }
      
      
hello=0;
      
      }
      }
}

      
     
    
