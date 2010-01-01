#include <core.h>
#include <stdio.h>
#include <pthread.h>
#define PWM_PERIOD 20000
#include <ControlServer.h>

//pin numbers
int E1 = 10;  
int M1 = 12;
int E2 =11;                        
int M2 = 13;
int ServoPin = 9;                         
//int SpeakerPin = 4;
//status values
int speed = 0;
int angle = 90;
boolean forward = true;
struct CarVector* carVectorPointer = new CarVector;
//set plus of servo
void servoSetPulse(int pin,int pulse)
{
	digitalWrite(pin,HIGH);
	delayMicroseconds(pulse);
	digitalWrite(pin,LOW);
	delayMicroseconds(PWM_PERIOD - pulse);
}

//set angle of servo
void servoSetAngle(int pin,int angle)
{
	if(angle >= 0 && angle <= 180)
	{
		servoSetPulse(pin,angle * 7 + 960);
	}
}

void setSpeed(int mSpeed){
	if(mSpeed < 256 && mSpeed >= 0 && speed!=mSpeed){
		speed = mSpeed;
		analogWrite(E1, speed);   //PWM调速
	}
		

}

void setForward(boolean mForward){
	if(mForward!=forward){
		forward = mForward;
		if(forward)
			digitalWrite(M1,LOW);
		else
			digitalWrite(M1,HIGH);
	}	

}

void setAngle(int mAngle){
	angle = mAngle;
}


//init pin mode and status
void initPins(){
	//pinMode(SpeakerPin,OUTPUT);
	pinMode(ServoPin, OUTPUT); ;//舵机接9脚
	pinMode(E1, OUTPUT);  
	pinMode(E2, OUTPUT);
	pinMode(M1, OUTPUT);  
	pinMode(M2, OUTPUT);
	analogWrite(E1, 0);   //PWM调速
	analogWrite(E2, 0);   //PWM调速
	
}
//listen cmd
void *listenCmd(void*){
    carVectorPointer->speed = 0;
    carVectorPointer->angle = 90;
    carVectorPointer->direction = 1;
    ControlServer server(carVectorPointer);
    printf("Listen Cmd Service started!\n");
    server.start();	

	
}

//start Listen Cmd Service
void startListenCmdService(){
	pthread_t id;
	int i,ret;
	ret=pthread_create(&id,NULL,listenCmd,NULL);
	if(ret!=0) {
	printf ("Create pthread error!\n");
	exit (1);
	}
	//pthread_join(id,NULL);
	

}

void setup()
{
	initPins();
	startListenCmdService();
}
 
void loop()

 {
		// for(int i =0;i<10;i++)	
   	//servoSetAngle(ServoPin,carVectorPointer->angle);
	setSpeed(carVectorPointer->speed);
	setForward(carVectorPointer->direction==1);
 for(int i =0;i<20;i++)
	  servoSetAngle(ServoPin,carVectorPointer->angle);
 delay(100);
	//printf("%d\n",angle);
//	delay(50);
	//prinf(angle);

 }
