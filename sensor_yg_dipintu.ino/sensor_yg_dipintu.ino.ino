// Inisialisasi pin
const int trigPin = 9;
const int echoPin = 8;
const int led = 2;
const int led2 = 3;
const int led3 = 4;
const int buzzer = 11;

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
  
  Serial.begin(9600);
}

void loop() 
{
  measureAndControl();
  delay(100); // Delay singkat untuk stabilitas
}

void measureAndControl() 
{
  // Kirim pulsa trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Baca waktu pantulan echo
  duration = pulseIn(echoPin, HIGH);

  // Konversi waktu ke centimeter
  distance = duration * 0.0343 / 2;

  // Logika kontrol berdasarkan jarak
  if (distance <= 70) 
  {
    digitalWrite(buzzer, HIGH);
    tone(buzzer, 900);
    digitalWrite(led, HIGH);
  }
  else 
  {
    noTone(buzzer);
    
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    
    digitalWrite(led2, HIGH);
    delay(1000);
    digitalWrite(led2, LOW);
    
    digitalWrite(led3, HIGH);
    delay(1000);
    digitalWrite(led3, LOW);
  }

  // Tampilkan hasil pada Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance, 1);
  Serial.println(" cm");
}