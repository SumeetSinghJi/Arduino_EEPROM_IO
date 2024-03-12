#include <EEPROM.h>

// Memory address in EEPROM where the message will be stored
int variableMemoryAddress = 0;

// Variable to store to EEPROM storage
String stringMessage = "Hello, World";

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialise serial communication at baud 9600 to read when plugged into computer e.g. at COM3
  Serial.begin(9600);

  writeStringToEEPROM(variableMemoryAddress, stringMessage);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Turn the LED on (HIGH)
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  // Turn the LED off (LOW)
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  // Read the stored variables message from EEPROM to serial monitor
  String retrievedMessage = readStringFromEEPROM(variableMemoryAddress);
  Serial.println(retrievedMessage);
}

void writeStringToEEPROM(int addr, String data) {
  /* e.g. if stringMessage = "Hello, World"
  it is stored in the positions below. So to retrieve we
  need to know which address in the EEPROM it started at
  Address 1: 'H'
  Address 2: 'e'
  Address 3: 'l'
  Address 4: 'l'
  Address 5: 'o'
  Address 6: ','
  Address 7: ' '
  Address 8: 'W'
  Address 9: 'o'
  Address 10: 'r'
  Address 11: 'l'
  Address 12: 'd'
  Address 13: '\0' (null terminator)
*/
  for (unsigned int i = 0; i < data.length(); i++) {
    EEPROM.write(addr + i, data[i]);
  }
  EEPROM.write(addr + data.length(), '\0');  // null terminate the string
}

String readStringFromEEPROM(int addr) {
  // Output the stored variable from writeStringToEEPROM()
  String data = "";
  char character = EEPROM.read(addr); // read the first character
  while (character != '\0' && addr < EEPROM.length()) { // Check EEPROM length
    data += character; // write first/next character e.g. "H" in Hello world to data
    addr++; // go to next memory address
    character = EEPROM.read(addr); // read the next character
  }
  return data;
}












