#define TRIG_PIN 10
#define ECHO_PIN 11
#define BUZZER_PIN 13

// LED pins
int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize LED pins as outputs
  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  long duration, distance;

  // Trigger the ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1; // Convert to cm

  // Determine which LEDs to light up
  int ledCount = mapDistanceToLEDs(distance);

  // Light up the LEDs based on the distance
  for (int i = 0; i < 8; i++) {
    if (i < ledCount) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }

  // Control the buzzer
  if (ledCount >= 6) {
    digitalWrite(BUZZER_PIN, HIGH); // Turn on the buzzer
  } else {
    digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer
  }

  delay(100); // Small delay to prevent excessive readings
}

int mapDistanceToLEDs(long distance) {
  // Map the distance to a number of LEDs
  switch (distance) {
    case 0 ... 31:
        return 8;
    case 32 ... 62:
        return 7;
    case 63 ... 93:
        return 6;
    case 94 ... 124:
        return 5;
    case 125 ... 155:
        return 4;
    case 156 ... 186:
        return 3;
    case 187 ... 217:
        return 2;
    case 218 ... 250:
        return 1;
    default:
        return 1;
  }
}
