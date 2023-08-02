#include <IRremote.h>

#define IR_TRANSMITTER 9

// For debugging purposes
int LED_PIN = 11;

// Sensor pin (A0-A7) to get real values from analog pins rather than the
// binary values from the digital pins
int SENSOR_PIN = A0;

// Holds the volume values up to MAX_VOLUME_LENGTH
const int MAX_VOLUME_LENGTH = 5;
int VOLUME_VALUES[MAX_VOLUME_LENGTH] = {0, 0, 0, 0, 0};

// Holds thresholds for volume (volumes bound to change)
int LOUD_THRESHOLD = 400;
int LOW_THRESHOLD = 200;

void setup() {
  IrSender.begin(IR_TRANSMITTER);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(9600);
}

void loop() {
  int sensor_value = analogRead(SENSOR_PIN);

  // Debugging
  Serial.println(sensor_value);

  // Record volume values
  recordVolumeValue(sensor_value);

  if (volumeArrayFull()) {
    int determine_value = determineThreshold();

    switch (determine_value) {
      case 1:
        // Majority of volumes are above high threshold, decrease volume
        decreaseVolume();
        break;
      case 0:
        // Majority of volumes are below low threshold, increase volume
        increaseVolume();
        break;
      case -1:
        // Majority of volumes are between thresholds, no action is necessary
        break;
    }
  }
}

void recordVolumeValue(int volume) {
  static int index = 0;
  VOLUME_VALUES[index] = volume;
  index = (index + 1) % MAX_VOLUME_LENGTH;

bool volumeArrayFull() {
  for (int i = 0; i < MAX_VOLUME_LENGTH; i++) {
    if (VOLUME_VALUES[i] == 0) {
      return false;
    }
  }
  return true;
}

int determineThreshold() {
  int low_counter = 0;
  int high_counter = 0;
  int middle_counter = 0;

  for (int i = 0; i < MAX_VOLUME_LENGTH; i++) {
    if (VOLUME_VALUES[i] <= LOW_THRESHOLD) {
      // Current volume is below the threshold
      low_counter++;
    } else if (VOLUME_VALUES[i] >= LOUD_THRESHOLD) {
      // Current volume is above the threshold
      high_counter++;
    } else {
      // Current volume is in bounds
      middle_counter++;
    }
  }

  if (low_counter > middle_counter && low_counter > high_counter) {
    // Return 0 if the volume is too low
    return 0;
  } else if (high_counter > middle_counter && high_counter > low_counter) {
    // Return 1 if the volume is too high
    return 1;
  } else {
    // Return -1 if the volume is between bounds
    return -1;
  }
}

// Debugging
void turn_on_led() {
  digitalWrite(LED_PIN, HIGH);
}

// Debugging
void turn_off_led() {
  digitalWrite(LED_PIN, LOW);
}

// Hex values are temp values. 

void increaseVolume() {
  IrSender.sendNEC("FFFFFFF", 32);
  delay(1000);
}

void decreaseVolume() {
  IrSender.sendNEC("FFFFFFF", 32);
  delay(1000);
}
