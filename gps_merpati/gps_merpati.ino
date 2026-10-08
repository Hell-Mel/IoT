// --- KONFIGURASI BLYNK (GANTI DENGAN MILIKMU) ---
#define BLYNK_TEMPLATE_ID "TMPL68-N2jldZ"
#define BLYNK_TEMPLATE_NAME "gps traker"
#define BLYNK_AUTH_TOKEN "NjUL9mhn84hVfn6FEJ7bYY3C7jqArnMT"

// Konfigurasi Modem SIM800L untuk TinyGSM
#define BLYNK_PRINT Serial
#define TINY_GSM_MODEM_SIM800

#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <TinyGsmClient.h>
#include <BlynkSimpleTinyGSM.h>
#include <TinyGPSPlus.h>

// --- KONFIGURASI PIN ---
// Wemos D1 (RX) terhubung ke TX GPS
// Wemos D2 (TX) terhubung ke RX GPS
#define GPS_RX_PIN D1
#define GPS_TX_PIN D2

// Wemos D6 (RX) terhubung ke TX SIM800L
// Wemos D7 (TX) terhubung ke RX SIM800L
#define GSM_RX_PIN D6
#define GSM_TX_PIN D7

SoftwareSerial gpsSerial(GPS_RX_PIN, GPS_TX_PIN);
SoftwareSerial gsmSerial(GSM_RX_PIN, GSM_TX_PIN);

TinyGPSPlus gps;
TinyGsm modem(gsmSerial);

// APN Provider (Telkomsel/Indosat dsb, default biasanya "internet")
char apn[]  = "internet";
char user[] = "";
char pass[] = "";

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println("\n--- Memulai GPS Tracker Merpati ---");

  // Mulai koneksi serial ke modul
  gpsSerial.begin(9600);
  gsmSerial.begin(9600);

  Serial.println("1. Mencari sinyal satelit GPS...");
  gpsSerial.listen();

  unsigned long startGPS = millis();
  bool gpsValid = false;

  // Beri waktu modul GPS mencari lokasi selama 10 detik
  while (millis() - startGPS < 60000) {
    while (gpsSerial.available() > 0) {
      if (gps.encode(gpsSerial.read())) {
        if (gps.location.isValid()) {
          gpsValid = true;
          break;
        }
      }
    }
    if (gpsValid) break;
  }

  if (gpsValid) {
    float latitude = gps.location.lat();
    float longitude = gps.location.lng();
    Serial.print("Koordinat Ditemukan! Lat: "); Serial.print(latitude);
    Serial.print(" Lon: "); Serial.println(longitude);

    Serial.println("2. Menyalakan Internet GSM & Menghubungkan ke Blynk...");
    gsmSerial.listen();
    
    Blynk.begin(BLYNK_AUTH_TOKEN, modem, apn, user, pass);

    if (Blynk.connected()) {
      // Kirim data ke Widget Map di aplikasi Blynk (berada di Virtual Pin V1)
      String linkPeta = "https://maps.google.com/?q=" + String(latitude, 6) + "," + String(longitude, 6);
      Blynk.virtualWrite(V1, linkPeta);
      Blynk.run();
      Serial.println("Status: DATA BERHASIL DIKIRIM KE WEB!");
    } else {
      Serial.println("Status: Gagal terhubung ke jaringan seluler/Blynk.");
    }
  } else {
    Serial.println("Status: Gagal mendapat sinyal satelit (Tunggu di luar ruangan).");
  }

  Serial.println("3. Alat masuk mode tidur (Deep Sleep) selama 5 Menit...");
  
  // Wemos tidur selama 5 Menit (300.000.000 microsecond) untuk irit baterai
  ESP.deepSleep(300e6);
}

void loop() {
  // Biarkan kosong. Alat ini tidak butuh putaran loop karena langsung tidur setelah selesai mengirim data.
}