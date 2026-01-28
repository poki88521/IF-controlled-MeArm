/*
操作规则：
  1.前后箭头控制爪子开合
    前=开,后=闭
  2.左右箭头控制前臂、后臂和底盘
    左=前，右=后
  3.使用数字1 2 3切换控制位置
    1=前臂，2=后臂，3=底盘
*/


#include <IRremote.h>
#include <Servo.h>

//将对应的红外编码定义为常量
#define UP 16712445
#define DOWN 16750695
#define LEFT 16769055
#define RIGHT 16748655

#define ONE 16724175
#define TWO 16718055
#define THREE 16743045
//“长按”常量
#define KEEP 4294967295
#define OTHERS 0


//接收器对象
IRrecv recv(7);
//接收器结果
decode_results result;
//操纵位置变量
unsigned long opcode = UP;

//舵机对象
Servo base, clow, fArm, rArm;
//舵机角度参数
int bPos, cPos, fPos, rPos;

void servoOp(unsigned long opcode){
  switch(opcode){
    case UP:
      base.write(++bPos);
      return;
    case DOWN:
      base.write(--bPos);
      return;
    default:
      return;
  }
}

void operation(unsigned long opcode){
  switch(opcode){
    case UP:
      Serial.println("claw open");
      return;
    case DOWN:
      Serial.println("claw close");
      return;
    case LEFT:
      Serial.println("left");
      return;
    case RIGHT:
      Serial.println("right");
      return;
    default:
      return;
  }
}


void setup() {
  // put your setup code here, to run once:
  base.attach(3);
  clow.attach(4);
  fArm.attach(5);
  rArm.attach(6);
  bPos = 0;
  cPos = 0;
  fPos = 0;
  rPos = 0;
  recv.enableIRIn();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    if(recv.decode(&result)){
      switch(result.value){
        case ONE:
          Serial.println("to fArm");
          opcode = ONE;
          break;
        case TWO:
          Serial.println("to rArm");
          opcode = TWO;
          break;
        case THREE:
          Serial.println("to base");
          opcode = THREE;
          break;

        case UP:
          Serial.println("claw open");
          opcode = UP;
          servoOp(UP);
          break;
        case DOWN:
          Serial.println("claw close");
          opcode = DOWN;
          servoOp(DOWN);
          break;
        case LEFT:
          Serial.println("left");
          opcode = LEFT;
          break;
        case RIGHT:
          Serial.println("right");
          opcode = RIGHT;
          break;
        case KEEP:
          operation(opcode);
          break;
        default:
          opcode = OTHERS;
          Serial.println("others");
          break;
      }
      recv.resume();
  }
}
