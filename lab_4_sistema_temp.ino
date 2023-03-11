// C++ code
//
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,7,6,5,4);
byte temp = A0;
byte pul1 = A1;
byte pul2 = A2;
byte pul3 = A3;
byte ventilador=3;
byte led=10;
byte bomb=8;
long unsigned tiempo_aumentar = millis();
long unsigned tiempo_disminuir = millis();
long unsigned tiempo_aceptar = millis();
long unsigned tiempo = 70;
long unsigned tiempo2 = 500;
long unsigned tiempo_clear=millis();
int cont;
int n;
void setup()
{
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16,2);
  pinMode(pul1, OUTPUT);
  pinMode(pul2, OUTPUT);
  pinMode(pul3, OUTPUT);
  pinMode(temp, INPUT);
  pinMode(led, OUTPUT);
  pinMode(bomb, OUTPUT);
  pinMode(ventilador, OUTPUT);
  cont=map(analogRead(temp), 20, 358, -40, 125);
  n= cont;
  lcd.setCursor(0,0);
  lcd.print("Hola");
  
}

void loop()
{
  //digitalWrite(bomb, HIGH);

  if(millis() > tiempo2+ tiempo_clear)
    {
      lcd.clear();
      tiempo_clear=millis();
    }
  float valor_centigrados = dht.readTemperature();
  lcd.setCursor(0,0);
  lcd.print(cont);
  lcd.setCursor(0,2);
  lcd.print(valor_centigrados);
  lcd.setCursor(6,0);
  lcd.print(n);
              
  if(digitalRead(pul1)!=LOW)
  {
    if(millis() > tiempo+tiempo_aumentar)
    {
      
      cont++;
      tiempo_aumentar=millis();
      Serial.println("Hola");
    }
    
  }
   if(digitalRead(pul2)!=LOW)
  {
    if(millis() > tiempo+tiempo_disminuir)
    {
        
      cont--;
      tiempo_disminuir=millis();
    }
    
    
  }
   if(digitalRead(pul3)!=LOW)
  {
    if(millis() > tiempo+tiempo_aceptar)
    {
    
      n=cont;
      tiempo_aceptar=millis();
    }
    
    
  }
  if(n<valor_centigrados)
  {
    
    digitalWrite(ventilador, HIGH);
  }
  else
  {
    analogWrite(ventilador, 0);
  }
  if(valor_centigrados<n)
     {
       digitalWrite(bomb, HIGH);
     }
  else
  {
    digitalWrite(bomb, LOW);
  }
}
