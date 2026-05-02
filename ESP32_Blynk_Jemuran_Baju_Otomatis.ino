/* 
 *  Proyek: Smart Jemuran / Smart Window
 *  Fitur: Tutup otomatis jika nilaiRain atau GELAP
 */

#define BLYNK_TEMPLATE_ID "TMPL6D27F0kXS"
#define BLYNK_TEMPLATE_NAME "Jemuran Baju Otomatis"
#define BLYNK_AUTH_TOKEN "e8BEUcmWMfIukFf-UCFMStXQCnuY_Jvh"

#define BLYNK_TEMPLATE_ID "TMPL6D27F0kXS"
#define BLYNK_TEMPLATE_NAME "Jemuran Baju Otomatis"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

// Konfigurasi WiFi
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "muktafi";
char pass[] = "12443411";

// Definisi Pin
#define PIN_LDR 15
#define PIN_RAIN 4
#define PIN_SERVO 13

Servo myservo;
BlynkTimer timer;

int tutup = 110;
int buka = 10;

void sendSensorData() {
  int nilaiLDR = digitalRead(PIN_LDR);
  int nilaiRain = digitalRead(PIN_RAIN);

  // Kirim data ke Aplikasi Blynk
  Blynk.virtualWrite(V1, nilaiLDR);
  Blynk.virtualWrite(V2, nilaiRain);

  // LOGIKA KONTROL SERVO
  // menulis pada serial monitor pembacaan sensor hujan dan cahaya
  // hasil output data sensor bisa dilihat di serial monitor arduino
  Serial.print("hujan ");
  Serial.print(nilaiRain);
  Serial.print(" ");
  Serial.print("Cahaya ");
  Serial.println(nilaiLDR);
  Serial.println(" ");


  // sensor hujan akan bernilai = 0 saat ada air
  // sensor Cahaya akan bernilai = 1 saat gelap
  // dan berlaku sebaliknya
  // jika kondisi hujan dan mendung
  if (nilaiRain == 0 && nilaiLDR == 1) {
    // servo menutup
    servo1.write(tutup);
    Blynk.virtualWrite(V3, "Kondisi: AMAN (Tertutup)");
  }

  //=================================================
  // jika kondisi hujan
  else if (nilaiRain == 0 && nilaiLDR == 0) {
    // servo menutup
    servo1.write(tutup);
    Blynk.virtualWrite(V3, "Kondisi: AMAN (Tertutup)");
  }


  //==================================================
  // jika kondisi mendung
  else if (nilaiRain == 1 && nilaiLDR == 1) {
    // servo menutup

    servo1.write(tutup);
    Blynk.virtualWrite(V3, "Kondisi: AMAN (Tertutup)");
  }


  //==================================================
  // jika kondisi tidak hujan dan tidak mendung
  else if (nilaiRain == 1 && nilaiLDR == 0) {
    // servo membuka
    servo1.write(buka);
    Blynk.virtualWrite(V3, "Kondisi: MENJEMUR (Terbuka)");
  }
}

void setup() {
  Serial.begin(9600);

  // Setup Servo menggunakan ESP32Servo
  myservo.attach(PIN_SERVO);

  // Inisialisasi Blynk
  Blynk.begin(auth, ssid, pass);

  // Jalankan fungsi setiap 1 detik
  timer.setInterval(1000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}