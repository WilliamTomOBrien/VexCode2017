/*-------------------------------------Start of General Robot Library-----------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------
| Most of my function library is within this library, as this controls the general movement of the robot,     |
| including the functions for the drive code, from simple functions only activating the motors,               |
| to the more advanced functions like eD, which can activate multiple drives at once, and stop them all       |
| at seperate times, by the use of several different sensors.Without this Library, 1200C's robot could not    |
| function.                                                                                                   |
-------------------------------------------------------------------------------------------------------------*/

//Creates a boolean value for getting out of a while loop in the playback function

bool shouldWeKeepGoingPE(int currentValue, int endValue)
{
	// Function to determine whether to keep going or not.
	// Assumption is endValue is always positive so convert currentValue to positive too
	// If it is negative, only switch endValue and currentValue
	bool shouldGo = true;
	if (currentValue >= endValue)
	{
		shouldGo = false;
	}
	return shouldGo;
}

bool shouldWeKeepGoingSen(AutonSensor SensorInfo, int FinalSensorValue)
{

	bool shouldWeKeepGoing;


	//SENSOR FLAG
	if(SensorInfo == leftEncUp)
	{
		shouldWeKeepGoing = shouldWeKeepGoingPE(SensorValue[leftEncoder],FinalSensorValue);
		//When SensorVal LeftEnc is greater than final SensorVal, Exit While Loop
	}
	if(SensorInfo == leftEncDown)
	{
		shouldWeKeepGoing = shouldWeKeepGoingPE(FinalSensorValue,SensorValue[leftEncoder]);
		//When SensorVal LeftEnc is lesser than final SensorVal, Exit While Loop
	}
	else if(SensorInfo == time)
	{
		shouldWeKeepGoing = shouldWeKeepGoingPE(time1[T1],FinalSensorValue);
		//When timer is greater than final SensorVal, Exit While Loop
	}
	else if(SensorInfo == rightEncUp)
	{
		shouldWeKeepGoing = shouldWeKeepGoingPE(SensorValue[rightEncoder], FinalSensorValue);
		//When SensorVal RightEnc is greater than final SensorVal, Exit While Loop
	}
	else if(SensorInfo == rightEncDown)
	{
		shouldWeKeepGoing = shouldWeKeepGoingPE(FinalSensorValue, SensorValue[rightEncoder]);
		//When SensorVal RightEnc is lesser than final SensorVal, Exit While Loop
	}

	else if(SensorInfo == gyroUp)
	{
		shouldWeKeepGoing = shouldWeKeepGoingPE(gGyro.angle, FinalSensorValue);
		//When SensorVal gyroXY is greater than final SensorVal, Exit While Loop
	}
	else if(SensorInfo == gyroDown)
	{
		shouldWeKeepGoing = shouldWeKeepGoingPE(FinalSensorValue, gGyro.angle);
		//When SensorVal gyroXY is lesser than final SensorVal, Exit While Loop
	}
	else if(SensorInfo == liftPotUp)
	{
		shouldWeKeepGoing = shouldWeKeepGoingPE(SensorValue[launchPot], FinalSensorValue);
		//When SensorVal gyroXY is greater than final SensorVal, Exit While Loop
	}
	else if(SensorInfo == liftPotDown)
	{
		shouldWeKeepGoing = shouldWeKeepGoingPE(FinalSensorValue, SensorValue[launchPot]);
		//When SensorVal gyroXY is lesser than final SensorVal, Exit While Loop
	}
	//TO DO --- INTEGRATE SONARS INTO THIS FUNCTION
	//else if(SensorInfo == sonarInc)
	//{
	//	if(SensorValue[Ultra] != -1)
	//	{
	//		if(SensorValue[Ultra] < FinalSensorValue)shouldWeKeepGoing = true;
	//		else shouldWeKeepGoing = false;
	//	}
	//}
	//else if(SensorInfo == sonarDec)
	//{
	//	if(SensorValue[Ultra] != -1)
	//	{
	//		if(SensorValue[Ultra] > FinalSensorValue)shouldWeKeepGoing = true;
	//		else shouldWeKeepGoing = false;
	//	}
	//}

	return(shouldWeKeepGoing);
}

//Previously used, and possibly in the future,
//to state where the lift was, as it looked
//cleaner as an enumeration


void chassisDrive (int leftSpeed, int rightSpeed)
{
	//Set Drive Motors


	motor[driveleftB] = leftSpeed;
	motor[driverightM] = rightSpeed;

	motor[driverightB] = rightSpeed;
	motor[driveleftM] = leftSpeed;

}

void liftDrive(int speed)
{
	//Set Lift Motors
	motor[liftBotLeft] = speed;
	motor[liftBotRight] = speed;
	motor[liftTopLeft] = speed;
	motor[liftMidRight] = speed;
	motor[liftMidLeft] = speed;
	motor[liftTopRight] = speed;

}


