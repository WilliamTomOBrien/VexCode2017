/*--------------------------------------------Start of XY Code Library--------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------
| This library is intended to help to "tell" the robot where it is on the field. Eventually, with this code,       |
| I would like to create a function that would allow the robot to move autonomously whilst bluetooth is inactive,  |
| and go find and pick up game objects in order to do so in said circumstance.                                     |
------------------------------------------------------------------------------------------------------------------*/
void sendGraph(int val1 = 0, int val2 = 0, int val3 = 0)
{
	bnsDebugStream("E%d,%d,%d\n");
}

void sendGraphFloat(float val1 = 0, float val2 = 0, float val3 = 0)
{
	bnsDebugStream("E%.5f,%.5f,%.5f\n");
}
//Functions to send data to the graph of the HC-05 Module App
//we use as a team

typedef struct _data{
	int data[2000];
	bool semaphore;
} data;
//Datatype to be used minimally (once)
//in order to collect data

data collect;


typedef struct {

	float x_pos;
	float y_pos;
	float lift_pos;
	float heading;
	int lift_pos;
	bool claw_pos;

	int lift_clear;
	int stars;
	int cubes;

}robot, *pRobot;

typedef struct {

	float x_pos;
	float y_pos;
	float rad_clearance;

	bool isThere;

}object, *pObject;

typedef enum {

	grab,
	block,
	dump,

}action;

object wall;
object backWall;
object leftWall;
object rightWall;
object backLeftStar;
object backRightStar;
object centerLeftStar;
object centerRightStar;
object centerStar;
object centerCube;
object reGrab;

robot C;
robot tempC;

void initObject(object* gameObject, float xpos, float ypos, float radclearance)
{
	gameObject -> x_pos = xpos;
	gameObject -> y_pos = ypos;
	gameObject -> rad_clearance = radclearance;
	gameObject -> isThere = true;
}

void initRobot(robot* gameRobot, float xpos, float ypos, float heading, int lift_pos, bool claw_pos, int liftClearance, int stars, int cubes)
{
	gameRobot -> x_pos = xpos;
	gameRobot -> y_pos = ypos;
	gameRobot -> heading = heading;
	gameRobot -> lift_pos = lift_pos;
	gameRobot -> claw_pos = claw_pos;
	gameRobot -> lift_clear = liftClearance;
	gameRobot -> stars = stars;
	gameRobot -> cubes = cubes;
}

void initAutonGrid ()
{
	initObject(&backLeftStar, 0.5, 0.5, 1);
	initObject(&backRightStar, 5.5, 0.5, 1);
	initObject(&centerLeftStar, 2.5, 0.5 ,1);
	initObject(&centerRightStar, 3.5, 0.5, 1);
	initObject(&centerStar, 3, 0.5, 1);
	initObject(&centerCube, 3, 1.5, 1.5);
	initObject(&centerCube, 3, 1.5, 2);

	initObject(&wall, -1, 6, 1);
	initObject(&backWall, -1, 0, 1);
	initObject(&rightWall, 6, -1, 1);
	initObject(&leftWall, 0, -1, 1)

	initRobot(&C, 0, 0, 0, 0, 0, 2100, 1, 0);
	initRobot(&tempC, 0, 0, 0, 0, 0, 2100, 1, 0);
}


void gyroStart(sGyro Gyro, tSensors port)
{
	//If the data collection array is "open," use it,
	//otherwise, just don't do it.
	collect.semaphore = false;

	Gyro.port = port;
	//Set the gyro sensor's port

	float ave = 0;
	float stdDev = 0;


	for(int i = 0; i < 2000; i++)
	{
		collect.data[i] = SensorValue[port];
		ave += (float)(SensorValue[port]);
		wait1Msec(1);
		//Add up 2000 data points for the gyro sensor
	}
	Gyro.gAve = ave/2000;
	//Find the average of the 2000 data points, and put
	//it in the struct
	for(int i = 0; i < 2000; i++)
	{
		stdDev += pow((collect.data[i] - Gyro.gAve), 2);
	}
	stdDev = (float)stdDev/2000;
	Gyro.stdDev = sqrt(stdDev);

	//Find Standard Deviation of Data, which is equal to
	//the square root of((summation of each (data point - the average)^2)
	//divided by the number of data points taken)

	float vMul = (5*(Gyro.gAve/4095))/(1.5);
	//Since the cortex applies a multiplier to the gyro
	//values, we can calculate this, and apply it to the
	//gyro's datasheet listed conversion rate of 1.1mV/dps
	//Since the datasheet says the gyro should emit 1.5 V
	//at 0 movement, we can divide the number of volts
	//actually emitted by 1.5 in order to find the voltage
	//multiplier
	Gyro.VtoDPS = (.0011)*vMul;
	collect.semaphore = true;

	Gyro.lastTime = nPgmTime;
	Gyro.lastDif = (SensorValue[gyro.port] - gyro.gAve);
	//Set other relevant struct information
}



