
int val1 = 0;  // variable to store the value read
int val2 = 0;
int val3 = 0;

void setup() {
  Serial.begin(19200);           //  setup serial
}

void loop() {
  val1 = analogRead(A3);  // read the input pin
  val2 = analogRead(A4);
  val3 = analogRead(A5);
  Serial.print(val1);
  Serial.print("    ");
  Serial.print(val2);
  Serial.print("    ");
  Serial.print(val3);
  Serial.println();
}
