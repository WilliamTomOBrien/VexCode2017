/*---------------------------------------Start of LCD Menu Library--------------------------------------*/

bool LCDMenuBool = true;
bool TopMenu = true;
string TopString;
string BotString;

int CaseValue = 1;
int CaseValue1 = 1;
int CaseValue2 = 1;

int CaseValueFinder(int autonRange, int numberOfCases, int prevV)
{
	//Works to find the case value for a switch given a number of Cases
	//the previous value (only needed in certain cases), and the range
	//of the sensor that you want for each case.

	int returnVal;


#ifndef _Target_Emulator_
	for(int b = 1; b <= numberOfCases; b++)
	{
		if(SensorValue[autonSelector] > (b-1)*autonRange && SensorValue[autonSelector] < (b)*autonRange)
		{
			//Checks to see if it is within the range for the specified auton task
			//if the sensor value is greater than autonRange*(caseValue - 1) and less than
			//autonRange*CaseValue. If it is, it sets that to be the case
			returnVal = b;
		}
	}


	while(SensorValue[autonSelector] < 0 || SensorValue[autonSelector] > numberOfCases*autonRange)
	{
		//Makes sure the sensor is within usable range. If the sensor
		//is not within usable range, resets the sensor to 0
		if(SensorValue[autonSelector] > numberOfCases*autonRange) SensorValue[autonSelector] -= numberOfCases*autonRange;
		if(SensorValue[autonSelector] < 0) SensorValue[autonSelector] =+ numberOfCases*autonRange;
	}
#endif

	return returnVal;
}

void SensorsMenu ()
{

	//Sensor Menu to see the value of all sensors, in order
	//to test specific functionalities of the sensor

#ifndef _Target_Emulator_
	CaseValue = CaseValueFinder(100,7, CaseValue);

	switch(CaseValue)
	{
	case 1:
		TopString = "";
		BotString = "";
		string mainBattery, backupBattery, secondBattery, batteryTwo;
		secondBattery = "  S:";
		strcat(TopString,"P:");
		//Start building strings to display battery voltages to LCD

		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V');
		//Build the string to display the normal battery voltage

		strcat(TopString,mainBattery);
		strcat(BotString, "B:");
		sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');
		//Sets the String for the Backup Battery in Volts, as the Cortex
		//Gives us this value

		sprintf(batteryTwo, "%1.2f%c", SensorValue[Battery]/280.0, 'V');
		//Gives us the value for the Power Expander Battery, converted from
		//Analog values to Voltages

		strcat(BotString, backupBattery);
		strcat(BotString, secondBattery);
		strcat(BotString, batteryTwo);
		break;
	case 2:
		float degreesVal = 0;
		if(SensorType[gyroXY] == sensorAnalog)
		{
			gyroUpdate(3, gGyro);
			degreesVal = gGyro.angle;
			//If we are running the self-integration code
			//use value from the gyro struct
		}
		else if(SensorType[gyroXY] == sensorGyro)
		{
			degreesVal = SensorValue[gyroXY]/10;
			//If we are not using the self-integration code
			//use value from the actual gyro
		}



		string gyro;
		sprintf(gyro, "%1.2f",degreesVal);
		if(SensorType[gyroXY] == sensorAnalog) TopString = "Analog Gyro:";
		if(SensorType[gyroXY] == sensorGyro) TopString = "RobotC Gyro:";
		BotString = gyro;
		//Display the Gyro Sensor
		break;
	case 3:
		string Encoder2;
		sprintf(Encoder2, "%d",SensorValue[leftEncoder]);
		TopString = "Left Enc Value:";
		BotString = Encoder2;
		//If we are on this case, display the left encoder
		//value
		break;
	case 4:
		string Encoder3;
		sprintf(Encoder3, "%d",SensorValue[rightEncoder]);
		TopString = "Right Enc Value:";
		BotString = Encoder3;
		//If we are on this case, display the right encoder
		//value
		break;
	case 5:
		string launchPotentiometer;
		sprintf(launchPotentiometer, "%d", SensorValue[launchPot]);
		TopString = "Launch Pot Val:";
		BotString = launchPotentiometer;
		//If we are on this case, display the potentiometer
		//value
		break;
	case 6:
		string UltraS;
		sprintf(UltraS, "%1.2f", SensorValue[Ultra]);
		TopString = "Ultra Sen Val:";
		BotString = UltraS;
		//If we are on this case, display the Ultrasonic
		//Sensor value
		break;
	case 7:
		TopString = "Go Back To Main";
		BotString = "Menu";
		//If we click the middle button, go back to the
		//top menu in this case
		break;
	}

	if(CaseValue == 7 && nLCDButtons == 2)
	{
		while(nLCDButtons == 2);
		TopMenu = true;
		//If you are on the return to main menu
		//window and click, go to the top menu
	}
#endif


}

