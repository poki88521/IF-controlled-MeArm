
/*
1更改操作位置（location）和动作（operation）变量确定操作类型
2根据location确定操作的上下限
3改写pos
4检测pos变量是否合规
5写入舵机
*/


#include <IRremote.h>
#include <Servo.h>

//将对应的红外编码定义为常量
#define UP 16712445
#define DOWN 16750695
#define LEFT 16769055
#define RIGHT 16748655

#define F_CODE 16724175
#define R_CODE 16718055
#define B_CODE 16743045
#define C_CODE 1
#define HI_SPEED 16753245
#define LO_SPEED 16769565

//“长按”常量
#define KEEP 4294967295
#define NONE 0
//舵机角度范围常量
#define F_MIN 90
#define F_MAX 130
#define R_MIN 40
#define R_MAX 110
#define B_MIN 0
#define B_MAX 180
#define C_MIN 0
#define C_MAX 105


//接收器对象
IRrecv recv(7);
//接收器结果
decode_results result;
//操纵位置变量
unsigned long location;
unsigned long operation;
//result.value
unsigned long value;

//舵机对象
int posNum;
Servo servo[4];
//舵机角度参数
int pos[4];
//clow,fPos,rPos,bPos
//当前角度上下限参数
int min, max;
int step;

//-----------------------------------函数区----------------------------------------
//检查舵机角度是否合规的函数
bool check(){
  if(pos[posNum] > max){
    pos[posNum]  = max;
    return false;
  }else if(pos[posNum] < min){
    pos[posNum]  = min;
    return false;
  }
  return true;
}

void execute(){
  //根据code选择操作时的判断限制范围
  switch(location){
    case F_CODE:
      min = F_MIN;
      max = F_MAX;
      posNum = 1;
      break;
    case R_CODE:
      min = R_MIN;
      max = R_MAX;
      posNum = 2;
      break;
    case B_CODE:
      min = B_MIN;
      max = B_MAX;
      posNum = 3;
      break;
    case C_CODE:
      min = C_MIN;
      max = C_MAX;
      posNum = 0;
      break;
    default:
      break;
  }
  //改写pos
  switch(operation){
    case UP:
    case LEFT:
      pos[posNum] += step;
      break;
    case DOWN:
    case RIGHT:
      pos[posNum] -= step;
      break;
    default:
      break;
  }
  //检查并写入舵机
  if(check()){
    servo[posNum].write(pos[posNum]);
    //打印参数
    Serial.print(location);
    Serial.print(",");
    Serial.print(operation);
    Serial.print(",");
    Serial.print(pos[posNum]);
    Serial.print(",");
    Serial.print(servo[posNum].read());
    Serial.println();
  }
}

void setup() {
  // put your setup code here, to run once:
  servo[3].attach(3);//b
  servo[0].attach(4);//c
  servo[1].attach(5);//f
  servo[2].attach(6);//r
  //初始化角度变量
  pos[3] = 90;
  pos[0] = 90;
  pos[1] = 100;
  pos[2] = 50;
  step = 2;
  servo[3].write(pos[3]);
  servo[0].write(pos[0]);
  servo[1].write(pos[1]);
  servo[2].write(pos[2]);
  recv.enableIRIn();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    if(recv.decode(&result)){
      value = result.value;
      //接收location
      switch(value){
        case F_CODE:
        case R_CODE:
        case B_CODE:
          location = value;
          operation = NONE;
          break;
        case HI_SPEED:
          step = 7;
          operation = NONE;
          Serial.println(step);
          break;
        case LO_SPEED:
          step = 2;
          operation = NONE;
          Serial.println(step);
          break;
        default:
          break;
      }
      //当操作为operation时不操作舵机
      ;
      //接收operation
      switch(value){
        case UP:
        case DOWN:
          location = C_CODE;
        case LEFT:
        case RIGHT:
          operation = value;
        case KEEP:
          execute();
          break;
        default:
          break;
      }
      recv.resume();
  }
}
