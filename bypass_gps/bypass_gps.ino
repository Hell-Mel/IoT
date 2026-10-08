#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

// Wemos D1 (RX) sambung ke pin TX di GPS
// Wemos D2 (TX) sambung ke pin RX di GPS
SoftwareSerial gpsSerial(D1, D2); 
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600);
  
  Serial.println("\n--- MODE TES KEKUATAN GPS ---");
  Serial.println("Mencari satelit... (Proses pertama kali bisa butuh 5 - 15 menit).");
  Serial.println("Biarkan alat di luar ruangan dengan langit terbuka.");
}

void loop() {
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        Serial.print("BERHASIL NGELOCK! Lat: ");
        Serial.print(gps.location.lat(), 6);
        Serial.print(" | Lon: ");
        Serial.println(gps.location.lng(), 6);
        delay(2000); // Tampilkan setiap 2 detik jika sudah dapat
      }
    }
  }
}