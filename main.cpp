#include "mbed.h"

RawSerial gs(USBTX,USBRX,9600);
DigitalOut cond(LED1);
Timer sattime;

int rcmd = 0, cmdflag = 0;
void commandget(){
    rcmd = gs.getc();
    cmdflag = 1;
}

void receive(int rcmd, int cmdflag){
    gs.attach(commandget,Serial::RxIrq);
}

void initialize(){
    rcmd = 0;
    cmdflag = 0;
}

int main() {
  sattime.start();
  receive(rcmd,cmdflag);
  float vol = 3.7; //demo data
  while(1) {
    gs.printf("hepta-sat: time = %f vol = %f\r\n",sattime.read(),vol);
    if(cmdflag == 1){
        if(rcmd == 'A'){
            gs.printf("Hello World!!\r\n");
        }
        initialize();
    }
    wait(1.0);
  }
  sattime.stop();
}
