# DE_LoRa

Библиотека для работы с модулями беспроводной связи LoRa и отправки данных.

## подключение
```cpp
#include <DE_LoRa.h>
```
## объект(ы)
```cpp
DE_LoRa lora(2, 3);  //пины
```
## функции
```cpp
String read();                       //читает и возвращает строку
void print(String &printString);     //печатает. Без переноса на новую строку
bool available();                    //флаг. Если данные пришли
uint16_t error();                    //возвращает число ошибок
void resetErr();                     //сбросить счётчик ошибок
uint16_t index();                    //напрямую считать индекс
uint16_t number();                   //напрямую считать число
void readCommand(int &indexOut, int &numberOut);     //читает возвращает индекс и число
void sendCommand(int indexIn, int numberIn);         //отправляет команду по индексу и числу
```
