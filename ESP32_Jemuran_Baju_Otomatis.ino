// -------------- Project System Jemuran Baju Otomatis ---------------- //
// -------- Berbasis Arduino dan motor servo sebagai aktuator -------- //
// ---------------- Dibuat oleh : M. Nofgi Y.P.U. -------------------- //
// ---------------- www.nofgipiston.wordpress.com ------------------- //
//*
//*
//*
// mohon dipelajari program yang sudah diberikan agar
// mendapat ilmu yang bermanfaat :)


// memanggil library motor servo
#include <ESP32Servo.h>

// inialisasi servo
Servo servo1;

// inialisasi pin sensor
const int pinHujan = 4;
const int pinLdr = 2;

// inialisasi pembacaan sensor
int hujan, cahaya;

// inialisasi derajat buka-tutup servo
int tutup = 110;
int buka = 10;



// ------------------------ program default awal ------------------------ //

void setup() {
  // setting baud rate serial monitor
  Serial.begin(9600);

  // inialisasi pin servo
  servo1.attach(13);

  // inialisasi status input/output pin
  pinMode(pinHujan, INPUT);
  pinMode(pinLdr, INPUT);
}



// -------------------------- program utama --------------------------- //

void loop() {
  // pembacaan sensor
  hujan = digitalRead(pinHujan);
  cahaya = digitalRead(pinLdr);

  // menulis pada serial monitor pembacaan sensor hujan dan cahaya
  // hasil output data sensor bisa dilihat di serial monitor arduino
  Serial.print(hujan);
  Serial.print(" ");
  Serial.println(cahaya);
  Serial.println(" ");


  // sensor hujan akan bernilai = 0 saat ada air
  // sensor cahaya akan bernilai = 1 saat gelap
  // dan berlaku sebaliknya

  // jika kondisi hujan dan mendung
  if (hujan == 0 && cahaya == 1) {
    // servo menutup
    servo1.write(tutup);
  }

  //=================================================

  // jika kondisi hujan
  else if (hujan == 0 && cahaya == 0) {
    // servo menutup
    servo1.write(tutup);
  }


  //==================================================

  // jika kondisi mendung
  else if (hujan == 1 && cahaya == 1) {
    // servo menutup
    servo1.write(tutup);
  }


  //==================================================

  // jika kondisi tidak hujan dan tidak mendung
  else if (hujan == 1 && cahaya == 0) {
    // servo membuka
    servo1.write(buka);
  }

  // delay jalannya program
  delay(300);
}
