#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <stdint.h>

#define LEFT_MOTOR_FWD 6
#define LEFT_MOTOR_RVRS 13
#define RIGHT_MOTOR_FWD 19
#define RIGHT_MOTOR_RVRS 26



int main(int argc,char*argv[])
{
	wiringPiSetupGpio();
	pinMode(LEFT_MOTOR_FWD, OUTPUT);
	pinMode(LEFT_MOTOR_RVRS, OUTPUT);
	pinMode(RIGHT_MOTOR_FWD, OUTPUT);
	pinMode(RIGHT_MOTOR_RVRS, OUTPUT);
	digitalWrite(LEFT_MOTOR_FWD, LOW);
	digitalWrite(LEFT_MOTOR_RVRS, LOW);
	digitalWrite(RIGHT_MOTOR_FWD, LOW);
	digitalWrite(RIGHT_MOTOR_RVRS, LOW);

	
	while(1)
	{
			delay(2000);
			digitalWrite(LEFT_MOTOR_FWD, LOW);	
			delay(2000);
			digitalWrite(LEFT_MOTOR_FWD, HIGH);
			delay(2000);
			digitalWrite(LEFT_MOTOR_RVRS, LOW);	
			delay(2000);
			digitalWrite(LEFT_MOTOR_RVRS, HIGH);		
			delay(2000);
			digitalWrite(RIGHT_MOTOR_FWD, LOW);
			delay(2000);
			digitalWrite(RIGHT_MOTOR_FWD, HIGH);
			delay(2000);
			digitalWrite(RIGHT_MOTOR_RVRS, LOW);
			delay(2000);
			digitalWrite(RIGHT_MOTOR_RVRS, HIGH);
	}
		return 0;
}


//gcc -o test imu_test_code_for_c.c -L/usr/local/lib -lwiringPi

