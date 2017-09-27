typedef struct menu_s {

	menu_s *next;
	menu_s *prev;
	menu_s *up;
	menu_s *down;

	string top;
	string bot;

	int FuncVal;
	int update;

	//Struct for an LCD Menu in order
	//to store important data for the LCD
	//MLM, such as linking the menus above
	//below, and to the right and left of it
	//and stating what the LCD should say,
	//and an integer to define how to handle
	//function calls and updating the strings

}menu,*pMenu;

void initMenu(pMenu newMenu, pMenu nextMenu, pMenu prevMenu, pMenu downMenu, pMenu upMenu, char* topString, char* botString, int functionNumber,int update)
{
	string topBuffer = "";
	string lowBuffer = "";

	for(int a = 0; (a<strlen(topString)); a++)
	{
		strcat(topBuffer, (topString + a));
	}
	for(int a = 0; (a<strlen(botString)); a++)
	{
		strcat(lowBuffer, (botString + a));
	}

	//Handling the "strings" via char* because RobotC
	//can't handle putting "string" in as a variable,
	//so we just write it to a string

	newMenu->next = nextMenu;
	newMenu->prev = prevMenu;
	newMenu->up = upMenu;
	newMenu->down = downMenu;
	newMenu->top = topBuffer;
	newMenu->bot = lowBuffer;
	newMenu->FuncVal = functionNumber;
	newMenu->update = update;
	//Writes all the wanted data into the newMenu
	//struct through the pointer provided
}

int rapidScroll = 0;
int speed = 0;
//Variables to Scroll through numbers and speeds
//Speed Up and Down, while rapid scroll is left
//and write, speed is used for motor speed, while
//rapid scroll is used for creating and storing
//data values

bool LCD = true;
//Var for telling the while loop to keep running
// the LCD task, so we can eventually set it off

void setMenu(menu* changeMenu, menu changeToMenu)
{

	//Since RobotC isn't exactly the pinnacle of struct
	//accuracy, I thought this function might be nice to use
	//instead of simply writing the structs equal to each other
	//as well as to reset the rapidScroll var every time we switch
	//menus

	rapidScroll = 0;

	changeMenu->next = changeToMenu.next;
	changeMenu->prev = changeToMenu.prev;
	changeMenu->up = changeToMenu.up;
	changeMenu->down = changeToMenu.down;
	changeMenu->top = changeToMenu.top;
	changeMenu->bot = changeToMenu.bot;
	changeMenu->FuncVal = changeToMenu.FuncVal;
	changeMenu->update = changeToMenu.update;
}

//All Menus Associated With FInal MLM
//As well as All Globals Associated with
//This Final MLM

#ifdef FULL_LCD_MENU

menu sensorTop;
menu sensor1;
menu sensor2;
menu sensor3;
menu sensor4;
menu sensor5;
menu sensor6;

//Menus to See Sensors and their Values
//Battery, Both Encoders, Gyro, Potentiometer, and Ultrasonic

menu motorTop;
menu motor1;
menu motor2;
menu motor3;
menu motor4;
menu motor5;
menu motor6;
menu motor7;
menu motor8;
menu motor9;
menu motor10;
menu motor11;
menu motor12;
menu motor13;

//Menus to test run motors, as well as different drives
//Able to run individual motors based on the power of the
//Y Axis on the controller, as well as able to run individual
//sets of drives. If possible, possibly we will use it to test
//Different types of drives, such as an exponential drive or
//a TrueSpeed Drive

menu functionTop;
menu function1;
menu function2;

//Menus that allow us to run functions at the push of a button
//As of right now, we can test auton and run the self writing
//auton through this, but we can add more.

menu diagnosticsTop;
menu diagnostics1;
menu diagnostics2;
menu diagnostics3;
menu diagnostics4;
menu diagnostics5;

//Menu for the programmer to put testing code on, in order to
//better program the robot. As of now, we are using it to test
//Truespeed array values

menu autonTop;
menu auton1;
menu auton2;
menu auton3;
menu auton4;
menu auton5;
menu auton6;
menu auton7;
menu auton8;
menu auton9;
menu auton10;

//Initialize the menus for being able to switch
//between 10 seperate autonomous programs

menu totalVarChangeTop;
menu incrementTop;
menu incrementS1;
menu incrementS2;
menu incrementS3;
menu incrementS4;
menu incrementS5;
menu incrementS6;
float increment = 0;


menu varLiveTop;
menu varS1;
menu varS2;
menu varS3;
menu varS4;
menu varS5;

float PVar = 0;
float IVar = 0;
float DVar = 0;
float Var4 = 0;
float Var5 = 0;

//Variables and menus associated with being able to
//manipulate variables while the robot is on and not
//connected to the robot in order to be able to debug
//PID easier

menu autonCreatorTop;

menu speeds;
menu leftSpeedC;
menu rightSpeedC;
menu liftSpeedC;
menu clawSpeedC;
menu arb5Speed;
menu arb6Speed;

int leftSpeedCV = 0;
int rightSpeedCV = 0;
int liftSpeedCV = 0;
int clawSpeedCV = 0;
int arb5SpeedV = 0;
int arb6SpeedV = 0;

menu sensorC;
menu sensorC1;
menu sensorC2;
menu sensorC3;
menu sensorC4;
menu sensorC5;
menu sensorC6;
menu sensorC7;
menu sensorC8;
menu sensorC9;
menu sensorC10;
menu sensorC11;
menu sensorC12;
menu sensorC13;
menu sensorC14;

AutonSensor sensorToUse = SensorNon;
int finalSenVal = 0;

menu autonRun;
menu autonBreak;
menu autonBreakY;
bool isBreak = true;
menu autonStop;
menu autonStopY;
bool isStop = true;
menu autonWrite;

//Variables and Menus associated with creating a
//written autonomous through the LCD, by printing a
//created function, and setting the speeds, sensor, and
//final sensor variable to the LCD, and then printing it to
//the Debug Stream or HC-05 Chip

menu initSenTop;

//Menu for re-initializing sensors

menu driveTop;
menu driver1;
menu driver2;

//Menus used to switch between seperate drivers

menu recordTop;
menu recordTime;

//Menus used to alter seperate aspects of the self-writing
//autonomous, but right now, solely alters the max time
//allowed to record, which normally we have shut off anyways

menu outputTop;
menu output1;
menu output2;
menu output3;

//Menus used to switch the output of data from the robot
//for debugging, either to the HC-05 Bluetooth Chip or to
//the standard Debug Stream

menu restoreTop;

//Menu that when pressed restores the robot's
//default settings

menu freezeTop;
menu freezer;

//Menu that when activated shuts off the LCD Screen
//so it cannot be used for the rest of the match

menu driveMenu;
//Menu to be displayed while we are driving

#endif

#ifdef COMPETITION_LCD_MENU


menu sensorTop;
menu sensor1;
menu sensor2;
menu sensor3;
menu sensor4;
menu sensor5;
menu sensor6;

//Menus to See Sensors and their Values
//Battery, Both Encoders, Gyro, Potentiometer, and Ultrasonic

menu motorTop;
menu motor1;
menu motor2;
menu motor3;
menu motor4;
menu motor5;
menu motor6;
menu motor7;
menu motor8;
menu motor9;
menu motor10;
menu motor11;
menu motor12;
menu motor13;

//Menus to test run motors, as well as different drives
//Able to run individual motors based on the power of the
//Y Axis on the controller, as well as able to run individual
//sets of drives. If possible, possibly we will use it to test
//Different types of drives, such as an exponential drive or
//a TrueSpeed Drive

menu autonTop;
menu auton1;
menu auton2;
menu auton3;
menu auton4;
menu auton5;
menu auton6;
menu auton7;
menu auton8;
menu auton9;
menu auton10;

//Initialize the menus for being able to switch
//between 10 seperate autonomous programs

int increment = 1;
float PVar = 0;
float IVar = 0;
float DVar = 0;
float Var4 = 0;
float Var5 = 0;

//Variables and menus associated with being able to
//manipulate variables while the robot is on and not
//connected to the robot in order to be able to debug
//PID easier

int leftSpeedCV = 0;
int rightSpeedCV = 0;
int liftSpeedCV = 0;
int clawSpeedCV = 0;
int arb5SpeedV = 0;
int arb6SpeedV = 0;

AutonSensor sensorToUse = SensorNon;
int finalSenVal = 0;

bool isBreak = true;

bool isStop = true;

//Variables and Menus associated with creating a
//written autonomous through the LCD, by printing a
//created function, and setting the speeds, sensor, and
//final sensor variable to the LCD, and then printing it to
//the Debug Stream or HC-05 Chip

menu initSenTop;

//Menu for re-initializing sensors

menu driveTop;
menu driver1;
menu driver2;

//Menus used to switch between seperate drivers

menu restoreTop;

//Menu that when pressed restores the robot's
//default settings

menu freezeTop;
menu freezer;

//Menu that when activated shuts off the LCD Screen
//so it cannot be used for the rest of the match

menu driveMenu;
//Menu to be displayed while we are driving

#endif


#ifdef DEBUG_MIN_LCD_MENU


menu sensorTop;
menu sensor1;
menu sensor2;
menu sensor3;
menu sensor4;
menu sensor5;
menu sensor6;

//Menus to See Sensors and their Values
//Battery, Both Encoders, Gyro, Potentiometer, and Ultrasonic

menu motorTop;
menu motor1;
menu motor2;
menu motor3;
menu motor4;
menu motor5;
menu motor6;
menu motor7;
menu motor8;
menu motor9;
menu motor10;
menu motor11;
menu motor12;
menu motor13;

//Menus to test run motors, as well as different drives
//Able to run individual motors based on the power of the
//Y Axis on the controller, as well as able to run individual
//sets of drives. If possible, possibly we will use it to test
//Different types of drives, such as an exponential drive or
//a TrueSpeed Drive

menu totalVarChangeTop;
menu incrementTop;
menu incrementS1;
menu incrementS2;
menu incrementS3;
menu incrementS4;
menu incrementS5;
menu incrementS6;
float increment = 0;


menu varLiveTop;
menu varS1;
menu varS2;
menu varS3;
menu varS4;
menu varS5;

float PVar = 0;
float IVar = 0;
float DVar = 0;
float Var4 = 0;
float Var5 = 0;

//Variables and menus associated with being able to
//manipulate variables while the robot is on and not
//connected to the robot in order to be able to debug
//PID easier

menu autonCreatorTop;

menu speeds;
menu leftSpeedC;
menu rightSpeedC;
menu liftSpeedC;
menu clawSpeedC;
menu arb5Speed;
menu arb6Speed;

int leftSpeedCV = 0;
int rightSpeedCV = 0;
int liftSpeedCV = 0;
int clawSpeedCV = 0;
int arb5SpeedV = 0;
int arb6SpeedV = 0;

menu sensorC;
menu sensorC1;
menu sensorC2;
menu sensorC3;
menu sensorC4;
menu sensorC5;
menu sensorC6;
menu sensorC7;
menu sensorC8;
menu sensorC9;
menu sensorC10;
menu sensorC11;
menu sensorC12;
menu sensorC13;
menu sensorC14;

AutonSensor sensorToUse = SensorNon;
int finalSenVal = 0;

menu autonRun;
menu autonBreak;
menu autonBreakY;
bool isBreak = true;
menu autonStop;
menu autonStopY;
bool isStop = true;
menu autonWrite;

//Variables and Menus associated with creating a
//written autonomous through the LCD, by printing a
//created function, and setting the speeds, sensor, and
//final sensor variable to the LCD, and then printing it to
//the Debug Stream or HC-05 Chip

