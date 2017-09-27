/*-----------------------------------------------------------------------------------------------------------*/
/*                                                                                                           */
/*                                           William O'Brien                                                 */
/*                                             1200 - 2016                                                   */
/*                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------*/
/*                                                                                                           */
/*    Module:     HedderCheck.c                                                                              */
/*    Author:     William O'Brien                                                                            */
/*    Created:    21 December 2014                                                                           */
/*                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------*/
/*                                                                                                           */
/*    If anyone should have any questions about this code,                                                   */
/*    the author can be contacted on the Vex Forums as ShadowIQ                                              */
/*    Email: William.O'Brien@stmarycentral.org                                                               */
/*                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------*/



/*---------------------------------------1200C Function Library-------------------------------------------------
| Just a precursor, if you are only reading this to see what I have coded, only read the Function              |
| Library Headers. They discribe the majority of what that library was intended to do. If you want to see      |
| my documentation of the code as I am writing it, like a journal, read the journal near the bottom of         |
| the code. If you want to understand all of the code, though, read all the comments.                          |
|                                                                                                              |
| To any reader, who may read this code, I will try to make this code easier to read by constantly             |
| commenting, and mentioning what every piece of code, function, and sets of variables. However,               |
| if I have already mentioned a variable, I do not plan on mentioning it again,                                |
| and the reader should know what it is,since it was previously mentioned. This will be for documentation      |
| purposes. Hopefully, this will allow anyone to look throught this code and be able to use it properly.       |
--------------------------------------------------------------------------------------------------------------*/


/*----------------------------------------------Programmer's Notes----------------------------------------------
| //Drive Flag - Means that whenever drive code is changed, code here needs to be changed as well.             |
| //Sensor Flag - Means that whenever sensor code is changed, code here needs to be changed as well.           |
--------------------------------------------------------------------------------------------------------------*/

//#define DEBUG
//#define RECORD_ONLY
#define COMPETITION

//There are several different configurations
//we want our robot to be able to have - one
//specifically for debugging, one specifically
//for recording autonomous programs, and one
//specifically for competition. This is realized
//through the above macros, each representing an
//archetype, and when uncommented, that robot
//archetype will be used

#ifdef COMPETITION
#define bnsDebugStream writeDebugStream
#define bnsDebugStreamLine writeDebugStreamLine
#endif


#define __General_Lib__
//Always have the regular robot functions


#ifdef COMPETITION

//During competition, the only thing
//worthwhile to have at all are the LCD
//and the Auton Lib

#define __LCD_Lib__
#define __Auton_Lib__
#endif

//#define DEBUG_LCD_MENU
#define DEBUG_MIN_LCD_MENU
//#define FULL_LCD_MENU
//#define COMPETITION_LCD_MENU

#ifdef DEBUG

//If we are debugging, we want to work
//with all of our code, both to fix
//peices of our own code, and to find
//new ways that it can interact together

#define __LCD_Lib__
#define __BNSLIB_HC05_H__
#define __Auton_Lib__
#define __Recorder_Lib__
#define recorderString

#endif

#ifdef RECORD_ONLY

//If we are recording, we solely need the
//means for recording. In the future, this might
//require the Auton Lib depending on how the
//Recorder Lib morphs over time

#define __BNSLIB_HC05_H__
#define __Recorder_Lib__
#define recorderString
#define __Auton_Lib__
#endif

#ifdef __Recorder_Lib__

//If we are using the recorder lib, warn
//about the fact the joystick will go through
//a bitmap

#warning "JoyStick Will Be Bitmapped"
#endif

bool DebugStream = false; //Dumps Data into Debug Stream
bool BNSBluetooth = true; //Dumps Data into UART
bool jinX = false; //False until PROS Port

//Large include file, handling function
//prototypes and including the seperate
//libraries based on the macros above

#include "Vex_Competition_Includes.c"

#define NumberOfAutons  12

int autoValue = 1;
//Global Variable For Selecting Auton

string autoNameString[12] = {"R 1C 2S", "R 4S", "R 2S", "R 1C 4S", "R 1C 1S", "L 1C 2S", "L 4S", "L 2S", "L 1C 4S", "L 1C 1S", "Skills", "None"};
//String Names for Autons, in case we need them for the LCD Menu


string NameMotor1 = "Back Left Drive";
string NameMotor2 = "Lift 2";
string NameMotor3 = "Lift 3";
string NameMotor4 = "Front Right Drive";
string NameMotor5 = "Lift 5";
string NameMotor6 = "Lift 6";
string NameMotor7 = "Front Left Drive";
string NameMotor8 = "Lift 8";
string NameMotor9 = "Lift 9";
string NameMotor10 = "Back Left Drive";

typedef struct{
	float VtoDPS;
	int lastDif;
	int lastTime;
	float stdDev;
	float gAve;
	tSensors port;
	float rate;
	float angle;
} sGyro;

sGyro gGyro;

//typedef struct gyro{
//	float VtoDPS;
//	int lastDif;
//	int lastTime;
//	float stdDev;
//	float gAve;
//	tSensors port;
//	float rate;
//	float angle;
//} sGyro;

//String Definitions For Motor Names
//In case we need the names for the LCD

string BlankSpace = "";
string BlankLine = "\n";

//Variables just used for string addition

typedef enum _Driver{
	Spencer = 0,
	Noah = 1,
}Driver;
//Creates a variable that stores which
//Driver is currently driving


typedef enum _AutonSensor{
	SensorNon = 0,
	leftEncUp = 1,
	leftEncDown,
	time,
	rightEncUp,
	rightEncDown,
	gyroUp,
	gyroDown,
	leftLine,
	midLine,
	rightLine,
	sonarInc,
	sonarDec,
	liftPotUp,
	liftPotDown,
	clawEncUp,
	clawEncDown,
}AutonSensor;