void motorHealth ()
{
	CaseValue = CaseValueFinder(100,11,CaseValue);

	BotString = "127         -127";
	//Display Possible Speeds to test at

	switch(CaseValue)
	{

		//For each individual case, if you click
		//the left or right button, run and test
		//one individual motor

	case 1:
		TopString = NameMotor1;
		if(nLCDButtons == 1)motor[port1] = 127;
		else if(nLCDButtons == 4) motor[port1] = -127;
		else motor[port1] = 0;
		break;
	case 2:
		TopString = NameMotor2;
		if(nLCDButtons == 1)motor[port2] = 127;
		else if(nLCDButtons == 4) motor[port2] = -127;
		else motor[port2] = 0;
		break;
	case 3:
		TopString = NameMotor3;
		if(nLCDButtons == 1)motor[port3] = 127;
		else if(nLCDButtons == 4) motor[port3] = -127;
		else motor[port3] = 0;
		break;
	case 4:
		TopString = NameMotor4;
		if(nLCDButtons == 1)motor[port4] = 127;
		else if(nLCDButtons == 4) motor[port4] = -127;
		else motor[port4] = 0;
		break;
	case 5:
		TopString = NameMotor5;
		if(nLCDButtons == 1)motor[port5] = 127;
		else if(nLCDButtons == 4) motor[port5] = -127;
		else motor[port5] = 0;
		break;
	case 6:
		TopString = NameMotor6;
		if(nLCDButtons == 1)motor[port6] = 127;
		else if(nLCDButtons == 4) motor[port6] = -127;
		else motor[port6] = 0;
		break;
	case 7:
		TopString = NameMotor7;
		if(nLCDButtons == 1)motor[port7] = 127;
		else if(nLCDButtons == 4) motor[port7] = -127;
		else motor[port7] = 0;
		break;
	case 8:
		TopString = NameMotor8;
		if(nLCDButtons == 1)motor[port8] = 127;
		else if(nLCDButtons == 4) motor[port8] = -127;
		else motor[port8] = 0;
		break;
	case 9:
		TopString = NameMotor9;
		if(nLCDButtons == 1)motor[port9] = 127;
		else if(nLCDButtons == 4) motor[port9] = -127;
		else motor[port9] = 0;
		break;
	case 10:
		TopString = NameMotor10;
		if(nLCDButtons == 1)motor[port10] = 127;
		else if(nLCDButtons == 4) motor[port10] = -127;
		else motor[port10] = 0;
		break;
	case 11:
		TopString = "Go To Top Menu";
		if(nLCDButtons != 0)
		{
			while(nLCDButtons != 0);
			TopMenu = true;
		}
		break;
	}
}

void runSpecifiedProgram()
{

	CaseValue = CaseValueFinder(100, 3, CaseValue);

	switch(CaseValue)
	{
	case 1:
		TopString = "Run Autonomous";
		BotString = "";
		if(nLCDButtons != 0)
		{
			while(nLCDButtons != 0);

			wait10Msec(300);
			autoCode(autoValue);
			//Run the autonomous if you click
			//the button on this menu
		}
		break;
#ifdef __Recorder_Lib__
	case 2:
		TopString = "Run Self Writing";
		BotString = "Autonomous";
		if(nLCDButtons != 0)
		{
			while(nLCDButtons != 0);
			if(recordBool == false) recordBool = true;
			if(recordBool == true) finalE3Bool = true;
		}
		//If we are using the self writing auton code
		//start or stop the self writing code
		break;
#endif
#ifndef __Recorder_Lib__
	case 2:
		TopString = "VOID";
		BotString = "VOID";
		//If we are not using the recorder, "void"
		//this menu
#endif
	case 3:
		TopString = "Return to Main";
		BotString = "Menu";
		if(nLCDButtons != 0)
		{
			while(nLCDButtons != 0);
			TopMenu = true;
			//If you click the middle button on this
			//menu, return to the top menu
		}
	}
}

void robotDiagnostics()
{
	CaseValue = CaseValueFinder(100, 6, CaseValue);
	//As of right now, this is used to test values
	//for the trueSpeed Array - each case displays
	//what motor powers will be tested, and the function
	//that runs after you hit it tests those motor
	//powers to find the average RPM that runs at that
	//motorSpeed
	switch(CaseValue)
	{
	case 1:
		TopString = "TSpd 0-27";
		break;
	case 2:
		TopString = "TSpd 28-55";
		break;
	case 3:
		TopString = "TSpd 55-82";
		break;
	case 4:
		TopString = "TSpd 83-110";
		break;
	case 5:
		TopString = "TSpd 111-127";
		break;
	case 6:
		TopString = "LEAVE";
		break;
	}

	if(nLCDButtons == 2 && CaseValue != 6)
	{
		while(nLCDButtons == 2);
		switch(CaseValue)
		{
		case 1:
			trueSpeedFind(0,27);
			break;
		case 2:
			trueSpeedFind(28,54);
			break;
		case 3:
			trueSpeedFind(55,82);
			break;
		case 4:
			trueSpeedFind(83,110);
			break;
		case 5:
			trueSpeedFind(111,127);
			break;
		}
	}
	else if(nLCDButtons == 2 && CaseValue == 6)
	{
		TopMenu = true;
	}
}

void autonSelection()
{
	//Function in the LCD Code to select an
	//autonomous program

	autoValue = CaseValueFinder(100, NumberOfAutons, autoValue);
	//Sets the autonomous value


	TopString = autoNameString[autoValue - 1];
	BotString = "Lock Now";

	if(nLCDButtons == 2)
	{
		//Locks in the autonomous value by leaving the
		//code that creates an ability to switch the code
		while(nLCDButtons == 2);
		TopMenu = true;
	}


}

//WE CAN CHANGE FIVE GLOBAL VALUES LIVE IN THE CODE
//MAINLY VALUABLE FOR PID TESTING, HENCE THE NAMING
//OF THE FIRST THREE VARIABLES

float kPLCD = 0;
float kILCD = 0;
float kDLCD = 0;
float globalFour = 0;
float globalFive = 0;

bool VariableManip = false;
bool IncrementSelect = false;

float Increment = .0001;

int coEf = 0;
int displayVal;

