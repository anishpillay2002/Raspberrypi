#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>
#define addr 0x68

static PyObject *

long long current_timestamp()		// Defining a function to calculate current time in milliseconds
{
	struct timeval te;
	gettimeofday(&te, NULL);
	long long milliseconds=te.tv_sec*1000LL+te.tv_usec/1000;
	return milliseconds;
}
int main(int argc,char*argv[])
{
	int fd;
	int16_t AcX,AcY,AcZ;
	int16_t AccxL, AccyL, AcczL;
	int16_t AccxH, AccyH, AcczH;
	
	int16_t GyX,GyY,GyZ;
	int16_t GyrxL, GyryL, GyrzL;
	int16_t GyrxH, GyryH, GyrzH;
	
	wiringPiSetup();
	fd=wiringPiI2CSetup(addr);
	if(fd==-1)
	{
		printf("Can't setup the I2C device\n");
		return -1;
	}
	else
	{
		//struct tm * timeinfo;
		//time_t now;
		//timeinfo=localtime(&now);
		long long start_time=current_timestamp();
		printf("milliseconds: %lld \n",start_time);
		long long step_time;
		float time_diff;
		//printf("Start Time=  %s",asctime(timeinfo));
		int i=0;
		int j=0;
		float info_arr[10000][7];
		
		wiringPiI2CWriteReg8(fd, 0x6B, 0);
		while((float)((step_time-start_time)/1000)<20)
		{
			AccxH=wiringPiI2CReadReg8(fd,0x3B);		// Reading all registers for accelerometer Refer MPU6050 document for map and description	
			AccxL=wiringPiI2CReadReg8(fd,0x3C);
			AccyH=wiringPiI2CReadReg8(fd,0x3D);
			AccyL=wiringPiI2CReadReg8(fd,0x3E);
			AcczH=wiringPiI2CReadReg8(fd,0x3F);
			AcczL=wiringPiI2CReadReg8(fd,0x40);
			AcX=AccxH<<8|AccxL;						// Combing the high and low bit
			AcY=AccyH<<8|AccyL;		
			AcZ=AcczH<<8|AcczL;
			printf("Acc X=%d\tAcc Y=%d\tAcc Z=%d\n",AcX, AcY,AcZ);		// Displaying Accelerometer Values
			//printf("Acc X=%d\tAcc Y=%d\tAcc Z=%d\n",(int16_t)AccxH<<8|AccxL, (int16_t)AccyH<<8|AccyL, (int16_t)AcczH<<8|AcczL);
			//printf("Acc X=%d & %d\tAcc Y=%d & %d\tAcc Z=%d & %d\n",AccxH,AccxL,AccyH,AccyL,AcczH,AcczL);
			GyrxH=wiringPiI2CReadReg8(fd,0x43);		//Reading all registers for gyroscope Refer MP6050 document for map and description
			GyrxL=wiringPiI2CReadReg8(fd,0x44);
			GyryH=wiringPiI2CReadReg8(fd,0x45);
			GyryL=wiringPiI2CReadReg8(fd,0x46);
			GyrzH=wiringPiI2CReadReg8(fd,0x47);
			GyrzL=wiringPiI2CReadReg8(fd,0x48);
			GyX=GyrxH<<8|GyrxL;						// Combining the high and low bit
			GyY=GyryH<<8|GyryL;
			GyZ=GyrzH<<8|GyrzL;						
			printf("Gyr X=%d\tGyr Y=%d\tGyr Z=%d\n",GyX, GyY,GyZ);		// Displaying Gyroscope values
			//time_t now;
			//timeinfo=localtime(&now);
			//printf("Start Time=  %s",asctime(timeinfo));
			step_time=current_timestamp();		// Running current_timestamp() function to get current time in milliseconds
			time_diff=((float)(step_time-start_time)/1000);	// Taking difference in time at every step
			printf("milliseconds: %f \n",time_diff);
			info_arr[i][j]=time_diff;		// Storing Acceleration and Dyro values in a matrix with first column as time
			info_arr[i][j+1]=(float)AcX;	// Next 3 columns as Acc values and Next 3 as Gyro Values
			info_arr[i][j+2]=(float)AcY;
			info_arr[i][j+3]=(float)AcZ;
			info_arr[i][j+4]=(float)GyX;
			info_arr[i][j+5]=(float)GyY;
			info_arr[i][j+6]=(float)GyZ;
			printf("information %f\n",info_arr[0][1]);
			i++;
			printf("%d",i);
			usleep(100000);
		}
		FILE * gnuplotPipe =popem("gnuplot -persistent","w");
		for (k=0;k<i;k++)
		{
			fprintf(gnuplotPipe,"%lf %lf\n",info_arr[i][0],info_arr[i][1]);
		}
		fprintf(gnuplotPipe,"e");
	
	
	}
	return 0;
}
