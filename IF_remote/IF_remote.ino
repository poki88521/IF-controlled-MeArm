#include<IRremote.h>

/*
up:16712445
down:16750695
left:16769055
right:16748655

1:16724175
2:16718055
3:16743045
4:16716015
5:16726215
6:16734885

option:16754775

A:16753245
C:16769565
*/



IRrecv recv(7);
decode_results result;

void setup() {
  // put your setup code here, to run once:
  recv.enableIRIn();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(recv.decode(&result)){
    Serial.println(result.value);
    recv.resume();
  }
  
}
