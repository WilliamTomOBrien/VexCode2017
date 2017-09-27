/*-------------------------------Start of Self Writing Autonomous Library-------------------------------*/
/*--------------------------------------------------------------------------------------------------------
| 	This code is to be used to write an autonomous by utilizing the Debugger window. As long as the      |
|	  debugger window does not have any limits, this recorder should be accurate to 1/100th of a           |
|		second. This code will need to be placed within usercontrol, and will need to be altered if          |
|		different drive functions are used. Copy and paste the code from your debugger window into           |
|		your autonomous function. 50-60 lines of code... That's pretty good, since it makes many more lines. |
|   This code records the robots motor and pneumatic values into an array every n/1000 of a second,      |
|   and then adds them in an autonomous format to the debugger window. I used the drive function e,      |
|   since I needed to use a minimal amount of characters, so the cortex could process the string values  |
|   without error.                                                                                       |
|        -William                                                                                        |
--------------------------------------------------------------------------------------------------------*/

int startTimeR = 0;
int endTimeR = 0;

string button = "clearSensors();";
string button2 = "Begin Auton	*/";

//Strings that indicate to the playback function
//the sensor to use as well as the value to stop

AutonSensor DirSenVal;

//Globals to indicate to the record
//function what the current speeds are

string DirSenString;
string SensorInfoString;
//Strings to hold information
//which will go into the self
//writing autonomous

int time1SenVal = 0;

string BatteryLevelAuton;

void SensorValueDecode()
{

	//ALIGN MOST ACCURATE TO LEAST ACCURATE, WITH TIMER AT THE VERY BOTTOM

	//Basically, depending on the inputs from the controller
	//choose an appropriate sensor for how to determine when
	//to stop the autonomous, as different sensors will be
	//better in different situations

	//As of now, we determine if the leftspeed or rightspeed
	//is greater, and then see if it is viable to use for
	//this time, and if it is, use the appropriate encoder,
	//or else use time


	if(((abs(PreviousJS.Ch1R + PreviousJS.Ch2R)) > 20) || ((abs(PreviousJS.Ch1R - PreviousJS.Ch2R)) > 20))
	{
		if(abs(PreviousJS.Ch1R + PreviousJS.Ch2R) > abs(PreviousJS.Ch1R - PreviousJS.Ch2R)) //IF LEFTSPEED IS BIGGER THAN RIGHTSPEED
		{
			if(PreviousJS.Ch1R + PreviousJS.Ch2R > 0)DirSenVal = leftEncDown;
			else DirSenVal = leftEncUp;
		}
		else //IF RIGHTSPEED IS EQUAL TO OR LESS THAN LEFTSPEED
		{
			if(PreviousJS.Ch1R - PreviousJS.Ch2R > 0)DirSenVal = rightEncDown;
			else DirSenVal = rightEncUp;
		}
	}

	else DirSenVal = time; //TIMER


	if(DirSenVal == time || finalE3Bool) sprintf(SensorInfoString, "%d", time1[T1]);
	else if(DirSenVal == leftEncUp || DirSenVal == leftEncDown)	sprintf(SensorInfoString, "%d", SensorValue[leftEncoder]);
	else if(DirSenVal == rightEncUp || DirSenVal == rightEncDown)	sprintf(SensorInfoString, "%d", SensorValue[rightEncoder]);
#ifdef __Auton_Lib__
	else if(DirSenVal == gyroUp || DirSenVal == gyroDown) sprintf(SensorInfoString, "%.2f", gGyro.angle);
#endif
#ifndef __Auton_Lib__
	else if(DirSenVal == gyroUp || DirSenVal == gyroDown) sprintf(SensorInfoString, "%d", SensorValue[gyroXY]);
#endif

	//Place the sensor value into the string
	//that has been chosen

	sprintf(DirSenString, "%d", DirSenVal);

	//Write in the enumeration for the
	//sensor/direction to use

}

//Variables involved with clearing the Sensors and a count system
//To only have so many functions per line. Guess which one is which

int count = 1;
int FullCount = 1;


//RECORDING FUNCTION

bool FirstTimeIsMoveLoop = true;

