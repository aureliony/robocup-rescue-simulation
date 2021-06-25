static inline bool isOnRed1() {return ColorSensorDetection(W1_COLOUR_RED);}
static inline bool isOnGreen1() {return ColorSensorDetection(W1_COLOUR_GREEN);}
static inline bool isOnBlack1() {return ColorSensorDetection(W1_COLOUR_BLACK);}
static inline int isOnYellow1() {return ColorSensorDetection(W1_COLOUR_YELLOW);}
static inline int isOnBonus1() {return ColorSensorDetection(W1_COLOUR_BONUS);}
static inline int isOnWhite1() {return ColorSensorDetection(W1_COLOUR_WHITE);}
static inline int isOnDeposit1() {return ColorSensorDetection(W1_COLOUR_DEPOSIT);}
static inline bool isInsideTrap1() {return ColorSensorDetection(W1_COLOUR_TRAP2_INSIDE);}
static inline bool isOnFloorDark1(){return ColorSensorDetection(W1_COLOUR_FLOOR_TILE_DARK);}
static inline bool isOnFloorLight1(){return ColorSensorDetection(W1_COLOUR_FLOOR_TILE_LIGHT);}
static inline bool isOnFloorDarkUp1(){return ColorSensorDetection(W1_COLOUR_FLOOR_TILE_DARK_UPPER);}
static inline bool isOnFloorLightLow1(){return ColorSensorDetection(W1_COLOUR_FLOOR_TILE_LIGHT_LOWER);}

static void InputColourInfo1()
{
	//Add colour RGB here
	ColourInformationStorer(W1_COLOUR_YELLOW,204,235,217,248,0,0);
	ColourInformationStorer(W1_COLOUR_RED,190,255,0,90,0,90);
	ColourInformationStorer(W1_COLOUR_GREEN,25,45,215,255,240,255);
	ColourInformationStorer(W1_COLOUR_BLACK,29,80,29,80,29,80);
	ColourInformationStorer(W1_COLOUR_BONUS,0,0,0,0,255,255);
	ColourInformationStorer(W1_COLOUR_DEPOSIT,204,235,130,160,0,0);
	ColourInformationStorer(W1_COLOUR_TRAP1_INSIDE,0,0,0,0,0,0);
	ColourInformationStorer(W1_COLOUR_TRAP2_INSIDE,122,140,87,99,255,255);
	ColourInformationStorer(W1_COLOUR_WHITE,204,255,217,255,235,255);
	ColourInformationStorer(W1_COLOUR_FLOOR_TILE_DARK,69,79,123,140,69,76);
	ColourInformationStorer(W1_COLOUR_FLOOR_TILE_DARK_UPPER,69,79,123,140,69,80);
	ColourInformationStorer(W1_COLOUR_FLOOR_TILE_LIGHT_LOWER,53,61,118,145,48,53);
	ColourInformationStorer(W1_COLOUR_FLOOR_TILE_LIGHT,64,74,121,138,60,66);

}

static inline bool checkCompass(bool One) {
	if (One) return (Compass >= 45 && Compass <= 135) || (Compass >= 225 && Compass <= 315);
	else return (Compass >= 80 && Compass <= 100) || (Compass >= 260 && Compass <= 280);
}

static inline void startw1()
{
	InputColourInfo1();
	speed(3,-3);
	setDuration(300);
	PREV_US[0] = US_Right;
	PREV_US[1] = US_Left;
	startingw1=false;
}

static inline bool shouldGoDepo() {
	return (LoadedObjects>3 || isRGBcol || (Time>180 && LoadedObjects>0));
}

static inline void depositw1()
{
	if(isOnDeposit1()!=3)
	{
		if(isOnDeposit1()==1) speed(0,3);
		else if(isOnDeposit1()==2) speed(3,0);
		return;
	}
	speed(0,0);
	LED_1=2;
	Duration=DEPOSIT_DURATION;
	depositing=true;
	bonusTimeOut = 0;
	Bonus = false;
	preProgramOn = 0;
	preProgramTimer = 0;
}