void liveVarChange()
{
	string varValue;
	if(IncrementSelect)
	{
		CaseValue2 = CaseValueFinder(100,8,CaseValue2);
		//Case Value selector for selecting which increment
		//to change
	}
	else if(VariableManip)
	{
		//If we are manipulating a variable, we do cannot
		//change casevalues, hence this being blank
	}
	else
	{
		CaseValue = CaseValueFinder(100,7,CaseValue);
		//Case value to pick the actual variable to
		//modify
	}

	if(IncrementSelect)BotString = "";

	switch(CaseValue)
	{
	case 1:
		if(!IncrementSelect)
		{
			TopString = "Change Inc";
			BotString = "";
			sprintf(BotString,"%1.4f", Increment);

			if(nLCDButtons == 2)
			{
				while(nLCDButtons == 2);
				IncrementSelect = true;
				wait10Msec(20);
			}
			//Display the Entry Screen to get into the increment
			//Select menu, hitting the button locks you into this
			//case until you leave increment select
		}
		else if(IncrementSelect)
		{

			TopString = "Changing Inc";
			BotString = "";
			sprintf(BotString,"%1.4f", Increment);

			while(IncrementSelect)
			{
				//Based on the following series of cases and
				//case values, switch the increment with which
				//you will manipulate your variable from anywhere
				//from 0.0001 to 100
				CaseValue2 = CaseValueFinder(100,8,CaseValue2);
				switch(CaseValue2)
				{
				case 1:
					Increment = 0.0001;
					BotString = "0.0001";
					if(nLCDButtons == 2)
					{
						while(nLCDButtons == 2);
						IncrementSelect = false;
					}
					break;
				case 2:
					Increment = 0.001;
					BotString = "0.001";
					if(nLCDButtons == 2)
					{
						while(nLCDButtons == 2);
						IncrementSelect = false;
					}
					break;
				case 3:
					Increment = 0.01;
					BotString = "0.01";
					if(nLCDButtons == 2)
					{
						while(nLCDButtons == 2);
						IncrementSelect = false;
					}
					break;
				case 4:
					Increment = 0.1;
					BotString = "0.1";
					if(nLCDButtons == 2)
					{
						while(nLCDButtons == 2);
						IncrementSelect = false;
					}
					break;
				case 5:
					Increment = 1;
					BotString = "1";
					if(nLCDButtons == 2)
					{
						while(nLCDButtons == 2);
						IncrementSelect = false;
					}
					break;
				case 6:
					Increment = 10;
					BotString = "10";
					if(nLCDButtons == 2)
					{
						while(nLCDButtons == 2);
						IncrementSelect = false;
					}
					break;
				case 7:
					Increment = 100;
					BotString = "100";
					if(nLCDButtons == 2)
					{
						while(nLCDButtons == 2);
						IncrementSelect = false;
					}
					break;
				case 8:
					Increment = 1000;
					BotString = "1000";
					if(nLCDButtons == 2)
					{
						while(nLCDButtons == 2);
						IncrementSelect = false;
					}
					break;
				}
				displayLCDCenteredString(0,TopString);
				displayLCDCenteredString(1,BotString);
			}

		}
		wait10Msec(20);
		break;
	case 2:
		displayVal = kPLCD;
		//If you click this button, start to manipulate
		//this current variable
		TopString = "Press Manip V1";
		if(!VariableManip)
		{
			if(nLCDButtons == 2)
			{
				clearTimer(T4);
				while(nLCDButtons == 2);
				VariableManip = true;
				coEf = 0;
				displayVal = kPLCD;
			}
		}
		if(VariableManip)
		{
			TopString = "Manip Var1";
			coEf = SensorValue[autonSelector]/50;
			//Manipulate the variable value based
			//on the Quad Encoder LCD Selector

			displayVal = kPLCD + coEf*Increment;
			sprintf(BotString,"%1.4f",displayVal);

			if(nLCDButtons == 2)
			{
				while(nLCDButtons == 2);
				VariableManip = false;
				kPLCD = kPLCD + coEf*Increment;
				//Lock in the value of the function
			}

		}
		if(!VariableManip)
		{
			BotString = "";
			sprintf(BotString,"Var1 = %1.4f",kPLCD);
			//If not manipulating the variable, solely
			//display the value
		}

		break;

	case 3:
		displayVal = kILCD;
		TopString = "Press Manip V2";
		if(!VariableManip)
		{
			if(nLCDButtons == 2)
			{
				clearTimer(T4);
				while(nLCDButtons == 2);
				VariableManip = true;
				coEf = 0;
				displayVal = kILCD;
				//Enter into manipulating variable menu
				//when middle button is clicked
			}
		}
		if(VariableManip)
		{
			TopString = "Manip Var2";

			coEf = SensorValue[autonSelector]/50;
			//Manipulate the variable based upon the LCD
			//Selector sensor

			displayVal = kILCD + coEf*Increment;
			sprintf(BotString,"Var2 = %1.4f",displayVal);

			if(nLCDButtons == 2)
			{
				while(nLCDButtons == 2);
				VariableManip = false;
				kILCD = kILCD + coEf*Increment;
				//Lock in the value
			}

		}
		if(!VariableManip)
		{
			BotString = "";
			sprintf(BotString,"Var2 = %1.4f",kILCD);
			//If we are not manipulating the variable,
			//display the variable

		}

		break;

	case 4:
		if(!VariableManip)
		{
			displayVal = kDLCD;
			TopString = "Press Manip V3";
			if(nLCDButtons == 2)
			{
				clearTimer(T4);
				while(nLCDButtons == 2);
				VariableManip = true;
				coEf = 0;
				displayVal = kDLCD;
				//Enter into manipulating variable menu
				//when middle button is clicked
			}
			if(VariableManip)
			{
				TopString = "Manip Var3";
				coEf = SensorValue[autonSelector]/50;
				//Manipulate the variable based upon the LCD
				//Selector sensor
				displayVal = kDLCD + coEf*Increment;
				sprintf(BotString,"Var3 = %1.4f",displayVal);

				if(nLCDButtons == 2)
				{
					while(nLCDButtons == 2);
					VariableManip = false;
					kDLCD = kDLCD + coEf*Increment;
					//Lock in the value
				}

			}
			if(!VariableManip)
			{
				BotString = "";
				sprintf(BotString,"Var3 = %1.4f",kDLCD);
				//If we are not manipulating the variable,
				//display the variable
			}

			break;
		case 5:
			displayVal = globalFour;
			TopString = "Press Manip V4";
			if(!VariableManip)
			{
				if(nLCDButtons == 2)
				{
					clearTimer(T4);
					while(nLCDButtons == 2);
					VariableManip = true;
					coEf = 0;
					displayVal = globalFour;
				}
				//Enter into manipulating variable menu
				//when middle button is clicked
			}
			if(VariableManip)
			{
				TopString = "Manip Var4";
#ifndef _Target_Emulator_
				coEf = SensorValue[autonSelector]/50;
				//Manipulate the variable based upon the LCD
				//Selector sensor
#endif

				displayVal = globalFour + coEf*Increment;
				sprintf(BotString,"Var4 = %1.4f",displayVal);

				if(nLCDButtons == 2)
				{
					while(nLCDButtons == 2);
					VariableManip = false;
					globalFour = globalFour + coEf*Increment;
					//Lock in the value
				}

			}
			if(!VariableManip)
			{
				BotString = "";
				sprintf(BotString,"Var4 = %1.4f",globalFour);
				//If we are not manipulating the variable,
				//display the variable
			}

			break;

		case 6:
			displayVal = globalFive;
			TopString = "Press Manip V5";
			if(nLCDButtons == 2)
			{
				clearTimer(T4);
				while(nLCDButtons == 2);
				VariableManip = true;
				coEf = 0;
				displayVal = globalFive;
				//Enter into manipulating variable menu
				//when middle button is clicked
			}
			if(VariableManip)
			{
				TopString = "Manip Var5";
#ifndef _Target_Emulator_
				coEf = SensorValue[autonSelector]/50;
				//Manipulate the variable based upon the LCD
				//Selector sensor
#endif
				displayVal = globalFive + coEf*Increment;
				sprintf(BotString,"Var5 = %1.4f",displayVal);

				if(nLCDButtons == 2)
				{
					while(nLCDButtons == 2);
					VariableManip = false;
					globalFive = globalFive + coEf*Increment;
					//Lock in the value
				}

			}
			if(!VariableManip)
			{
				BotString = "";
				sprintf(BotString,"Var5 = %1.4f",globalFive);
				//If we are not manipulating the variable,
				//display the variable
			}


			break;
		case 7:
			TopString = "Leave Var Manip";
			BotString = "Hold";
			if(nLCDButtons == 2)
			{
				while(nLCDButtons == 2);
				TopMenu = true;
				//Leave the variable manipulator if you
				//hit this button on this menu
			}
			break;
		}
	}
}
int aCLeftSpeed = 0;
int aCRightSpeed = 0;
int aCArb1Speed = 0; //LIFT SPEED
int aCArb2Speed = 0; //CLAW SPEED
int aCArb3Speed = 0;
int aCArb4Speed = 0;
AutonSensor aCSensorValue = time;
int aCFinalSensorValue = 0;