//Creates a variable that is used
//for all the self writing auton
//programs to distinguish which sensor
//to use and in what direction to use it

typedef enum _Direction{
	Forward,
	Backward,
	LeftTurn,
	RightTurn,
	RightSweep,
	RightSweepBack,
	LeftSweep,
	LeftSweepBack,
	Custom,
}Direction;

//Whenever I make an encompassing autonomous
//function, having a Direction variable is
//always helpful for me overall to keep the code
//clean

Driver DriveMan = Spencer;

#ifdef DEBUG
#pragma debuggerWindows("DebugStream");
#pragma debuggerWindows("Motors");
#pragma debuggerWindows("Sensors");
#pragma debuggerWindows("VexLCD");
#pragma debuggerWindows("Globals");

//If we are debugging, pull up all the stuff for the
//debugging purposes for RobotC.

#endif

//Prototype Definitions For Functions so We can
//Use them everywhere in the library.

#ifdef __General_Lib__

bool shouldWeKeepGoingPE(int currentValue, int endValue);
bool shouldWeKeepGoingSen(AutonSensor SensorInfo, int FinalSensorValue);
void chassisDrive (int leftSpeed, int rightSpeed);
void SetMotors(int motorSpeed1, int motorSpeed2, int motorSpeed3, int motorSpeed4, int motorSpeed5, int motorSpeed6);
void clearSensors();
int MaxMinClip (int Max, int Min, int Value);
int MaxMinRpt (int Max, int Min, int Value);
void e(int joyCh1, int joyCh2, int joyCh3, int joyCh4, int joyButtons, AutonSensor SensorInfo = SensorNon, int FinalSensorValue = 0, bool playBack = false, int timeOut = 250);
void b(int Ch1Ch2Ch3Ch4, int joyButtons, AutonSensor SensorInfo = SensorNon, int FinalSensorValue = 0, bool playBack = false, int timeOut = 250);
signed char joyTestCh1 = 0;
signed char joyTestCh2 = 0;
signed char joyTestCh3 = 0;
signed char joyTestCh4 = 0;
float mSonar = 0;



#endif



#ifdef __LCD_Lib__

bool bControllerLCD = true;

#endif



#ifdef __Recorder_Lib__

typedef struct JoyStick{

	int Ch1Ch2Ch3Ch4;
	signed char Ch1R;
	signed char Ch2R;
	signed char Ch3R;
	signed char Ch4R;
	int Buttons;

}JS;

JS PreviousJS;
JS CurrentJS;

void GetJoystick();
void DecodeButtons(int Buttons);

bool stopperBool = false;
int stopperVal = 15000;

bool recordBool = false;
bool finalE3Bool = false;


void SensorValueDecode();
void ShamalamE3 (int buffer = 0, int n = 1, int pL = 3, Driver Driver = Spencer, bool condense = false, bool PID = false);

#endif


#ifdef __Auton_Lib__

void gyroStart(sGyro Gyro, tSensors port);
void gyroUpdate (int stdDev, sGyro gyro);
void a(int leftDrive, int rightDrive, int lift, bool claw, bool holding, int timeAllot);
void aR(int leftDrive, int rightDrive, int lift, bool claw, bool holding, int timeAllot, bool liftReset = true);

#endif

#ifdef __BNSLIB_HC05_H__

// ------------------------------------------------------------------------
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// The author can be contacted by email at jmarple@umass.edu
//
// ------------------------------------------------------------------------

/**
* Sends a string to a specified UART port.
* Optionally, the size parameter (if provided) specifies how much data
* to read from the data buffer. If not provided or -1, then data is read
* until a null byte
*
* Returns the amount of data read from the "data" buffer
*/
int bnsSerialSend(const TUARTs uart, const char* data, int size = (-1));

/**
* Reads data from the UART port into the buffer "data"
* Reads at most `stringSize` bytes, and will stop reading after
* `timeoutMilli` milliseconds without any new data.
*
* Returns the amount of bytes read into the buffer.
*/
int bnsSerialRead(const TUARTs uart, char* data, int stringSize, int timeoutMilli);

/**
* This function will send the "AT\r\n" command, looking for an "OK" back from the
* HC05 device.
*/
bool bnsATTestConnection(const TUARTs uart);

/**
* Asks and prints the version number to the HC05 device to the debug stream.
*/
bool bnsATGetVersion(const TUARTs uart);

/**
* Asks and prints the name of the HC05 device to the debug stream.
*/
bool bnsATGetName(const TUARTs uart);

/**
* Sets the name of the HC05 device.
*/
bool bnsATSetName(const TUARTs uart, const string name);

/**
* Asks and prints the uart baudrate of the HC05 device to the debug stream.
*/
bool bnsATGetBaudrate(const TUARTs uart);

/**
* Sets the baudrate of the HC05 device.
* Note: When parity = 0, no parity will be set.
*       When parity = 1, odd partiy will be set.
*       When parity = 2, even parity will be set.
*/
bool bnsATSetBaudrate(const TUARTs uart, int baudrate, int stopbits, int parity);

/**
* Sets the PIN of the HC05
*/
bool bnsATSetPIN(const TUARTs uart, int pin);

/**
* Sets the Password for the HC05
*/
bool bnsATSetPassword(const TUARTs uart, int pass);

#include "BNSlib_HC05.c"

#endif

#ifdef __General_Lib__
#include "GeneralLib.c"
#endif



#ifdef __LCD_Lib__

#include "LCDLib.c"

#endif



#ifdef __Recorder_Lib__
#include "RecorderLib.c"
#endif



#ifdef __Auton_Lib__
#include "AutonLib.c"
#endif
