#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <stdint.h>
#include <softPwm.h>

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
	int pwm_return_LF=softPwmCreate(LEFT_MOTOR_FWD,0,100);
	int pwm_return_LR=softPwmCreate(LEFT_MOTOR_RVRS,0,100);
	int pwm_return_RF=softPwmCreate(RIGHT_MOTOR_FWD,0,100);
	int pwm_return_RR=softPwmCreate(RIGHT_MOTOR_RVRS,0,100);
	unsigned int pwm_value=0;
	while(1)
	{
			delay(200);
			softPwmWrite(LEFT_MOTOR_FWD, pwm_value);
			pwm_value+=1;
			printf("PWM_VALUE= %d \n",pwm_value);
			if(pwm_value>100)
			{
				pwm_value =0;
				softPwmWrite(LEFT_MOTOR_FWD, pwm_value);
				delay(1000);
				}
	}
		return 0;
}


//gcc -o test imu_test_code_for_c.c -L/usr/local/lib -lwiringPi
//sudo ./test

