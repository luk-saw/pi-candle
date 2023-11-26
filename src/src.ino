int const buttonPinNumber = 12;
int const ledCount = 6;
int const ledPinNumbers[ledCount] = { 14, 15, 16, 17, 18, 19 };
int ledBrightness[ledCount] = { 0, 0, 0, 0, 0, 0 };
bool loopEnabled = false;
bool buttonPressed = false;
bool doCleanUp = false;

int const regularFade = 2;
int const variationPercent = 2;
int const variationFade = 50;

int fadeAmount = 5;  // how many points to fade the LED by

void applyledBrightness(int pinNumber, int ledBrightnessToSet) {
  // set the ledBrightness of pin
  analogWrite(pinNumber, ledBrightnessToSet);
}

int calcLedBrightness(int currentledBrightness) {
  // random variation
  randomSeed(analogRead(0));
  bool isVariation = random(100) <= variationPercent;

  randomSeed(analogRead(1));
  if (isVariation) {
    currentledBrightness += random(regularFade - (2 * regularFade), regularFade);
  } else {
    currentledBrightness += random(variationFade - (2 * variationFade), variationFade);
  }

  if (currentledBrightness <= 0) {
    currentledBrightness = 0;
  }
  if (currentledBrightness >= 255) {
    currentledBrightness = 255;
  }

  return currentledBrightness;
}

// the setup routine runs once when you press reset:
void setup() {
  pinMode(buttonPinNumber, INPUT);
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPinNumbers[i], OUTPUT);
  }
}

// the loop routine runs over and over again forever:
void loop() {
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (digitalRead(buttonPinNumber) == LOW) {
    // turn toggle loopEnabled
    if (!buttonPressed) {
      loopEnabled = !loopEnabled;

      // loop was just disabled
      if (!loopEnabled) {
        doCleanUp = true;
      }
    }
    buttonPressed = true;
  } else {
    // button released
    buttonPressed = false;
  }

  if (loopEnabled) {
    for (int i = 0; i < ledCount; i++) {
      ledBrightness[i] = calcLedBrightness(ledBrightness[i]);
      applyledBrightness(ledPinNumbers[i], ledBrightness[i]);
    }
  }

  if (doCleanUp) {
    for (int i = 0; i < ledCount; i++) {
      ledBrightness[i] = 0;
      applyledBrightness(ledPinNumbers[i], ledBrightness[i]);
    }
    doCleanUp = false;
  }

  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
