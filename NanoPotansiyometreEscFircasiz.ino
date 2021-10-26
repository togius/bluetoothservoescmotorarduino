#include <Servo.h>
Servo ESC;     // create servo object to control the ESC
Servo servoDumen;
int hizDegeri;  // value from the analog pin
int aciDegeri;
String bluetoothOkunan;

void setup() {
  Serial.begin(9600);
  // Attach the ESC on pin 3
  ESC.attach(3, 1000, 2000); // (pin, min pulse width, max pulse width in microseconds)
  servoDumen.attach(9);
  hizDegeri = 700; //700 de motor duruyor
}
void loop() {

  //    Serial.println(hizDegeri);
  while (Serial.available()) {
    bluetoothOkunan = Serial.readString(); // read the incoming data as string
    //    hizDegeri = analogRead(A0);// reads the value of the potentiometer (value between 0 and 1023)
    String hizOkunan = getValue(bluetoothOkunan, '_', 0); // get 1
    String dumenOkunan = getValue(bluetoothOkunan, '_', 1); // get 2
    Serial.print(hizOkunan);
    Serial.print(' ');
    Serial.println(dumenOkunan);

    hizDegeri = hizOkunan.toInt();// appInventorden 0-1023 arası bir deger gelecek
    hizDegeri = map(hizDegeri, 0, 1023, -200, 200); //motor hızını -200,200 arası belirledik
    ESC.write(hizDegeri);    // Escye sinyaligonderdik
    aciDegeri = dumenOkunan.toInt();
    servoDumen.write(aciDegeri);
  }
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