menu initSenTop;

//Menu for re-initializing sensors

#endif

#ifdef DEBUG_LCD_MENU


menu sensorTop;
menu sensor1;
menu sensor2;
menu sensor3;
menu sensor4;
menu sensor5;
menu sensor6;

//Menus to See Sensors and their Values
//Battery, Both Encoders, Gyro, Potentiometer, and Ultrasonic

menu motorTop;
menu motor1;
menu motor2;
menu motor3;
menu motor4;
menu motor5;
menu motor6;
menu motor7;
menu motor8;
menu motor9;
menu motor10;
menu motor11;
menu motor12;
menu motor13;

//Menus to test run motors, as well as different drives
//Able to run individual motors based on the power of the
//Y Axis on the controller, as well as able to run individual
//sets of drives. If possible, possibly we will use it to test
//Different types of drives, such as an exponential drive or
//a TrueSpeed Drive

menu functionTop;
menu function1;
menu function2;

//Menus that allow us to run functions at the push of a button
//As of right now, we can test auton and run the self writing
//auton through this, but we can add more.

menu diagnosticsTop;
menu diagnostics1;
menu diagnostics2;
menu diagnostics3;
menu diagnostics4;
menu diagnostics5;

//Menu for the programmer to put testing code on, in order to
//better program the robot. As of now, we are using it to test
//Truespeed array values

menu autonTop;
menu auton1;
menu auton2;
menu auton3;
menu auton4;
menu auton5;
menu auton6;
menu auton7;
menu auton8;
menu auton9;
menu auton10;

//Initialize the menus for being able to switch
//between 10 seperate autonomous programs

menu totalVarChangeTop;
menu incrementTop;
menu incrementS1;
menu incrementS2;
menu incrementS3;
menu incrementS4;
menu incrementS5;
menu incrementS6;
float increment = 0;


menu varLiveTop;
menu varS1;
menu varS2;
menu varS3;
menu varS4;
menu varS5;

float PVar = 0;
float IVar = 0;
float DVar = 0;
float Var4 = 0;
float Var5 = 0;

//Variables and menus associated with being able to
//manipulate variables while the robot is on and not
//connected to the robot in order to be able to debug
//PID easier

menu autonCreatorTop;

menu speeds;
menu leftSpeedC;
menu rightSpeedC;
menu liftSpeedC;
menu clawSpeedC;
menu arb5Speed;
menu arb6Speed;

int leftSpeedCV = 0;
int rightSpeedCV = 0;
int liftSpeedCV = 0;
int clawSpeedCV = 0;
int arb5SpeedV = 0;
int arb6SpeedV = 0;

menu sensorC;
menu sensorC1;
menu sensorC2;
menu sensorC3;
menu sensorC4;
menu sensorC5;
menu sensorC6;
menu sensorC7;
menu sensorC8;
menu sensorC9;
menu sensorC10;
menu sensorC11;
menu sensorC12;
menu sensorC13;
menu sensorC14;

AutonSensor sensorToUse = SensorNon;
int finalSenVal = 0;

menu autonRun;
menu autonBreak;
menu autonBreakY;
bool isBreak = true;
menu autonStop;
menu autonStopY;
bool isStop = true;
menu autonWrite;

//Variables and Menus associated with creating a
//written autonomous through the LCD, by printing a
//created function, and setting the speeds, sensor, and
//final sensor variable to the LCD, and then printing it to
//the Debug Stream or HC-05 Chip

menu initSenTop;

//Menu for re-initializing sensors

menu recordTop;
menu recordTime;

//Menus used to alter seperate aspects of the self-writing
//autonomous, but right now, solely alters the max time
//allowed to record, which normally we have shut off anyways

menu outputTop;
menu output1;
menu output2;
menu output3;

//Menus used to switch the output of data from the robot
//for debugging, either to the HC-05 Bluetooth Chip or to
//the standard Debug Stream

menu restoreTop;

//Menu that when pressed restores the robot's
//default settings

menu freezeTop;
menu freezer;

//Menu that when activated shuts off the LCD Screen
//so it cannot be used for the rest of the match

#endif