void SetMotors(int motorSpeed1, int motorSpeed2, int motorSpeed3, int motorSpeed4, int motorSpeed5, int motorSpeed6)
{
	//Sets Motors For LCD Menu Functions
	//Based on 6 Arbitrary Drives...
	//We won't have more than 6, right?

	motor[port1] = motorSpeed2;
	motor[port2] = motorSpeed2;
	motor[port3] = motorSpeed3;
	motor[port4] = motorSpeed3;
	motor[port5] = motorSpeed4;
	motor[port6] = motorSpeed4;
	motor[port7] = motorSpeed3;
	motor[port8] = motorSpeed3;
	motor[port9] = motorSpeed1;
	motor[port10] = motorSpeed1;
}

//Clears Pertinent Sensors

void clearSensors()
{
	//Clear Arbitrary Encoders and Timers
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;
	gGyro.angle = 0;
	//	SensorValue[clawEncoder] = 0;

	clearTimer(T1);
	clearTimer(T2);
}




int MaxMinClip (int Max, int Min, int Value)
{
	//Clips a value between a max and
	//a min, and forces them to not
	//go beyond them

	if (Value > Max)
	{
		Value = Max;
	}
	if (Value < Min)
	{
		Value = Min;
	}
	return Value;
}

int MaxMinRpt (int Max, int Min, int Value)
{
	//Works like the function above,
	//however, instead of clipping it,
	//when it goes above the max, it goes
	//to the min

	if (Value > Max)
	{
		Value = Value - (Max);
	}
	if (Value < Min)
	{
		Value = Value + (Max);
	}
	return Value;
}

void trueSpeedFind(int startSpeed, int endSpeed)
{
	//This is a test that finds the average
	//RPM for each motor speed
	if(DebugStream)
	{
		writeDebugStream("TrueSpeed Test:");
		writeDebugStreamLine("%d to %d", startSpeed, endSpeed);
		writeDebugStreamLine(BlankLine);
		//States in the Debugger Stream the Test
		//Is Starting
	}
	for(int i = startSpeed; i < endSpeed; i++)
	{
		//Finds the Average RPM for all speeds from startSpeed
		//To End Speed
		chassisDrive((pow(-1,startSpeed%2))*startSpeed,(pow(-1,startSpeed%2))*startSpeed);
		//(pow(-1,startSpeed%2) changes the direction of the motor
		//after every speed so we do not have to reset the robot
		//after every test, since -1 to the 1 power is -1, but -1
		// to the 0 power is 1
		wait10Msec(200); //Allow the Motors To Accelerate
		clearSensors(); //Clear Sensors for Data Collection
		wait10Msec(300); //Wait 3 Seconds for Data Collection to find Ave RPM
		float leftEncSpeed = SensorValue[leftEncoder]/3;
		float rightEncSpeed = SensorValue[rightEncoder]/3;
		float AveEncSpeed = (rightEncSpeed + leftEncSpeed)/2;
		//Find Average RPM For this Speed

		if(DebugStream)
		{
			writeDebugStreamLine("%d, %1.4f", startSpeed, AveEncSpeed);
		}
		if(BNSBluetooth)
		{
			bnsDebugStreamLine("%d, %1.4f", startSpeed, AveEncSpeed);
		}
		//Output the Data into the Debugger of Choice!
	}
}

//Global Variables for the Self-Writing
//Autonomous's Buttons, so that it "remembers"
//that they were pushed, are used in the quasi
//bitmap code

bool B6U;
bool B6D;
bool B5U;
bool B5D;
bool B7U;
bool B7D;
bool B7R;
bool B7L;
bool B8U;
bool B8D;
bool B8R;
bool B8L;


void DecodeButtons(int Buttons)
{
	//if(Buttons&1 == 1)B7U = true;
	//else B7U = false;
	//if(Buttons&2 == 2)B7D = true;
	//else B7D = false;
	//if(Buttons&4 == 4)B7L = true;
	//B7L = false;
	//if(Buttons&8 == 8)B7R = true;
	//B7R = false;
	//if(Buttons&16 == 16)B8U = true;
	//else B8U = false;
	//if(Buttons&32 == 32)B8D = true;
	//B8D = false;
	//if(Buttons&64 == 64)B8L = true;
	//else B8L = false;
	//if(Buttons&128 == 128)B8R = true;
	//else B8R = false;
	//if(Buttons&256 == 256)B5U = true;
	//else B5U = false;
	//if(Buttons&512 == 512)B5D = true;
	//else B5D = false;
	//if(Buttons&1024 == 1024)B6U = true;
	//else B6U = false;
	//if(Buttons&2048 == 2048)B6D = true;
	//else B6D = false;

	// Decodes one value into a series of toggles
	// For the buttons on the controller, using
	// principles in Bitmaps. Each Button is assigned
	// a power of 2, and if the value inputted is greater
	// or equal to that power of two, the toggle is
	// turned on, otherwise, it is toggled false

	if(Buttons >= 2048)
	{
		Buttons =- 2048;
		B6D = true;
	}
	else B6D = false;

	if(Buttons >= 1024)
	{
		Buttons =- 1024;
		B6U = true;
	}
	else B6U = false;

	if(Buttons >= 512)
	{
		Buttons =- 512;
		B5D = true;
	}
	else B5D = false;

	if(Buttons >= 256)
	{
		Buttons =- 256;
		B5U = true;
	}
	else B5U = false;

	if(Buttons >= 128)
	{
		Buttons =- 128;
		B8R = true;
	}
	else B8R = false;

	if(Buttons >= 64)
	{
		Buttons =- 64;
		B8L = true;
	}
	else B8L = false;

	if(Buttons >= 32)
	{
		Buttons =- 32;
		B8D = true;
	}
	else B8D = false;

	if(Buttons >= 16)
	{
		Buttons =- 16;
		B8U = true;
	}
	else B8U = false;

	if(Buttons >= 8)
	{
		Buttons =- 8;
		B7R = true;
	}
	else B7R = false;

	if(Buttons >= 4)
	{
		Buttons =- 4;
		B7L = true;
	}
	else B7L = false;

	if(Buttons >= 2)
	{
		Buttons =- 2;
		B7D = true;
	}
	else B7D = false;

	if(Buttons == 1)
	{
		Buttons =- 1;
		B7U = true;
	}
	else B7U = false;

	//	CurrentJS.Ch1Ch2Ch3Ch4 = CurrentJS.Ch1R + (CurrentJS.Ch2R << 4) + (CurrentJS.Ch3R << 8) + (CurrentJS.Ch4R << 12);


}

