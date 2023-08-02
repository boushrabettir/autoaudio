#include <IRremote.hpp>

// Sensor pin (A0-A7) to get real values from analog pins rather than the
// binary values from the digital pins
int SENSOR_PIN = A0;

// Holds the volume values up to MAX_VOLUME_LENGTH
const int MAX_VOLUME_LENGTH = 5;
int VOLUME_VALUES[MAX_VOLUME_LENGTH] = {0, 0, 0, 0, 0};

// Holds thresholds for volume (volumes bound to change)
int LOUD_THRESHOLD = 600;
int LOW_THRESHOLD = 300;

// Pin mode for IR Transmitter
int IR_TRANSMITTER = 9;

void setup() {
  // Set up connection with IR Transmitter
  IrSender.begin(IR_TRANSMITTER);
  Serial.begin(9600);
}

void loop() {
  int sensor_value = analogRead(SENSOR_PIN);

  // Debugging
  Serial.println(sensor_value);

  // Record volume values
  record_volume_values(sensor_value);

  if (is_volume_array_full()) {
    int determine_value = determine_threshold();
    Serial.println("DETERMINE VOLUME!");
    switch (determine_value) {
      case 1:
        // Majority of volumes are above high threshold, decrease volume
        decrease_volume();
        break;
      case 0:
        // Majority of volumes are below low threshold, increase volume
        increase_volume();
        break;
      case -1:
        // Majority of volumes are between thresholds, no action is necessary
        reset_list();
        break;
    }
  }
}


void record_volume_values(int volume) {
  static int index = 0;
  VOLUME_VALUES[index] = volume;
  index = (index + 1) % MAX_VOLUME_LENGTH;

} 

bool is_volume_array_full() {
  for (int i = 0; i < MAX_VOLUME_LENGTH; i++) {
    if (VOLUME_VALUES[i] == 0) {
      return false;
    }
  }
  return true;
}

int determine_threshold() {
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

void increase_volume() {
  Serial.println("INCREASE VOLUME!");
  for (int i=0; i < 5; i++) {
    IrSender.sendNEC("F8070707", 32);
  }
  reset_list();
  delay(1000);
}

void decrease_volume() {
  Serial.println("DECREASE VOLUME!");
  for (int i=0; i < 5; i++) {
    IrSender.sendNEC("F40B0707", 32);
  }
  reset_list();
  delay(1000);
}

void reset_list() {
  for (int i = 0; i < MAX_VOLUME_LENGTH; i++) {
    VOLUME_VALUES[i] = 0;
  }
}



