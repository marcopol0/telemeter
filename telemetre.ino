/*
  LiquidCrystal Library - Hello World

 
   Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
/* Pinmapping */
const byte TRIGGER_PIN = 8; // Broche TRIGGER
const byte ECHO_PIN = 9;    // Broche ECHO

const long MEASURE_TIMEOUT = 25000L; // 40Hz = 25ms = ~8m à 340m/s
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Telemetre");
  Serial.begin(9600);
   
  /* Initialisation des broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIGGER_PIN, LOW); // DOIT être à LOW au repos
   
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
    /* 1) Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  /* 2) Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
   
  /* 3) Calcul la distance à partir du temps mesuré */
  long mm = measure / 2 * 0.3434;
  Serial.println(mm);
  //mm = sqrt(mm*mm - 33.75*33.75);
  // print the number of seconds since reset:
  lcd.print(mm/1000.0, 3);
  lcd.print (" m");
  delay (600);
}