void gyroUpdate (int stdDev, sGyro gyro)
{
	int val = SensorValue[gyro.port];
	//Take Gyro Value
	float gyroDif = val - gyro.gAve;
	//Find Difference in Gyro Value from Gyro at 0 Movement
	int deltaTime = nPgmTime - gyro.lastTime;
	//Find last time integrated

	if(deltaTime > 500)
	{
		deltaTime = 0;
		gyro.angle = 0;
		//Reset if we haven't checked in a while
	}

	//Don't integrate if it seems that the difference is smaller than
	//stdDev deviations from the 0 movement average
	if(fabs(gyroDif) > gyro.stdDev*stdDev)
	{
		gyro.angle += (((float)deltaTime/1000)*((float)5/4095)*((gyroDif + gyro.lastDif)/2))/gyro.VtoDps;
		//Integrate angle value through trapezoid rule by converting the analog values
		//values to Voltages, then dividing by the volts to dps conversion rate

		gyro.rate = ((float)5/4095)*((gyroDif + gyro.lastDif)/2)/gyro.VtoDps;
		//FInd the average rate, between this data point and the last, by using
		//5/4095 to convert to voltages, then dividing by the volts to dps conversion
	}
	else gyro.rate = 0; //If we don't integrate, as there is 0 movement, the angular rate is 0

	gyro.lastTime = nPgmTime;
	gyro.lastDif = gyroDif;
	//Set relevant struct info for next integration
}

typedef struct _PID{

	float kP;
	float kI;
	float kD;

	float error;
	float error_min;
	float error_max;

	float timeLast;
	float previous_error;
	float integral;

	float speed;
	float maxSpeed;
	float accel;

}PID, *pPID;

//Struct to work to build a PID System

void pidInit(pPID pid, float kP, float kI, float kD, float max_error, float min_error, float increment = .5)
{
	//Function to initialize PID Struct
	pid -> kP = kP;
	pid -> kI = kI;
	pid -> kD = kD;
	pid -> error_max = max_error;
	pid -> error_min = min_error;

	pid -> timeLast = nPgmTime;
	pid -> previous_error = 0;
	pid -> integral = 0;
	pid -> maxSpeed = 0;
	pid -> accel = increment;
}


void pidOut (pPID pid, int targetVal, int actualVal)
{
	int error = (targetVal) - (actualVal);
	pid -> error = error;
	float deltaTime = nPgmTime - (pid -> timeLast);
	//Calculate relevant starting variables

	pid -> integral = (pid -> integral) + error*deltaTime;
	if (fabs(error) < (pid -> error_min))
	{
		pid -> integral = 0;
	}
	if (fabs(error) > pid -> error_max)
	{
		(pid -> integral) = (pid -> error_max)*sgn(error);
	}
	//Calculate Integral

	float derivative = 0;
	if(deltaTime > 0)//Make sure we do not get the divide by zero error
	{
		derivative = ((actualVal - (pid -> previous_error))/deltaTime);
	}
	//Calculate Derivitive

	pid -> speed = (pid -> kP)*error + (pid -> kI)*(pid -> integral) - (pid -> kD)*derivative;
	//Calculate actual speed

	if((pid -> speed) > 127) pid -> speed = 127;
	if((pid -> speed) < -127) pid -> speed = -127;
	//MaxMin the speeds to make sure they stay within
	//wanted values

	pid -> timeLast = nPgmTime;
	pid -> previous_error = actualVal;
	//Reset relevant variables

	pid -> maxSpeed += (pid -> accel)
	if(abs(pid -> speed) > abs(pid -> maxSpeed)) pid -> speed = sgn(error)*(pid -> maxSpeed);

}

