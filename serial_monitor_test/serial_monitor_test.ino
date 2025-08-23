int counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial); 
  Serial.println("setup");
}

void loop() {
  Serial.println(counter);
  counter = counter + 1;
  delay(1000);
}
