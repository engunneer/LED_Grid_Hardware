
String inputString = "";         // a string to hold incoming data
boolean newNumberArrived = false;  // whether the string is complete
int newNumber;

void interfaceSetup(){  // initialize serial:
  Serial.begin(115200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

  }