void pidOutNc (pPID pid, float targetVal, float actualVal)
{
	float error = (targetVal) - (actualVal);
	float deltaTime = nPgmTime - (pid -> timeLast);
	//Calculate relevant starting variables

	pid -> integral = (pid -> integral) + error*deltaTime;

	if (fabs(error) > pid -> error_max)
	{
		(pid -> integral) = (pid -> error_max)*sgn(error);
	}
	//Calculate Integral

	float derivative = 0;
	if(deltaTime > 0)//Make sure we don't get a divide by zero error
	{
		derivative = ((actualVal - (pid -> previous_error))/deltaTime);
		//calculate derivitive
	}

	pid -> speed = (pid -> kP)*error + (pid -> kI)*(pid -> integral) - (pid -> kD)*derivative;
	//calculate teh actual PID Speed

	if((pid -> speed) > 127) pid -> speed = 127;
	if((pid -> speed) < -127) pid -> speed = -127;
	//MaxMin the speeds to make sure they stay within
	//wanted values

	pid -> timeLast = nPgmTime;
	pid -> previous_error = actualVal;
	//Reset relevant variables

	pid -> maxSpeed += (pid -> accel)
	if(abs(pid -> speed) > abs(pid -> maxSpeed)) pid -> speed = sgn(error)*(pid -> maxSpeed);

}

bool open = true;
bool close = false;

void Turn (float angle, int lift, bool clawState, int maxTime, int clawRelease = 3600, int dOverride = 0, int lOverride = 0,int liftStart = -1, int clawStart = -1, bool driveBreak = false)
{
	PID turn;
	PID pidLift;

	int leftSpeed = 0;
	int rightSpeed = 0;
	int liftSpeed = 0;
	bool claw = clawState;

	int maxTimeVal = maxTime;

	pidInit(&turn, 1.8, 0.005,.2, 45, .3, 0.75);
	pidInit(&pidLift, .1, 0.0001, 0, 1000, 5, 127);

	clearSensors();

	bool run = true;

	while(run)
	{

		pidOut(&turn, angle, gGyro.angle);
		pidOutNc(&pidLift, lift, SensorValue[launchPot]);

		if(dOverride)
		{
			if(!driveBreak)
			{
				if(abs(gGyro.angle) > abs(angle))
				{
					run = false;
					dOverride = false;
				}
			}
			else if(driveBreak && (abs(gGyro.angle - angle)) < 15)
			{
				dOverride = false;
				maxTimeVal = 250 + time1[T1];
			}
			leftSpeed = dOverride;
			rightSpeed = dOverride;
		}

		else if(!dOverride)
		{
			if(time1[T1] > maxTimeVal) run = false;
			leftSpeed = turn.speed;
			rightSpeed = turn.speed;
		}


		if(clawRelease < lift && SensorValue[launchPot] > clawRelease)
		{
			claw = open;
		}

		leftSpeed = (-leftSpeed);
		rightSpeed = (rightSpeed);

		if(liftStart > abs(gGyro.angle))
		{
			if(lOverride)
			{
				liftSpeed = lOverride;
				if(abs(lift - SensorValue[launchPot]) < 20) lOverride = false;
			}

			else if(!lOverride) liftSpeed = pidLift.speed
		}

		if(abs(gGyro.angle) > abs(clawStart))
		{
			SensorValue[solenoid1] = claw;
			SensorValue[solenoid2] = claw;
		}

		liftDrive(liftSpeed);
		chassisDrive(leftSpeed, rightSpeed);

		if(time1[T1] > maxTimeVal) run = false;

	}
}





