//inisiasi pin 
const int trigPin = 8;
const int echoPin = 9; 
const int led = 2;
const int buzzer = 3;

// tinggi dari tanah ke sensor
const float TINGGI_MAX = 200.0;

// variabel ukur 
long durasi; 
float jarak;
float tinggi; 

void setup() {
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}



void loop() {
  void tinggiBadan();
  delay(200);
}

void tinggiBadan() {
  // kirim sinyal ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);


  // dpt sinyal
  durasi = pulseIn(echoPin, HIGH);

  // konversi 
  jarak = durasi * 0.0343 / 2;
  tinggi = TINGGI_MAX - jarak; 


  if (tinggi > 30.0 && tinggi < TINGGI_MAX) {
    tone(buzzer, 999);
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(50);
  } 
  else {
    tone(buzzer, 999);
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(50);
  }

 // CETAK HASIL KE SERIAL MONITOR
  Serial.print("Jarak Sensor: ");
  Serial.print(jarak);
  Serial.print(" cm | Tinggi Badan: ");
  Serial.print(tinggi);
  Serial.println(" cm");
}
