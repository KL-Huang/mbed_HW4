#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"
#include "mbed_rpc.h"

Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BufferedSerial xbee(D1, D0);

BBCar car(pin5, pin6, servo_ticker);
double d1, d2, direction;
int move_us;

int main() {
   
   pin5.period_ms(20); 
   pin6.period_ms(20); 
   car.stop();

   char buf[256], outbuf[256];
   FILE *devin = fdopen(&xbee, "r");
   FILE *devout = fdopen(&xbee, "w");
   while (1) {
      memset(buf, 0, 256);
      for( int i = 0; ; i++ ) {
         char recv = fgetc(devin);
         if(recv == '\n') {
            printf("\r\n");
            break;
         }
         buf[i] = fputc(recv, devout);
      }
      d1 = in->getArg<double>();
    d2 = in->getArg<double>();
    direction = in->getArg<double>();

    if (direction == 1) {
        move_us = (d2 + 2) * 1000000 / 6;
        car.goStraight(20);
        wait_us(move_us);
        car.turn(20, 0.1);
        ThisThread::sleep_for(2900ms);
        move_us = (d1 + 4) * 1000000 / 6;
        car.goStraight(20);
        wait_us(move_us);
    }
    else if (direction == 2) {
        move_us = (d2 + 2) * 1000000 / 6;
        car.goStraight(20);
        wait_us(move_us);
        car.turn(20, -0.1);
        ThisThread::sleep_for(2900ms);
        move_us = (d1 + 4) * 1000000 / 6;
        car.goStraight(20);
        wait_us(move_us);
    }
    else if (direction == 3) {
        move_us = (d2 + 2) * 1000000 / 6;
        car.goStraight(20);
        wait_us(move_us);
        ThisThread::sleep_for(2900ms);
        move_us = (d1 + 4) * 1000000 / 6;
        car.goStraight(20);
        wait_us(move_us);
    }
    car.stop();
      RPC::call(buf, outbuf);
   }
}