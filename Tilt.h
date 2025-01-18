//get library from https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/I2Cdev and
//get library from https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050 and
//read https://github.com/jrowberg/i2cdevlib/issues/688
#include "MPU6050_6Axis_MotionApps612.h"

TwoWire I2Cone=TwoWire(0);
MPU6050 mpu(0x68,&I2Cone);

struct tiltStruct { float x; float y; float z; float d; float xy; } tilt;
uint8_t fifoBuffer[64]; Quaternion quat; VectorFloat gravity; float ypr[3];

void calibrateTilt() { mpu.CalibrateAccel(6); mpu.CalibrateGyro(6); mpu.PrintActiveOffsets(); }

void tiltWorker() {
  static uint64_t tiltTimer=millis()+100;
  if (millis()>=tiltTimer) { tiltTimer=millis()+100;
    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
      mpu.dmpGetQuaternion(&quat,fifoBuffer);
      mpu.dmpGetGravity(&gravity,&quat);
      mpu.dmpGetYawPitchRoll(ypr,&quat,&gravity);
      if (ypr[2]<-M_PI/2 || ypr[2]>M_PI/2) { if (ypr[1]<0) { ypr[1]=-M_PI-ypr[1]; } else { ypr[1]=M_PI-ypr[1]; } }
      if (ypr[1]<-M_PI/2 || ypr[1]>M_PI/2) { if (ypr[2]<0) { ypr[2]=-M_PI-ypr[2]; } else { ypr[2]=M_PI-ypr[2]; } }
      tilt.z=ypr[0]*180/M_PI; tilt.y=ypr[1]*180/M_PI; tilt.x=ypr[2]*180/M_PI;
      tilt.d=(atan2(ypr[1],ypr[2])*180/M_PI)+180;
      tilt.xy=sqrt(ypr[1]*ypr[1]+ypr[2]*ypr[2])*180/M_PI; } } }

void initTilt() {
  I2Cone.begin(21,22,400000);
  mpu.initialize();
  mpu.dmpInitialize();
  calibrateTilt(); calibrateTilt();
  mpu.setDMPEnabled(true); }
