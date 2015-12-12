#define LED0 9
#define LED1 10

unsigned char s = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  s = rand() % 200;
  analogWrite(LED0, s);
  delay(s/10);

  s = rand() % 200;
  analogWrite(LED1, s);
  delay(s/10);
}