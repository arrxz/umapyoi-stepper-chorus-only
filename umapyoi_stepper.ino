// === PIN DEFINISI CNC Shield (slot X) ===
#define STEP_PIN 2
#define DIR_PIN 5
#define EN_PIN 8   // Enable pin, aktif LOW

// === Definisi nada (Hz) ===
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_Fs4 370
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_D4  294
#define NOTE_E4  330

// Struktur untuk menyimpan nada & durasi
struct Note {
  int freq;
  int duration; // dalam ms
};

// === Melodi contoh ===
// Format: {FREQUENCY, DURASI(ms)}
Note melody[] = {
  {NOTE_D5, 150},
  {NOTE_D5, 150},
  {NOTE_D5, 150},
  {NOTE_D5, 150},
  
  {NOTE_C5, 150},
  {NOTE_B4, 150},
  
  {NOTE_G4, 350},
  {NOTE_G4, 190},
  {NOTE_D5, 300},
  {NOTE_G4, 190},
  {NOTE_D5, 300},
  
  {NOTE_G4, 150},
  {NOTE_G4, 150},
  {NOTE_Fs4,150},
  {NOTE_G4, 150},
  {NOTE_A4, 680},
  {0, 400},

  {NOTE_A4, 150},
  {NOTE_A4, 250},
  {0, 30},
  {NOTE_A4, 150},
  {NOTE_D5, 260},
  {0, 20},
  {NOTE_G4, 150},
  {NOTE_A4, 350},
  {NOTE_G4, 350},
  {NOTE_Fs4, 350},
  {NOTE_G4, 350},
  {0, 300}, 
  {NOTE_B4, 285},
  {0, 1},
  {NOTE_E4, 600},
  {0, 20},
  {NOTE_E4, 150},
  {NOTE_D4, 150},
  {NOTE_A4, 350},
  {NOTE_A4, 450},
  {0, 320},
  {NOTE_A4, 670},
  {NOTE_B4, 150},
  {NOTE_C5, 150},
  {NOTE_B4, 690},
  
};

int melodyLength = sizeof(melody) / sizeof(melody[0]);

// === Fungsi untuk mainkan nada dengan stepper ===
void playTone(int freq, int duration) {
  if (freq == 0) {        // nada diam (rest)
    delay(duration);
    return;
  }

  long halfPeriod = 1000000L / (2 * freq);   // mikrodetik per setengah gelombang
  long cycles = (long)freq * duration / 1000; // jumlah siklus sesuai durasi

  for (long i = 0; i < cycles; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(halfPeriod);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(halfPeriod);
  }
}

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);

  digitalWrite(DIR_PIN, HIGH); // arah putar
  digitalWrite(EN_PIN, LOW);   // ENABLE driver (aktif)

  // Mainkan melodi hanya sekali
  for (int i = 0; i < melodyLength; i++) {
    playTone(melody[i].freq, melody[i].duration);
    delay(50); // jeda antar nada
  }

  digitalWrite(EN_PIN, HIGH);  // setelah selesai, disable driver
}

void loop() {
  // kosong, supaya tidak diulang otomatis
}
