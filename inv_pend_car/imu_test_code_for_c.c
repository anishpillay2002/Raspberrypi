#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <unistd.h>
#include <stdint.h>

#define addr 0x68

int main(int argc,char*argv[])
{
	int fd;
	int16_t AcX,AcY,AcZ;
	int16_t AccxL, AccyL, AcczL;
	int16_t AccxH, AccyH, AcczH;
	wiringPiSetup();
	fd=wiringPiI2CSetup(addr);
	if(fd==-1)
	{
		printf("Can't setup the I2C device\n");
		return -1;
	}
	else
	{
		wiringPiI2CWriteReg8(fd, 0x6B, 0);
		
		for(;;)
		{
			AccxH=wiringPiI2CReadReg8(fd,0x3B);
			AccxL=wiringPiI2CReadReg8(fd,0x3C);
			AccyH=wiringPiI2CReadReg8(fd,0x3D);
			AccyL=wiringPiI2CReadReg8(fd,0x3E);
			AcczH=wiringPiI2CReadReg8(fd,0x3F);
			AcczL=wiringPiI2CReadReg8(fd,0x40);
			AcX=AccxH<<8|AccxL;
			AcY=AccyH<<8|AccyL;
			AcZ=AcczH<<8|AcczL;
			printf("Acc X=%d\tAcc Y=%d\tAcc Z=%d\n",AcX, AcY,AcZ);
			//printf("Acc X=%d\tAcc Y=%d\tAcc Z=%d\n",(int16_t)AccxH<<8|AccxL, (int16_t)AccyH<<8|AccyL, (int16_t)AcczH<<8|AcczL);
			//printf("Acc X=%d & %d\tAcc Y=%d & %d\tAcc Z=%d & %d\n",AccxH,AccxL,AccyH,AccyL,AcczH,AcczL);

			usleep(10000);
		}
	}
	return 0;
}
