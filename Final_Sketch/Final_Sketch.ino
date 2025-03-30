int ledPin = 2; //Initalize data pin
int bytes[8]; //Create byte string
int evenParity = 0; //Create parity variable

void setup() {
  pinMode(ledPin, OUTPUT);  //Set data pin to output
  Serial.begin(9600); //Set baud rate
}

void loop() {
  serialByte(); //Start data sending function
}

void serialByte() {
  Serial.println("Enter data:");  //Prompt user to enter data to send
  while (Serial.available() == 0) { //Checks if there is any data to send
    digitalWrite(ledPin, HIGH); //Defaults high if there is nothing to send
  }
  String message = Serial.readString(); //Reads the string sent in the serial monitor
  Serial.println("Transmitting: " + message); //Sends transmitting message in serial monitor
  message.trim(); //Removes whitespace from string
  digitalWrite(ledPin, LOW);  //Sends starting bit of 0

  for(int i=0; i < message.length(); i++) { //Iterates through each character in the message
    char character = message.charAt(i); //Grabs the character at index i
    evenParity = 0; //Reset parity bit
    for (int j = 7; j >= 0; j--) {  //Iterates 8 times
      bytes[j] = bitRead(character , j);  //Reads the jth bit of the character
      Serial.print(bytes[j]); //Prints the bit to the serial monitor
      if (bytes[j] == 1) {  //Checks if the bit is 1
        digitalWrite(ledPin, HIGH); //If the bit is 1, set pin high
        evenParity += 1;  //If bit is 1, increment evenParity
      } else {
        digitalWrite(ledPin, LOW);  //If the bit is 0, set pin low
      }
      //delay(10);
      delayMicroseconds(666); //Delay by 100 ms
    } 
    if (evenParity % 2 == 0) {  //Check if evenParity is even
      digitalWrite(ledPin, LOW);  //If evenParity is even, parity bit is low
      Serial.print(" Parity Bit: 0"); //Send parity bit in serial monitor
    } else {
      digitalWrite(ledPin, HIGH); //If evenParity is odd, parity bit is high
      Serial.print(" Parity Bit: 1"); //Send parity bit in serial monitor
    }
    delayMicroseconds(666); //Delay by 100 ms
    //delay(10);
    Serial.println(""); //Print new line
  }
  Serial.println(""); //Print new line
}

