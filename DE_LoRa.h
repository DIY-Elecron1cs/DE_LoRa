#pragma once

#include <SoftwareSerial.h>   //подключаем библиотеку

class DE_LoRa {
  public:
    DE_LoRa(uint8_t rx_pin, uint8_t tx_pin) {                        //конструктор класса, задаём пины
      loraSerial = new SoftwareSerial(rx_pin, tx_pin);    //создаём объект SoftwareSerial внутри класса LoRa
      loraSerial->begin(9600);
    }

    String read() {                               //читает и возвращает строку
      return String(loraSerial->readString());
    }

    void print(String &printString) {             //печатает. Без переноса на новую строку
      return loraSerial->print(printString);
    }

    bool available() {                  //флаг. Если данные пришли
      return loraSerial->available();
    }

    uint16_t error() {    //возвращает число ошибок
      return _error;
    }

    void resetErr() {     //сбросить счётчик ошибок
      _error = 0;
    }

    uint16_t index() {    //напрямую считать индекс
      return _index;
    }

    uint16_t number() {   //напрямую считать число
      return _number;
    }

    void readCommand(int &indexOut, int &numberOut) {   //читает возвращает индекс и число
      decode(String(loraSerial->readString()));
      indexOut = _index;
      numberOut = _number;
    }

    void sendCommand(int indexIn, int numberIn) {   //отправляет команду по индексу и числу
      loraSerial->println(code(indexIn, numberIn));
    }

  private:
    void decode(String input) {                   //декодирует пришедшие данные (индекс и число)
      int separatorIndex = input.indexOf(':');    //знак разделения
      if (separatorIndex != -1) {
        String indexString = input.substring(0, separatorIndex);    //выделяет подстроку с индексом
        String numberString = input.substring(separatorIndex + 1);  //выделяет подстроку с числом
        _index = indexString.toInt();   //преобразуем в целочисленные значения
        _number = numberString.toInt();
      }
      else {    //если пришла некорректная команда
        _error = _error + 1;    //увеличиваем счётчик ошибок
      }
    }

    String code(uint16_t index, uint16_t number) {      //кодирует строку для отправки
      String codeString = String(index) + ": " + String(number);
      return codeString;
    }

    uint16_t _error = 0;
    int _index = 0;
    int _number = 0;
    SoftwareSerial *loraSerial;
};