bool aCBreakVal = false;
bool aCStopVal = true;

bool writeAuton = false;

int numberOfAutonSteps = 0;

string TopString1;
string BotString1;

void autonCreator()
{
	//Function to work to create autonomous programs
	//through the use of the LCD Screen
	wait10Msec(20);

	bool autonBeingCreated = true;
	do{
		bool setSpeeds = true;
		bool ChooseDrive = true;
		while(setSpeeds)
		{
			if(ChooseDrive)
			{
				//Set Speeds for each "drive" system
				//for this current step of the autonomous

				CaseValue = CaseValueFinder(100,7,CaseValue);
				//Use CaseValue function in order to find which system
				//you want to manipulate

				BotString1 = "Set Drive";

				if(CaseValue == 1) TopString1 = "Set Left Speed";
				if(CaseValue == 2) TopString1 = "Set Right Speed";
				if(CaseValue == 3) TopString1 = "Set Lift Speed";
				if(CaseValue == 4) TopString1 = "Set Claw Speed";
				if(CaseValue == 5) TopString1 = "Set Arb3 Speed";
				if(CaseValue == 6) TopString1 = "Set Arb4 Speed";
				if(CaseValue == 7) TopString1 = "All Speeds Set";

				if(nLCDButtons == 2 && CaseValue != 7)
				{
					while(nLCDButtons == 2);
					ChooseDrive = false;
				}
				if(nLCDButtons == 2 && CaseValue == 7)
				{
					while(nLCDButtons == 2);
					setSpeeds = false;
				}
			}
			if(!ChooseDrive)
			{
				CaseValue1 = CaseValueFinder(10,255,CaseValue1);
				BotString1 = "Set Speed";
				//DRIVE FLAG

				//Set the speed of the drive systems anywhere
				//from -127 to 127

				if(CaseValue == 1)
				{
					TopString1 = "";
					sprintf(TopString1,"LftSpd = %d",CaseValue1 - 128);

					if(nLCDButtons == 2)
					{
						while(nLCDButtons == 2);
						aCLeftSpeed = CaseValue1 - 128;
						ChooseDrive = true;
					}
				}
				if(CaseValue == 2)
				{
					TopString1 = "";
					sprintf(TopString1,"RghtSpd = %d",CaseValue1 - 128);

					if(nLCDButtons == 2)
					{
						while(nLCDButtons == 2);
						aCRightSpeed = CaseValue1 - 128;
						ChooseDrive = true;
					}
				}
				if(CaseValue == 3)
				{

					TopString1 = "";
					sprintf(TopString1,"LiftSpd = %d",CaseValue1 - 128);

					if(nLCDButtons == 2)
					{
						while(nLCDButtons == 2);
						aCArb1Speed = CaseValue1 - 128;
						ChooseDrive = true;
					}
				}
				if(CaseValue == 4)
				{

					TopString1 = "";
					sprintf(TopString1,"ClawSpd = %d",CaseValue1 - 128);


					if(nLCDButtons == 2)
					{
						while(nLCDButtons == 2);
						aCArb2Speed = abs(CaseValue1 - 128);
						ChooseDrive = true;
					}
				}
				if(CaseValue == 5)
				{

					TopString1 = "";
					sprintf(TopString1,"A3S = %d",CaseValue1 - 128);

					if(nLCDButtons == 2)
					{
						while(nLCDButtons == 2);
						aCArb3Speed = CaseValue1 - 128;
						ChooseDrive = true;
					}
				}
				if(CaseValue == 6)
				{

					TopString1 = "";
					sprintf(TopString1,"A4S = %d",CaseValue1 - 128);

					if(nLCDButtons == 2)
					{
						while(nLCDButtons == 2);
						aCArb4Speed = CaseValue1 - 128;
						ChooseDrive = true;
					}
				}

			}

			displayLCDCenteredString(0, TopString1);
			displayLCDCenteredString(1, BotString1);

		}

		displayLCDCenteredString(0,"");
		displayLCDCenteredString(0,"");

		bool ChooseSensorData = true;
		bool ChooseSensor = true;
		while(ChooseSensorData)
		{
			if(ChooseSensor)
			{


				CaseValue2 = CaseValueFinder(100,13,CaseValue2);
				//Choose what sensor, as well as in what direction
				//you would like this autonomous step to stop at,
				//through the use of the auton Sensor enumeration

				BotString1 = "Choose Sensor";


				if(CaseValue2 == 1) TopString1 = "LeftEncUp";
				if(CaseValue2 == 2) TopString1 = "LeftEncDown";
				if(CaseValue2 == 3) TopString1 = "Time";
				if(CaseValue2 == 4) TopString1 = "rightEncUp";
				if(CaseValue2 == 5) TopString1 = "rightEncDown";
				if(CaseValue2 == 6) TopString1 = "gyroUp";
				if(CaseValue2 == 7) TopString1 = "gyroDown";
				if(CaseValue2 == 8) TopString1 = "leftLine";
				if(CaseValue2 == 9) TopString1 = "midLine";
				if(CaseValue2 == 10) TopString1 = "rightLine";
				if(CaseValue2 == 11) TopString1 = "sonarInc";
				if(CaseValue2 == 12) TopString1 = "sonarDec";
				if(CaseValue2 == 13) TopString1 = "Leave SensorMenu";

				if(nLCDButtons == 2 && CaseValue2 != 13)
				{
					while(nLCDButtons);
					ChooseSensor = false;
					aCSensorValue = CaseValue2;
					//Once you have picked a sensor, and a final sensor
					//value, click this button to leave this overall menu
				}
				if(nLCDButtons == 2 && CaseValue2 == 13)
				{
					while(nLCDButtons);
					ChooseSensorData = false;
				}

			}
			if(!ChooseSensor)
			{
				BotString = "Choose FSV";

				string FSVS;
#ifndef _Target_Emulator_
				sprintf(FSVS,"FSV = %d",abs(SensorValue[autonSelector]));
				//Display the stopping sensor value you would have if you clicked
				//at any given point in time
#endif

				TopString1 = FSVS;

				if(nLCDButtons == 2)
				{
#ifndef _Target_Emulator_
					aCFinalSensorValue = abs(SensorValue[autonSelector]);
#endif


					ChooseSensor = true;
					while(nLCDButtons);
				}
			}

			displayLCDCenteredString(0,TopString1);
			displayLCDCenteredString(1,BotString1);

		}

		displayLCDCenteredString(0,"");
		displayLCDCenteredString(1,"");

		bool chooseBreak = true;

		while(chooseBreak)
		{
			//Decide whether you want the robot to break
			//after the auton step is completed
			TopString1 = "Break?";
			BotString1 = "Yes           No";
			if(nLCDButtons == 1)
			{
				while(nLCDButtons);
				aCBreakVal = true;
				chooseBreak = false;
				//Decide to break
			}
			if(nLCDButtons == 4)
			{
				while(nLCDButtons);
				aCBreakVal = false;
				chooseBreak = false;
				//Decide not to break
			}

			displayLCDCenteredString(0, TopString1);
			displayLCDCenteredString(1, BotString1);
		}

		wait10Msec(20);

		bool chooseStop = true;

		while(chooseStop)
		{
			//Decide whether or not you want to stop
			//the robot
			TopString1 = "Stop?";
			BotString1 = "Yes           No";
			if(nLCDButtons == 1)
			{
				while(nLCDButtons == 1);
				aCStopVal = true;
				chooseStop = false;
				//Decide to stop
			}
			if(nLCDButtons == 4)
			{
				while(nLCDButtons == 4);
				aCStopVal = false;
				chooseStop = false;
				//Decide not to stop
			}

			displayLCDCenteredString(0, TopString1);
			displayLCDCenteredString(1, BotString1);
		}


		wait10Msec(20);

		clearSensors();
		bool AutonStepRun = true;


		while(AutonStepRun)
		{
			//Run the auton step in order to make
			//sure that this is actually what you want
			//allowing you to go back and change it
			bool RUNAUTON = true;
			displayLCDCenteredString(0, "Press to Run");
			displayLCDCenteredString(1, "Auton Step");
			while(nLCDButtons == 0);
			while(nLCDButtons != 0);
			wait10Msec(20);

			if(RUNAUTON)
			{
				clearSensors();
				displayLCDCenteredString(0,"IF GOES AWRY");
				displayLCDCenteredString(1,"HIT BUTTON");
				while(shouldWeKeepGoingSen(aCSensorValue, aCFinalSensorValue))
				{
					//Actually run the auton step
					SetMotors(aCLeftSpeed, aCRightSpeed, aCArb1Speed, aCArb2Speed, aCArb3Speed, aCArb4Speed);
					if(nLCDButtons == 2)
					{
						while(nLCDButtons == 2);
						goto AUTONAWRY;
					}
				}
				if(aCBreakVal)
				{
					SetMotors(-aCLeftSpeed/2,-aCRightSpeed/2,0,0,0,0);
					wait10Msec(10);
				}
				if(aCStopVal) SetMotors(0,0,0,0,0,0);
				RUNAUTON = false;
				wait10Msec(10);
			AUTONAWRY:
				displayLCDCenteredString(0,"Run Again?");
				displayLCDCenteredString(1,"Yes           No");
				while(nLCDButtons != 1 && nLCDButtons != 4);
				if(nLCDButtons == 4)
				{
					//Decide whether you want to keep this current
					//auton step, or get rid of it entirely
					while(nLCDButtons == 4);
					AutonStepRun = false;
					wait10Msec(20);
					displayLCDCenteredString(0,"Satisfactory?");
					displayLCDCenteredString(1,"Yes           No");
					while(nLCDButtons != 1 && nLCDButtons != 4);


					if(nLCDButtons == 1)
					{
						//Write the auton step to the current
						//autonomous
						writeAuton = true;
						while(nLCDButtons == 1);
					}
					else
					{
						//Do not write the auton step to the
						//current autonomous
						writeAuton = false;
						while(nLCDButtons);
					}

					wait10Msec(20);

				}
				if(nLCDButtons == 1)
				{
					while(nLCDButtons == 1);
				}
				wait10Msec(20);
			}
		}

		if(writeAuton)
		{
			//write the auton step to either
			//the debugger stream or the HC-05 Chip,
			//depending on Global statements
			if(DebugStream)
			{
				writeDebugStream("f(%d,%d,%d,",aCLeftSpeed, aCArb1Speed, aCArb1Speed);
				writeDebugStream("%d,%d,%d,",aCRightSpeed,aCArb1Speed,aCArb1Speed);
				writeDebugStream("%d,%d,%d,",aCLeftSpeed,aCArb1Speed,aCArb1Speed);
				writeDebugStream("%d,%d",aCRightSpeed, aCArb2Speed);
				writeDebugStream("%d,%d,false);,",aCSensorValue, aCFinalSensorValue);
				if(aCBreakVal)
				{
					writeDebugStream("f(%d,%d,%d,",-aCLeftSpeed/2, 0, 0);
					writeDebugStream("%d,%d,%d,",-aCRightSpeed/2,0,0);
					writeDebugStream("%d,%d,%d,",-aCLeftSpeed/2,0,-aCLeftSpeed/2);
					writeDebugStream("%d,%d,",-aCRightSpeed/2, aCArb2Speed);
					writeDebugStream("%d,%d,false);,",3, 100);
				}
				if(aCStopVal)
				{
					writeDebugStream("f(0,0,0,");
					writeDebugStream("0,0,0,");
					writeDebugStream("0,0,0,");
					writeDebugStream("0,%d,", aCArb2Speed);
					writeDebugStream("%d,%d,false);,",3, 100);
				}

				writeDebugStreamLine(BlankSpace);
			}

			//DRIVE FLAG

			if(BNSBluetooth)
			{

				bnsDebugStream("f(%d,%d,%d,",aCLeftSpeed, aCArb1Speed, aCArb1Speed);
				bnsDebugStream("%d,%d,%d,",aCRightSpeed,aCArb1Speed,aCArb1Speed);
				bnsDebugStream("%d,%d,%d,",aCLeftSpeed,aCArb1Speed,aCArb1Speed);
				bnsDebugStream("%d,%d",aCRightSpeed, aCArb2Speed);
				bnsDebugStream("%d,%d,false);,",aCSensorValue, aCFinalSensorValue);
				if(aCBreakVal)
				{
					bnsDebugStream("f(%d,%d,%d,",-aCLeftSpeed/2, 0, 0);
					bnsDebugStream("%d,%d,%d,",-aCRightSpeed/2,0,0);
					bnsDebugStream("%d,%d,%d,",-aCLeftSpeed/2,0,-aCLeftSpeed/2);
					bnsDebugStream("%d,%d,",-aCRightSpeed/2, aCArb2Speed);
					bnsDebugStream("%d,%d,false);,",3, 100);
				}
				if(aCStopVal)
				{
					bnsDebugStream("f(0,0,0,");
					bnsDebugStream("0,0,0,");
					bnsDebugStream("0,0,0,");
					bnsDebugStream("0,%d,", aCArb2Speed);
					bnsDebugStream("%d,%d,false);,",3, 100);
				}

				bnsDebugStreamLine(BlankSpace);
			}

			if(aCBreakVal)
			{
				numberOfAutonSteps += 3;
			}
			else
			{
				numberOfAutonSteps += 2;
			}

			displayLCDCenteredString(0,"Is Auton Done?");
			displayLCDCenteredString(1,"Yes           No");
			//Decide whether or not you have finished the
			//autonomous program
			while(nLCDButtons != 1 && nLCDButtons != 4);
			if(nLCDButtons == 1)
			{
				while(nLCDButtons == 1);
				autonBeingCreated = false;
			}
			if(nLCDButtons == 4)
			{
				while(nLCDButtons == 4);
			}
		}

	}while(autonBeingCreated);

	numberOfAutonSteps++;
	//Write the final auton step, after
	//it has been created

	if(DebugStream)
	{
		writeDebugStream("f(0,0,0,");
		writeDebugStream("0,0,0,");
		writeDebugStream("0,0,0,");
		writeDebugStream("0},");
		writeDebugStream("%d,%d,true);",3, 100);

		writeDebugStreamLine(BlankSpace);
		writeDebugStreamLine(BlankSpace);
		writeDebugStreamLine("%d Auton Steps", numberOfAutonSteps);
	}

	if(BNSBluetooth)
	{
		bnsDebugStream("f(0,0,0,");
		bnsDebugStream("0,0,0,");
		bnsDebugStream("0,0,0,");
		bnsDebugStream("0},");
		bnsDebugStream("%d,%d,true);",3, 100);

		bnsDebugStreamLine(BlankSpace);
		bnsDebugStreamLine(BlankSpace);
		bnsDebugStreamLine("Auton Steps : %d", numberOfAutonSteps);
		//Write how many steps the auton contained
	}

	TopMenu = true;
}

