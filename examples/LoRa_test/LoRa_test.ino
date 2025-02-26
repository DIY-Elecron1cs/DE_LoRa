#include <DE_LoRa.h>      //сама библиотека

/*---ПРИМЕР, использование---*/

#define MODE 1  //0 - отправка, 1 - получение

DE_LoRa lora(2, 3);    //создаём объект класса LoRa

void setup() {
  Serial.begin(9600);
}

void loop() {
#if MODE == 1   //приём
  int index, number;
  if (lora.available()) {               //как в обычном Serial
    lora.readCommand(index, number);    //читаем и записываем в переменные index и number

    Serial.print(index);    //выводим
    Serial.print('\t');
    Serial.println(number);
  }
#else           //отправка
  lora.sendCommand(5, 108);
  delay(1000);
#endif
}