static inline void find_obj_world1(unsigned int color)
{
	Duration = W1_COLLECT_DURATION;
	if(color==S)
	{
		loaded_objects[S]++;
		going_to_super=false;
	}
	else if(color==R)
	{
		loaded_objects[R]++;
		loaded_objects[RG]++;
		loaded_objects[RB]++;
		loaded_objects[RGB]++;
	}
	else if(color==G)
	{
		loaded_objects[G]++;
		loaded_objects[RG]++;
		loaded_objects[GB]++;
		loaded_objects[RGB]++;
	}
	else if(color==B)
	{
		loaded_objects[B]++;
		loaded_objects[RB]++;
		loaded_objects[GB]++;
		loaded_objects[RGB]++;
	}
	else cout << "\nFIND OBJ ERROR\nFIND OBJ ERROR\nFIND OBJ ERROR\nFIND OBJ ERROR\nFIND OBJ ERROR\n\n";

	LoadedObjects++;

	LED_1=1;
	speed(0,0);
	printf("find_obj color=%d\n",color);
	isFindingObj = true;
	TimeOutNoObj = 0;
	if (Bonus) bonusTimeOut = 0;

	if (Bonus){
		bonusColour[color] = true;
		string s = "";
		for (int i=1;i<4;i++)
		{
			if(bonusColour[i]){
				s += intToStr[i];
			}
		}

		int num=4;
		if(s.size()==0) assert(0);
		else if(s.size()==1) num=4;
		else if(s.size()==2) num=5;
		else if(s.size()==3) num=6;
		if((int)loaded_objects[strToInt[s]]>=num)
			Bonus=false;
		bonusType = strToInt[s];
	}


	//Set bonus

}

static inline void avdWallWorld1() {

	FRONT = 12;
	LEFT = 7;
	RIGHT = 7;

	if(US_Front<=FRONT)
	{
		//shouldGoDepo() ? speed(-2,3) : speed(3,-2);
		speed(-2,3);
	}

	else if(US_Left<=LEFT)
	{
	speed(2,-1);
	printf("Avd Wall L\n");
	}

	else if(US_Right<=RIGHT)
	{
	speed(-1,2);
	printf("Avd Wall R\n");
	}
	else speed(3,3);



}

static inline void avdWallsTracing() {

	FRONT = 5;
	LEFT = 2;
	RIGHT = 2;


	if(US_Front<=FRONT)
	{
		if (preProgramOn==2) speed(-1,-4);
		else speed(-4,-1);
		setDuration(120);
	}

	else if(US_Left<=LEFT)
	{
		if ((shouldGoDepo() || (Time>TELEPORTTIME-10 && LoadedObjects>0) )) speed(-1,-4);
		else speed(-4,-1);
	printf("Avoid Wall L\n");
	}

	else if(US_Right<=RIGHT)
	{
		if (preProgramOn==2) speed(-1,-4);
		else speed(-4,-1);
	printf("Avoid Wall R\n");
	}

	else speed(3,3);


}

static inline void WallTrace() {


	// if ((Compass<45 || Compass>315) || ((Compass >135 && Compass<225) && (LoadedObjects>3 || isRGBcol || (Time>180 && LoadedObjects>0))))
	// {
	// 	if(US_Front<5) speed(-5,-2);
	// 	else if(US_Right>8)
	// 	{
	// 		speed(5,3);
	// 		TimeOut++;
	// 		TimeOutNoObj++;
	// 	}
	// 	else if (US_Right<8){
	// 		TimeOut=0;
	// 		speed(3,5);
	// 		TimeOutNoObj++;
	// 	}
	// 	else if (US_Right==8)
	// 	{
	// 		speed(4,4);
	// 	}
	// }
	int mins = 2, maxs = 5;
	THRESH = 20;

	if ((isOnFloorDark1() || isOnFloorLight1()) && (shouldGoDepo() || (Time>TELEPORTTIME-10 && LoadedObjects>0)) ) {mins=2;maxs=4; THRESH=8;}
	if (1)//preProgramOn<=1)
	{
		if(US_Right>THRESH)
		{
			speed(maxs,mins);
			TimeOut++;
			TimeOutNoObj++;
		}
		else if (US_Right<THRESH) {
			TimeOut=0;
			speed(mins,maxs);
			TimeOutNoObj++;
		}
		else if (US_Right==THRESH) speed(3,3);
	}
	else if (preProgramOn==2)
	{
		if(US_Left>15)
		{
			speed(mins,maxs);
			TimeOut++;
			TimeOutNoObj++;
		}
		else if (US_Left<15){
			TimeOut=0;
			speed(maxs,mins);
			TimeOutNoObj++;
		}
		else if (US_Left==15) speed(3,3);

		}
	else speed(4,4);
	}



static inline void avdYellowWorld1() {
	int yellow_case=isOnYellow1();
	if (yellow_case==1)//left
	{
		if ((shouldGoDepo() || (Time>TELEPORTTIME-10 && LoadedObjects>0)) && Compass>0 && Compass<180) speed(-1,3);
		else speed(3,-1);
		setDuration(120);
	}
	else if (yellow_case==2)//right
	{
		speed(-1, 3);
		setDuration(120);
	}
	else if (yellow_case==3)//both
	{
		speed(-5, -2);
		setDuration(120);

	}

}