void initAllMenus()
{

	//initMenu(pMenu newMenu, pMenu nextMenu, pMenu prevMenu, pMenu downMenu, pMenu upMenu, string topString, string botString, int functionNumber,int update)

#ifdef FULL_LCD_MENU

	initMenu(&sensorTop, &motorTop, &freezeTop, &sensor1, (NULL), "Sensor Values", "Shamalam Menu", (-1), (-1)); //menu sensorTop;
		initMenu(&sensor1, &sensor2, &sensor6, (NULL), &sensorTop, "Main: Sec:", "Backup:", (-1), (1));//menu sensor1;
		initMenu(&sensor2, &sensor3, &sensor1, (NULL), &sensorTop, "Gyro Value", "", (-1), (2));//menu sensor2;
		initMenu(&sensor3, &sensor4, &sensor2, (NULL), &sensorTop, "Left Enc Value", "", (-1), (3));//menu sensor3;
		initMenu(&sensor4, &sensor5, &sensor3, (NULL), &sensorTop, "Right Enc Value", "", (-1), (4));//menu sensor4;
		initMenu(&sensor5, &sensor6, &sensor4, (NULL), &sensorTop, "Pot Value", "", (-1), (5));//menu sensor5;
		initMenu(&sensor6, &sensor1, &sensor5, (NULL), &sensorTop, "Ultra Value", "", (-1), (6));//menu sensor6;

		//Initialize Sensor Menus and the Strings Associated With them

	initMenu(&motorTop, &functionTop, &sensorTop, &motor1, (NULL), "Drive Motors", "Shamalam Menu", (-1), (-1));//menu motorTop;
		initMenu(&motor1, &motor2, &motor13, (NULL), &motorTop, "Port 1", "Speed = ", (-1), (7));//menu motor1;
		initMenu(&motor2, &motor3, &motor1, (NULL), &motorTop, "Port 2", "Speed = ", (-1), (8));//menu motor2;
		initMenu(&motor3, &motor4, &motor2, (NULL), &motorTop, "Port 3", "Speed = ", (-1), (9));//menu motor3;
		initMenu(&motor4, &motor5, &motor3, (NULL), &motorTop, "Port 4", "Speed = ", (-1), (10));//menu motor4;
		initMenu(&motor5, &motor6, &motor4, (NULL), &motorTop, "Port 5", "Speed = ", (-1), (11));//menu motor5;
		initMenu(&motor6, &motor7, &motor5, (NULL), &motorTop, "Port 6", "Speed = ", (-1), (12));//menu motor6;
		initMenu(&motor7, &motor8, &motor6, (NULL), &motorTop, "Port 7", "Speed = ", (-1), (13));//menu motor7;
		initMenu(&motor8, &motor9, &motor7, (NULL), &motorTop, "Port 8", "Speed = ", (-1), (14));//menu motor8;
		initMenu(&motor9, &motor10, &motor8, (NULL), &motorTop, "Port 9", "Speed = ", (-1), (15));//menu motor9;
		initMenu(&motor10, &motor11, &motor9, (NULL), &motorTop, "Port 10", "Speed = ", (-1), (16));//menu motor10;
		initMenu(&motor11, &motor12, &motor10, (NULL), &motorTop, "Drive", "Speed = ", (-1), (17));//menu motor11;
		initMenu(&motor12, &motor13, &motor11, (NULL), &motorTop, "Lift", "Speed = ", (-1), (18));//menu motor12;
		initMenu(&motor13, &motor1, &motor12, (NULL), &motorTop, "Claw", "Speed = ", (-1), (19));//menu motor13;

		//Initialize Motor Menus and the Associated Strings with them

	initMenu(&functionTop, &diagnosticsTop, &motorTop, &function1, (NULL), "Function Select", "Shamalam Menu", (-1), (-1));//menu functionTop;
		initMenu(&function1, &function2, &function2, (NULL), &functionTop, "Run Auton", "Press to Start", (1), (-1));	//menu function1;
		initMenu(&function2, &function1, &function1, (NULL), &functionTop, "Run Self", "Writing Auton", (2), (-1));	//menu function2;

		//Initialize Function Menus and their associated strings

	initMenu(&diagnosticsTop, &autonTop, &functionTop, &diagnostics1, (NULL), "Diagnostic Select", "Shamalam Menu", (-1), (-1));//menu diagnosticsTop;
		initMenu(&diagnostics1, &diagnostics2, &diagnostics5, (NULL), &diagnosticsTop, "True Speed Test", "Part 1", (3), (-1));//menu diagnostics1;
		initMenu(&diagnostics2, &diagnostics3, &diagnostics1, (NULL), &diagnosticsTop, "True Speed Test", "Part 2", (4), (-1));//menu diagnostics2;
		initMenu(&diagnostics3, &diagnostics4, &diagnostics2, (NULL), &diagnosticsTop, "True Speed Test", "Part 3", (5), (-1));//menu diagnostics3;
		initMenu(&diagnostics4, &diagnostics5, &diagnostics3, (NULL), &diagnosticsTop, "True Speed Test", "Part 4", (6), (-1));//menu diagnostics4;
		initMenu(&diagnostics5, &diagnostics1, &diagnostics4, (NULL), &diagnosticsTop, "True Speed Test", "Part 5", (7), (-1));//menu diagnostics5;

		//Initialize Diagnostic Menus and their associated strings

	initMenu(&autonTop, &totalVarChangeTop, &diagnosticsTop, &auton1, (NULL), "Auton Select", "Shamalam Menu", (-1), (-1));//menu autonTop;
		initMenu(&auton1, &auton2, &auton10, (NULL), &autonTop, "Auton 1", "Choose Auton", (8), (-1));//menu auton1;
		initMenu(&auton2, &auton3, &auton1, (NULL), &autonTop, "Auton 2", "Choose Auton", (9), (-1));//menu auton2;
		initMenu(&auton3, &auton4, &auton2, (NULL), &autonTop, "Auton 3", "Choose Auton", (10), (-1));//menu auton3;
		initMenu(&auton4, &auton5, &auton3, (NULL), &autonTop, "Auton 4", "Choose Auton", (11), (-1));//menu auton4;
		initMenu(&auton5, &auton6, &auton4, (NULL), &autonTop, "Auton 5", "Choose Auton", (12), (-1));//menu auton5;
		initMenu(&auton6, &auton7, &auton5, (NULL), &autonTop, "Auton 6", "Choose Auton", (13), (-1));//menu auton6;
		initMenu(&auton7, &auton8, &auton6, (NULL), &autonTop, "Auton 7", "Choose Auton", (14), (-1));//menu auton7;
		initMenu(&auton8, &auton9, &auton7, (NULL), &autonTop, "Auton 8", "Choose Auton", (15), (-1));//menu auton8;
		initMenu(&auton9, &auton10, &auton8, (NULL), &autonTop, "Prog Skills 1", "Choose Auton", (16), (-1));//menu auton9;
		initMenu(&auton10, &auton1, &auton9, (NULL), &autonTop, "Prog Skills 2", "Choose Auton", (17), (-1));//menu auton10;

		//Initialize Menus to choose our auton for the competition or for programming skills

	initMenu(&totalVarChangeTop, &autonCreatorTop, &autonTop, &incrementTop, (NULL), "Live Var Change", "Shamalam Menu", (-1), (-1));//menu autonCreatorTop;

		initMenu(&incrementTop, &varLiveTop, &varLiveTop, &incrementS1, &totalVarChangeTop, "Increment Select", "Shamalam Menu", (-1), (-1));//menu incrementTop;
			initMenu(&incrementS1, &incrementS2, &incrementS6, (NULL), &incrementTop, "1", "True/False", (57), (55));//menu incrementS1;
			initMenu(&incrementS2, &incrementS3, &incrementS1, (NULL), &incrementTop, "10", "True/False", (58), (56));//menu incrementS2;
			initMenu(&incrementS3, &incrementS4, &incrementS2, (NULL), &incrementTop, "100", "True/False", (59), (57));//menu incrementS3;
			initMenu(&incrementS4, &incrementS5, &incrementS3, (NULL), &incrementTop, ".1", "True/False", (60), (58));//menu incrementS4;
			initMenu(&incrementS5, &incrementS6, &incrementS4, (NULL), &incrementTop, ".01", "True/False", (61), (59));//menu incrementS5;
			initMenu(&incrementS6, &incrementS1, &incrementS5, (NULL), &incrementTop, ".001", "True/False", (62), (60));//menu incrementS6;

		initMenu(&varLiveTop, &incrementTop, &incrementTop, &varS1, &totalVarChangeTop, "Variable Manip", "Shamalam Menu", (-1), (-1));//menu varLiveTop;
			initMenu(&varS1, &varS2, &varS5, (NULL), &varLiveTop, "P Var", "VALUE", (52), (50));//menu varS1; SAMPLE P
			initMenu(&varS2, &varS3, &varS1, (NULL), &varLiveTop, "I Var", "VALUE", (53), (51));//menu varS2; SAMPLE I
			initMenu(&varS3, &varS4, &varS2, (NULL), &varLiveTop, "D Var", "VALUE", (54), (52));//menu varS3; SAMPLE D
			initMenu(&varS4, &varS5, &varS3, (NULL), &varLiveTop, "4th Var", "VALUE", (55), (53));//menu varS4;
			initMenu(&varS5, &varS1, &varS4, (NULL), &varLiveTop, "5th Val", "VALUE", (56), (54));//menu varS5;

			//Initialize Menus to be able to manipulate variables for more effective debugging overall

	initMenu(&autonCreatorTop, &initSenTop, &totalVarChangeTop, &speeds, (NULL), "Auton Creator", "Shamalam Menu", (-1), (-1));//menu autonCreatorTop

		initMenu(&speeds, &sensorC, &autonWrite, &leftSpeedC, &autonCreatorTop, "Speed Manip", "Shamalam Menu", (-1), (-1));//menu speeds;
			initMenu(&leftSpeedC, &rightSpeedC, &arb6Speed, (NULL), &speeds, "LeftSpeed", "VALUE", (46), (44));//menu leftSpeedC;
			initMenu(&rightSpeedC, &liftSpeedC, &leftSpeedC, (NULL), &speeds, "RightSpeed", "VALUE", (47), (45));//menu rightSpeedC;
			initMenu(&liftSpeedC, &clawSpeedC, &rightSpeedC, (NULL), &speeds, "LiftSpeed", "VALUE", (48), (46));//menu liftSpeedC;
			initMenu(&clawSpeedC, &arb5Speed, &liftSpeedC, (NULL), &speeds, "ClawSpeed", "VALUE", (49), (47));//menu clawSpeedC;
			initMenu(&arb5Speed, &arb6Speed, &clawSpeedC, (NULL), &speeds, "arb1Speed", "VALUE", (50), (48));//menu arb5Speed;
			initMenu(&arb6Speed, &leftSpeedC, &arb5Speed, (NULL), &speeds, "arb2Speed", "VALUE", (51), (49));//menu arb6Speed;

		initMenu(&sensorC, &autonBreak, &autonWrite, &leftSpeedC, &autonCreatorTop, "Sensor Manip", "Shamalam Menu", (-1), (-1));//menu sensorC;
			initMenu(&sensorC1, &sensorC2, &sensorC14, (NULL), &sensorC, "LeftEncUp", "True/False VALUE", (34), (32));//menu sensorC1;
			initMenu(&sensorC2, &sensorC3, &sensorC1, (NULL), &sensorC, "LeftEncDown", "True/False VALUE", (35), (33));//menu sensorC2;
			initMenu(&sensorC3, &sensorC4, &sensorC2, (NULL), &sensorC, "Time", "True/False VALUE", (36), (34));//menu sensorC3;
			initMenu(&sensorC4, &sensorC5, &sensorC3, (NULL), &sensorC, "RightEncUp", "True/False VALUE", (37), (35));//menu sensorC4;
			initMenu(&sensorC5, &sensorC6, &sensorC4, (NULL), &sensorC, "RightEncDown", "True/False VALUE", (38), (36));//menu sensorC5;
			initMenu(&sensorC6, &sensorC7, &sensorC5, (NULL), &sensorC, "gyroUp", "True/False VALUE", (39), (37));//menu sensorC6;
			initMenu(&sensorC7, &sensorC8, &sensorC6, (NULL), &sensorC, "gyroDown", "True/False VALUE", (40), (38));//menu sensorC7;
			initMenu(&sensorC8, &sensorC9, &sensorC7, (NULL), &sensorC, "leftLine", "True/False VALUE", (41), (39));//menu sensorC8;
			initMenu(&sensorC9, &sensorC10, &sensorC8, (NULL), &sensorC, "midLine", "True/False VALUE", (42), (40));//menu sensorC9;
			initMenu(&sensorC10, &sensorC11, &sensorC9, (NULL), &sensorC, "rightLine", "True/False VALUE", (43), (41));//menu sensorC10;
			initMenu(&sensorC11, &sensorC12, &sensorC10, (NULL), &sensorC, "SonarInc", "True/False VALUE", (44), (42));//menu sensorC11;
			initMenu(&sensorC12, &sensorC13, &sensorC11, (NULL), &sensorC, "SonarDown", "True/False VALUE", (45), (43));//menu sensorC12;
			initMenu(&sensorC13, &sensorC14, &sensorC12, (NULL), &sensorC, "Pot Up", "True/False VALUE", (63), (62));//menu sensorC13;
			initMenu(&sensorC14, &sensorC1, &sensorC13, (NULL), &sensorC, "Pot Down", "True/False VALUE", (64), (63));//menu sensorC14;


		initMenu(&autonBreak, &autonStop, &sensorC, &autonBreakY, &autonCreatorTop, "Auton Break?", "Click to Choose", (-1), (-1));//menu autonBreak;
			initMenu(&autonBreakY, &autonBreakY, &autonBreakY, (NULL), &autonBreak, "Auton Break", "True/False", (32), (30));//menu autonBreakY;

		initMenu(&autonStop, &autonRun, &autonBreak, &autonStopY, &autonCreatorTop, "Auton Stop?", "Click to Choose", (-1), (-1));//menu autonStop;
			initMenu(&autonStopY, &autonStopY, &autonStopY, (NULL), &autonStop, "Auton Stop", "True/False", (30), (28));//menu autonStopY;

		initMenu(&autonRun, &autonWrite, &autonStop, (NULL), &autonCreatorTop, "Run Auton", "Step", (19), (-1));//menu autonRun;
		initMenu(&autonWrite, &speeds, &autonRun, (NULL), &autonCreatorTop, "Write Auton", "Step", (20), (-1));//menu autonWrite;

		//Initialize Menus in order to create an auton via the LCD Menu by setting values, and when satisfied by running the steps
		//printing it to the designated output

	initMenu(&initSenTop, &driveTop, &autonCreatorTop, (NULL), (NULL), "Init Sensors", "Shamalam Menu", (21), (20));//menu initSenTop

	//Initialize Menu used to reinitialize Sensors

	initMenu(&driveTop, &recordTop, &driveTop, &driver1, (NULL), "Choose Drivers", "Shamalam Menu", (-1), (-1));//menu driveTop;
		initMenu(&driver1, &driver2, &driver2, (NULL), &driveTop, "Spencer Driving", "True/False", (28), (26));//menu driver1;
		initMenu(&driver2, &driver1, &driver1, (NULL), &driveTop, "Noah Driving", "True/False", (29), (27));//menu driver2;

	//Initialize Menu used to switch drivers in between matches during competition

	initMenu(&recordTop, &outputTop, &driveTop, &recordTime, (NULL), "Change Rec Time", "Shamalam Menu", (-1), (-1));//menu recordTop;
		initMenu(&recordTime, &recordTime, &recordTime, (NULL), &recordTop, "Time to Record", "____ mS", (27), (25));//menu recordTime;

	//Initialize menus to switch details associated with the self-writing auton, now used for time, however, if we come up with a seperate
	//function, we will be able to switch between those.

	initMenu(&outputTop, &restoreTop, &recordTop, &output1, (NULL), "Output Switch", "Shamalam Menu", (-1), (-1));//menu outputTop;
		initMenu(&output1, &output2, &output3, (NULL), &outputTop, "HC-05", "True/False", (24), (22));//menu output1;
		initMenu(&output2, &output3, &output1, (NULL), &outputTop, "Serial Stream", "True/False", (25), (23));//menu output2;
		initMenu(&output3, &output1, &output2, (NULL), &outputTop, "jinX", "True/False", (26), (24));//menu output3

		//Initialize Menus used to designate which output we are using for our data while we are debugging.

	initMenu(&restoreTop, &freezeTop, &outputTop, (NULL), (NULL), "Restore Defaults", "Shamalam Menu", (22), (21));//menu restoreTop;

	//Initialize the menu used to reset defaults within the original robot

	initMenu(&freezeTop, &sensorTop, &restoreTop, &freezer, (NULL), "Freeze Menu", "Shamalam Menu", (-1), (-1));//menu freezeTop;
		initMenu(&freezer, &freezer, &freezer, (NULL), (NULL), "Are You Sure?", "Exit", (23), (-1));//menu freezer;

		//Initialize the menu used to stop the LCD Menu Entirely so we can switch it off when we want to

	initMenu(&driveMenu, (NULL), (NULL), (NULL), (NULL), "1200C", "Shamalamalamalam", (-1), (-1));//menu driveMenu;

	//Initialize Menu used while we are driving
#endif

#ifdef COMPETITION_LCD_MENU

	initMenu(&sensorTop, &motorTop, &freezeTop, &sensor1, (NULL), "Sensor Values", "Shamalam Menu", (-1), (-1)); //menu sensorTop;
		initMenu(&sensor1, &sensor2, &sensor6, (NULL), &sensorTop, "Main: Sec:", "Backup:", (-1), (1));//menu sensor1;
		initMenu(&sensor2, &sensor3, &sensor1, (NULL), &sensorTop, "Gyro Value", "", (-1), (2));//menu sensor2;
		initMenu(&sensor3, &sensor4, &sensor2, (NULL), &sensorTop, "Left Enc Value", "", (-1), (3));//menu sensor3;
		initMenu(&sensor4, &sensor5, &sensor3, (NULL), &sensorTop, "Right Enc Value", "", (-1), (4));//menu sensor4;
		initMenu(&sensor5, &sensor6, &sensor4, (NULL), &sensorTop, "Pot Value", "", (-1), (5));//menu sensor5;
		initMenu(&sensor6, &sensor1, &sensor5, (NULL), &sensorTop, "Ultra Value", "", (-1), (6));//menu sensor6;

		//Initialize Sensor Menus and the Strings Associated With them

	initMenu(&motorTop, &autonTop, &sensorTop, &motor1, (NULL), "Drive Motors", "Shamalam Menu", (-1), (-1));//menu motorTop;
		initMenu(&motor1, &motor2, &motor13, (NULL), &motorTop, "Port 1", "Speed = ", (-1), (7));//menu motor1;
		initMenu(&motor2, &motor3, &motor1, (NULL), &motorTop, "Port 2", "Speed = ", (-1), (8));//menu motor2;
		initMenu(&motor3, &motor4, &motor2, (NULL), &motorTop, "Port 3", "Speed = ", (-1), (9));//menu motor3;
		initMenu(&motor4, &motor5, &motor3, (NULL), &motorTop, "Port 4", "Speed = ", (-1), (10));//menu motor4;
		initMenu(&motor5, &motor6, &motor4, (NULL), &motorTop, "Port 5", "Speed = ", (-1), (11));//menu motor5;
		initMenu(&motor6, &motor7, &motor5, (NULL), &motorTop, "Port 6", "Speed = ", (-1), (12));//menu motor6;
		initMenu(&motor7, &motor8, &motor6, (NULL), &motorTop, "Port 7", "Speed = ", (-1), (13));//menu motor7;
		initMenu(&motor8, &motor9, &motor7, (NULL), &motorTop, "Port 8", "Speed = ", (-1), (14));//menu motor8;
		initMenu(&motor9, &motor10, &motor8, (NULL), &motorTop, "Port 9", "Speed = ", (-1), (15));//menu motor9;
		initMenu(&motor10, &motor11, &motor9, (NULL), &motorTop, "Port 10", "Speed = ", (-1), (16));//menu motor10;
		initMenu(&motor11, &motor12, &motor10, (NULL), &motorTop, "Drive", "Speed = ", (-1), (17));//menu motor11;
		initMenu(&motor12, &motor13, &motor11, (NULL), &motorTop, "Lift", "Speed = ", (-1), (18));//menu motor12;
		initMenu(&motor13, &motor1, &motor12, (NULL), &motorTop, "Claw", "Speed = ", (-1), (19));//menu motor13;

		//Initialize Motor Menus and the Associated Strings with them

	initMenu(&autonTop, &initSenTop, &motorTop, &auton1, (NULL), "Auton Select", "Shamalam Menu", (-1), (-1));//menu autonTop;
		initMenu(&auton1, &auton2, &auton10, (NULL), &autonTop, "Auton 1", "Choose Auton", (8), (-1));//menu auton1;
		initMenu(&auton2, &auton3, &auton1, (NULL), &autonTop, "Auton 2", "Choose Auton", (9), (-1));//menu auton2;
		initMenu(&auton3, &auton4, &auton2, (NULL), &autonTop, "Auton 3", "Choose Auton", (10), (-1));//menu auton3;
		initMenu(&auton4, &auton5, &auton3, (NULL), &autonTop, "Auton 4", "Choose Auton", (11), (-1));//menu auton4;
		initMenu(&auton5, &auton6, &auton4, (NULL), &autonTop, "Auton 5", "Choose Auton", (12), (-1));//menu auton5;
		initMenu(&auton6, &auton7, &auton5, (NULL), &autonTop, "Auton 6", "Choose Auton", (13), (-1));//menu auton6;
		initMenu(&auton7, &auton8, &auton6, (NULL), &autonTop, "Auton 7", "Choose Auton", (14), (-1));//menu auton7;
		initMenu(&auton8, &auton9, &auton7, (NULL), &autonTop, "Auton 8", "Choose Auton", (15), (-1));//menu auton8;
		initMenu(&auton9, &auton10, &auton8, (NULL), &autonTop, "Prog Skills 1", "Choose Auton", (16), (-1));//menu auton9;
		initMenu(&auton10, &auton1, &auton9, (NULL), &autonTop, "Prog Skills 2", "Choose Auton", (17), (-1));//menu auton10;

		//Initialize Menus to choose our auton for the competition or for programming skills
	initMenu(&initSenTop, &driveTop, &autonTop, (NULL), (NULL), "Init Sensors", "Shamalam Menu", (21), (20));//menu initSenTop

	//Initialize Menu used to reinitialize Sensors

	initMenu(&driveTop, &restoreTop, &driveTop, &driver1, (NULL), "Choose Drivers", "Shamalam Menu", (-1), (-1));//menu driveTop;
		initMenu(&driver1, &driver2, &driver2, (NULL), &driveTop, "Spencer Driving", "True/False", (28), (26));//menu driver1;
		initMenu(&driver2, &driver1, &driver1, (NULL), &driveTop, "Noah Driving", "True/False", (29), (27));//menu driver2;

	//Initialize Menu used to switch drivers in between matches during competition

	initMenu(&restoreTop, &freezeTop, &driveTop, (NULL), (NULL), "Restore Defaults", "Shamalam Menu", (22), (21));//menu restoreTop;

	//Initialize the menu used to reset defaults within the original robot

	initMenu(&freezeTop, &sensorTop, &restoreTop, &freezer, (NULL), "Freeze Menu", "Shamalam Menu", (-1), (-1));//menu freezeTop;
		initMenu(&freezer, &freezer, &freezer, (NULL), (NULL), "Are You Sure?", "Exit", (23), (-1));//menu freezer;

		//Initialize the menu used to stop the LCD Menu Entirely so we can switch it off when we want to

	initMenu(&driveMenu, (NULL), (NULL), (NULL), (NULL), "1200C", "Shamalamalamalam", (-1), (-1));//menu driveMenu;

	//Initialize Menu used while we are driving

#endif

#ifdef DEBUG_MIN_LCD_MENU

	initMenu(&sensorTop, &motorTop, &initSenTop, &sensor1, (NULL), "Sensor Values", "Shamalam Menu", (-1), (-1)); //menu sensorTop;
		initMenu(&sensor1, &sensor2, &sensor6, (NULL), &sensorTop, "Main: Sec:", "Backup:", (-1), (1));//menu sensor1;
		initMenu(&sensor2, &sensor3, &sensor1, (NULL), &sensorTop, "Gyro Value", "", (-1), (2));//menu sensor2;
		initMenu(&sensor3, &sensor4, &sensor2, (NULL), &sensorTop, "Left Enc Value", "", (-1), (3));//menu sensor3;
		initMenu(&sensor4, &sensor5, &sensor3, (NULL), &sensorTop, "Right Enc Value", "", (-1), (4));//menu sensor4;
		initMenu(&sensor5, &sensor6, &sensor4, (NULL), &sensorTop, "Pot Value", "", (-1), (5));//menu sensor5;
		initMenu(&sensor6, &sensor1, &sensor5, (NULL), &sensorTop, "Ultra Value", "", (-1), (6));//menu sensor6;

		//Initialize Sensor Menus and the Strings Associated With them

	initMenu(&motorTop, &totalVarChangeTop, &sensorTop, &motor1, (NULL), "Drive Motors", "Shamalam Menu", (-1), (-1));//menu motorTop;
		initMenu(&motor1, &motor2, &motor13, (NULL), &motorTop, "Port 1", "Speed = ", (-1), (7));//menu motor1;
		initMenu(&motor2, &motor3, &motor1, (NULL), &motorTop, "Port 2", "Speed = ", (-1), (8));//menu motor2;
		initMenu(&motor3, &motor4, &motor2, (NULL), &motorTop, "Port 3", "Speed = ", (-1), (9));//menu motor3;
		initMenu(&motor4, &motor5, &motor3, (NULL), &motorTop, "Port 4", "Speed = ", (-1), (10));//menu motor4;
		initMenu(&motor5, &motor6, &motor4, (NULL), &motorTop, "Port 5", "Speed = ", (-1), (11));//menu motor5;
		initMenu(&motor6, &motor7, &motor5, (NULL), &motorTop, "Port 6", "Speed = ", (-1), (12));//menu motor6;
		initMenu(&motor7, &motor8, &motor6, (NULL), &motorTop, "Port 7", "Speed = ", (-1), (13));//menu motor7;
		initMenu(&motor8, &motor9, &motor7, (NULL), &motorTop, "Port 8", "Speed = ", (-1), (14));//menu motor8;
		initMenu(&motor9, &motor10, &motor8, (NULL), &motorTop, "Port 9", "Speed = ", (-1), (15));//menu motor9;
		initMenu(&motor10, &motor11, &motor9, (NULL), &motorTop, "Port 10", "Speed = ", (-1), (16));//menu motor10;
		initMenu(&motor11, &motor12, &motor10, (NULL), &motorTop, "Drive", "Speed = ", (-1), (17));//menu motor11;
		initMenu(&motor12, &motor13, &motor11, (NULL), &motorTop, "Lift", "Speed = ", (-1), (18));//menu motor12;
		initMenu(&motor13, &motor1, &motor12, (NULL), &motorTop, "Claw", "Speed = ", (-1), (19));//menu motor13;

		//Initialize Motor Menus and the Associated Strings with them

	initMenu(&totalVarChangeTop, &autonCreatorTop, &motorTop, &incrementTop, (NULL), "Live Var Change", "Shamalam Menu", (-1), (-1));//menu autonCreatorTop;

		initMenu(&incrementTop, &varLiveTop, &varLiveTop, &incrementS1, &totalVarChangeTop, "Increment Select", "Shamalam Menu", (-1), (-1));//menu incrementTop;
			initMenu(&incrementS1, &incrementS2, &incrementS6, (NULL), &incrementTop, "1", "True/False", (57), (55));//menu incrementS1;
			initMenu(&incrementS2, &incrementS3, &incrementS1, (NULL), &incrementTop, "10", "True/False", (58), (56));//menu incrementS2;
			initMenu(&incrementS3, &incrementS4, &incrementS2, (NULL), &incrementTop, "100", "True/False", (59), (57));//menu incrementS3;
			initMenu(&incrementS4, &incrementS5, &incrementS3, (NULL), &incrementTop, ".1", "True/False", (60), (58));//menu incrementS4;
			initMenu(&incrementS5, &incrementS6, &incrementS4, (NULL), &incrementTop, ".01", "True/False", (61), (59));//menu incrementS5;
			initMenu(&incrementS6, &incrementS1, &incrementS5, (NULL), &incrementTop, ".001", "True/False", (62), (60));//menu incrementS6;

		initMenu(&varLiveTop, &incrementTop, &incrementTop, &varS1, &totalVarChangeTop, "Variable Manip", "Shamalam Menu", (-1), (-1));//menu varLiveTop;
			initMenu(&varS1, &varS2, &varS5, (NULL), &varLiveTop, "P Var", "VALUE", (52), (50));//menu varS1; SAMPLE P
			initMenu(&varS2, &varS3, &varS1, (NULL), &varLiveTop, "I Var", "VALUE", (53), (51));//menu varS2; SAMPLE I
			initMenu(&varS3, &varS4, &varS2, (NULL), &varLiveTop, "D Var", "VALUE", (54), (52));//menu varS3; SAMPLE D
			initMenu(&varS4, &varS5, &varS3, (NULL), &varLiveTop, "4th Var", "VALUE", (55), (53));//menu varS4;
			initMenu(&varS5, &varS1, &varS4, (NULL), &varLiveTop, "5th Val", "VALUE", (56), (54));//menu varS5;

			//Initialize Menus to be able to manipulate variables for more effective debugging overall

	initMenu(&autonCreatorTop, &initSenTop, &totalVarChangeTop, &speeds, (NULL), "Auton Creator", "Shamalam Menu", (-1), (-1));//menu autonCreatorTop

		initMenu(&speeds, &sensorC, &autonWrite, &leftSpeedC, &autonCreatorTop, "Speed Manip", "Shamalam Menu", (-1), (-1));//menu speeds;
			initMenu(&leftSpeedC, &rightSpeedC, &arb6Speed, (NULL), &speeds, "LeftSpeed", "VALUE", (46), (44));//menu leftSpeedC;
			initMenu(&rightSpeedC, &liftSpeedC, &leftSpeedC, (NULL), &speeds, "RightSpeed", "VALUE", (47), (45));//menu rightSpeedC;
			initMenu(&liftSpeedC, &clawSpeedC, &rightSpeedC, (NULL), &speeds, "LiftSpeed", "VALUE", (48), (46));//menu liftSpeedC;
			initMenu(&clawSpeedC, &arb5Speed, &liftSpeedC, (NULL), &speeds, "ClawSpeed", "VALUE", (49), (47));//menu clawSpeedC;
			initMenu(&arb5Speed, &arb6Speed, &clawSpeedC, (NULL), &speeds, "arb1Speed", "VALUE", (50), (48));//menu arb5Speed;
			initMenu(&arb6Speed, &leftSpeedC, &arb5Speed, (NULL), &speeds, "arb2Speed", "VALUE", (51), (49));//menu arb6Speed;

		initMenu(&sensorC, &autonBreak, &autonWrite, &leftSpeedC, &autonCreatorTop, "Sensor Manip", "Shamalam Menu", (-1), (-1));//menu sensorC;
			initMenu(&sensorC1, &sensorC2, &sensorC14, (NULL), &sensorC, "LeftEncUp", "True/False VALUE", (34), (32));//menu sensorC1;
			initMenu(&sensorC2, &sensorC3, &sensorC1, (NULL), &sensorC, "LeftEncDown", "True/False VALUE", (35), (33));//menu sensorC2;
			initMenu(&sensorC3, &sensorC4, &sensorC2, (NULL), &sensorC, "Time", "True/False VALUE", (36), (34));//menu sensorC3;
			initMenu(&sensorC4, &sensorC5, &sensorC3, (NULL), &sensorC, "RightEncUp", "True/False VALUE", (37), (35));//menu sensorC4;
			initMenu(&sensorC5, &sensorC6, &sensorC4, (NULL), &sensorC, "RightEncDown", "True/False VALUE", (38), (36));//menu sensorC5;
			initMenu(&sensorC6, &sensorC7, &sensorC5, (NULL), &sensorC, "gyroUp", "True/False VALUE", (39), (37));//menu sensorC6;
			initMenu(&sensorC7, &sensorC8, &sensorC6, (NULL), &sensorC, "gyroDown", "True/False VALUE", (40), (38));//menu sensorC7;
			initMenu(&sensorC8, &sensorC9, &sensorC7, (NULL), &sensorC, "leftLine", "True/False VALUE", (41), (39));//menu sensorC8;
			initMenu(&sensorC9, &sensorC10, &sensorC8, (NULL), &sensorC, "midLine", "True/False VALUE", (42), (40));//menu sensorC9;
			initMenu(&sensorC10, &sensorC11, &sensorC9, (NULL), &sensorC, "rightLine", "True/False VALUE", (43), (41));//menu sensorC10;
			initMenu(&sensorC11, &sensorC12, &sensorC10, (NULL), &sensorC, "SonarInc", "True/False VALUE", (44), (42));//menu sensorC11;
			initMenu(&sensorC12, &sensorC13, &sensorC11, (NULL), &sensorC, "SonarDown", "True/False VALUE", (45), (43));//menu sensorC12;
			initMenu(&sensorC13, &sensorC14, &sensorC12, (NULL), &sensorC, "Pot Up", "True/False VALUE", (63), (62));//menu sensorC13;
			initMenu(&sensorC14, &sensorC1, &sensorC13, (NULL), &sensorC, "Pot Down", "True/False VALUE", (64), (63));//menu sensorC14;

		initMenu(&autonBreak, &autonStop, &sensorC, &autonBreakY, &autonCreatorTop, "Auton Break?", "Click to Choose", (-1), (-1));//menu autonBreak;
			initMenu(&autonBreakY, &autonBreakY, &autonBreakY, (NULL), &autonBreak, "Auton Break", "True/False", (32), (30));//menu autonBreakY;

		initMenu(&autonStop, &autonRun, &autonBreak, &autonStopY, &autonCreatorTop, "Auton Stop?", "Click to Choose", (-1), (-1));//menu autonStop;
			initMenu(&autonStopY, &autonStopY, &autonStopY, (NULL), &autonStop, "Auton Stop", "True/False", (30), (28));//menu autonStopY;

		initMenu(&autonRun, &autonWrite, &autonStop, (NULL), &autonCreatorTop, "Run Auton", "Step", (19), (-1));//menu autonRun;
		initMenu(&autonWrite, &speeds, &autonRun, (NULL), &autonCreatorTop, "Write Auton", "Step", (20), (-1));//menu autonWrite;

		//Initialize Menus in order to create an auton via the LCD Menu by setting values, and when satisfied by running the steps
		//printing it to the designated output

	initMenu(&initSenTop, &sensorTop, &autonCreatorTop, (NULL), (NULL), "Init Sensors", "Shamalam Menu", (21), (20));//menu initSenTop

	//Initialize Menu used to reinitialize Sensors

#endif

#ifdef DEBUG_LCD_MENU

	initMenu(&sensorTop, &motorTop, &freezeTop, &sensor1, (NULL), "Sensor Values", "Shamalam Menu", (-1), (-1)); //menu sensorTop;
		initMenu(&sensor1, &sensor2, &sensor6, (NULL), &sensorTop, "Main: Sec:", "Backup:", (-1), (1));//menu sensor1;
		initMenu(&sensor2, &sensor3, &sensor1, (NULL), &sensorTop, "Gyro Value", "", (-1), (2));//menu sensor2;
		initMenu(&sensor3, &sensor4, &sensor2, (NULL), &sensorTop, "Left Enc Value", "", (-1), (3));//menu sensor3;
		initMenu(&sensor4, &sensor5, &sensor3, (NULL), &sensorTop, "Right Enc Value", "", (-1), (4));//menu sensor4;
		initMenu(&sensor5, &sensor6, &sensor4, (NULL), &sensorTop, "Pot Value", "", (-1), (5));//menu sensor5;
		initMenu(&sensor6, &sensor1, &sensor5, (NULL), &sensorTop, "Ultra Value", "", (-1), (6));//menu sensor6;

		//Initialize Sensor Menus and the Strings Associated With them

	initMenu(&motorTop, &functionTop, &sensorTop, &motor1, (NULL), "Drive Motors", "Shamalam Menu", (-1), (-1));//menu motorTop;
		initMenu(&motor1, &motor2, &motor13, (NULL), &motorTop, "Port 1", "Speed = ", (-1), (7));//menu motor1;
		initMenu(&motor2, &motor3, &motor1, (NULL), &motorTop, "Port 2", "Speed = ", (-1), (8));//menu motor2;
		initMenu(&motor3, &motor4, &motor2, (NULL), &motorTop, "Port 3", "Speed = ", (-1), (9));//menu motor3;
		initMenu(&motor4, &motor5, &motor3, (NULL), &motorTop, "Port 4", "Speed = ", (-1), (10));//menu motor4;
		initMenu(&motor5, &motor6, &motor4, (NULL), &motorTop, "Port 5", "Speed = ", (-1), (11));//menu motor5;
		initMenu(&motor6, &motor7, &motor5, (NULL), &motorTop, "Port 6", "Speed = ", (-1), (12));//menu motor6;
		initMenu(&motor7, &motor8, &motor6, (NULL), &motorTop, "Port 7", "Speed = ", (-1), (13));//menu motor7;
		initMenu(&motor8, &motor9, &motor7, (NULL), &motorTop, "Port 8", "Speed = ", (-1), (14));//menu motor8;
		initMenu(&motor9, &motor10, &motor8, (NULL), &motorTop, "Port 9", "Speed = ", (-1), (15));//menu motor9;
		initMenu(&motor10, &motor11, &motor9, (NULL), &motorTop, "Port 10", "Speed = ", (-1), (16));//menu motor10;
		initMenu(&motor11, &motor12, &motor10, (NULL), &motorTop, "Drive", "Speed = ", (-1), (17));//menu motor11;
		initMenu(&motor12, &motor13, &motor11, (NULL), &motorTop, "Lift", "Speed = ", (-1), (18));//menu motor12;
		initMenu(&motor13, &motor1, &motor12, (NULL), &motorTop, "Claw", "Speed = ", (-1), (19));//menu motor13;

		//Initialize Motor Menus and the Associated Strings with them

	initMenu(&functionTop, &diagnosticsTop, &motorTop, &function1, (NULL), "Function Select", "Shamalam Menu", (-1), (-1));//menu functionTop;
		initMenu(&function1, &function2, &function2, (NULL), &functionTop, "Run Auton", "Press to Start", (1), (-1));	//menu function1;
		initMenu(&function2, &function1, &function1, (NULL), &functionTop, "Run Self", "Writing Auton", (2), (-1));	//menu function2;

		//Initialize Function Menus and their associated strings

	initMenu(&diagnosticsTop, &autonTop, &functionTop, &diagnostics1, (NULL), "Diagnostic Select", "Shamalam Menu", (-1), (-1));//menu diagnosticsTop;
		initMenu(&diagnostics1, &diagnostics2, &diagnostics5, (NULL), &diagnosticsTop, "True Speed Test", "Part 1", (3), (-1));//menu diagnostics1;
		initMenu(&diagnostics2, &diagnostics3, &diagnostics1, (NULL), &diagnosticsTop, "True Speed Test", "Part 2", (4), (-1));//menu diagnostics2;
		initMenu(&diagnostics3, &diagnostics4, &diagnostics2, (NULL), &diagnosticsTop, "True Speed Test", "Part 3", (5), (-1));//menu diagnostics3;
		initMenu(&diagnostics4, &diagnostics5, &diagnostics3, (NULL), &diagnosticsTop, "True Speed Test", "Part 4", (6), (-1));//menu diagnostics4;
		initMenu(&diagnostics5, &diagnostics1, &diagnostics4, (NULL), &diagnosticsTop, "True Speed Test", "Part 5", (7), (-1));//menu diagnostics5;

		//Initialize Diagnostic Menus and their associated strings

	initMenu(&autonTop, &totalVarChangeTop, &diagnosticsTop, &auton1, (NULL), "Auton Select", "Shamalam Menu", (-1), (-1));//menu autonTop;
		initMenu(&auton1, &auton2, &auton10, (NULL), &autonTop, "Auton 1", "Choose Auton", (8), (-1));//menu auton1;
		initMenu(&auton2, &auton3, &auton1, (NULL), &autonTop, "Auton 2", "Choose Auton", (9), (-1));//menu auton2;
		initMenu(&auton3, &auton4, &auton2, (NULL), &autonTop, "Auton 3", "Choose Auton", (10), (-1));//menu auton3;
		initMenu(&auton4, &auton5, &auton3, (NULL), &autonTop, "Auton 4", "Choose Auton", (11), (-1));//menu auton4;
		initMenu(&auton5, &auton6, &auton4, (NULL), &autonTop, "Auton 5", "Choose Auton", (12), (-1));//menu auton5;
		initMenu(&auton6, &auton7, &auton5, (NULL), &autonTop, "Auton 6", "Choose Auton", (13), (-1));//menu auton6;
		initMenu(&auton7, &auton8, &auton6, (NULL), &autonTop, "Auton 7", "Choose Auton", (14), (-1));//menu auton7;
		initMenu(&auton8, &auton9, &auton7, (NULL), &autonTop, "Auton 8", "Choose Auton", (15), (-1));//menu auton8;
		initMenu(&auton9, &auton10, &auton8, (NULL), &autonTop, "Prog Skills 1", "Choose Auton", (16), (-1));//menu auton9;
		initMenu(&auton10, &auton1, &auton9, (NULL), &autonTop, "Prog Skills 2", "Choose Auton", (17), (-1));//menu auton10;

		//Initialize Menus to choose our auton for the competition or for programming skills

	initMenu(&totalVarChangeTop, &autonCreatorTop, &motorTop, &incrementTop, (NULL), "Live Var Change", "Shamalam Menu", (-1), (-1));//menu autonCreatorTop;

		initMenu(&incrementTop, &varLiveTop, &varLiveTop, &incrementS1, &totalVarChangeTop, "Increment Select", "Shamalam Menu", (-1), (-1));//menu incrementTop;
			initMenu(&incrementS1, &incrementS2, &incrementS6, (NULL), &incrementTop, "1", "True/False", (57), (55));//menu incrementS1;
			initMenu(&incrementS2, &incrementS3, &incrementS1, (NULL), &incrementTop, "10", "True/False", (58), (56));//menu incrementS2;
			initMenu(&incrementS3, &incrementS4, &incrementS2, (NULL), &incrementTop, "100", "True/False", (59), (57));//menu incrementS3;
			initMenu(&incrementS4, &incrementS5, &incrementS3, (NULL), &incrementTop, ".1", "True/False", (60), (58));//menu incrementS4;
			initMenu(&incrementS5, &incrementS6, &incrementS4, (NULL), &incrementTop, ".01", "True/False", (61), (59));//menu incrementS5;
			initMenu(&incrementS6, &incrementS1, &incrementS5, (NULL), &incrementTop, ".001", "True/False", (62), (60));//menu incrementS6;

		initMenu(&varLiveTop, &incrementTop, &incrementTop, &varS1, &totalVarChangeTop, "Variable Manip", "Shamalam Menu", (-1), (-1));//menu varLiveTop;
			initMenu(&varS1, &varS2, &varS5, (NULL), &varLiveTop, "P Var", "VALUE", (52), (50));//menu varS1; SAMPLE P
			initMenu(&varS2, &varS3, &varS1, (NULL), &varLiveTop, "I Var", "VALUE", (53), (51));//menu varS2; SAMPLE I
			initMenu(&varS3, &varS4, &varS2, (NULL), &varLiveTop, "D Var", "VALUE", (54), (52));//menu varS3; SAMPLE D
			initMenu(&varS4, &varS5, &varS3, (NULL), &varLiveTop, "4th Var", "VALUE", (55), (53));//menu varS4;
			initMenu(&varS5, &varS1, &varS4, (NULL), &varLiveTop, "5th Val", "VALUE", (56), (54));//menu varS5;

			//Initialize Menus to be able to manipulate variables for more effective debugging overall

	initMenu(&autonCreatorTop, &initSenTop, &totalVarChangeTop, &speeds, (NULL), "Auton Creator", "Shamalam Menu", (-1), (-1));//menu autonCreatorTop

		initMenu(&speeds, &sensorC, &autonWrite, &leftSpeedC, &autonCreatorTop, "Speed Manip", "Shamalam Menu", (-1), (-1));//menu speeds;
			initMenu(&leftSpeedC, &rightSpeedC, &arb6Speed, (NULL), &speeds, "LeftSpeed", "VALUE", (46), (44));//menu leftSpeedC;
			initMenu(&rightSpeedC, &liftSpeedC, &leftSpeedC, (NULL), &speeds, "RightSpeed", "VALUE", (47), (45));//menu rightSpeedC;
			initMenu(&liftSpeedC, &clawSpeedC, &rightSpeedC, (NULL), &speeds, "LiftSpeed", "VALUE", (48), (46));//menu liftSpeedC;
			initMenu(&clawSpeedC, &arb5Speed, &liftSpeedC, (NULL), &speeds, "ClawSpeed", "VALUE", (49), (47));//menu clawSpeedC;
			initMenu(&arb5Speed, &arb6Speed, &clawSpeedC, (NULL), &speeds, "arb1Speed", "VALUE", (50), (48));//menu arb5Speed;
			initMenu(&arb6Speed, &leftSpeedC, &arb5Speed, (NULL), &speeds, "arb2Speed", "VALUE", (51), (49));//menu arb6Speed;

		initMenu(&sensorC, &autonBreak, &autonWrite, &leftSpeedC, &autonCreatorTop, "Sensor Manip", "Shamalam Menu", (-1), (-1));//menu sensorC;
			initMenu(&sensorC1, &sensorC2, &sensorC14, (NULL), &sensorC, "LeftEncUp", "True/False VALUE", (34), (32));//menu sensorC1;
			initMenu(&sensorC2, &sensorC3, &sensorC1, (NULL), &sensorC, "LeftEncDown", "True/False VALUE", (35), (33));//menu sensorC2;
			initMenu(&sensorC3, &sensorC4, &sensorC2, (NULL), &sensorC, "Time", "True/False VALUE", (36), (34));//menu sensorC3;
			initMenu(&sensorC4, &sensorC5, &sensorC3, (NULL), &sensorC, "RightEncUp", "True/False VALUE", (37), (35));//menu sensorC4;
			initMenu(&sensorC5, &sensorC6, &sensorC4, (NULL), &sensorC, "RightEncDown", "True/False VALUE", (38), (36));//menu sensorC5;
			initMenu(&sensorC6, &sensorC7, &sensorC5, (NULL), &sensorC, "gyroUp", "True/False VALUE", (39), (37));//menu sensorC6;
			initMenu(&sensorC7, &sensorC8, &sensorC6, (NULL), &sensorC, "gyroDown", "True/False VALUE", (40), (38));//menu sensorC7;
			initMenu(&sensorC8, &sensorC9, &sensorC7, (NULL), &sensorC, "leftLine", "True/False VALUE", (41), (39));//menu sensorC8;
			initMenu(&sensorC9, &sensorC10, &sensorC8, (NULL), &sensorC, "midLine", "True/False VALUE", (42), (40));//menu sensorC9;
			initMenu(&sensorC10, &sensorC11, &sensorC9, (NULL), &sensorC, "rightLine", "True/False VALUE", (43), (41));//menu sensorC10;
			initMenu(&sensorC11, &sensorC12, &sensorC10, (NULL), &sensorC, "SonarInc", "True/False VALUE", (44), (42));//menu sensorC11;
			initMenu(&sensorC12, &sensorC13, &sensorC11, (NULL), &sensorC, "SonarDown", "True/False VALUE", (45), (43));//menu sensorC12;
			initMenu(&sensorC13, &sensorC14, &sensorC12, (NULL), &sensorC, "Pot Up", "True/False VALUE", (63), (62));//menu sensorC13;
			initMenu(&sensorC14, &sensorC1, &sensorC13, (NULL), &sensorC, "Pot Down", "True/False VALUE", (64), (63));//menu sensorC14;

		initMenu(&autonBreak, &autonStop, &sensorC, &autonBreakY, &autonCreatorTop, "Auton Break?", "Click to Choose", (-1), (-1));//menu autonBreak;
			initMenu(&autonBreakY, &autonBreakY, &autonBreakY, (NULL), &autonBreak, "Auton Break", "True/False", (32), (30));//menu autonBreakY;

		initMenu(&autonStop, &autonRun, &autonBreak, &autonStopY, &autonCreatorTop, "Auton Stop?", "Click to Choose", (-1), (-1));//menu autonStop;
			initMenu(&autonStopY, &autonStopY, &autonStopY, (NULL), &autonStop, "Auton Stop", "True/False", (30), (28));//menu autonStopY;

		initMenu(&autonRun, &autonWrite, &autonStop, (NULL), &autonCreatorTop, "Run Auton", "Step", (19), (-1));//menu autonRun;
		initMenu(&autonWrite, &speeds, &autonRun, (NULL), &autonCreatorTop, "Write Auton", "Step", (20), (-1));//menu autonWrite;

		//Initialize Menus in order to create an auton via the LCD Menu by setting values, and when satisfied by running the steps
		//printing it to the designated output

	initMenu(&initSenTop, &recordTop, &autonCreatorTop, (NULL), (NULL), "Init Sensors", "Shamalam Menu", (21), (20));//menu initSenTop

	//Initialize Menu used to reinitialize Sensors

	initMenu(&recordTop, &outputTop, &initSenTop, &recordTime, (NULL), "Change Rec Time", "Shamalam Menu", (-1), (-1));//menu recordTop;
		initMenu(&recordTime, &recordTime, &recordTime, (NULL), &recordTop, "Time to Record", "____ mS", (27), (25));//menu recordTime;

	//Initialize menus to switch details associated with the self-writing auton, now used for time, however, if we come up with a seperate
	//function, we will be able to switch between those.

	initMenu(&outputTop, &restoreTop, &recordTop, &output1, (NULL), "Output Switch", "Shamalam Menu", (-1), (-1));//menu outputTop;
		initMenu(&output1, &output2, &output3, (NULL), &outputTop, "HC-05", "True/False", (24), (22));//menu output1;
		initMenu(&output2, &output3, &output1, (NULL), &outputTop, "Serial Stream", "True/False", (25), (23));//menu output2;
		initMenu(&output3, &output1, &output2, (NULL), &outputTop, "jinX", "True/False", (26), (24));//menu output3

		//Initialize Menus used to designate which output we are using for our data while we are debugging.

	initMenu(&restoreTop, &freezeTop, &outputTop, (NULL), (NULL), "Restore Defaults", "Shamalam Menu", (22), (21));//menu restoreTop;

	//Initialize the menu used to reset defaults within the original robot

	initMenu(&freezeTop, &sensorTop, &restoreTop, &freezer, (NULL), "Freeze Menu", "Shamalam Menu", (-1), (-1));//menu freezeTop;
		initMenu(&freezer, &freezer, &freezer, (NULL), (NULL), "Are You Sure?", "Exit", (23), (-1));//menu freezer;

		//Initialize the menu used to stop the LCD Menu Entirely so we can switch it off when we want to
#endif



}

