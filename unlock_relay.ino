#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define Password_Length 8 // Inserire la lunghezza della password
//se la password è lunga 7 caratteri inserire 8
//se la password è lunga 8 caratteri inserire 9 ecc..

int signalPin = 12;    // Pin su cui è collegato il relè

char Data[Password_Length]; 
char Master[Password_Length] = "1234567";   //Modifica la password 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// set the LCD address to "0x27"(or "0x3f") for a 16 chars and 2 line display
// set the LCD address to "0x3f"(or "0x27") for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 4);  

void setup(){

  lcd.init(); 
  lcd.backlight();
  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, HIGH);
}

void loop(){

  lcd.setCursor(0,0);
  lcd.print("  PASSWORD...");

  customKey = customKeypad.getKey();
  if (customKey){
    Data[data_count] = customKey; 
    lcd.setCursor(data_count,1); 
    lcd.print(Data[data_count]); 
    data_count++; 
    }

  if(data_count == Password_Length-1){
    lcd.clear();

    if(!strcmp(Data, Master)){
      lcd.print(" Pass Corretta");
      digitalWrite(signalPin, LOW); 
      delay(1500);
      digitalWrite(signalPin, HIGH);
      }
    else{
      lcd.print("Pass Errata");
      delay(3000);
      }
    
    lcd.clear();
    clearData();  
  }
}

void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
  return;
}