void initializeSensors()
{
	//Initialize all relevant sensors
	//In this case, mainly the Gyro
	displayLCDCenteredString(0,"Initializing...");
	displayLCDCenteredString(1,"Do Not Move Robot");
	SensorType[gyroXY] = sensorNone;
	wait10Msec(100);

	SensorType[gyroXY] = sensorAnalog;
	gyroStart(gGyro, gyroXY);

	clearSensors();
	displayLCDCenteredString(0,"DONE!");
	TopMenu = true;
}

void switchDrivers()
{
	//Code to change the global
	//that tells the rest of the
	//code what driver is to be
	//used

	CaseValue = CaseValueFinder(100,2,CaseValue);

	if(CaseValue == 1)
	{
		TopString = "Spencer Drives";
		DriveMan = Spencer;
		//Click if you want to lock
		//Spencer in as the driver
	}
	if(CaseValue == 2)
	{
		TopString = "Noah Drives";
		DriveMan = Noah;
		//Click midle button if you want to
		//lock in Noah as the driver
	}
	BotString = "Lock Now";

	if(nLCDButtons != 0)
	{
		while(nLCDButtons != 0);
		TopMenu = true;
	}

}

void switchRecorder()
{

	//Function to be able to switch the amount
	//of time you are able to use RecorderLib
	//for, or to be able to switch autonomous
	//recording functions if we ever build
	//a different version of one

#ifdef __Recorder_Lib__

	CaseValue = CaseValueFinder(100,2,CaseValue);


	if(CaseValue == 1)
	{
		TopString = "Set Time";
		BotString = "Allowed";
		if(nLCDButtons == 2)
		{
			while(nLCDButtons == 2);
			wait10Msec(20);

			while(nLCDButtons != 2)
			{

				CaseValue2 = CaseValueFinder(100,2,CaseValue2);

				if(CaseValue2 == 1)
				{
					string Value1;
					sprintf(Value1,"%1.3f mS", stopperVal);
					displayLCDCenteredString(0,"Time Limit Set");
					displayLCDCenteredString(1,Value1);
					//Choose to set a time limit
				}
				if(CaseValue2 == 2)
				{
					displayLCDCenteredString(0,"No Time Limit");
					displayLCDCenteredString(1,"");
					//Decide not to choose a time limit
				}

			}
			if(CaseValue2 == 1)stopperBool = true;
			else if(CaseValue2 == 2)stopperBool = false;

			wait10Msec(20);

			while(nLCDButtons != 2 && stopperBool == true)
			{
#ifndef _Target_Emulator_
				if(SensorValue[autonSelector] < 0) SensorValue[autonSelector] = 0;

				string Value1;
				sprintf(Value1,"%1.3f mS", stopperVal);

				displayLCDCenteredString(0,"Time Limit");
				displayLCDCenteredString(1,Value1);
				stopperVal = SensorValue[autonSelector];
				//Set the max time for the RecorderLib using
				//the autonSelector sensor
#endif
			}
			wait10Msec(20);

			//CHANGE TIME LIMIT
		}
	}

	if(CaseValue == 2)
	{
		TopString = "Leave Menu";
		BotString = "";
	}

	if(nLCDButtons != 0 && CaseValue == 5)
	{
		while(nLCDButtons != 0);
		TopMenu = true;
	}


#endif

#ifndef __Recorder_Lib__

	displayLCDCenteredString(0, "VOID");
	displayLCDCenteredString(1, "VOID");

	wait10Msec(200);

	TopMenu = true;
	//If we are not using the RecorderLib
	//file, we will not be able to use
	//this function, and therefore, it
	//becomes void

#endif
}