void updateMessages(pMenu menu)
{
	if(time1[T4] > 250)
	{
		//Limit the rate of the rapid-scroller so
		//it does not become too rapid, both through
		//the /6 modifier and that it only adds onto
		//the entire variable four times a second.
		clearTimer(T4);
		rapidScroll =+ vexRT[Ch1]/6;
	}
	speed = vexRT[Ch3];
	if(abs(speed) < 15) speed = 0;
	//Create a deadzone, so when we are in the motor testing
	//the motors don't go off willy nilly

	//Set Variables for Manipulating Data in the LCD Screen
	//When appropriate

	switch(menu->update)
	{
	case 1:
	//When the Appropriate menu is up, Display all the battery voltages
		sprintf(menu->top, "Main:%.2f Back:%.2f", (nAvgBatteryLevel/1000), (BackupBatteryLevel/1000));
		sprintf(menu->bot, "Second: %.2f", SensorValue[Battery]/280);
		break;
	case 2:
	//When the appropriate menu is up, display the gyro value
		sprintf(menu->bot, "%.2f", SensorValue[gyroXY]);
		break;
	case 3:
	//When the appropriate menu is up, display the left encoder value
		sprintf(menu->bot, "%d", SensorValue[leftEncoder]);
		break;
	case 4:
	//When the appropriate menu is up, display the right encoder value
		sprintf(menu->bot, "%d", SensorValue[rightEncoder]);
		break;
	case 5:
	//When the appropriate menu is up, display the ptentiometer value
		sprintf(menu->bot, "%d", SensorValue[launchPot]);
		break;
	case 6:
	//When the appropriate menu is up, display the Ultrasonic sensor value
		sprintf(menu->bot, "%d", SensorValue[Ultra]);
		break;

		//For all the motor menus, display the "speed" variable,
		//as that variable determines the speed at which we will
		//test the motors in question.

	case 7:
		sprintf(menu->bot, "Speed = %d", speed);
		motor[port1] = speed;
		break;
	case 8:
		sprintf(menu->bot, "Speed = %d", speed);
		motor[port2] = speed;
		break;
	case 9:
		sprintf(menu->bot, "Speed = %d", speed);
		motor[port3] = speed;
		break;
	case 10:
		sprintf(menu->bot, "Speed = %d", speed);
		motor[port4] = speed;
		break;
	case 11:
		sprintf(menu->bot, "Speed = %d", speed);
		motor[port5] = speed;
		break;
	case 12:
		sprintf(menu->bot, "Speed = %d", speed);
		motor[port6] = speed;
		break;
	case 13:
		sprintf(menu->bot, "Speed = %d", speed);
		motor[port7] = speed;
		break;
	case 14:
		sprintf(menu->bot, "Speed = %d", speed);
		motor[port8] = speed;
		break;
	case 15:
		sprintf(menu->bot, "Speed = %d", speed);
		motor[port9] = speed;
		break;
	case 16:
		sprintf(menu->bot, "Speed = %d", speed);
		motor[port10] = speed;
		break;
	case 17:
		sprintf(menu->bot, "Speed = %d", speed);
		chassisDrive(vexRT[Ch2] + vexRT[Ch1], vexRT[Ch2] - vexRT[Ch1]);
		break;
	case 18:
		sprintf(menu->bot, "Speed = %d", speed);
		liftDrive(speed);
		break;
	case 19:
		sprintf(menu->bot, "Speed = %d", speed);
		clawDrive(speed);
		break;
	case 20:
		//UPDATES FOR INIT SENSOR PART - No Code
		break;
	case 21:
		//UPDATES FOR UPDATING TO DEFAULTS - No Code
		break;
	case 22:
		//Display whether the UART Comm systeme will be used
		//while in the appropriate menu
		if(BNSBluetooth) sprintf(menu->bot,"HC-05 - TRUE");
		else sprintf(menu->bot,"HC-05 - False");
		break;
	case 23:
		//Display whether the debug stream comm will be used
		//while in the appropriate menu
		if(DebugStream) sprintf(menu->bot,"TRUE");
		else sprintf(menu->bot,"False");
		break;
	case 24:
		//Display whether the JinX PROS comm is being
		//used - if not using PROS, Porting should be on
		//the ToDo List
		if(jinX) sprintf(menu->bot,"TRUE");
		else sprintf(menu->bot,"False - Switch to PROS");
		break;
	case 25:
		//When at the appropriate menu is up, display the
		//stop time for the self writing auton and display
		//the value you could change it to
		sprintf(menu->bot,"Rec Time = %d to %d", stopperVal, rapidScroll);
		break;
	case 26:
		//Display whether or not the code believes Spencer
		//is driving at this point in time
		if(DriveMan == Spencer) sprintf(menu->bot,"TRUE");
		else sprintf(menu->bot,"False");
		break;
	case 27:
		//At the appropriate menu, state whether or not
		//the code believes Noah is driving the robot at
		//this point in time
		if(DriveMan == Noah) sprintf(menu->bot,"TRUE");
		else sprintf(menu->bot,"False");
		break;
	case 28:
		//Display whether or not the robot is going
		//to stop during this step of the auton being
		//written out on the LCD Screen
		if(isStop) sprintf(menu->bot,"TRUE");
		else sprintf(menu->bot,"False");
		break;
	case 29:
		//Display whether or not the robot is going
		//to stop during this step of the auton being
		//written out on the LCD Screen
		if(!isStop) sprintf(menu->bot,"TRUE");
		else sprintf(menu->bot,"False");
		break;
	case 30:
		//Display whether or not the robot is going
		//to break during this step of the auton being
		//written out on the LCD Screen
		if(isBreak) sprintf(menu->bot,"TRUE");
		else sprintf(menu->bot,"False");
		break;
	case 31:
		//Display whether or not the robot is going
		//to break during this step of the auton being
		//written out on the LCD Screen
		if(!isBreak) sprintf(menu->bot,"TRUE");
		else sprintf(menu->bot,"False");
		break;
	case 32:
		//If the LCD written autonomous wants to use
		//left Encoder going up, display it as true on the LCD
		//on this menu
		if(sensorToUse == leftEncUp) sprintf(menu->bot, "TRUE Val = %d", rapidScroll);
		else sprintf(menu->bot, "False", rapidScroll);
		break;
	case 33:
		//If the LCD written autonomous wants to use
		//left Encoder going down, display it as true on the LCD
		//on this menu
		if(sensorToUse == leftEncDown) sprintf(menu->bot, "TRUE Val = %d", rapidScroll);
		else sprintf(menu->bot, "False", rapidScroll);
		break;
	case 34:
		//If the LCD written autonomous wants to use
		//time, display it as true on the LCD
		//on this menu
		if(sensorToUse == time) sprintf(menu->bot, "TRUE Val = %d", rapidScroll);
		else sprintf(menu->bot, "False", rapidScroll);
		break;
	case 35:
		//If the LCD written autonomous wants to use
		//right Encoder going up, display it as true on the LCD
		//on this menu
		if(sensorToUse == rightEncUp) sprintf(menu->bot, "TRUE Val = %d", rapidScroll);
		else sprintf(menu->bot, "False", rapidScroll);
		break;
	case 36:
		//If the LCD written autonomous wants to use
		//right Encoder going down, display it as true on the LCD
		//on this menu
		if(sensorToUse == rightEncDown) sprintf(menu->bot, "TRUE Val = %d", rapidScroll);
		else sprintf(menu->bot, "False", rapidScroll);
		break;
	case 37:
		//If the LCD written autonomous wants to use
		//gyro going up, display it as true on the LCD
		//on this menu
		if(sensorToUse == gyroUp) sprintf(menu->bot, "TRUE Val = %d", rapidScroll);
		else sprintf(menu->bot, "False", rapidScroll);
		break;
	case 38:
		//If the LCD written autonomous wants to use
		//gyro going down, display it as true on the LCD
		//on this menu
		if(sensorToUse == gyroDown) sprintf(menu->bot, "TRUE Val = %d", rapidScroll);
		else sprintf(menu->bot, "False", rapidScroll);
		break;
	case 39:
		//If the LCD written autonomous wants to use
		//left line sensor, display it as true on the LCD
		//on this menu
		if(sensorToUse == leftLine) sprintf(menu->bot, "TRUE Val = %d", rapidScroll);
		else sprintf(menu->bot, "False", rapidScroll);
		break;
	case 40:
		//If the LCD written autonomous wants to use
		//mid line sensor, display it as true on the LCD
		//on this menu
		if(sensorToUse == midLine) sprintf(menu->bot, "TRUE Val = %d", rapidScroll);
		else sprintf(menu->bot, "False", rapidScroll);
		break;
	case 41:
		//If the LCD written autonomous wants to use
		//right Line sensor, display it as true on the LCD
		//on this menu
		if(sensorToUse == rightLine) sprintf(menu->bot, "TRUE Val = %d", rapidScroll);
		else sprintf(menu->bot, "False", rapidScroll);
		break;
	case 42:
		//If the LCD written autonomous wants to use
		//sonar going up, display it as true on the LCD
		//on this menu
		if(sensorToUse == sonarInc) sprintf(menu->bot, "TRUE Val = %d", rapidScroll);
		else sprintf(menu->bot, "False", rapidScroll);
		break;
	case 43:
		//If the LCD written autonomous wants to use
		//sonar going down, display it as true on the LCD
		//on this menu
		if(sensorToUse == sonarDec) sprintf(menu->bot, "TRUE Val = %d", rapidScroll);
		else sprintf(menu->bot, "False", rapidScroll);
		break;

		//Cases 44-49 Handle Displaying Speed Values from rapidscroll
		//in order to set speeds for the autonomous created from the LCD

	case 44:
		sprintf(menu->bot,"%d", MaxMinClip(127, -128, rapidScroll));
		break;
	case 45:
		sprintf(menu->bot,"%d", MaxMinClip(127, -128, rapidScroll));
		break;
	case 46:
		sprintf(menu->bot,"%d", MaxMinClip(127, -128, rapidScroll));
		break;
	case 47:
		sprintf(menu->bot,"%d", MaxMinClip(127, -128, rapidScroll));
		break;
	case 48:
		sprintf(menu->bot,"%d", MaxMinClip(127, -128, rapidScroll));
		break;

		//Cases 49-54 Involve displaying variables and their potential
		//values after a click of a button in order to be used more
		//efficently for debugging while the robot is not connected
		//to a computer

	case 49:
		sprintf(menu->bot,"%d", MaxMinClip(127, -128, rapidScroll));
		break;
	case 50:
		sprintf(menu->bot,"%.3f, $.3f", PVar, (PVar + increment*rapidScroll));
		break;
	case 51:
		sprintf(menu->bot,"%.3f", (IVar + increment*rapidScroll));
		break;
	case 52:
		sprintf(menu->bot,"%.3f", (DVar + increment*rapidScroll));
		break;
	case 53:
		sprintf(menu->bot,"%.3f", (Var4 + increment*rapidScroll));
		break;
	case 54:
		sprintf(menu->bot,"%.3f", (Var5 + increment*rapidScroll));
		break;
	case 55:
		//In the appropriate menu, display whether or not
		//the increment is at 1, or if it
		//can be set to that value
		if(increment == 1)sprintf(menu->bot,"TRUE");
		else sprintf(menu->bot,"False");
		break;
	case 56:
		//In the appropriate menu, display whether or not
		//the increment is at 10, or if it
		//can be set to that value
		if(increment == 10)sprintf(menu->bot,"TRUE");
		else sprintf(menu->bot,"False");
		break;
	case 57:
		//In the appropriate menu, display whether or not
		//the increment is at 100, or if it
		//can be set to that value
		if(increment == 100)sprintf(menu->bot,"TRUE");
		else sprintf(menu->bot,"False");
		break;
	case 58:
		//In the appropriate menu, display whether or not
		//the increment is at .1, or if it
		//can be set to that value
		if(increment == .1)sprintf(menu->bot,"TRUE");
		else sprintf(menu->bot,"False");
		break;
	case 59:
		//In the appropriate menu, display whether or not
		//the increment is at .01, or if it
		//can be set to that value
		if(increment == .01)sprintf(menu->bot,"TRUE");
		else sprintf(menu->bot,"False");
		break;
	case 60:
		//In the appropriate menu, display whether or not
		//the increment is at .001, or if it
		//can be set to that value
		if(increment == .001)sprintf(menu->bot,"TRUE");
		else sprintf(menu->bot,"False");
		break;
	case 62:
		//If the LCD written autonomous wants to use
		//mid line sensor, display it as true on the LCD
		//on this menu
		if(sensorToUse == potUp) sprintf(menu->bot, "TRUE Val = %d", rapidScroll);
		else sprintf(menu->bot, "False", rapidScroll);
		break;
	case 63:
		//If the LCD written autonomous wants to use
		//right Line sensor, display it as true on the LCD
		//on this menu
		if(sensorToUse == potDown) sprintf(menu->bot, "TRUE Val = %d", rapidScroll);
		else sprintf(menu->bot, "False", rapidScroll);
		break;
	case -1:
		break;
	default:
		//Error Message, as if they aren't set to a number,
		//they are assigned negative one value
		sprintf(menu->top, "Ya Done");
		sprintf(menu->bot, "Screwed Up");
		break;
	}

	wait1Msec(1);

}