static inline void avdWhiteWorld1() {
	int white_case=isOnWhite1();
	if (white_case==1)//left
	{
		speed(3, -1);
		setDuration(120);
	}
	else if (white_case==2)//right
	{
		speed(-1, 3);
		setDuration(120);
	}
	else if (white_case==3)//both
	{
		speed(-2, -5);
		setDuration(120);
	}

}

static inline void sweep(int angle, int minspeed, int maxspeed) {
	(Compass/angle)%2==1 ? speed(minspeed,maxspeed) : speed(maxspeed,minspeed);
}

static inline void conditions(){
	if ((abs(PREV_US[0]-US_Right) > 15) || (abs(PREV_US[1]-US_Left) > 15)) {
		if (TracingSide == leftt) TracingSide = rightt;
		else TracingSide = leftt;
	}
	PREV_US[0] = US_Right;
	PREV_US[1] = US_Left;
}

static inline void timeouts() {
	if (TimeOut >= TIMEOUT)
	{
		TOTO++;
	}
	if (US_Right<20)
	{
		TimeOut = 0;
		TOTO = 0;
	}
	if (TimeOutNoObj >= TIMEOUTNOOBJ)
	{
		TOTONO ++;

		if (TOTONO > TIMEOUTNO && US_Right < 20)
		{
			TOTONO = 0;
			TimeOutNoObj = 0;
		}
	}

	if (preProgramOn>0) {
		preProgramTimer++;
		if (preProgramTimer > 100)
		{
			preProgramOn = 0;
			preProgramTimer = 0;
		}
	}

}

static inline void checkTracing() {
	if (TimeOut>=TIMEOUT || TimeOutNoObj>=TIMEOUTNOOBJ) {
		Tracing = false;
	}
	/*if (isOnFloorDark1() && US_Front<=11 && US_Right<=10 && checkCompass(true) && preProgramOn==0 && shouldGoDepo()){
		preProgramOn = 1;
		TimeOutNoObj = 0;
		TimeOut = 0;
	}
	else if (isOnFloorLight1() && preProgramOn == 1 && shouldGoDepo() && US_Front>9){
		speed(5,3);
		setDuration(840);
		preProgramOn = 2;
	}*/
	cout <<"preProgramOn= " << preProgramOn << endl;
	cout << "DARK? = " << isOnFloorDark1() << endl;
	cout << "COMPASS? = " << checkCompass(false) << endl;
	cout <<"TRACING?= " << Tracing<<endl;
}

static inline void avdDepositWorld1() {
	int orange_case=isOnDeposit1();
	if (orange_case==1)//left
	{
		speed(3,-1);
		setDuration(120);
	}
	else if (orange_case==2)//right
	{
		speed(-1, 3);
		setDuration(120);
	}
	else if (orange_case==3)//both
	{
		speed(-5, -2);
		setDuration(120);

		TimeOutNoObj=TIMEOUTNOOBJ;
	}
}

static inline void avdWallsAll() {
	if (preProgramOn<=1) speed(-4, -1);
	else speed(-1,-4);
}

static inline int checkDirection() {
	if (Compass < 45 || Compass > 315) return 1; //North
	else if (Compass >= 45 && Compass <= 135) return 2; //West
	else if (Compass > 135 && Compass < 225) return 3; //South
	else return 4; //East
}

static inline bool shouldCollectLastMinute() {
	return (LoadedObjects<6 && Time>TELEPORTTIME-15);
}

static inline bool shouldCollect(int colour) {
	if (colour == R) return ((LoadedObjects<6 && loaded_objects[B]>0 && loaded_objects[G]>0) || (LoadedObjects<5 && loaded_objects[R]<4));

	else if (colour == G) return ((LoadedObjects<6 && loaded_objects[B]>0 && loaded_objects[R]>0) || (LoadedObjects<5 && loaded_objects[G]<4));

	else if (colour == B) return ((LoadedObjects<6 && loaded_objects[R]>0 && loaded_objects[G]>0) || (LoadedObjects<5 && loaded_objects[B]<4));

	else {cout << "\nFIND OBJ ERROR\nFIND OBJ ERROR\nFIND OBJ ERROR\nFIND OBJ ERROR\nFIND OBJ ERROR\n\n"; return false;};
}

static inline bool shouldTp() {
	return (( ( (Time>=180 && LoadedObjects==0 && !isRGBcol) || (Time>183 && LoadedObjects<2 && !isRGBcol) || (Time>187 && LoadedObjects<3 && !isRGBcol ) || (Time>193 && LoadedObjects<4 && !isRGBcol) || (Time>197 && LoadedObjects<5 && !isRGBcol) || (Time>203 && LoadedObjects<6 && !isRGBcol ) || (Time>207 && !isRGBcol) || Time>212) && !isOnDeposit1() ) || Time>295);
}