void ShamalamE3 (int buffer, int n, int pL, Driver Driver, bool condense, bool PID)
{
	//The heart of this library, for recording autonomi

	//Initiate Booleans that tell us whether or not
	//the speed has changed on the drive functions
	//and help us find WHEN they changed.
	bool isCh1Move = false;
	bool isCh2Move = false;
	bool isCh3Move = false;
	bool isCh4Move = false;
	bool isButtonsMove = false;

	//Strings to hold the joystick controller values
	//for when the joystick values change.
	string SCh1;
	string SCh2;
	string SCh3;
	string SCh4;
	string SBNs;

	if (CurrentJS.Ch1R > PreviousJS.Ch1R + buffer || CurrentJS.Ch1R < PreviousJS.Ch1R - buffer)
	{
		//if the actual speed is less or greater than the
		//previous speed + or - the buffer, write the actual Speed
		isCh1Move = true;
		SCh1 = "";
	}
	else
	{
		//otherwise, the values do not change
		isCh1Move = false;
	}
	if (CurrentJS.Ch2R > PreviousJS.Ch2R + buffer || CurrentJS.Ch2R < PreviousJS.Ch2R - buffer)
	{
		//if the actual speed is less or greater than the
		//previous speed + or - the buffer, write the actual Speed
		isCh2Move = true;
		SCh2 = "";
	}
	else
	{
		//otherwise, the values do not change
		isCh2Move = false;
	}
	if (CurrentJS.Ch3R > PreviousJS.Ch3R + buffer || CurrentJS.Ch3R < PreviousJS.Ch3R - buffer)
	{
		//if the actual speed is less or greater than the
		//previous speed + or - the buffer, write the actual Speed
		isCh3Move = true;
		SCh3 = "";
	}
	else
	{
		//otherwise, the values do not change
		isCh3Move = false;
	}
	if (CurrentJS.Ch4R > PreviousJS.Ch4R + buffer || CurrentJS.Ch4R < PreviousJS.Ch4R - buffer)
	{
		//if the actual speed is less or greater than the
		//previous speed + or - the buffer, write the actual Speed
		isCh4Move = true;
		SCh4 = "";
	}
	else
	{
		//otherwise, the values do not change
		isCh4Move = false;
	}
	if (CurrentJS.Buttons != PreviousJS.Buttons)
	{
		//if the actual speed is less or greater than the
		//previous speed + or - the buffer, write the actual Speed
		isButtonsMove = true;
		SBNs = "";
	}
	else
	{
		//otherwise, the values do not change
		isButtonsMove = false;
	}

	//Creation of Strings for use in the playback function

	string comma = ",";
	string e = "e(";
	string eend = ",1);";

	if(condense) e = "b(";


	//The String is Finished, We Solely Need to
	//Decide if the String Need be Added to the Debug Stream
	//This isMove tells the code whether
	//or not any part of the robot has moved

	int isMove = false;

	isMove = isCh1Move + isCh2Move + isCh3Move + isCh4Move + isButtonsMove;
	//If any of the channels move, as stated
	//by the boolean, or this is the final
	//step of the autonomous, then write down
	//the string

	if (isMove > 0 || finalE3Bool)
	{

		if(!FirstTimeIsMoveLoop)
		{

			//If any of the motor speeds, positions, or states change,
			//or it is the end of the recording, write out a new function e string

			//List down previous speeds onto strings so they can be added to the function

			if(!condense)
			{
				sprintf(SCh1,"%d", PreviousJS.Ch1R);
				sprintf(SCh2,"%d", PreviousJS.Ch2R);
				sprintf(SCh3,"%d", PreviousJS.Ch3R);
				sprintf(SCh4,"%d", PreviousJS.Ch4R);
				sprintf(SBNs,"%d", PreviousJS.Buttons);
			}
			if(condense) sprintf(SCh1,"%d", PreviousJS.Ch1Ch2Ch3Ch4);

			//List down the stopping value under the string SensorNumber

			SensorValueDecode();
			//Figure out what sensor value to use in
			//this scenerio

			clearSensors();

			//List Down the Sensor Number onto a string so the playback function can distinguish what sensor to use
			//and whether it needs to be less than or greater than in order to go onto the next function

			//List down the SensorInfo Number and the Sensor Stopping Value into the playback Function
			//Strcat copies the values of the second string onto the end of the the original string

			//Start adding the speeds to the playback function string in the Debug Stream and BNSBluetooth

			if(time1[T4] > 250)
			{
				eend = "";
				sprintf(eend, ",1,%d);", ((((int)time1[T4]/50)*50) + 250);
			}

			if(DebugStream)
			{

				writeDebugStream(e);
				if(!condense)
				{
					writeDebugStream(SCh1);
					writeDebugStream(comma);
					writeDebugStream(SCh2);
					writeDebugStream(comma);
					writeDebugStream(SCh3);
					writeDebugStream(comma);
					writeDebugStream(SCh4);
					writeDebugStream(comma);
				}
				if(condense)
				{
					writeDebugStream(SCh1);
					writeDebugStream(comma);
				}
				writeDebugStream(SBNs);
				writeDebugStream(comma);

				writeDebugStream(DirSenString);
				writeDebugStream(comma);
				writeDebugStream(SensorInfoString);
				if(finalE3Bool) writeDebugStreamLine(eend);
				else writeDebugStream(eend);

			}
			if (BNSBluetooth)
			{
				bnsDebugStream(e);
				bnsDebugStream(SCh1);
				bnsDebugStream(comma);
				if(!condense)
				{
					bnsDebugStream(SCh2);
					bnsDebugStream(comma);
					bnsDebugStream(SCh3);
					bnsDebugStream(comma);
					bnsDebugStream(SCh4);
					bnsDebugStream(comma);
				}
				bnsDebugStream(SBNs);
				bnsDebugStream(comma);

				bnsDebugStream(DirSenString);
				bnsDebugStream(comma);
				bnsDebugStream(SensorInfoString);
				if (finalE3Bool) bnsDebugStreamLine(eend);
				else bnsDebugStream(eend);

			}

			//Writing the function and then the values to the previous speeds into one string, as strcat copies one
			//string to the end of the other, as well as telling the function what sensor to use, what number to
			//stop at, and whether it should be above or below the stopping value to end the playback function.

			count++;
			FullCount++;
		}

		if(FirstTimeIsMoveLoop)
		{
			//The first time this runs
			//through, figure out what the
			//battery level of the auton
			//is, and the starting system
			//time of the autonomous, and write
			//the initializing statements of the
			//auton
			sprintf(BatteryLevelAuton,".2f", nImmediateBatteryLevel/1000);
			startTimeR = nSysTime;

			if(DebugStream)
			{
				writeDebugStreamLine("/* Auton Name:");
				writeDebugStreamLine(BlankLine);
				writeDebugStreamLine(button2);
				writeDebugStreamLine(BlankSpace);
				writeDebugStreamLine(BlankSpace);
				writeDebugStream(button);
			}
			if(BNSBluetooth)
			{
				bnsDebugStreamLine("/* Auton Name:");
				bnsDebugStreamLine(BlankLine);
				bnsDebugStreamLine(button2);
				bnsDebugStreamLine(BlankSpace);
				bnsDebugStreamLine(BlankSpace);
				bnsDebugStream(button);
			}
		}

		PreviousJS.Ch1R = CurrentJS.Ch1R;
		PreviousJS.Ch2R = CurrentJS.Ch2R;
		PreviousJS.Ch3R = CurrentJS.Ch3R;
		PreviousJS.Ch4R = CurrentJS.Ch4R;
		PreviousJS.Buttons = CurrentJS.Buttons;
		PreviousJS.Ch1Ch2Ch3Ch4 = CurrentJS.Ch1Ch2Ch3Ch4;
		//The robot starts moving here, so we
		//don't have to put it in the debugger
		//window, but still have to write them
		//down

		//wait n/1000 of a second so it has time to process all of the strings

		//If the robot moves, write the playback string to the debugger window, change the previous speed
		//values to the previous speeds values, so in the future, it will be able to tell if the speed goes up or down
		//below the previousSpeed value more than the buffer. Also, clear all clearable Sensors, and add one to the count
		//so there are never no more than five functions on a line.
		FirstTimeIsMoveLoop = false;
		time1SenVal = 0;
		clearSensors();
		clearTimer(T4); //Clear TimeOut Timer
	}

	if (count >= pL && !finalE3Bool)
	{
		//If there is more than 5 lines of code in one line, make a new line in the debugger window
		if(DebugStream) writeDebugStreamLine(BlankSpace);
		if(BNSBluetooth) bnsDebugStreamLine(BlankSpace);
		count -= pL;
	}

	if (finalE3Bool)
	{
		//If this is the last time we
		//run through this function,
		//turn relevant variables to their
		//starting state
		finalE3Bool = false;
		recordBool = false;

		count = 1;
		FirstTimeIsMoveLoop = true;

		(float) endTimeR = nSysTime;
		//Find what time the auotnomous ended
		float timeR = (float)(endTimeR - startTimeR)/1000;
		//var to find the length of the autonomous

#ifdef recorderString


		//If we want to document the different specs of
		//the autonomous we have just recorded, such
		//as things like the Date the code that made it
		//was compiled on, how long the actual auton is,
		//the battery voltage it was recorded at, and
		//how many lines of code are written.
		if(DebugStream)
		{

			writeDebugStream("Volts: %s%c", BatteryLevelAuton, "V");
			writeDebugStreamLine("Time: %.2f Second(s)", ((float)(endTimeR - startTimeR)/1000));
			writeDebugStreamLine("Lines of Code: %d", FullCount);

		}
		if(BNSBluetooth)
		{
			bnsDebugStream("Volts: ");
			bnsDebugStream(BatteryLevelAuton);
			bnsDebugStreamLine("V");
			bnsDebugStreamLine("Time: %.2f Second(s)", ((float)(endTimeR - startTimeR)/1000));
			bnsDebugStreamLine("Lines of Code: %d", FullCount);
		}
#endif

	}

	wait1Msec(n);
	time1SenVal += n;

	//Taking advantage of the debugger window and UART for nefarious reasons? What? Who said anything about that?
	//Strings are better used in code than by cats, no matter how much fun they have with them.
	//This autonomous will write a lot of code... A ton for one auton... It should work though... Goodness I hope so...

}

void GetJoystick()
{

	//Set the Joystick Struct you are using
	//to the values on the joystick

	CurrentJS.Ch1R = vexRT[Ch1];
	CurrentJS.Ch2R = vexRT[Ch2];
	CurrentJS.Ch3R = vexRT[Ch3];
	CurrentJS.Ch4R = vexRT[Ch4];

	CurrentJS.Ch1Ch2Ch3Ch4 = CurrentJS.Ch1R + (CurrentJS.Ch2R << 4) + (CurrentJS.Ch3R << 8) + (CurrentJS.Ch4R << 12);

	CurrentJS.Buttons = 0;

	//CurrentJS.Buttons |= (vexRT[ Btn7U ] == 1) ? 1  : 0;
	//CurrentJS.Buttons |= (vexRT[ Btn7D ] == 1) ? 2  : 0;
	//CurrentJS.Buttons |= (vexRT[ Btn7L ] == 1) ? 4  : 0;
	//CurrentJS.Buttons |= (vexRT[ Btn7R ] == 1) ? 8  : 0;

	//CurrentJS.Buttons |= (vexRT[ Btn8U ] == 1) ? 16  : 0;
	//CurrentJS.Buttons |= (vexRT[ Btn8D ] == 1) ? 32  : 0;
	//CurrentJS.Buttons |= (vexRT[ Btn8L ] == 1) ? 64  : 0;
	//CurrentJS.Buttons |= (vexRT[ Btn8R ] == 1) ? 128  : 0;

	//CurrentJS.Buttons |= (vexRT[ Btn5U ] == 1) ? 256 : 0;
	//CurrentJS.Buttons |= (vexRT[ Btn5D ] == 1) ? 512 : 0;

	//CurrentJS.Buttons |= (vexRT[ Btn6U ] == 1) ? 1024 : 0;
	//CurrentJS.Buttons |= (vexRT[ Btn6D ] == 1) ? 2048 : 0;


	//Use a Quasi-Bitmap System to store
	//the joystick values in as few characters
	//as possible

	CurrentJS.Buttons = vexRT[Btn6D]*2048 + vexRT[Btn6U]*1024 + vexRT[Btn5D]*512 +
	vexRT[Btn5U]*256 + vexRT[Btn8R]*128 + vexRT[Btn8L]*64 + vexRT[Btn8D]*32 +
	vexRT[Btn8U]*16 + vexRT[Btn7R]*8 + vexRT[Btn7L]*4 + vexRT[Btn7D]*2 + vexRT[Btn7U]*1;

}


/*-------------------------------Further Notes To Remember On ProjectE Function-------------------------------------
| - When making the speed limits that default it to the timer, it is not always 10 or 20 around zero. It must      |
|   be the range at which it does not move at all. If it goes down due to gravity at motor speed 5, then that must |
|   be accounted for by adding up to 5 in the range that will only stop that particular motor power whenst the     |
|   value has gone below the FinalSensorValue set during Recording.                                                |
| - Always make sure the timer has last priority, as it is least accurate                                          |
| - Unless you account for it using a boolean, like is done with the timers, list the if statements that lead      |
|   to SensorInfo values from least accurate to most accurate, as the last one that is accepted will be the value  |
|   if more than one are accepted.                                                                                 |
| - Remember, this function is weird as heck, as it stores the current speeds, and then puts in your previous      |
|   speeds with the current sensorVal, as it will change speeds AT that sensorVal. The logic is sound, but it      |
|   is somewhat trippy.                                                                                            |
| - Timer must clear at the end of the record function (ProjectE3) and the beginning of the playback function      |
|   (e)as the end of the playback occurs at the same time as the beginning of the playback function. This is not   |
|   solely for the timer however. You can use it for all Sensors, except position based ones that will go Back     |
|   to the value they are set at after you change it, so basically, you can do this to encoders and timers, but    |
|   thats about it.                                                                                                |
| - Account for reversed SensorVals either directly in the code, in the pragma statement, or even better,          |
|   make the -SensorVal a variable and use that for the FinalSensorVal.                                            |
--------------------------------------------------------------------------------------------------------------------
/*------------------------------------End of Self Writing Autonomous Library--------------------------------------*/
