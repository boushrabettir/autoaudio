// This script will be used to for the remote controls + volume

// For debugging purposes
int LED_PIN = 11;

// Sensor pin (A0-A7) to get real values from analog pins rather than the
// binary values from the dialog pins
int SENSOR_PIN = A0;

// Index for volumes
int index = 0;

void setup() {  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(9600);
}

void loop() {
  int sensor_value = analogRead(SENSOR_PIN);

  // Debugging
  Serial.println(sensor_value);

  // The amount of volumes placed
  int MAX_VOLUME_LENGTH = 5;

  // Holds the volume values up to MAX_VOLUME_LENGTH
  int VOLUME_VALUES[5] = {0,0,0,0,0};

  // Holds thresholds for volume (volumes bound to change)
  int LOUD_THRESHOLD = 400;
  int LOW_THRESHOLD = 200;

  if (index < 5) {
    VOLUME_VALUES[index] = sensor_value;
    index += 1;
  } else {
    
    // Reset the index value back to 0 to accept the next 5 volume values
    index = 0;

    // Recieve the final value to determine what action to take
    int determine_value = determine_threshold(VOLUME_VALUES, LOUD_THRESHOLD, LOW_THRESHOLD);

    switch (determine_value) {
      case 1:
        // Majority of volumes is above high threshold, decrease volume
        turn_off_led();
        VOLUME_
        delay(1000);
        break;
      case 0:
        // Majority of volumes is below low threshold, ncrease volume
        turn_on_led();
        break;
      case -1:
        // Majority of volumes is between threshold, thus no action is necessary
        break;
    }

}

int determine_threshold(int volume_list, int loud_threshold, int low_threshold) {
  // E.g. - [235, 255, 210, 200, 217]

  int low_counter = 0;
  int high_counter = 0;
  int middle_counter = 0;
  
  for (int i = 0; i < volume_list.length(); i++) {
    if (volume_list[i] <= low_threshold) {
      // Current volume is below the threshold
      low_counter += 1;
    } else if (volume_list[i] >= loud_threshold) {
      // Current volume is above the threshold
      high_counter += 1;
    } else {
      // Current volume is in bounds
      middle_counter += 1;
    }
  }

  // TODO
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
