#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BufferedSerial xbee(D1, D0);

BBCar car(pin5, pin6, servo_ticker);
void parking(Arguments *in, Reply *out);
RPCFunction rpcparking(&parking, "parking");
double d1, d2, direction;
int time;

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
      RPC::call(buf, outbuf);
   }
}

void parking(Arguments *in, Reply *out)
{
      d1 = in->getArg<double>();
      d2 = in->getArg<double>();
      direction = in->getArg<double>();

    if (direction == 1) {
        time = (d2 + 2) * 200000;
        car.goStraight(-50*d2);
        wait_us(time);
        car.turn(35, 0.1);
        ThisThread::sleep_for(3000ms);
        time = (d1 + 4) * 200000;
        car.goStraight(-50*d1);
        wait_us(time);
    }
    else if (direction == 2) {
        time = (d2 + 2) * 200000;
        car.goStraight(-50*d2);
        wait_us(time);
        car.turn(35, -0.1);
        ThisThread::sleep_for(3000ms);
        time = (d1 + 4) * 200000;
        car.goStraight(-50*d1);
        wait_us(time);
    }
    else car.stop();
    car.stop();
    return;
}