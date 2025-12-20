// NodeMCU Relay Test Program
// Relay ON and OFF every 2 seconds

#define RELAY_PIN D1   // GPIO5

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);  // Relay OFF (LOW-level trigger)
}

void loop() {
  digitalWrite(RELAY_PIN, LOW);   // Relay ON
  delay(2000);                    // 2 seconds

  digitalWrite(RELAY_PIN, HIGH);  // Relay OFF
  delay(2000);                    // 2 seconds
}
