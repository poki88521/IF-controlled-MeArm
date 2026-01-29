#include <Servo.h>

Servo myservo;  // 创建舵机对象

void setup() {
  Serial.begin(9600);
  myservo.attach(4);        // 将舵机连接到数字引脚9
  // 或使用自定义脉冲宽度：
  // myservo.attach(9, 500, 2500); // 最小500μs，最大2500μs
}

void loop() {
  myservo.write(90);        // 舵机转到90度位置
  delay(1000);
  
  myservo.write(0);         // 舵机转到0度位置
  delay(1000);
  
  myservo.write(180);       // 舵机转到180度位置
  delay(1000);
  
  // 使用微秒控制
  //myservo.writeMicroseconds(1500);  // 中间位置
  //delay(1000);
}