void switchOutput()
{
	//Function to be able to switch between using
	//the HC-05 Bluetooth Chip as the generally
	//used output or the Debug Stream as that output

	CaseValue = CaseValueFinder(100,3,CaseValue);

	if(CaseValue == 1)
	{
		TopString = "DebugStream";
		//Decide if you want to use the debugStream
		if(DebugStream) BotString = "On";
		else if(!DebugStream) BotString = "Off";
		//Say on the LCD if you are using the debug
		//stream

		if(nLCDButtons == 2)
		{
			while(nLCDButtons == 2);
			if(DebugStream)
			{
				DebugStream = false;
			}
			else if(!DebugStream)
			{
				DebugStream = true;
			}
			//If you click the LCD, switch
			//whether or not you are using
			//the debugger stream
		}
	}
	if(CaseValue == 2)
	{
		TopString = "BNSBluetooth";
		//Choose if you want to use the HC-05
		//Bluetooth chip
		if(BNSBluetooth) BotString = "On";
		else if(!BNSBluetooth) BotString = "Off";

		if(nLCDButtons == 2)
		{
			while(nLCDButtons == 2);
			if(BNSBluetooth)
			{
				BNSBluetooth = false;
			}
			else if(!BNSBluetooth)
			{
				BNSBluetooth = true;
			}
			//If you click the middle button, switch
			//whether or not you are going to use
			//the HC-05 Chip
		}
	}

	if(CaseValue == 3)
	{
		TopString = "Leave Menu";
		BotString = "";
	}

	if(nLCDButtons != 0 && CaseValue == 3)
	{
		while(nLCDButtons != 0);
		TopMenu = true;
		//Leave Menu if you click this menu
	}

}