//Globals for the Self-Writing Auton
//so that the code "remembers" they are
//toggled that way, as they will not
//be in a continuous while loop.

bool solBool = true;
bool btn5DPress = false;
bool btn5UPress = false;
bool btn6UPress = false;
bool btn8UPress = false;
bool btn6DPress = false;
bool btn7DPress = false;

void e(int joyCh1, int joyCh2, int joyCh3, int joyCh4, int joyButtons, AutonSensor SensorInfo, int FinalSensorValue, bool playBack, int timeOut)
{
	DecodeButtons(joyButtons);
	//Turns the one value into a set of
	//booleans representing the joystick
	//buttons

	if(playBack)
	{
		//clears relevant sensors if
		//we are playing it back
		clearSensors();
		clearTimer(T1);
		clearTimer(T4);
	}
	if(!B7D) btn7DPress = false;
	if(!B5U) btn5UPress = false;
	//We are using a do-while loop here
	//as in all circumstances, this will have
	//to run once, but if we are playing it back
	//it will have o run within this while loop
	do
	{
		//See Drive Code Comments, As this is a
		//Carbon Copy of the Drive Code
		if(vexRT[Btn5U] && !btn5UPress)
		{
			btn5UPress = true;
			if(solBool) solBool = false;
			else solBool = true;
		}
		//Set claw bool in case we switch back
		//to pneumatics, and keep the logic and
		//switch the variable names if we use the
		//pneumatics for something else

		int leftSpeed = joyCh2 + joyCh1;
		int rightSpeed = joyCh2 - joyCh1;
		int liftSpeed = joyCh3;
		//Set Drive and Lift Speeds

		int clawSpeed = 0;


		if(DriveMan == Noah) liftSpeed = -liftSpeed;

		SensorValue[solenoid1] = solBool;
		SensorValue[solenoid2] = solBool;
		//Setting Pneumatics, in case we
		//switch back to them

		chassisDrive(leftSpeed, rightSpeed);
		liftDrive(liftSpeed);
		//Run the Claw, Drive, and Lift Motors

		wait1Msec(1);
		//Don't hog the CPU
		//Wait time is built into Recorder
		//so don't wait when that is being run

		gyroUpdate(2, gGyro);
		//Any Updates in Sensors in the General Drive Must Also Be Part of the Auto While Loop

		// Since listing all the drive functions is tedious in self writing autonomi
		// (especially when there is a limit to the debugger window) I made function e
		// to lessen the characters needed while writing a self writing autonomous
		if(time1[T4] > timeOut) goto OUT;

	}while(playBack && shouldWeKeepGoingSen(SensorInfo, FinalSensorValue));
OUT:

}


void f(int motorSpeed1, int motorSpeed2, int motorSpeed3, int motorSpeed4, int motorSpeed5, int motorSpeed6, int motorSpeed7, int motorSpeed8, int motorSpeed9, int motorSpeed10, bool sol, AutonSensor Sensor, int FSV)
{
	//This function, with the autonomous
	//Creator, via the LCD, sets the motors,
	//and waits for the appropriate Sensor
	//Value

	motor[port1] = motorSpeed1;
	motor[port2] = motorSpeed2;
	motor[port3] = motorSpeed3;
	motor[port4] = motorSpeed4;
	motor[port5] = motorSpeed5;
	motor[port6] = motorSpeed6;
	motor[port7] = motorSpeed7;
	motor[port8] = motorSpeed8;
	motor[port9] = motorSpeed9;
	motor[port10] = motorSpeed10;

	SensorValue[solenoid1] = sol;
	SensorValue[solenoid2] = sol;

	while(shouldWeKeepGoingSen(Sensor, FSV));
}


void c()
{
	//Reserved for a better version of the
	//self writing auton, because we are 1200C
}


