int analogPin = A3; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
int val1 = 0;  // variable to store the value read
int val2 = 0;
int val_inv = 0;

void setup() {
  Serial.begin(9600);           //  setup serial
}

void loop() {
  val1 = analogRead(analogPin);  // read the input pin
  val2 = analogRead(A4);
  val_inv = analogRead(A5);
  Serial.print(val2);
  Serial.print("    ");
  Serial.print(val_inv);
  Serial.print("    ");
  Serial.println(val1);
}
