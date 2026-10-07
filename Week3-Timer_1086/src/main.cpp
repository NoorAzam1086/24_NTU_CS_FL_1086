#include <Arduino.h>

#define LED 4

hw_timer_t *My_timer = NULL;
// hw_timer_t  special data type hai jo timer ke liye use hota hai
// *My_timer aik pointer hai jo timer ke address ko point karta hai
 // NULL se initialize karte hain taki pata chale ke abhi tak koi timer create nahi hua hai

void ARDUINO_ISR_ATTR onTimer() {
  digitalWrite(LED, !digitalRead(LED));
}
// ARDUIN0_ISR_ATTR compiler ko batata hai ky function ko ESP32 ky RAM ma store krna hai na ky flash memory ma.
// onTimer aik function hai jo timer interrupt ke waqt call hota hai
// digitalWrite(LED, !digitalRead(LED)); LED ki state ko toggle karta hai

void setup() {
  pinMode(LED, OUTPUT);


  My_timer = timerBegin(0, 80, true);
  //timerBegin aik function hai jo timer ko initialize karta hai
  // Hm na simply desired frequency input ki hai, Jo ky, Is ka mtlb hai timer 1 micro-second per tick kaam karega

  timerAttachInterrupt(My_timer, &onTimer, true);
// Yeh code ko hardware timer ky sath connect karta hai, aur jab timer interrupt hota hai to onTimer function call hota hai
  
  timerAlarmWrite(My_timer, 1000000, true);
// My_timer ko 1 second (1000000 microseconds) ke baad alarm set karte hain, aur true ka mtlb hai ke timer automatically reset ho jaye ga
  
  timerAlarmEnable(My_timer);
  //timerAlarmEnable function timer alarm ko enable karta hai taki timer interrupt kaam kare
}

void loop() {
  // sarra kam interrupt ke zariye ho raha hai, is liye loop function khali hai
}
