/*
$ roscore
#新终端打开
$  rosrun rosserial_python serial_node.py _port:=/dev/ttyUSB0
#新终端打开
$ rostopic pub PC2Arduino std_msgs/UInt16 1
 
*/

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>
#include <DynamixelWorkbench.h>

#define DXL_BUS_SERIAL1 "1"            //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 "2"            //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 "3"            //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#define DXL_BUS_SERIAL4 "/dev/ttyACM0" //Dynamixel on Serial3(USART3)  <-OpenCR

ros::NodeHandle nh;
std_msgs::String str_msg;


#define BAUDRATE 1000000
//#define ID1 12
//#define ID2 9
//#define ID3 13
//#define ID4 10

#define ID5 11
#define ID6 8
#define ID7 17
#define ID8 16
#define ID11 21

//#define ID9 2
//#define ID10 1

int a,c,d,i,ccc,mode=0;
String b="";
int id5 =2061;
int id6 =4040;
int id7 =4052;
int id8 =2076;
int id11 =2500;
DynamixelWorkbench dxl_wb;


void Control(const std_msgs::UInt16& cmd_msg)
{
  mode=cmd_msg.data;
   
   if(cmd_msg.data == 0)
  {
      digitalWrite(14, LOW); 
  }
  
  if(cmd_msg.data == 1)
  {
      digitalWrite(14, HIGH); 
  }
     
}
void Control2(const std_msgs::String& cmd_msg2)
{
  b=cmd_msg2.data;
}
//ros::Subscriber <std_msgs::String> 
ros::Subscriber <std_msgs::UInt16> sub1("PC2Arduino", &Control);
ros::Subscriber <std_msgs::String> sub2("PC2Arduino2", &Control2);
void setup()
{
  pinMode(14, OUTPUT);
  dxl_wb.begin(DXL_BUS_SERIAL3, BAUDRATE);  
  Serial.begin(57600);
  
  dxl_wb.ping(ID5);
 // dxl_wb.ping(ID6);
   dxl_wb.ping(ID8);
   dxl_wb.ping(ID7);

  dxl_wb.ping(ID11);

   nh.initNode();
   nh.subscribe(sub1);
   nh.subscribe(sub2);
}
void loop()
{  
  nh.spinOnce();
  test();
}

void test()
{
 /* if(Serial.available()){
  b = Serial.readString();
  Serial.println(b);
  }  
*/  if(b=="w"){id5=id5-150;}
  if(b=="x"){id5=id5+150;}
  if(b=="a"){id6=id6-150;}
  if(b=="d"){id6=id6+150;}
  if(b=="q"){id7=id7-150;}
  if(b=="e"){id7=id7+150;}
  if(b=="c"){id8=id8-150;}
  if(b=="z"){id8=id8+150;}
  if(b=="g"){id11=id11-150;}
  if(b=="f"){id11=id11+150;}
  if(b=="s"){id5=2061;id6=4040; id7=4052; id8=2076; id11=2500;}
  b="";   
  Serial.println(a);
  Serial.println(id5);
  Serial.println(id6);
  Serial.println(id7);
  Serial.println(id8);
    Serial.println(id11);  
  if (mode==0){   //initial action

       dxl_wb.goalSpeed(ID5,50);
        dxl_wb.goalPosition(ID5,id5);//2078 //大後小前
        //dxl_wb.goalSpeed(ID6,50);        
       // dxl_wb.goalPosition(ID6,id6);
        dxl_wb.goalSpeed(ID8,50);
        dxl_wb.goalPosition(ID8,id8);
        dxl_wb.goalSpeed(ID7,50);
        dxl_wb.goalPosition(ID7,id7);

        dxl_wb.goalSpeed(ID11,50);
        dxl_wb.goalPosition(ID11,id11);
   }
   if(mode==1)
   {
        dxl_wb.goalSpeed(ID5,50);
        dxl_wb.goalPosition(ID5,2061);
      //  dxl_wb.goalSpeed(ID6,50);
      //  dxl_wb.goalPosition(ID6,4040);
        dxl_wb.goalSpeed(ID8,50);
        dxl_wb.goalPosition(ID8,4052);
        dxl_wb.goalSpeed(ID7,50);
        dxl_wb.goalPosition(ID7,2076);

        dxl_wb.goalSpeed(ID11,50);
        dxl_wb.goalPosition(ID11,2500);
    }
 
     
  }