void deploy()
{
	clearSensors();
	SensorValue[solenoid1] = true;
	SensorValue[solenoid2] = true;
	chassisDrive(127,127);
	while(SensorValue[rightEncoder] > -100);
	chassisDrive(-70,-70);
	while(SensorValue[rightEncoder] < 0);
	chassisDrive(0,0);
}

void leftAuton1()
{
	//Tested a bit, Ill do this one later too.
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	//	wait10Msec(100);
	//	gyroStart(gGyro, gyroXY);

	liftDrive(-50);
	wait10Msec(10);

	clearSensors();
	liftDrive(20);
	while(SensorValue[launchPot] < 1350);
	liftDrive(0);
	SensorValue[solenoid1] = true;
	SensorValue[solenoid2] = true;
	clearSensors();
	chassisDrive(-70,-70);
	while(SensorValue[rightEncoder] < 700);
	chassisDrive(0,0);
	//	liftDrive(-60);
	//while(SensorValue[launchPot] > 1350);
	liftDrive(0);
	clearSensors();
	chassisDrive(80,80);
	while(SensorValue[rightEncoder] > -1050);
	chassisDrive(0,0);
	clearSensors();
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	chassisDrive(-50,-50);
	while(SensorValue[rightEncoder] < 100);
	chassisDrive(0,0);


	clearSensors();
	chassisDrive(60,-60);
	while(abs(gGyro.angle) < 150)
	{
		gyroUpdate(2,gGyro);
		wait1Msec(1);
	}
	chassisDrive(0,0);
	clearSensors();
	SensorValue[solenoid1] = true;
	SensorValue[solenoid2] = true;
	chassisDrive(100,100);
	while(SensorValue[rightEncoder] > -500);
	chassisDrive(0,0);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	clearSensors();
	chassisDrive(30,-127);

	while(abs(gGyro.angle) < 130)
	{
		gyroUpdate(2,gGyro);
		wait1Msec(1);
		if(SensorValue[launchPot] < 1600)
		{
			liftDrive(50);
		}
		else liftDrive(0);
	}
	clearSensors();
	chassisDrive(-100,-100);
	wait10Msec(20);
	liftDrive(120);
	bool endBool = false;

	while(SensorValue[leftEncoder] < 700 && !endBool)
	{
		if(SensorValue[launchPot] > 2500)
		{
			SensorValue[solenoid1] = true;
			SensorValue[solenoid2] = true;
		}
		if(SensorValue[launchPot] > 3500)
		{
			liftDrive(0);
			endBool = true;
		}
	}
	chassisDrive(0,0);
	while(!endBool)
	{
		if(SensorValue[launchPot] > 2500)
		{
			SensorValue[solenoid1] = true;
			SensorValue[solenoid2] = true;
		}
		if(SensorValue[launchPot] > 3500)
		{
			liftDrive(0);
			endBool = true;
		}
	}
}

void leftAuton2()
{
	//Face towards the set of three stars
	//Will grab the three stars,
	//Go back, turn, and then dump
	//the three stars

	//Test using orange cord.
	//Its faster than downloading
	//via VexNet
	clearSensors();
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	//	wait10Msec(100);

	//	liftDrive(0);

	deploy();
	clearSensors();
	chassisDrive(120,120);
	while(SensorValue[rightEncoder] > -1000);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] =	false;
	chassisDrive(-100,-100);
	while(SensorValue[rightEncoder] < 0)
	{
		if(SensorValue[launchPot] < 2300) liftDrive(60);
		else liftDrive(0); //Keep lift up
	}
	liftDrive(30);//Make sure lift is up
	chassisDrive(0,0);
	clearSensors();
	chassisDrive(80,-80);
	while(SensorValue[leftEncoder] < 240); //Turn

	wait10Msec(20);
	clearSensors();
	chassisDrive(-100,-100);
	while(SensorValue[rightEncoder] < 700);
	liftDrive(127); //DUMP
	clearTimer(T1);
	while(time1[T1] < 1500)
	{
		if(SensorValue[launchPot] > 2700)
		{
			SensorValue[solenoid1] = true;
			SensorValue[solenoid2] =	true;
		}
		if(SensorValue[launchPot] > 4000) liftDrive(0);
		//Drive Backwards
		//While you do so, if the pot value goes above
		//2700, open the claw, or if it goes above 4000
		//stop the lift
	}
	chassisDrive(0,0);
	liftDrive(0); //STOP ALL DRIVEs


}

