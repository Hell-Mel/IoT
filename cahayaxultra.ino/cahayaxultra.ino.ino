// Inisialisasi pin
const int trigPin = 9;
const int echoPin = 8;
const int led = 2;
const int led2 = 3;
const int led3 = 4;
const int buzzer = 11;

// Timer 1: Khusus untuk Buzzer dan LED2 (Jarak 10-25cm)
unsigned long previousMillis_Buzzer = 0;
const unsigned long interval_Buzzer = 1000; // Bip setiap 1 detik
bool stateBuzzer = false;

// Timer untuk LED sequence
unsigned long previousMillis_LED = 0;
const unsigned long interval_LED = 1000;
int stepLED = 0;

// Variabel pengukuran
long duration;
float distance;

void setup() 
{
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(A5, INPUT); 
  
  Serial.begin(9600);
}

void loop() 
{
  // Kirim pulsa trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Baca waktu pantulan echo
  duration = pulseIn(echoPin, HIGH);
  // Baca LDR 
  int ldr = analogRead(A5);

  //Ambil Waktu
  unsigned long currentMillis = millis(); 

  // Konversi waktu ke centimeter
  distance = duration * 0.0343 / 2;

  // Logika kontrol berdasarkan jarak
  if (distance <= 10 && ldr < 1000) 
  {
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(buzzer, HIGH);
    tone(buzzer, 999);
    digitalWrite(led, HIGH);
  }
  else if (distance > 10 && distance <= 25 && ldr < 400) 
  { if (currentMillis - previousMillis_Buzzer >= interval_Buzzer) {
      previousMillis_Buzzer = currentMillis; // Update catatan waktu Timer 1
  }
    digitalWrite(led3, LOW);
    digitalWrite(led, LOW);
    digitalWrite(buzzer, HIGH);
    tone(buzzer, 999);
    digitalWrite(led2, HIGH);
    digitalWrite(led2, LOW);
  }
  else 
  { // Running LED bergantian setiap 1 detik
    noTone(buzzer);

    if (currentMillis - previousMillis_LED >= interval_LED) {
      previousMillis_LED = currentMillis;

      // Reset semua LED
      digitalWrite(led, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);

      // Jalankan step LED
      if (stepLED == 0) {
        digitalWrite(led, HIGH);
      } else if (stepLED == 1) {
        digitalWrite(led2, HIGH);
      } else if (stepLED == 2) {
        digitalWrite(led3, HIGH);
      }

      stepLED++;
      if (stepLED > 2) stepLED = 0;
    }
  }


}

