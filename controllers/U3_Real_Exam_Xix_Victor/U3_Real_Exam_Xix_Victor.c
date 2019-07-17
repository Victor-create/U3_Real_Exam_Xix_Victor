/*
 * File:          U3_Real_Exam_Xix_Victor.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */
#include <webots/robot.h>
#include <webots/distance_sensor.h>
#include <webots/position_sensor.h>
#include <webots/motor.h>
#include <webots/keyboard.h>

#include <stdio.h>

#include <promedio.h>

#define TIME_STEP 64
#define PI 3.1416

double b1=0;  //posicion inicial en 0
double b2=0; // Posicion incial en 0
double b3=0;
int times=0;
int times2=0;
int key;  // Variable para el teclado
int a=1; //Variable modo automatico
int m=0; //Variable modo Manual
double a1, a2,a3;
float Buzz = 0;
int turn_left = 0;
int turn_right = 0;
double d1,d2;// Variables para el sensor de distancia
double speed = 3;
double null = 0;


 void goRobot(WbDeviceTag wheel_1,WbDeviceTag wheel_2,WbDeviceTag wheel_3){
  wb_motor_set_velocity(wheel_1, -speed);
  wb_motor_set_velocity(wheel_2, speed);
  wb_motor_set_velocity(wheel_3, null);

  }
 void downRobot(WbDeviceTag wheel_1,WbDeviceTag wheel_2,WbDeviceTag wheel_3){
  wb_motor_set_velocity(wheel_1,speed);
  wb_motor_set_velocity(wheel_2,-speed);
  wb_motor_set_velocity(wheel_3, null);
  }
 void leftRobot(WbDeviceTag wheel_1,WbDeviceTag wheel_2,WbDeviceTag wheel_3){
  wb_motor_set_velocity(wheel_1, -speed);
  wb_motor_set_velocity(wheel_2, -speed);
  wb_motor_set_velocity(wheel_3, 6.1);
  }
 void rightRobot(WbDeviceTag wheel_1,WbDeviceTag wheel_2,WbDeviceTag wheel_3){
  wb_motor_set_velocity(wheel_1, speed);
  wb_motor_set_velocity(wheel_2, speed);
  wb_motor_set_velocity(wheel_3, -6.1);
  }
 void stopRobot(WbDeviceTag wheel_1,WbDeviceTag wheel_2,WbDeviceTag wheel_3){
  wb_motor_set_velocity(wheel_1,null);
  wb_motor_set_velocity(wheel_2,null);
  wb_motor_set_velocity(wheel_3,null);
  }
 void turnRight(WbDeviceTag wheel_1,WbDeviceTag wheel_2,WbDeviceTag wheel_3){
  wb_motor_set_velocity(wheel_1,-0.785398);
  wb_motor_set_velocity(wheel_2,-0.785398);
  wb_motor_set_velocity(wheel_3,-0.785398);
  }
 void turnLeft(WbDeviceTag wheel_1,WbDeviceTag wheel_2,WbDeviceTag wheel_3){
    wb_motor_set_velocity(wheel_1,0.785398);
    wb_motor_set_velocity(wheel_2,0.785398);
    wb_motor_set_velocity(wheel_3,0.785398);
  }
 void goAuto(WbDeviceTag wheel_1,WbDeviceTag wheel_2,WbDeviceTag wheel_3){
    wb_motor_set_velocity(wheel_1,-1);
    wb_motor_set_velocity(wheel_2,1);
    wb_motor_set_velocity(wheel_3,0);
  }
 void turnrAuto(WbDeviceTag wheel_1,WbDeviceTag wheel_2,WbDeviceTag wheel_3){
    wb_motor_set_velocity(wheel_1,1);
    wb_motor_set_velocity(wheel_2,1);
    wb_motor_set_velocity(wheel_3,1);
  }
 void turnlAuto(WbDeviceTag wheel_1,WbDeviceTag wheel_2,WbDeviceTag wheel_3){
    wb_motor_set_velocity(wheel_1,-1);
    wb_motor_set_velocity(wheel_2,-1);
    wb_motor_set_velocity(wheel_3,-1);
  }