void leftAuton3()
{
	//Start facing the robot towards yourself
	//Away from the fence, towards the wall
	//as close to the star in the corner as you can

	//In the case that we dont want to do much during
	//auton, this will just deploy the claw, grab the preload
	//and hopefully the other star
	clearSensors();
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	//	wait10Msec(100);
	chassisDrive(-100,-100);
	while(SensorValue[rightEncoder] < 500); //Back Up

	chassisDrive(0,0);
	wait10Msec(50);

	deploy();
	chassisDrive(120,30);
	clearSensors();
	while(SensorValue[leftEncoder] > -400 && time1[T1] < 2550);
	chassisDrive(50,50);
	wait10Msec(30);
	//Go forward back to original position
	//with the claw open
	chassisDrive(0,0);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	liftDrive(50);
	wait10Msec(40);
	liftDrive(30);
	//grab the (hopefully) two stars
	clearSensors();
	chassisDrive(-100,-70);
	while(SensorValue[leftEncoder] < 700);
	liftDrive(127); //DUMP
	clearTimer(T1);
	while(time1[T1] < 1500)
	{
		if(SensorValue[launchPot] > 2700)
		{
			SensorValue[solenoid1] = true;
			SensorValue[solenoid2] =	true;
		}
		if(SensorValue[launchPot] > 4000) liftDrive(0);
		//Drive Backwards
		//While you do so, if the pot value goes above
		//2700, open the claw, or if it goes above 4000
		//stop the lift
	}

	chassisDrive(0,0);
	liftDrive(0);

}

void rightAuton1()
{
	//Tested a bit, Ill do this one later too.
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	//	wait10Msec(100);
	//	gyroStart(gGyro, gyroXY);

	liftDrive(-50);
	wait10Msec(10);

	clearSensors();
	liftDrive(20);
	while(SensorValue[launchPot] < 1350);
	liftDrive(0);
	SensorValue[solenoid1] = true;
	SensorValue[solenoid2] = true;
	clearSensors();
	chassisDrive(-70,-70);
	while(SensorValue[rightEncoder] < 700);
	chassisDrive(0,0);
	//	liftDrive(-60);
	//while(SensorValue[launchPot] > 1350);
	liftDrive(0);
	clearSensors();
	chassisDrive(80,80);
	while(SensorValue[rightEncoder] > -1050);
	chassisDrive(0,0);
	clearSensors();
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	chassisDrive(-50,-50);
	while(SensorValue[rightEncoder] < 100);
	chassisDrive(0,0);


	clearSensors();
	chassisDrive(-60,60);
	while(gGyro.angle < 150)
	{
		gyroUpdate(2,gGyro);
		wait1Msec(1);
	}
	chassisDrive(0,0);
	clearSensors();
	SensorValue[solenoid1] = true;
	SensorValue[solenoid2] = true;
	chassisDrive(100,100);
	while(SensorValue[rightEncoder] > -500);
	chassisDrive(0,0);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	clearSensors();
	chassisDrive(-127,30);

	while(abs(gGyro.angle) < 130)
	{
		gyroUpdate(2,gGyro);
		wait1Msec(1);
		if(SensorValue[launchPot] < 1600)
		{
			liftDrive(50);
		}
		else liftDrive(0);
	}
	clearSensors();
	chassisDrive(-100,-100);
	wait10Msec(20);
	liftDrive(120);
	bool endBool = false
	while(SensorValue[leftEncoder] < 700 && !endBool)
	{
		if(SensorValue[launchPot] > 2500)
		{
			SensorValue[solenoid1] = true;
			SensorValue[solenoid2] = true;
		}
		if(SensorValue[launchPot] > 3500)
		{
			liftDrive(0);
			endBool = true;
		}
	}
	chassisDrive(0,0);
	while(!endBool)
	{
		if(SensorValue[launchPot] > 2500)
		{
			SensorValue[solenoid1] = true;
			SensorValue[solenoid2] = true;
		}
		if(SensorValue[launchPot] > 3500)
		{
			liftDrive(0);
			endBool = true;
		}
	}
}

void rightAuton2()
{
	//Face towards the set of three stars
	//Will grab the three stars,
	//Go back, turn, and then dump
	//the three stars

	//Test using orange cord.
	//Its faster than downloading
	//via VexNet
	clearSensors();
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	//wait10Msec(100);

	//	liftDrive(0);

	deploy();
	clearSensors();
	chassisDrive(120,120);
	while(SensorValue[rightEncoder] > -1000);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] =	false;
	chassisDrive(-100,-100);
	while(SensorValue[rightEncoder] < 0)
	{
		if(SensorValue[launchPot] < 2300) liftDrive(60);
		else liftDrive(0); //Keep lift up
	}
	liftDrive(30);//Make sure lift is up
	chassisDrive(0,0);
	clearSensors();
	chassisDrive(-80,80);
	while(SensorValue[rightEncoder] < 240); //Turn

	wait10Msec(20);
	clearSensors();
	chassisDrive(-100,-100);
	while(SensorValue[rightEncoder] < 700);
	liftDrive(127); //DUMP
	clearTimer(T1);
	while(time1[T1] < 1500)
	{
		if(SensorValue[launchPot] > 2700)
		{
			SensorValue[solenoid1] = true;
			SensorValue[solenoid2] =	true;
		}
		if(SensorValue[launchPot] > 4000) liftDrive(0);
		//Drive Backwards
		//While you do so, if the pot value goes above
		//2700, open the claw, or if it goes above 4000
		//stop the lift
	}
	chassisDrive(0,0);
	liftDrive(0); //STOP ALL DRIVEs


}