void funcCall(int functionNumber)
{
	switch (functionNumber)
	{
	case 1:
		//When you press the appropriate menu, run the
		//autonomous program you have decided to run
		displayLCDCenteredString(0, "Auton Running");
		autoCode(autoValue);
		break;
	case 2:
		//When the appropriate menu is pressed, switch the
		//toggle for the recording function - if it is on,
		//turn it off, and vice versa
		recordBool =! recordBool;
		break;

	//For Cases 3-7, When the Appropriate Menu is clicked
	//run the appropriate diagnostic test, for now, truespeed
	//array finders

	case 3:
		displayLCDCenteredString(0, "Test In Progress");
		trueSpeedFind(0,27);
		break;
	case 4:
		displayLCDCenteredString(0, "Test In Progress");
		trueSpeedFind(28,54);
		break;
	case 5:
		displayLCDCenteredString(0, "Test In Progress");
		trueSpeedFind(55,82);
		break;
	case 6:
		displayLCDCenteredString(0, "Test In Progress");
		trueSpeedFind(83,110);
		break;
	case 7:
		displayLCDCenteredString(0, "Test In Progress");
		trueSpeedFind(111,127);
		break;

	//For cases 8-17, at the appropriate menu, switch which
	//auton will be the one running by altering the autoValue
	//which is the variable which controls what autonomous program
	//to run.

	case 8:
		autoValue = 1;
		break;
	case 9:
		autoValue = 2;
		break;
	case 10:
		autoValue = 3;
		break;
	case 11:
		autoValue = 4;
		break;
	case 12:
		autoValue = 5;
		break;
	case 13:
		autoValue = 6;
		break;
	case 14:
		autoValue = 7;
		break;
	case 15:
		autoValue = 8;
		break;
	case 16:
		autoValue = 9;
		break;
	case 17:
		autoValue = 10;
		break;
	case 18:
		//Currently Empty
		break;
	case 19:
		//If the appropriate menu is clicked, run the LCD autonomous step that is stored
		//in the variables that can be manipulated throughout that section of the MLM
		displayLCDCenteredString(0, "STEP RUNNING");
		f(rightSpeedCV, rightSpeedCV, liftSpeedCV, liftSpeedCV, liftSpeedCV, clawSpeedCV, liftSpeedCV, liftSpeedCV,leftSpeedCV, leftSpeedCV, sensorToUse, finalSenVal);
		break;
	case 20:
		//If the appropriate menu is clicked, write down the function stored in the variables
		//that can be manipulated throughout the autonomous creator section of the MLM through
		//the appropriate communications
		if(DebugStream)
		{
			writeDebugStream("f(%d,%d,%d,",rightSpeedCV, rightSpeedCV, liftSpeedCV);
			writeDebugStream("%d,%d,%d,",liftSpeedCV,clawSpeedCV,clawSpeedCV);
			writeDebugStream("%d,%d,%d,",liftSpeedCV,liftSpeedCV,leftSpeedCV);
			writeDebugStream("%d,",leftSpeedCV);
			writeDebugStream("%d,%d);,",sensorToUse, finalSenVal);
		}
		if(BNSBluetooth)
		{
			bnsDebugStream("f(%d,%d,%d,",rightSpeedCV, rightSpeedCV, liftSpeedCV);
			bnsDebugStream("%d,%d,%d,",liftSpeedCV,clawSpeedCV,clawSpeedCV);
			bnsDebugStream("%d,%d,%d,",liftSpeedCV,liftSpeedCV,leftSpeedCV);
			bnsDebugStream("%d,",leftSpeedCV);
			bnsDebugStream("%d,%d);,",sensorToUse, finalSenVal);
		}
		break;
	case 21:
		//When the appropriate menu is clicked, reinstate
		//volatile sensors, and reset sensors which need
		//to be reset
		displayLCDCenteredString(0,"Initializing...");
		displayLCDCenteredString(1,"Do Not Move Robot");
		SensorType[in1] = sensorNone;
		wait10Msec(300);
#ifndef __Auton_Lib__
		SensorType[in1] = sensorGyro;
		wait10Msec(100);
#endif
#ifdef __Auton_Lib__
		SensorType[in1] = sensorAnalog;
		gyroInit(gGyro, in1);
#endif
		clearSensors();
		break;
	case 22:
		//RESTORE DEFAULTS to the robot
		DriveMan = Spencer;
		break;
	case 23:
		//When the appropriate menu is clicked, set the boolean
		//for the while loop within the task to false, causing us
		//to leave the entirety of the LCD Menu
		LCD = false;
		break;
	case 24:
		//When the appropriate menu is clicked, toggle the output
		//boolean for the HC-05: if it is off turn it on, and
		//vice versa
		BNSBluetooth =! BNSBluetooth;
		break;
	case 25:
		//When the appropriate menu is clicked, toggle the output
		//boolean for the Debug Stream: if it is off turn it on, and
		//vice versa
		DebugStream =! DebugStream;
		break;
	case 26:
		//When the appropriate menu is clicked, toggle the output
		//boolean for jinX - in case we switch to PROS: if it is
		//off turn it on, and vice versa
		jinX =! jinX;
		break;
	case 27:
		//If the appropriate menu is clicked, reset the stopping time
		//for the self-writing autonomous to whatever the value is for
		//the scroller, then reset the scroller
		stopperVal = rapidScroll;
		rapidScroll = 0;
		break;
	case 28:
		//If the button is pressed, set the driver to
		//be spencer, if it is already not so.
		if(DriveMan == Noah) DriveMan = Spencer;
		break;
	case 29:
		//If the button is pressed, set the driver
		//to be Noah, if it is not already so.
		if(DriveMan == Spencer) DriveMan = Noah;
		break;
	case 30:
		//If the appropriate menu is clicked, toggle
		//the auton Creator stop value: if it is on, turn
		//it off, and vice versa, to tell the robot if you
		//want it to stop after it has completed the step
		isStop =! isStop;
		break;
	case 31:
		//REMOVED DUE TO LOGICAL INEFFICENTCIES
		break;
	case 32:
		//If the appropriate menu is clicked, toggle
		//the auton Creator break value: if it is on, turn
		//it off, and vice versa, to tell the robot if you
		//want it to break after it has completed the step
		isBreak =! isBreak;
		break;
	case 33:
		//REMOVED DUE TO LOGICAL INEFFICENCIES
		break;

	//For Cases 34-45, if the appropriate menu is clicked,
	//set the sensorToUse variable, an integral part of the
	//LCD auton creator function, to the sensor and direction
	//that you wish it to be set at.

	case 34:
		sensorToUse = leftEncUp;
		break;
	case 35:
		sensorToUse = leftEncDown;
		break;
	case 36:
		sensorToUse = time;
		break;
	case 37:
		sensorToUse = rightEncUp;
		break;
	case 38:
		sensorToUse = rightEncDown;
		break;
	case 39:
		sensorToUse = gyroUp;
		break;
	case 40:
		sensorToUse = gyroDown;
		break;
	case 41:
		sensorToUse = leftLine;
		break;
	case 42:
		sensorToUse = midLine;
		break;
	case 43:
		sensorToUse = rightLine;
		break;
	case 44:
		sensorToUse = sonarInc;
		break;
	case 45:
		sensorToUse = sonarDec;
		break;

	//For cases 46-51, when the appropriate menu is clicked,
	//set the appropriate speed to the variable associated
	//with the menu that you are currently in.

	case 46:
		leftSpeedCV = MaxMinClip(127, -127, rapidScroll);
		break;
	case 47:
		rightSpeedCV = MaxMinClip(127, -127, rapidScroll);
		break;
	case 48:
		liftSpeedCV = MaxMinClip(127, -127, rapidScroll);
		break;
	case 49:
		clawSpeedCV = MaxMinClip(127, -127, rapidScroll);
		break;
	case 50:
		arb5SpeedV = MaxMinClip(127, -127, rapidScroll);
		break;
	case 51:
		arb6SpeedV = MaxMinClip(127, -127, rapidScroll);
		break;

	//For cases 52-56, use the increment setting variable,
	//and the rapid scroll variable, and when the button is
	//pushed on the appropriate menu, set the variable equal
	//to itself plus the increment times the rapid scroll value.

	case 52:
		PVar = PVar + increment*rapidScroll;
		break;
	case 53:
		IVar = IVar + increment*rapidScroll;
		break;
	case 54:
		DVar = DVar + increment*rapidScroll;
		break;
	case 55:
		Var4 = Var4 + increment*rapidScroll;
		break;
	case 56:
		Var5 = Var5 + increment*rapidScroll;
		break;

	//For cases 57-62, when the appropriate menu is clicked,
	//switch the increment value for the live variable manipulator
	//in accordance with the menu associated with that case value

	case 57:
		increment = 1;
		break;
	case 58:
		increment = 10;
		break;
	case 59:
		increment = 100;
		break;
	case 60:
		increment = .1;
		break;
	case 61:
		increment = .01;
		break;
	case 62:
		increment = .001;
		break;
	case 63:
		sensorToUse = potUp;
		break;
	case 64:
		sensorToUse = potDown;
		break;
	default:
		break;
	}
}