void Drive (float tiles, int lift, bool clawState, int maxTime, int clawRelease = 3600, int dOverride = 0, int lOverride = 0,int liftStart = -1, int clawStart = -1, bool driveBreak = false)
{
	PID pidLeft;
	PID pidRight;
	PID pidLift;

	int leftSpeed = 0;
	int rightSpeed = 0;
	int liftSpeed = 0;
	bool claw = clawState;

	int maxTimeVal = maxTime;

	float encToInch = 28.6;

	float drive = tiles*encToInch*24;

	pidInit(&pidLeft,.6,.00032,.2,45,2,0.75);
	pidInit(&pidRight,.6,.00032,.2,45,2,0.75);
	pidInit(&pidLift,.1,0.0001,0,1000,5,127);

	clearSensors();

	bool run = true;

	while(run)
	{

		pidOut(&pidLeft, drive, SensorValue[leftEncoder]);
		pidOut(&pidRight, drive, SensorValue[rightEncoder]);
		pidOutNc(&pidLift, lift, SensorValue[launchPot]);

		if(dOverride)
		{
			if(!driveBreak)
			{
				if(abs(SensorValue[leftEncoder]) > abs(drive))
				{
					run = false;
					dOverride = false;
				}
			}
			else if(driveBreak && (abs(SensorValue[leftEncoder] - drive) < 50))
			{
				dOverride = false;
				maxTimeVal = 250 + time1[T1];
			}
			leftSpeed = dOverride;
			rightSpeed = dOverride;
		}

		else if(!dOverride)
		{
			if(time1[T1] > maxTimeVal) run = false;
			leftSpeed = pidLeft.speed;
			rightSpeed = pidRight.speed;
		}

		if(liftStart > abs(SensorValue[leftEncoder]))
		{
			if(lOverride)
			{
				liftSpeed = lOverride;
				if(abs(lift - SensorValue[launchPot]) < 20) lOverride = false;
			}

			else if(!lOverride) liftSpeed = pidLift.speed;
		}


		if(clawRelease < lift && SensorValue[launchPot] > clawRelease)
		{
			claw = open;
		}

		if(abs(SensorValue[leftEncoder]) > abs(clawStart))
		{
			SensorValue[solenoid1] = claw;
			SensorValue[solenoid2] = claw;
		}

		liftDrive(liftSpeed);
		chassisDrive(leftSpeed, rightSpeed);

		if(time1[T1] > maxTimeVal) run = false;

	}
}


void sTurn (float left, float right, int lift, bool clawState, int maxTime, int clawRelease = 3600, int dOverride = 0, int lOverride = 0,int liftStart = -1, int clawStart = -1, bool driveBreak = false)
{
	PID pidLeft;
	PID pidRight;
	PID pidLift;

	int leftSpeed = 0;
	int rightSpeed = 0;
	int liftSpeed = 0;
	bool claw = clawState;

	int maxTimeVal = maxTime;

	float degreeToEnc = 8.4858;


	pidInit(&pidLeft,.6,.00032,.2,45,2,0.75);
	pidInit(&pidRight,.6,.00032,.2,45,2,0.75);
	pidInit(&pidLift,.1,0.0001,0,1000,5,127);

	clearSensors();

	bool run = true;

	while(run)
	{

		pidOut(&pidLeft, left*degreeToEnc, SensorValue[leftEncoder]);
		pidOut(&pidRight, right*degreeToEnc, SensorValue[rightEncoder]);
		pidOutNc(&pidLift, lift, SensorValue[launchPot]);

		if(dOverride)
		{
			if(!left)
			{
				if(abs(SensorValue[leftEncoder]) > abs(left*degreeToEnc))
				{
					dOverride = false;
					run = false;
				}

			}
			if(!right)
			{
				if(abs(SensorValue[rightEncoder]) > abs(right*degreeToEnc))
				{
					dOverride = false;
					run = false;
				}
			}
		}

		else if(!dOverride)
		{
			leftSpeed = pidLeft.speed;
			rightSpeed = pidRight.speed;
		}

		if(liftStart > abs(SensorValue[leftEncoder]))
		{
			if(lOverride)
			{
				liftSpeed = lOverride;
				if(abs(lift - SensorValue[launchPot]) < 20) lOverride = false;
			}

			else if(!lOverride) liftSpeed = pidLift.speed;
		}


		if(clawRelease < lift && SensorValue[launchPot] > clawRelease)
		{
			claw = open;
		}

		if(abs(SensorValue[leftEncoder]) > abs(clawStart))
		{
			SensorValue[solenoid1] = claw;
			SensorValue[solenoid2] = claw;
		}

		liftDrive(liftSpeed);
		chassisDrive(leftSpeed, rightSpeed);

		if(time1[T1] > maxTimeVal) run = false;

	}
}

//#include "CustomAutoProtocol.c"
/*---------------------------------------------End of XY Code Library---------------------------------------------*/