void restoreDefaults()
{
	//Restore globals to default value
	//Right now, solely concerned with
	//the driver
	displayLCDCenteredString(0,"Restoring.");
	wait10Msec(20);
	DriveMan = Spencer;
	displayLCDCenteredString(0,"Restoring..");
	wait10Msec(20);

	displayLCDCenteredString(0,"Restoring...");
	wait10Msec(20);
	displayLCDCenteredString(0,"Restoring.");
	wait10Msec(20);
	displayLCDCenteredString(0,"Restoring..");
	wait10Msec(20);
	displayLCDCenteredString(0,"Restoring...");
	wait10Msec(20);
	displayLCDCenteredString(0,"Restoring.");
	wait10Msec(20);
	displayLCDCenteredString(0,"Restoring..");
	wait10Msec(20);
	displayLCDCenteredString(0,"Restoring...");

	TopMenu = true;
}

void freezeMenu()
{
	//Function to work to get you out of
	//the LCD loop
	CaseValue = CaseValueFinder(100,2,CaseValue);

	switch(CaseValue)
	{
	case 1:
		TopString = "Hold to Freeze";
		BotString = "Here";
		if(nLCDButtons != 0)
		{
			time1[T4] = 0;
			while(nLCDButtons != 0)
			{
				if(time1[T4] > 2000)
				{
					displayLCDCenteredString(0, "FROZEN");
					displayLCDCenteredString(1, "REBOOT TO CHANGE");
					//If you hold a button for more than two seconds
					//you get out of the LCD Task
				}
				else
				{
					displayLCDCenteredString(0, "CONTINUE TO");
					displayLCDCenteredString(1, "HOLD TO FREEZE");
				}
			}
			if(time1[T4] < 2000) goto HERE;
			LCDMenuBool = false;
		HERE:
		}
		break;
	case 2:
		TopString = "Return";
		BotString = "To Main Menu";
		if(nLCDButtons != 0)
		{
			while(nLCDButtons != 0);
			TopMenu = true;
		}
		break;
	}
}
int topMenuSwitch = 1;
task LCDMenu ()
{
	//Actual LCD Task, organizes the rest of
	//the functions in this library

	bLCDBacklight = true;

	while(LCDMenuBool)
	{
		if(nLCDButtons == 5)
		{
			while(nLCDButtons == 5);
			TopMenu = false;
			topMenuSwitch = 5;
			//IF LEFT AND RIGHT BUTTONS ARE HIT AT THE SAME TIME, GO TO AUTON PICKER
		}

		if(TopMenu)
		{
#ifdef COMPETITION
			topMenuSwitch = CaseValueFinder(100,3,topMenuSwitch);
#endif
#ifdef DEBUG
			topMenuSwitch = CaseValueFinder(100,13,topMenuSwitch);
#endif

			//If we are running competition, we only want the first three functions
			//but for debugging, we want the first thirteen
			if(nLCDButtons == 2)
			{
				while(nLCDButtons == 2);
				TopMenu = false;
				//If you click the button, leave the "top"
				//menu, and go to the chosen lower menu
			}

			if(topMenuSwitch == 1) TopString = "Sensors Menu";
			if(topMenuSwitch == 2) TopString = "Motor Health";
			if(topMenuSwitch == 3) TopString = "Auton Select";
			if(topMenuSwitch == 4) TopString = "Robot Diagnostic";
			if(topMenuSwitch == 5) TopString = "Run Programs";
			if(topMenuSwitch == 6) TopString = "Var Manipuation";
			if(topMenuSwitch == 7) TopString = "Auton Creator";
			if(topMenuSwitch == 8) TopString = "Init Sensors";
			if(topMenuSwitch == 9) TopString = "Switch Driver";
			if(topMenuSwitch == 10) TopString = "Time For Record";
			if(topMenuSwitch == 11) TopString = "Switch Output";
			if(topMenuSwitch == 12) TopString = "Restore Defaults";
			if(topMenuSwitch == 13) TopString = "Freeze Menu";

			BotString = "Shamalam Menu";
		}
		else
		{
			switch(topMenuSwitch)
			{
				//Switch to run the function after you have
				//Pressed the LCD Button
			case 1:
				SensorsMenu(); //FINISHED
				break;
			case 2:
				motorHealth(); //FINISHED
				break;
			case 3:
				autonSelection(); //FINISHED
				break;
			case 4:
				robotDiagnostics(); //NOTHING ELSE NEEDED, ADD THINGS AS NEEDED
				break;
			case 5:
				runSpecifiedProgram(); //FINISHED
				break;
			case 6:
				liveVarChange();
				break;
			case 7:
				autonCreator(); //FINISHED
				break;
			case 8:
				initializeSensors(); //FINISHED
				break;
			case 9:
				switchDrivers();
				break;
			case 10:
				switchRecorder();
				break;
			case 11:
				switchOutput();
				break;
			case 12:
				restoreDefaults();
				break;
			case 13:
				freezeMenu(); //FINISHED
				break;
			}
		}

		if(!LCDMenuBool)
		{
			TopString = "FROZEN";
			BotString = "REBOOT TO CHANGE";
		}

#ifdef _Unstable_Auton_Lib_
		gyroUpdate(gGyro);
#endif

		displayLCDCenteredString(0, TopString);
		displayLCDCenteredString(1, BotString);
	}
}
/*----------------------------------------End of LCD Menu Library---------------------------------------*/