void rightAuton3()
{
	//Start facing the robot towards yourself
	//Away from the fence, towards the wall
	//as close to the star in the corner as you can

	//In the case that we dont want to do much during
	//auton, this will just deploy the claw, grab the preload
	//and hopefully the other star
	clearSensors();
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	//	wait10Msec(100);
	chassisDrive(-100,-100);
	while(SensorValue[rightEncoder] < 500); //Back Up

	chassisDrive(0,0);
	wait10Msec(50);

	deploy();
	chassisDrive(30,120);
	clearSensors();
	while(SensorValue[rightEncoder] > -400 && time1[T1] < 2550);
	chassisDrive(50,50);
	wait10Msec(30);
	//Go forward back to original position
	//with the claw open
	chassisDrive(0,0);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	liftDrive(50);
	wait10Msec(40);
	liftDrive(30);
	//grab the (hopefully) two stars
	clearSensors();
	chassisDrive(-70,-100);
	while(SensorValue[rightEncoder] < 700);
	liftDrive(127); //DUMP
	clearTimer(T1)
	while(time1[T1] < 1500)
	{
		if(SensorValue[launchPot] > 2700)
		{
			SensorValue[solenoid1] = true;
			SensorValue[solenoid2] =	true;
		}
		if(SensorValue[launchPot] > 4000) liftDrive(0);
		//Drive Backwards
		//While you do so, if the pot value goes above
		//2700, open the claw, or if it goes above 4000
		//stop the lift
	}

	chassisDrive(0,0);
	liftDrive(0);

}

void rightAuton4()
{
	//202 style auton, start facing cube
	//	gyroStart(gGyro, gyroXY);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	//	wait10Msec(100);
	deploy();
	liftDrive(0);
	chassisDrive(127,127);
	while(SensorValue[rightEncoder] > -1000);
	chassisDrive(0,0);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	clearSensors();
	chassisDrive(0,127);
	clearSensors();
	while(SensorValue[leftEncoder] > -700)
	{
		if(SensorValue[launchPot] < 2300) liftDrive(100);
		else liftDrive(0);
	}
	liftDrive(30);
	chassisDrive(-80,-80);
	wait10Msec(50);
	clearTimer(T1);
	while(time1[T1] < 1600)
	{
		liftDrive(100);
		if(SensorValue[launchPot] > 2700)
		{
			SensorValue[solenoid1] = true;
			SensorValue[solenoid2] =	true;
		}
		if(SensorValue[launchPot] > 4000) liftDrive(0);
		//Drive Backwards
		//While you do so, if the pot value goes above
		//2700, open the claw, or if it goes above 4000
		//stop the lift
	}
	chassisDrive(0,0);
	wait10Msec(70);
	liftDrive(-120);
	wait10Msec(90);
	while(SensorValue[launchPot] > 1400)
	{;}
	liftDrive(0);
	clearSensors();
	chassisDrive(100,100);
	while(SensorValue[rightEncoder] > -900 && time1[T1] < 1500);
	chassisDrive(0,0);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	wait10Msec(40);
	clearTimer(T1);
	//	liftDrive(50);
	chassisDrive(-70,-70);
	wait10Msec(30);
	while(time1[T1] < 2000)
	{
		liftDrive(70);
		if(SensorValue[launchPot] > 2700)
		{
			SensorValue[solenoid1] = true;
			SensorValue[solenoid2] =	true;
		}
		if(SensorValue[launchPot] > 4000) liftDrive(0);
		//Drive Backwards
		//While you do so, if the pot value goes above
		//2700, open the claw, or if it goes above 4000
		//stop the lift
	}
	chassisDrive(0,0);
	liftDrive(0);



	wait10Msec(80);
	liftDrive(-120);
	wait10Msec(90);
	while(SensorValue[launchPot] > 1400)
	{;}
	liftDrive(0);
	clearSensors();
	chassisDrive(100,100);
	while(SensorValue[rightEncoder] > -900 && time1[T1] < 1500);
	chassisDrive(0,0);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	wait10Msec(40);
	clearTimer(T1);
	//	liftDrive(50);
	chassisDrive(-90,-90);
	while(time1[T1] < 2300)
	{

	}
	//	liftDrive(0);
}

void rightAuton5()
{
	//202 style auton, start facing cube
	//	gyroStart(gGyro, gyroXY);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	deploy();
	liftDrive(0);
	chassisDrive(127,127);
	while(SensorValue[rightEncoder] > -1000);
	chassisDrive(0,0);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	clearSensors();
	chassisDrive(0,127);
	clearSensors();
	while(SensorValue[leftEncoder] > -700)
	{
		if(SensorValue[launchPot] < 2300) liftDrive(100);
		else liftDrive(0);
	}
	liftDrive(30);
	chassisDrive(-80,-80);
	wait10Msec(50);
	clearTimer(T1);
	while(time1[T1] < 1800)
	{
		liftDrive(100);
		if(SensorValue[launchPot] > 2700)
		{
			SensorValue[solenoid1] = true;
			SensorValue[solenoid2] =	true;
		}
		if(SensorValue[launchPot] > 4000) liftDrive(0);
		//Drive Backwards
		//While you do so, if the pot value goes above
		//2700, open the claw, or if it goes above 4000
		//stop the lift
	}
	chassisDrive(0,0);
}

