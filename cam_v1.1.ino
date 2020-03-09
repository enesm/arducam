// Tum ekran pinleri
int e = 6;
int d = 7;
int c = 8;
int g = 9;
int f = 10;
int a = 11;
int b = 12;
int ekranPinleri[] = {b, a, f, g, c, d, e};

// Mod switch
int modSwitch = A0;

// Artirma butonu
int artButton = 2;

// Run switch
int runSwitch = A2;

// Cam pin
int camPin = A3;

// Denklansor gecikmesi
int takePhotoDelay = 50;

// Ilk modlar
int modSure = 0;
int modFotoMiktari = 0;
unsigned int modlarSure[] = {5, 10, 30, 60, 300, 600, 900, 1200, 1500, 1800}; // sec
int modlarFoto[] = {50, 100, 150, 200, 250, 300, 350, 400, 450, 500};

void setup() {
  // Sag ekran
  pinMode(b, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  // Mod switch
  pinMode(modSwitch, INPUT);
  // Artirma butonu
  pinMode(artButton, INPUT);
  // Run switch
  pinMode(runSwitch, INPUT);
  // Cam pin
  pinMode(camPin, OUTPUT);
  // Bootup
  bootScreen();
  updateFotoScreen();
  updateTimeScreen();
}

void loop() {
  readArtiButton();
  updateScreen();
  if (readRunSwitch() == 1) startShots();
}

void incTimeMod() {
  modSure = (++modSure == 10 ? 0 : modSure);
  updateTimeScreen();
}

void incFotoMod() {
  modFotoMiktari = (++modFotoMiktari == 10 ? 0 : modFotoMiktari);
  updateFotoScreen();
}

void updateFotoScreen() {
  updateScreen();
}

void updateTimeScreen() {
  updateScreen();
}

void updateScreen() {
  if (readModSwitch() == 0) {
    writeScreen(modFotoMiktari);
  } else if (readModSwitch() == 1) {
    writeScreen(modSure);
  }
}

int getCurrentTimeMod() {
  return modlarSure[modSure];
}

int getCurrentFotoMod() {
  return modlarFoto[modFotoMiktari];
}

int readModSwitch() {
  return digitalRead(modSwitch);
}

int readRunSwitch() {
  return digitalRead(runSwitch);
}

int readArtiButton() {
  int buttonState = digitalRead(artButton);
  if (buttonState == 1) {
    while(digitalRead(artButton) == 1) {}
    if(readModSwitch() == 0) incFotoMod();
    else incTimeMod();
  }
}

void takeShot() {
  digitalWrite(camPin, HIGH);
  delay(takePhotoDelay);
  digitalWrite(camPin, LOW);  
  delay(takePhotoDelay);
}

void startShots() {
  countdown();
  while (true) {
    if (readRunSwitch() == 0) break;
    for (int i=0; i<getCurrentFotoMod(); i++) {
      if (readRunSwitch() == 0) break;
      takeShot();
    }
    for (int timeCount=0; timeCount<getCurrentTimeMod(); timeCount++) {
      if (readRunSwitch() == 0) break;
      if (delayInterruptable() == 0) break;
    }
  }
}

void countdown() {
  cleanScreens();
  for (int i=5; i>=0; i--) {
    writeScreen(i);
    if (delayInterruptable() == 0) break;
  }
  updateFotoScreen();
  updateTimeScreen();
}

int delayInterruptable() {
  delay(1000);
  return readRunSwitch();
}

void cleanScreens() {
  for (byte i = 0; i < (sizeof(ekranPinleri) / sizeof(int)); i++) {
    digitalWrite(ekranPinleri[i], LOW);
  }
}

void bootScreen() {
  cleanScreens();
  int animPins[] = {a, b, c, d, e, f};
  for (int p = 0; p < 6; p++) digitalWrite(animPins[p], HIGH);
  for (byte c = 0; c < 4; c++) {
    for (byte i = 0; i < 6; i++) {
      digitalWrite(animPins[i], LOW);
      delay(50);
      digitalWrite(animPins[i], HIGH);
    }
  }
  cleanScreens();
}

void writeScreen(int number) {
    switch (number) {
      case 0:
        digitalWrite(e, HIGH);
        digitalWrite(d, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(g, LOW);
        digitalWrite(f, HIGH);
        digitalWrite(a, HIGH);
        digitalWrite(b, HIGH);
        break;
      case 1:
        digitalWrite(e, LOW);
        digitalWrite(d, LOW);
        digitalWrite(c, HIGH);
        digitalWrite(g, LOW);
        digitalWrite(f, LOW);
        digitalWrite(a, LOW);
        digitalWrite(b, HIGH);
        break;
      case 2:
        digitalWrite(e, HIGH);
        digitalWrite(d, HIGH);
        digitalWrite(c, LOW);
        digitalWrite(g, HIGH);
        digitalWrite(f, LOW);
        digitalWrite(a, HIGH);
        digitalWrite(b, HIGH);
        break;
      case 3:
        digitalWrite(e, LOW);
        digitalWrite(d, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(g, HIGH);
        digitalWrite(f, LOW);
        digitalWrite(a, HIGH);
        digitalWrite(b, HIGH);
        break;
      case 4:
        digitalWrite(e, LOW);
        digitalWrite(d, LOW);
        digitalWrite(c, HIGH);
        digitalWrite(g, HIGH);
        digitalWrite(f, HIGH);
        digitalWrite(a, LOW);
        digitalWrite(b, HIGH);
        break;
      case 5:
        digitalWrite(e, LOW);
        digitalWrite(d, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(g, HIGH);
        digitalWrite(f, HIGH);
        digitalWrite(a, HIGH);
        digitalWrite(b, LOW);
        break;
  
      case 6:
        digitalWrite(e, HIGH);
        digitalWrite(d, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(g, HIGH);
        digitalWrite(f, HIGH);
        digitalWrite(a, HIGH);
        digitalWrite(b, LOW);
        break;
      case 7:
        digitalWrite(e, LOW);
        digitalWrite(d, LOW);
        digitalWrite(c, HIGH);
        digitalWrite(g, LOW);
        digitalWrite(f, LOW);
        digitalWrite(a, HIGH);
        digitalWrite(b, HIGH);
        break;
      case 8:
        digitalWrite(e, HIGH);
        digitalWrite(d, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(g, HIGH);
        digitalWrite(f, HIGH);
        digitalWrite(a, HIGH);
        digitalWrite(b, HIGH);
        break;
      case 9:
        digitalWrite(e, LOW);
        digitalWrite(d, HIGH);
        digitalWrite(c, HIGH);
        digitalWrite(g, HIGH);
        digitalWrite(f, HIGH);
        digitalWrite(a, HIGH);
        digitalWrite(b, HIGH);
        break;
  }
}
