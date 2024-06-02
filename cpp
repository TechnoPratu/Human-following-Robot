// Define pins for ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;

// Define pins for motor driver
const int in1 = 2;
const int in2 = 3;
const int in3 = 4;
const int in4 = 5;
const int ena = 6;
const int enb = 7;

// Define distance thresholds
const int distanceThreshold = 30;  // Distance in cm to maintain from the human

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Set motor driver pins as outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);

  // Set ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Get distance from ultrasonic sensor
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Print the distance for debugging
  Serial.print("Distance: ");
  Serial.println(distance);

  // Control the robot based on distance
  if (distance < distanceThreshold) {
    // Move backward if too close
    moveBackward();
  } else {
    // Move forward if not too close
    moveForward();
  }

  delay(100);
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, 200);  // Speed for left motor
  analogWrite(enb, 200);  // Speed for right motor
}

void moveBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, 150);  // Speed for left motor
  analogWrite(enb, 150);  // Speed for right motor
}

void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
