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


int times=0;
int times2=0;
int times3=0;
double a;
double d1,d2,d3;// Variables para el sensor de distancia
double speed = 1;
double null = 0;
double dsvel = .3; //Velocidad del sensor del sensorgun



 void stopRobot(WbDeviceTag wheel_1,WbDeviceTag wheel_2,WbDeviceTag wheel_3){
   wb_motor_set_velocity(wheel_1,null);
   wb_motor_set_velocity(wheel_2,null);
   wb_motor_set_velocity(wheel_3,null);
  }
 void goAuto(WbDeviceTag wheel_1,WbDeviceTag wheel_2,WbDeviceTag wheel_3){
   wb_motor_set_velocity(wheel_1,-speed);
   wb_motor_set_velocity(wheel_2,speed);
   wb_motor_set_velocity(wheel_3,null);

  }
 void turnrAuto(WbDeviceTag wheel_1,WbDeviceTag wheel_2,WbDeviceTag wheel_3){
   wb_motor_set_velocity(wheel_1,speed);
   wb_motor_set_velocity(wheel_2,speed);
   wb_motor_set_velocity(wheel_3,speed);
  }
 void turnlAuto(WbDeviceTag wheel_1,WbDeviceTag wheel_2,WbDeviceTag wheel_3){
   wb_motor_set_velocity(wheel_1,-speed);
   wb_motor_set_velocity(wheel_2,-speed);
   wb_motor_set_velocity(wheel_3,-speed);
  }
 void gunMovement(WbDeviceTag gun) {

   wb_motor_set_velocity(gun,null);
 }
 void sensorMovement(WbDeviceTag gunsensor) {
   wb_motor_set_velocity(gunsensor,dsvel);
 }
 void stopGuns(WbDeviceTag gunsensor,WbDeviceTag gun) {
   wb_motor_set_velocity(gunsensor,null);
   wb_motor_set_velocity(gun,null);

 }


int main(int argc, char **argv){
  /* necessary to initialize webots stuff */
  wb_robot_init();
  wb_keyboard_enable(TIME_STEP);

   WbDeviceTag wheel_1 = wb_robot_get_device("motor_1");
   WbDeviceTag wheel_2 = wb_robot_get_device("motor_2");
   WbDeviceTag wheel_3 = wb_robot_get_device("motor_3");
   WbDeviceTag gunsensor = wb_robot_get_device("motor_4");
   WbDeviceTag gun = wb_robot_get_device("motor_5");

   WbDeviceTag ps_1 = wb_robot_get_device("position_1");
   WbDeviceTag ps_2 = wb_robot_get_device("position_2");
   WbDeviceTag ps_3 = wb_robot_get_device("position_3");
   WbDeviceTag ps_4 = wb_robot_get_device("position_4");
   WbDeviceTag ps_5 = wb_robot_get_device("position_5");

   wb_motor_set_position(wheel_1,INFINITY);
   wb_motor_set_position(wheel_2,INFINITY);
   wb_motor_set_position(wheel_3,INFINITY);
   wb_motor_set_position(gunsensor,INFINITY);
   wb_motor_set_position(gun,INFINITY);

   wb_position_sensor_enable(ps_1, TIME_STEP);
   wb_position_sensor_enable(ps_2, TIME_STEP);
   wb_position_sensor_enable(ps_3, TIME_STEP);
   wb_position_sensor_enable(ps_4, TIME_STEP);
   wb_position_sensor_enable(ps_5, TIME_STEP);

   WbDeviceTag ds_r1 = wb_robot_get_device("distance_sensor1");
   WbDeviceTag ds_r2 = wb_robot_get_device("distance_sensor2");
   WbDeviceTag ds_r3 = wb_robot_get_device("distance_sensor3");

   wb_distance_sensor_enable(ds_r1, TIME_STEP);
   wb_distance_sensor_enable(ds_r2, TIME_STEP);
   wb_distance_sensor_enable(ds_r3, TIME_STEP);

   d1=(wb_distance_sensor_get_value(ds_r1)*0.4)/255;
   d2=(wb_distance_sensor_get_value(ds_r2)*0.4)/255;
   d3=(wb_distance_sensor_get_value(ds_r3)*2)/1023;

   void shoot() {

     if (d3<= 2 && d3 >= 1.5 ) {
        printf("Enemy: THA!\n");
      }
      else if (d3<= 1.4 && d3 >= 1.2 ) {
        printf("Enemy: THATHA!\n");
      }
      else if (d3<= 1.1 && d3 >= 0.8 ) {
        printf("Enemy: THATHATHA!\n");
      }
      else if (d3<= 0.8 && d3 >= 0.5 ){
        printf("Enemy: THATHATHATHATHA!\n");
      }


   }
   void giroDerecha() {
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
   void giroIzquierda() {
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


   }

  void automatic(){
     WbDeviceTag ds_r1 = wb_robot_get_device("distance_sensor1");
     WbDeviceTag ds_r2 = wb_robot_get_device("distance_sensor2");
     WbDeviceTag ds_r3 = wb_robot_get_device("distance_sensor3");

     wb_distance_sensor_enable(ds_r1, TIME_STEP);
     wb_distance_sensor_enable(ds_r2, TIME_STEP);
     wb_distance_sensor_enable(ds_r3, TIME_STEP);

     d1=(wb_distance_sensor_get_value(ds_r1)*0.4)/255;
     d2=(wb_distance_sensor_get_value(ds_r2)*0.4)/255;
     d3=(wb_distance_sensor_get_value(ds_r3)*2)/1023;

     if (d3<2){
       a=wb_position_sensor_get_value(ps_4);
       times3++;
       shoot();
     }
     if (times3 >=1){
       stopRobot(wheel_1,wheel_2, wheel_3);
       stopGuns(gun,gunsensor);
       wb_motor_set_position(gun,a);
       wb_motor_set_velocity(gun,10);
       times3++;
     }

     else{
       times3=0;
     }
   }


  while (wb_robot_step(TIME_STEP) != -1) {

    goAuto( wheel_1, wheel_2, wheel_3);
    sensorMovement(gunsensor);
    gunMovement(gun);
    giroDerecha();
    giroIzquierda();
    automatic();

  };


  wb_robot_cleanup();

  return 0;
}
