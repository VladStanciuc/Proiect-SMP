#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Se seteaza lcd la adresa 0x27 pentru 16 caractere si 2 linii
LiquidCrystal_I2C lcd(0x27,20,4);

//Pini senzor umiditate
#define pinHumidityPower 7
#define pinReadHumidity A0

//Pin pompa
#define pinWaterPump 4

//Valori umiditate
#define MaxValueHumidity 1010
#define MinValueHumidity 400
#define LevelStartPump 50

byte stem[] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00101,
  B10110,
  B01110,
  B00110
};

byte flower[] = {
  B10101,
  B11101,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00100
};


void setup() {
  // Se ititializeaza pinul de umiditate
  pinMode(pinHumidityPower, OUTPUT);
  digitalWrite(pinHumidityPower, LOW);

  // Se intitializeaza pimul de pompa de apa
  pinMode(pinWaterPump, OUTPUT);
  digitalWrite(pinWaterPump, LOW);
  

  // Se initializeaza lcd
  lcd.init();
  lcd.backlight();

  // Se genereaza caracterele custom
  lcd.createChar(0,stem);
  lcd.createChar(1,flower);
 
}


void loop() {
  // Se sterge ecranul
  lcd.clear();
  //Se citeste valoare de la senzorul de umiditate
  double humidity = readHumiditySensor();
  
  if (humidity < LevelStartPump){
    //Se afiseaza mesajul  
    lcd.setCursor(0,0);
    lcd.print("Solul se uda!");
    lcd.setCursor(0,1);
    lcd.print("Happy Flower!");
    lcd.setCursor(15,0);
    lcd.write(1);
    lcd.setCursor(15,1);
    lcd.write(0);
    
    // Se porneste pompa pentru 2 seculde
    digitalWrite(pinWaterPump, HIGH);
    delay(2000);
    digitalWrite(pinWaterPump, LOW);
  }else {

    // Se afiseaza umiditatea
    lcd.setCursor(0,0);
    lcd.print("Umiditate:");
    lcd.setCursor(0,1);

    lcd.print(humidity);
  }

  // Se asteapta 5 secunde pana la urmatoare citire
  delay(5000);

  
}

// Functia returneaza valoarea citita de senzorul de umiditate in procente
double readHumiditySensor() {
  // Se porneste senzorul
  digitalWrite(pinHumidityPower, HIGH);  
  delay(30);
  // Se citeste valoarea              
  double val = analogRead(pinReadHumidity); 
  // Se opreste senzorul 
  digitalWrite(pinHumidityPower, LOW);   
  return 100 - ((val-MinValueHumidity)*100/(MaxValueHumidity - MinValueHumidity));
}
  