int main(int argc, char **argv){
  /* necessary to initialize webots stuff */
  wb_robot_init();
  wb_keyboard_enable(TIME_STEP);



   WbDeviceTag wheel_1 = wb_robot_get_device("motor_1");
   WbDeviceTag wheel_2 = wb_robot_get_device("motor_2");
   WbDeviceTag wheel_3 = wb_robot_get_device("motor_3");

   WbDeviceTag ps_1 = wb_robot_get_device("position_1");
   WbDeviceTag ps_2 = wb_robot_get_device("position_2");
   WbDeviceTag ps_3 = wb_robot_get_device("position_3");

   wb_motor_set_position(wheel_1,INFINITY);
   wb_motor_set_position(wheel_2,INFINITY);
   wb_motor_set_position(wheel_3,INFINITY);

   wb_position_sensor_enable(ps_1, TIME_STEP);
   wb_position_sensor_enable(ps_2, TIME_STEP);
   wb_position_sensor_enable(ps_3, TIME_STEP);

   WbDeviceTag ds_r1 = wb_robot_get_device("distance_sensor1");
   WbDeviceTag ds_r2 = wb_robot_get_device("distance_sensor2");

   wb_distance_sensor_enable(ds_r1, TIME_STEP);
   wb_distance_sensor_enable(ds_r2, TIME_STEP);

   d1=(wb_distance_sensor_get_value(ds_r1)*0.2)/65535;
   d2=(wb_distance_sensor_get_value(ds_r2)*0.2)/65535;

  void automatic(){
     WbDeviceTag ds_r1 = wb_robot_get_device("distance_sensor1");
     WbDeviceTag ds_r2 = wb_robot_get_device("distance_sensor2");

     wb_distance_sensor_enable(ds_r1, TIME_STEP);
     wb_distance_sensor_enable(ds_r2, TIME_STEP);

     d1=(wb_distance_sensor_get_value(ds_r1)*0.2)/65535;
     d2=(wb_distance_sensor_get_value(ds_r2)*0.2)/65535;


     goAuto( wheel_1, wheel_2, wheel_3);

     if (d1<= 0.17 && d1<d2){
       times++;
     }
     if (times>=1 && times<=58){
     turnlAuto( wheel_1, wheel_2, wheel_3);
     times++;
     }
     else {
      times=0;
     }

     if (d2<0.17 && d2<d1){
       times2++;
     }

     if(times2 >=1 && times2<=58){
     turnrAuto( wheel_1, wheel_2, wheel_3);
     times2++;
     }
     else{
     times2=0;
     }
   }
  void manual(){

        if(key == WB_KEYBOARD_UP){
          goRobot( wheel_1, wheel_2, wheel_3);


        }
        else if(key == WB_KEYBOARD_DOWN){
          downRobot( wheel_1, wheel_2, wheel_3);

        }
        else if(key == WB_KEYBOARD_LEFT){
          leftRobot(wheel_1,wheel_2,wheel_3);

        }
        else if(key == WB_KEYBOARD_RIGHT){
          rightRobot(wheel_1,wheel_2,wheel_3);

        }
        else if(key == 'S' ){
          Buzz = a1 + 0.785398; //.75 = 45 degrees to the left
          turn_left = 1;
        }

        else if(turn_left == 1){

          if(a1 <= Buzz){
          turnLeft(wheel_1,wheel_2,wheel_3);
        }
        else{
          stopRobot(wheel_1,wheel_2,wheel_3);

          turn_left = 0;
        }

      }

        else if(key == 'A' ){
        Buzz = a1 - 0.785398; // 45 degrees to the right
        turn_right = 1;

        }
         else if(turn_right == 1){

          if(a1 >= Buzz){
          turnRight(wheel_1,wheel_2,wheel_3);

        }
        else{
          stopRobot(wheel_1,wheel_2,wheel_3);

          turn_right = 0;
        }

        }
        else{
          stopRobot(wheel_1,wheel_2,wheel_3);
        }
   }

  while (wb_robot_step(TIME_STEP) != -1) {

  double pos_final1, pos_final2,pos_final3; //posiciones finales
  double RPM_1, RPM_2, RPM_3;

  ////rueda 1//////////////
  a1 = wb_position_sensor_get_value(ps_1);
          pos_final1 = ((a1 - b1)*1)/0.064;  //0-064 es el time step en segundos
          RPM_1= (pos_final1*60)/(2*PI);
          b1 = a1;

  //////rueda 2////////////
  a2 = wb_position_sensor_get_value(ps_2);
          pos_final2 = ((a2 - b2)*1)/0.064;
          RPM_2= (pos_final2*60)/(2*PI);
          b2 = a2;
  //////rueda 3////////////
  a3 = wb_position_sensor_get_value(ps_3);
          pos_final3 = ((a3 - b3)*1)/0.064;
          RPM_3= (pos_final3*60)/(2*PI);
          b3 = a3;

  /////////velocidad lineal del robot///////
  float radio=0.06; //radio de la llanta
  double linvel1, linvel2, linvel3;//velocidad lineal por llanta
  double linvel_rob; //velocidad lineal del robot

  linvel1=pos_final1*radio;
  linvel2=pos_final2*radio;
  linvel3=pos_final3*radio;
  linvel_rob=prom(linvel1,linvel2,linvel3);

  key = wb_keyboard_get_key();

  if(key == 'W'){
    m = 1;
    a = 0;
    printf("Manual mode \n");
  }

   if (key == 'G'){
    m = 0;
    a = 1;
   printf("Automatic mode \n");

  }

  if(m == 1){
  manual();
}
  if(a == 1){
  automatic();
  }


     printf("Wheel1:RW_RPM %f RPM\tWheel2:RW_RPM %f RPM\tWheel3:RW_RPM %f RPM\
     tlinear_velocity %f \n",RPM_1,RPM_2,RPM_3,linvel_rob);


  };


  wb_robot_cleanup();

  return 0;
}