task LCDMenu()
{
	initAllMenus();

	menu currentMenu;
	//Create a currentMenu to store the data relevant
	//at any given time - holds the data of the menu that
	//will be stored

	setMenu(&currentMenu, sensorTop);
	//Start the MLM at the auton selector
	//As we will use that primarily at competition

	while(LCD)
	{
		if(bControllerLCD)
		{
#ifdef COMPETITION_LCD_MENU
			if(nLCDButtons == 2) 	setMenu(&currentMenu, autonTop);
			if(nLCDButtons == 1) 	setMenu(&currentMenu, sensor1);
			//For Competition, in case we are in a rush, having
			//shortcuts like this one will be nice.
#endif


			if(vexRT[Btn7R])
			{
				//When we hit the 7R Button on the Controller
				//move to the next menu
				while(vexRT[Btn7R]);
				setMenu(&currentMenu, (*currentMenu.next));
			}
			if(vexRT[Btn7L])
			{
				//When we hit the 7L button on the controller,
				//move to the previous menu
				while(vexRT[Btn7L]);
				setMenu(&currentMenu, (*currentMenu.prev));
			}
			if(vexRT[Btn7U] && &currentMenu.up != NULL)
			{
				//When we hit the 7U button, move to the menu
				//above the current menu, if there is one there
				while(vexRT[Btn7U]);
				setMenu(&currentMenu, (*currentMenu.up));
			}
			if(vexRT[Btn7D] && &currentMenu.down != NULL)
			{
				//When we hit the 7D Button, move to the menu
				//below the current menu, if there is one there
				while(vexRT[Btn7D]);
				setMenu(&currentMenu, (*currentMenu.down));
			}
			else if(vexRT[Btn7D] && &currentMenu.down == NULL)
			{
				//If we press the 7D button and there is not a
				//function below the current menu, there will be
				//a function to run instead, so run it
				while(vexRT[Btn7D]) displayLCDCenteredString(1, "Pressing Button");
				funcCall(currentMenu.FuncVal);
			}
		}
		else
		{
			string batVolt;
			sprintf(batVolt, "Main: %f%c", nImmediateBatteryLevel/1000, "V");
			currentMenu.bot = batVolt;
		}

		updateMessages(&currentMenu);

		displayLCDCenteredString(0, currentMenu.top);
		displayLCDCenteredString(1, currentMenu.bot);
		//Set the strings in the struct to the actual LCD.
		//Lots of code just to have it realized in two lines.
	}
	stopTask(LCDMenu);
	//When we exit this while loop, just exit this task entirely
}