void leftAuton4()
{
	//202 style auton, start facing cube
	//	gyroStart(gGyro, gyroXY);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	//wait10Msec(100);
	deploy();
	liftDrive(0);
	chassisDrive(127,127);
	while(SensorValue[rightEncoder] > -800);
	chassisDrive(0,0);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	clearSensors();
	chassisDrive(127,0);
	clearSensors();
	while(SensorValue[rightEncoder] > -1000)
	{
		if(SensorValue[launchPot] < 2300) liftDrive(100);
		else liftDrive(0);
	}
	liftDrive(30);
	chassisDrive(-80,-80);
	wait10Msec(50);
	clearTimer(T1);
	while(time1[T1] < 1600)
	{
		liftDrive(100);
		if(SensorValue[launchPot] > 2700)
		{
			SensorValue[solenoid1] = true;
			SensorValue[solenoid2] =	true;
		}
		if(SensorValue[launchPot] > 4000) liftDrive(0);
		//Drive Backwards
		//While you do so, if the pot value goes above
		//2700, open the claw, or if it goes above 4000
		//stop the lift
	}
	chassisDrive(0,0);
	wait10Msec(70);
	liftDrive(-120);
	wait10Msec(90);
	while(SensorValue[launchPot] > 1400)
	{;}
	liftDrive(0);
	clearSensors();
	chassisDrive(100,100);
	while(SensorValue[rightEncoder] > -900 && time1[T1] < 1500);
	chassisDrive(0,0);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	wait10Msec(40);
	clearTimer(T1);
	//	liftDrive(50);
	chassisDrive(-70,-70);
	wait10Msec(30);
	while(time1[T1] < 2000)
	{
		liftDrive(70);
		if(SensorValue[launchPot] > 2700)
		{
			SensorValue[solenoid1] = true;
			SensorValue[solenoid2] =	true;
		}
		if(SensorValue[launchPot] > 4000) liftDrive(0);
		//Drive Backwards
		//While you do so, if the pot value goes above
		//2700, open the claw, or if it goes above 4000
		//stop the lift
	}
	chassisDrive(0,0);
	liftDrive(0);



	wait10Msec(80);
	liftDrive(-120);
	wait10Msec(90);
	while(SensorValue[launchPot] > 1400)
	{;}
	liftDrive(0);
	clearSensors();
	chassisDrive(100,100);
	while(SensorValue[rightEncoder] > -900 && time1[T1] < 1500);
	chassisDrive(0,0);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	wait10Msec(40);
	clearTimer(T1);
	//	liftDrive(50);
	chassisDrive(-90,-90);
	while(time1[T1] < 2300)
	{

	}
	liftDrive(0);
}

void leftAuton5()
{
	//202 style auton, start facing cube
	//	gyroStart(gGyro, gyroXY);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	//wait10Msec(100);
	deploy();
	liftDrive(0);
	chassisDrive(127,127);
	while(SensorValue[rightEncoder] > -800);
	chassisDrive(0,0);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	clearSensors();
	chassisDrive(127,0);
	clearSensors();
	while(SensorValue[rightEncoder] > -1000)
	{
		if(SensorValue[launchPot] < 2300) liftDrive(100);
		else liftDrive(0);
	}
	liftDrive(30);
	chassisDrive(-80,-80);
	wait10Msec(50);
	clearTimer(T1);
	while(time1[T1] < 1800)
	{
		liftDrive(100);
		if(SensorValue[launchPot] > 2700)
		{
			SensorValue[solenoid1] = true;
			SensorValue[solenoid2] =	true;
		}
		if(SensorValue[launchPot] > 4000) liftDrive(0);
		//Drive Backwards
		//While you do so, if the pot value goes above
		//2700, open the claw, or if it goes above 4000
		//stop the lift
	}
	chassisDrive(0,0);
}

