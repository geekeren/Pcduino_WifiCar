#include <core.h>
#include <stdio.h>
#include <pthread.h>
#include <key.c>
#define PWM_PERIOD 20000

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
		servoSetPulse(pin,angle * 7 + 920);
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
	while(1){
		int i = scanKeyboard();
		switch(i){
			case 'e':
				printf("e to Stop\n");setSpeed(0);break;
			case 'w':
				printf("Forward\n");setForward(true);setAngle(90);setSpeed(100);break;
			case 's':
				printf("Slow or backward\n");setForward(false);setSpeed(100);break;
			case 'a':
				printf("Left\n");setAngle(angle+10);break;
			case 'd':
				printf("Right\n");setAngle(angle-10);break;
		}
		
		
	}
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
	printf("Listen Cmd Service started!\n");

}

void setup()
{
	initPins();
	startListenCmdService();
}
 
void loop()

 {  	
    servoSetAngle(ServoPin,angle);
	//printf("%d\n",angle);
	delay(50);
	//prinf(angle);

 }
