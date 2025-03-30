const int RECEIVE_PIN = A0;
const int MESSAGE_SIZE = 10; // 8 data bits + parity + 1 stop bit
unsigned long bitDuration = 1500; // Bit duration in microseconds for 1500 baud
const int THRESHOLD = 10; // Threshold for detecting HIGH or LOW
bool fifo[MESSAGE_SIZE]; // FIFO buffer for bits
int bitTracker = 0;
bool calculateBitRateFlag = false; // Flag to trigger bit rate calculation
unsigned long startTime = 0; // Variable to track the start time for 5 seconds

void setup() {
  Serial.begin(9600);
  Serial.println("Receiver setup...");
}

void loop() {
  // Check if "bit rate" is typed in the Serial Monitor
  
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim(); // Remove any trailing newline characters or spaces
    if (input.equalsIgnoreCase("bit rate")) {
      calculateBitRate(); // Set the flag to start calculating bit rate
       // Record the start time
      
    }
  }
 

  //Serial.println(analogRead(A0));}
  
  if (analogRead(RECEIVE_PIN) > THRESHOLD) { // Detect start bit (HIGH)
    delayMicrosecondsCustom(750); // Wait for the middle of the start bit to avoid timing drift
    
    // Read the next 8 data bits + 1 parity + 1 stop bit
    for (int i = 0; i < MESSAGE_SIZE; i++) {
      delayMicrosecondsCustom(bitDuration); // Wait for the center of each bit
      fifo[i] = analogRead(RECEIVE_PIN) < THRESHOLD ? LOW : HIGH; // Read bit
    }
    
    // Call the function to print the received bits
    printReceivedBits(fifo, MESSAGE_SIZE);

    // Validate parity and stop bit
    if (verifyByte(fifo)) {
      char receivedChar = convertToAscii();
      Serial.print("Received character: ");
      Serial.println(receivedChar);
    } else {
      Serial.println("Transmission error detected!");
    }
    
    // Reset bit tracker
    bitTracker = 0;
  }
}

bool verifyByte(bool byteMessage[]) {
  int parity = 0;
  for (int i = 0; i < 8; i++) { // Check first 8 bits (data bits)
    if (byteMessage[i] == HIGH) parity++;
  }
  bool parityBit = byteMessage[8]; // Check parity bit
  bool stopBit = byteMessage[9]; // Check stop bit
  return (stopBit == LOW && parityBit == (parity % 2));

}

char convertToAscii() {
  char ascii = 0;
  for (int i = 0; i < 8; i++) { // Convert first 8 bits into ASCII character
    if (fifo[i]) {
      ascii |= 1 << i;
    }
  }
  return ascii;
}

void printReceivedBits(bool byteMessage[], int size) {
  bool startBitDetected = false;
  for (int i = 0; i < size; i++) {
      Serial.print(byteMessage[i]); // Print the bit
  }
  
    Serial.println(); // New line after printing bits
  
}



void calculateBitRate() {
  unsigned long startMillis = millis(); // Record the start time
  unsigned long previousMillis = 0;
  int transitionCount = 0;
  bool lastState = LOW;
  unsigned long errors = 0;
  unsigned long count = 0;

  while (millis() - startMillis < 10000) { // Run for 10 seconds
    unsigned long currentMillis = millis();

    // Check if 1 second has passed
    if (currentMillis - previousMillis >= 1000) {
      // Calculate bit rate (transitions represent  a cycle of a bit)
      int bitRate = transitionCount;
      Serial.print("Bit rate: ");
      Serial.println(bitRate);

      // Reset for the next 1-second interval
      previousMillis = currentMillis;
      transitionCount = 0;
    }

    // Read current state from the pin (analog read with threshold comparison)
    bool currentState = analogRead(RECEIVE_PIN) > THRESHOLD ? HIGH : LOW;
    count++
    // Detect transitions between HIGH and LOW
    if (currentState != lastState) {
      transitionCount++; // Increment on every transition
      lastState = currentState; // Update the last state
    }
    else{
      errors++;
    }
  }

  Serial.println("10 seconds of bit rate calculation finished.");
}


void delayMicrosecondsCustom(unsigned long delayTime ) {
  unsigned long startTime = micros(); // Record the starting time
  while (micros() - startTime < delayTime) {
    // Wait until the specified time has passed
  }
}
