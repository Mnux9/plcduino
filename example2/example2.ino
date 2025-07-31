const int outputPinsA[] = {2, 3, 4, 5};
const int inputPinsB[] = {7, 8, 9, 10, 11};

const int numOutputPins = sizeof(outputPins) / sizeof(outputPins[0]);
const int numInputPins = sizeof(inputPins) / sizeof(inputPins[0]);

String inputCommand = "";

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < numOutputPins; i++) {
    pinMode(outputPins[i], OUTPUT);
    digitalWrite(outputPins[i], LOW); // Optional
  }

  for (int i = 0; i < numInputPins; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
  }

  Serial.println("Ready. Send 'RP1' to read pin states.");
}

void loop() {
  while (Serial.available() > 0) {
    char received = Serial.read();

    if (received == '\n' || received == '\r') {
      if (inputCommand == "G STE A") {
        reportPinStatesJSON();
      }
      inputCommand = "";
    } else {
      inputCommand += received;
    }
  }
}

void reportPinStatesJSON() {
  Serial.print("{\"outputs\":{");

  for (int i = 0; i < numOutputPins; i++) {
    int state = digitalRead(outputPins[i]);
    Serial.print("\"");
    Serial.print(outputPins[i]);
    Serial.print("\":\"");
    Serial.print(state == HIGH ? "HIGH" : "LOW");
    Serial.print("\"");
    if (i < numOutputPins - 1) Serial.print(", ");
  }

  Serial.print("}, \"inputs\":{");

  for (int i = 0; i < numInputPins; i++) {
    int state = digitalRead(inputPins[i]);
    Serial.print("\"");
    Serial.print(inputPins[i]);
    Serial.print("\":\"");
    Serial.print(state == HIGH ? "HIGH" : "LOW");
    Serial.print("\"");
    if (i < numInputPins - 1) Serial.print(", ");
  }

  Serial.println("}}");
}