void skillz()
{

	leftAuton2();



	wait10Msec(30);

	liftDrive(-120);
	wait10Msec(90);
	while(SensorValue[launchPot] > 1400)
	{;}
	liftDrive(0);
	clearSensors();
	chassisDrive(100,100);
	while(SensorValue[rightEncoder] > -900 && time1[T1] < 1500);
	chassisDrive(0,0);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] = false;
	wait10Msec(40);
	clearTimer(T1);
	//	liftDrive(50);
	chassisDrive(-70,-70);
	wait10Msec(30);
	while(time1[T1] < 2000)
	{
		liftDrive(70);
		if(SensorValue[launchPot] > 2700)
		{
			SensorValue[solenoid1] = true;
			SensorValue[solenoid2] =	true;
		}
		if(SensorValue[launchPot] > 4000) liftDrive(0);
		//Drive Backwards
		//While you do so, if the pot value goes above
		//2700, open the claw, or if it goes above 4000
		//stop the lift
	}
	chassisDrive(0,0);
	liftDrive(0);
	wait10Msec(40);
	liftDrive(-120);
	wait10Msec(90);
	while(SensorValue[launchPot] > 1400)
	{;}
	liftDrive(0);
	clearSensors();
	chassisDrive(100,100);
	while(SensorValue[rightEncoder] > -900 && time1[T1] < 1500);
	chassisDrive(0,0);


	wait10Msec(500);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] =	false;
	clearTimer(T1);
	//	liftDrive(50);
	chassisDrive(-70,-70);
	wait10Msec(30);
	while(time1[T1] < 2000)
	{
		liftDrive(70);
		if(SensorValue[launchPot] > 2700)
		{
			SensorValue[solenoid1] = true;
			SensorValue[solenoid2] =	true;
		}
		if(SensorValue[launchPot] > 4000) liftDrive(0);
		//Drive Backwards
		//While you do so, if the pot value goes above
		//2700, open the claw, or if it goes above 4000
		//stop the lift
	}
	chassisDrive(0,0);
	liftDrive(0);
	wait10Msec(40);
	liftDrive(-120);
	wait10Msec(60);
	while(SensorValue[launchPot] > 1400)
	{;}
	liftDrive(0);
	clearSensors();
	chassisDrive(100,100);
	while(SensorValue[rightEncoder] > -900 && time1[T1] < 1500);
	chassisDrive(0,0);


	wait10Msec(500);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] =	false;

	clearTimer(T1);
	//	liftDrive(50);
	chassisDrive(-70,-70);
	wait10Msec(30);
	while(time1[T1] < 2000)
	{
		liftDrive(70);
		if(SensorValue[launchPot] > 2700)
		{
			SensorValue[solenoid1] = true;
			SensorValue[solenoid2] =	true;
		}
		if(SensorValue[launchPot] > 4000) liftDrive(0);
		//Drive Backwards
		//While you do so, if the pot value goes above
		//2700, open the claw, or if it goes above 4000
		//stop the lift
	}
	chassisDrive(0,0);
	liftDrive(0);
	wait10Msec(40);
	liftDrive(-120);
	wait10Msec(60);
	while(SensorValue[launchPot] > 1400)
	{;}
	liftDrive(0);
	clearSensors();
	chassisDrive(100,100);
	while(SensorValue[rightEncoder] > -900 && time1[T1] < 1500);
	chassisDrive(0,0);


	wait10Msec(500);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] =	false;

	clearTimer(T1);
	//	liftDrive(50);
	chassisDrive(-70,-70);
	wait10Msec(30);
	while(time1[T1] < 2000)
	{
		liftDrive(70);
		if(SensorValue[launchPot] > 2700)
		{
			SensorValue[solenoid1] = true;
			SensorValue[solenoid2] =	true;
		}
		if(SensorValue[launchPot] > 4000) liftDrive(0);
		//Drive Backwards
		//While you do so, if the pot value goes above
		//2700, open the claw, or if it goes above 4000
		//stop the lift
	}
	chassisDrive(0,0);
	liftDrive(0);
	wait10Msec(40);
	liftDrive(-120);
	wait10Msec(60);
	while(SensorValue[launchPot] > 1400)
	{;}
	liftDrive(0);
	clearSensors();
	chassisDrive(100,100);
	while(SensorValue[rightEncoder] > -900 && time1[T1] < 1500);
	chassisDrive(0,0);


	wait10Msec(500);
	SensorValue[solenoid1] = false;
	SensorValue[solenoid2] =	false;


}


void autoCode(int auton)
{
	//Switch to choose autonomous to use
	switch(auton)
	{
	case 1:
		rightAuton1();
		break;

	case 2:
		rightAuton2();
		break;

	case 3:
		rightAuton3();
		break;

	case 4:
		rightAuton4();
		break;

	case 5:
		rightAuton5();
		break;

	case 6:
		leftAuton1();
		break;

	case 7:
		leftAuton2();
		break;

	case 8:
		leftAuton3();
		break;

	case 9:
		leftAuton4();
		break;

	case 10:
		leftAuton5();
		break;

	case 11:
		skillz();
		break;

	case 12:

		break;

	default:

		break;
	}
}


float median(int val1, int val2, int val3, int val4, int val5)
{
	int x[5];
	x[0] = val1;
	x[1] = val2;
	x[2] = val3;
	x[3] = val4;
	x[4] = val5;

	float temp;
	int i, j;
	// the following two loops sort the array x in ascending order
	for(i=0; i<4; i++) {
		for(j=i+1; j<5; j++) {
			if(x[j] < x[i]) {
				// swap elements
				temp = x[i];
				x[i] = x[j];
				x[j] = temp;
			}
		}
	}
	// else return the element in the middle
	return x[2];
}


void simpleRecord(bool holdBool)
{
	//void a(int leftDrive, int rightDrive, int lift, bool claw, bool holding, int timeAllot)

	bnsDebugStream("a(%d,%d,%d,", SensorValue[leftEncoder], SensorValue[rightEncoder], SensorValue[launchPot]);
	if(holdBool)bnsDebugStreamLine("%d, %d, 3000);",SensorValue[solenoid1], holdBool);

}


/*----------------------------------End of General Robot Drive Library----------------------------------*/
