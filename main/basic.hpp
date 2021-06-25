#pragma once

static inline void speed(int a,int b){WheelLeft=a,WheelRight=b;}
#define rmnTime (480-Time)
template<typename T1, typename T2> static inline double pythag(T1 a, T2 b){return sqrt(a*a+b*b);}
template<typename T> static inline bool inRange(T a, T b, T c){return b<=a&&a<=c;}
static inline void setDuration(int dur){Duration=(int)round((dur-60)/60.0);}
static inline bool percentChance(int x){return randint(1,100)<=x;}
template<typename T1, typename T2, typename T3> static inline bool isWithinCoord(T1 x, T2 y, T3 range){return pythag(PositionX1-x, PositionY1-y)<=range;}
static inline bool isInfoLost(){return PositionX==0&&PositionY==0;}
#define isRGBcol (loaded_objects[R]>0&&loaded_objects[G]>0&&loaded_objects[B]>0)

enum {
	W1_COLOUR_RED,
	W1_COLOUR_GREEN,
	W1_COLOUR_BLACK,
	W1_COLOUR_YELLOW,
	W1_COLOUR_BONUS,
	W1_COLOUR_DEPOSIT,
	W1_COLOUR_TRAP1_INSIDE,
	W1_COLOUR_TRAP2_INSIDE,
	W1_COLOUR_WHITE,
	W1_COLOUR_FLOOR_TILE_DARK,
	W1_COLOUR_FLOOR_TILE_DARK_UPPER,
	W1_COLOUR_FLOOR_TILE_LIGHT,
	W1_COLOUR_FLOOR_TILE_LIGHT_LOWER,
	W2_COLOUR_RED,
	W2_COLOUR_GREEN,
	W2_COLOUR_BLACK,
	W2_COLOUR_SUPEROBJ,
	W2_COLOUR_YELLOW,
	W2_COLOUR_BONUS,
	W2_COLOUR_SWAMP,
	W2_COLOUR_DEPOSIT,
	W2_COLOUR_TRAP1_INSIDE,
	W2_COLOUR_TRAP2_INSIDE,
	TOTAL_COLOURS
};

static uintf8 colours[TOTAL_COLOURS][3][2];

static void ColourInformationStorer(uintf8 num,uintf8 r1,uintf8 r2,uintf8 g1,uintf8 g2,uintf8 b1,uintf8 b2)
{
	colours[num][0][0] = r1;
	colours[num][0][1] = r2;
	colours[num][1][0] = g1;
	colours[num][1][1] = g2;
	colours[num][2][0] = b1;
	colours[num][2][1] = b2;
}

static void InputColourInfo()
{
	//Add colour RGB here
	ColourInformationStorer(W2_COLOUR_YELLOW,204,235,217,248,0,0);
	ColourInformationStorer(W2_COLOUR_RED,190,255,0,90,0,90);
	ColourInformationStorer(W2_COLOUR_GREEN,25,45,215,255,240,255);
	ColourInformationStorer(W2_COLOUR_BLACK,25,75,25,75,25,75);
	ColourInformationStorer(W2_COLOUR_BONUS,0,0,150,171,0,0);
	ColourInformationStorer(W2_COLOUR_SWAMP,101,116,108,123,143,158);
	ColourInformationStorer(W2_COLOUR_DEPOSIT,204,235,140,160,0,0);
	ColourInformationStorer(W2_COLOUR_SUPEROBJ,200,255,20,50,200,255);
	ColourInformationStorer(W2_COLOUR_TRAP1_INSIDE,152,177,0,0,0,0);
	ColourInformationStorer(W2_COLOUR_TRAP2_INSIDE,122,140,87,99,255,255);
}

static inline uintf8 ColorSensorDetection(int color)
{
	/*
		0 - Not detected
		1 - Left Side Detected
		2 - Right Side Detected
		3 - Both Detected
	*/
	static constexpr uintf8 o = 0;
	uintf8 r1 = colours[color][0][0];
	uintf8 r2 = colours[color][0][1];
	uintf8 g1 = colours[color][1][0];
	uintf8 g2 = colours[color][1][1];
	uintf8 b1 = colours[color][2][0];
	uintf8 b2 = colours[color][2][1];

	// if (color == W2_COLOUR_TRAP_INSIDE) //if the map has colours similar to trap
	// {
	// 	if ((CSLeft_R==r1 && CSLeft_G==g1 && CSLeft_B==b1) || (CSLeft_R==r2 && CSLeft_G==g2 && CSLeft_B==b2))
	// 		return 1;
	// 	if ((CSRight_R==r1 && CSRight_G==g1 && CSRight_B==b1) || (CSRight_R==r2 && CSRight_G==g2 && CSRight_B==b2))
	// 		return 2;
	// 	return 0;
	// }

	uintf8 result = 0;
	// if( inRange(CSLeft_R,r1-o,r2+o)&&inRange(CSLeft_G,g1-o,g2+o)&&inRange(CSLeft_B,b1-o,b2+o) &&
	//   inRange(CSRight_R,r1-o,r2+o)&&inRange(CSRight_G,g1-o,g2+o)&&inRange(CSRight_B,b1-o,b2+o) )
	//   	result+=2;
	if ( inRange(CSLeft_R,r1-o,r2+o) && inRange(CSLeft_G,g1-o,g2+o) && inRange(CSLeft_B,b1-o,b2+o) )
		result++;//left
	if ( inRange(CSRight_R,r1-o,r2+o) && inRange(CSRight_G,g1-o,g2+o) && inRange(CSRight_B,b1-o,b2+o) )
		result+=2;//right
	return result;
}
static inline bool isOnRed() {return ColorSensorDetection(W2_COLOUR_RED);}
static inline bool isOnGreen() {return ColorSensorDetection(W2_COLOUR_GREEN);}
static inline bool isOnBlack() {return ColorSensorDetection(W2_COLOUR_BLACK);}
static inline bool isOnSuperObj() {return ColorSensorDetection(W2_COLOUR_SUPEROBJ);}
static inline int isOnYellow() {return ColorSensorDetection(W2_COLOUR_YELLOW);}
static inline int isOnBonus() {return ColorSensorDetection(W2_COLOUR_BONUS);}
static inline bool isOnSwamp() {return ColorSensorDetection(W2_COLOUR_SWAMP);}
static inline int isOnDeposit() {return ColorSensorDetection(W2_COLOUR_DEPOSIT);}
static inline bool isInsideTrap()
{
	return ColorSensorDetection(W2_COLOUR_TRAP1_INSIDE) || ColorSensorDetection(W2_COLOUR_TRAP2_INSIDE);
}

static inline void resetLoadedObjs()
{
	LoadedObjects=0;
	for(auto& i : loaded_objects)
		i = 0;
}
static inline void resetPhases()
{
	depoPhase=1;
	superObjPhase=1;
}
static inline void resetTimeouts()
{
	SuperObjTimeout=0;
	TrapTimeout=0;
	WallTimeout=0;
}

static inline bool posIsInColorLoc(int x, int y)
{
	int addedreturntrue;
	return true;
	int pos = conv(x,y);
	for(const auto& i : navi.places)
	{
		if (binary_search(i.loc, i.loc + i.len,pos))
			return true;
	}
	return false;
}

static inline bool blackIsInColorLoc(int x, int y)
{
	if(0<=x && x<=95 && 85<=y && y<=185) return true;
	if(120<=x && x<=275 && 0<=y && y<=55) return true;
	if(250<=x && x<=360 && 80<=y && y<=185) return true;
	if(85<=x && x<=230 && 215<=y && y<=270) return true;
	return false;
}

static vector<Place>::iterator currLocIt;
static void goToRandPt(uintf8);

static inline void find_obj(unsigned int color)
{
	Duration = COLLECT_DURATION;
	if(color==S)
	{
		loaded_objects[S]++;
		resetPhases();
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
	if(going_to_rand_pt && color!=S)
	{
		unsigned int mycol = currLocIt->color;
		if(mycol==color || mycol==RGB || (mycol==RG && (color==R||color==G)) || (mycol==RB && (color==R||color==B)) || (mycol==GB && (color==G||color==B)) ) goToRandPt(1);
	}
	else
	{
		uintf8 TODO_BINARYSEARCH_HERE;
	}

	LED_1=1;
	speed(0,0);
	resetTimeouts();
	printf("find_obj color=%d\n",color);
}

//Deposit Function
static inline void deposit()
{
	if(isOnDeposit()!=3)
	{
		if(isOnDeposit()==1)
		{
			speed(0,3);
		}
		else if(isOnDeposit()==2)
		{
			speed(3,0);
		}
		return;
	}
	speed(0,0);
	LED_1=2;
	SuperX=0;
	SuperY=0;
	going_to_place=false;
	going_to_rand_pt=false;
	Duration=DEPOSIT_DURATION;
	depositing=true;
}

static inline bool isNearTrapXY()
{
	return false;
}

static inline void avdTrapXY()
{
	return;
}

static inline int isOutOfXY()
{
	if(PositionX<4 && PositionY>265 && (Compass<180 || Compass>270) ) // Top Left
		return 1;
	else if(PositionX>355 && PositionY>265 && (Compass<90 || Compass>180)) // Top Right
		return 2;
	else if(PositionX>355 && PositionY<4 && Compass>90) // Bottom Right
		return 3;
	else if(PositionX<4 && PositionY<4 && Compass<270) // Bottom Left
		return 4;
	else if(PositionY>265 && (Compass<90 || Compass>270)) // North
		return 5;
	else if(PositionY<4 && (Compass>180 && Compass<270)) // South
		return 6;
	else if(PositionX>355 && Compass>180) // East
		return 7;
	else if(PositionX<4 && Compass<180) // West
		return 8;
	return 0;
}

static inline void avdNSEW()
{
	minSpeed=-1;
	maxSpeed=3;
	switch(isOutOfXY())
	{
		case 0:
			break;
		case 1:
			if(Compass<=45 || Compass>=270) speed(3,-2);
			else if(Compass>=45 && Compass<=180) speed(-2,3);
			break;
		case 2:
			if(Compass<=90 || Compass>=315) speed(-2,3);
			else if(Compass>=180 && Compass<=315) speed(3,-2);
			break;
		case 3:
			if(Compass>=225) speed(-2,3);
			else if(Compass>=90 && Compass<=225) speed(3,-2);
			break;
		case 4:
			if(Compass<=135) speed(3,-2);
			else if(Compass>=135 && Compass<=270) speed(-2,3);
			break;
		case 5:
			if(CWAngleDiff==180)
			{
				if(Compass<=90) speed(minSpeed,maxSpeed);
				else if(Compass>=270) speed(maxSpeed,minSpeed);
			}
			else if(CWAngleDiff<ACWAngleDiff) speed(maxSpeed,minSpeed);//turn clockwise
			else if(ACWAngleDiff<CWAngleDiff) speed(minSpeed,maxSpeed);//turn anti-clockwise
			else speed(maxSpeed,maxSpeed);
			break;
		case 6:
			if(CWAngleDiff==180)
			{
				if(Compass>=90&&Compass<=180) speed(maxSpeed,minSpeed);
				else if(Compass>=180&&Compass<=270) speed(minSpeed,maxSpeed);
			}
			else if(CWAngleDiff<ACWAngleDiff) speed(maxSpeed,minSpeed);//turn clockwise
			else if(ACWAngleDiff<CWAngleDiff) speed(minSpeed,maxSpeed);//turn anti-clockwise
			else speed(maxSpeed,maxSpeed);
			break;
		case 7:
			if(CWAngleDiff==180)
			{
				if(Compass>=180&&Compass<=270) speed(maxSpeed,minSpeed);
				else if(Compass>=270&&Compass<360) speed(minSpeed,maxSpeed);
			}
			else if(CWAngleDiff<ACWAngleDiff) speed(maxSpeed,minSpeed);//turn clockwise
			else if(ACWAngleDiff<CWAngleDiff)speed(minSpeed,maxSpeed);//turn anti-clockwise
			else speed(maxSpeed,maxSpeed);
			break;
		case 8:
			if(CWAngleDiff==180)
			{
				if(Compass<=90) speed(maxSpeed,minSpeed);
				else if(Compass>=90&&Compass<=180) speed(minSpeed,maxSpeed);
			}
			else if(CWAngleDiff<ACWAngleDiff) speed(maxSpeed,minSpeed);//turn clockwise
			else if(ACWAngleDiff<CWAngleDiff) speed(minSpeed,maxSpeed);
			else speed(maxSpeed,maxSpeed);
			break;
		default:
			cout<<"TRIED TO AVD NSEW\n";
			break;
	}
}

static inline void avdWallNear()
{
	WallTimeout++;
	if(US_Front<=FRONT_NEAR&&US_Left<=LEFT_NEAR&&US_Right<=RIGHT_NEAR)
	{
		speed(-2,-5);
		setDuration(300);
	}
	else if(US_Front<=FRONT_NEAR&&US_Left<=LEFT_NEAR)
	{
		speed(-1,-5);
		setDuration(240);
	}
	else if(US_Front<=FRONT_NEAR&&US_Right<=RIGHT_NEAR)
	{
		speed(-5,-1);
		setDuration(240);
	}
	else if(US_Front<=FRONT_NEAR)
	{
		if(US_Left<US_Right)
		{
			speed(-1,-4);
			setDuration(180);
		}
		else
		{
			speed(-4,-1);
			setDuration(180);
		}
	}
	else if(US_Left<=LEFT_NEAR)
	{
		speed(-1,-3);
		setDuration(120);
	}
	else if(US_Right<=RIGHT_NEAR)
	{
		speed(-3,-1);
		setDuration(120);
	}
}

static inline void avdYellow()
{
	TrapTimeout++;
	int yellow_case=isOnYellow();
	if(yellow_case==1)//left
	{
		speed(-1,-5);
		setDuration(isOnSwamp() ? 900 : 300);
	}
	else if(yellow_case==2)//right
	{
		speed(-5,-1);
		setDuration(isOnSwamp() ? 540 : 180);
	}
	else if(yellow_case==3)//both
	{
		speed(-1,-5);
		setDuration(isOnSwamp() ? 540 : 180);
	}
}

static inline void turnToAngle(int targetAngle)
{
	//must have set minSpeed AND maxSpeed BEFORE CALLING THIS FUNC
	if(Compass>=targetAngle)
	{
		CWAngleDiff=Compass-targetAngle;
		ACWAngleDiff=360-(Compass-targetAngle);
	}
	else //Compass<targetAngle
	{
		ACWAngleDiff=targetAngle-Compass;
		CWAngleDiff=360-(targetAngle-Compass);
	}

	if(CWAngleDiff<=ACWAngleDiff) speed(maxSpeed,minSpeed);//turn clockwise
	else if(ACWAngleDiff<CWAngleDiff) speed(minSpeed,maxSpeed);//turn anti-clockwise
	else speed(maxSpeed,maxSpeed);//move forward
}

void reduceSpeeds(int& spd1, int& spd2)
{
	spd1 = spd1>=0 ? spd1/2+1 : spd1/2-1;
	spd2 = spd2>=0 ? spd2/2+1 : spd2/2-1;
}

static inline void calcTheta(int originX, int originY, int targetX, int targetY)
{
	const int deltaX = targetX - originX;
	const int deltaY = targetY - originY;
		 if (deltaX==0 && deltaY>0) theta = 0;
	else if (deltaX<0 && deltaY==0) theta = 90;
	else if (deltaX<0 && deltaY>0)  theta = 90 - (int)round(atan((double)abs(deltaY)/abs(deltaX))*180/PI);
	else if (deltaX<0 && deltaY<0)  theta = 90 + (int)round(atan((double)abs(deltaY)/abs(deltaX))*180/PI);
	else if (deltaX==0 && deltaY<0) theta = 180;
	else if (deltaX>0 && deltaY<0)  theta = 270 - (int)round(atan((double)abs(deltaY)/abs(deltaX))*180/PI);
	else if (deltaX>0 && deltaY==0) theta = 270;
	else if (deltaX>0 && deltaY>0)  theta = 270 + (int)round(atan((double)abs(deltaY)/abs(deltaX))*180/PI);
}

static inline void trigo(int targetX, int targetY)
{
	calcTheta(PositionX1, PositionY1, targetX, targetY);
	AngleDiff=abs(Compass-theta);
	if(AngleDiff>180) AngleDiff=360-AngleDiff;
	if(AngleDiff>=130&&AngleDiff<=180)
	{
		minSpeed=-4;
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-4;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>=80&&AngleDiff<130)
	{
		minSpeed=-3;
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-4;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>=30&&AngleDiff<80)
	{
		minSpeed=1;//1
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-3;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>=15&&AngleDiff<30)
	{
		minSpeed=2;
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-3;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>=5&&AngleDiff<15)
	{
		minSpeed=4;
		maxSpeed=5;
	}
	else if(AngleDiff<5)
	{
		minSpeed=5;
		maxSpeed=5;
	}
	else //failsafe
	{
		minSpeed=-3;
		maxSpeed=-3;
	}
	if(US_Front<=FRONT_MOVE_BACK+10) reduceSpeeds(minSpeed,maxSpeed);
	turnToAngle(theta);
}

static inline void trigoSuper(int targetX, int targetY)
{
	double distance = pythag(SuperX-colorSensorX, SuperY-colorSensorY);
	// printf("Dist from SuperObj = %.2f\n",distance);
	if(distance>SUPEROBJTARGETDIST)
	{
		trigo(targetX,targetY);
		return;
	}

	calcTheta(colorSensorX, colorSensorY, targetX, targetY);
	AngleDiff=abs(Compass-theta);
	if(AngleDiff>180) AngleDiff=360-AngleDiff;
	if(AngleDiff>=130&&AngleDiff<=180)
	{
		minSpeed=-5;
		maxSpeed=-1;
		if(isOnSwamp()) setDuration(750);
	}
	else if(AngleDiff>=80&&AngleDiff<130)
	{
		minSpeed=-4;
		maxSpeed=1;
	}
	else if(AngleDiff>=30&&AngleDiff<80)
	{
		minSpeed=-2;
		maxSpeed=4;
	}
	else if(AngleDiff>=15&&AngleDiff<30)
	{
		minSpeed=2;
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-3;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>=5&&AngleDiff<15)
	{
		minSpeed=4;
		maxSpeed=5;
	}
	else if(AngleDiff<5)
	{
		minSpeed=5;
		maxSpeed=5;
	}
	else //failsafe
	{
		minSpeed=-3;
		maxSpeed=-3;
	}
	if(US_Front<=FRONT_MOVE_BACK+7) reduceSpeeds(minSpeed,maxSpeed);
	turnToAngle(theta);
}
static inline void trigoSweep(int targetX,int targetY)
{
	calcTheta(PositionX1, PositionY1, targetX, targetY);
	AngleDiff=abs(Compass-theta);
	if(AngleDiff>180) AngleDiff=360-AngleDiff;
	if(AngleDiff>=130&&AngleDiff<=180)
	{
		minSpeed=-4;
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-4;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>=80&&AngleDiff<130)
	{
		minSpeed=-3;
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-3;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>=30&&AngleDiff<80)
	{
		minSpeed=1;
		maxSpeed=5;
		if(isOnSwamp()){
			minSpeed=-3;
			maxSpeed=5;
		}
	}
	else if(AngleDiff>15&&AngleDiff<30)
	{
		minSpeed=2;
		maxSpeed=5;
	}
	else if(AngleDiff>0&&AngleDiff<=15)
	{
		minSpeed=3;
		maxSpeed=5;
	}
	else if(AngleDiff==0)
	{
		minSpeed=4;
		maxSpeed=5;
	}
	else //failsafe
	{
		minSpeed=-3;
		maxSpeed=-3;
	}
	if(US_Front<=FRONT_MOVE_BACK+7) reduceSpeeds(minSpeed,maxSpeed);
	turnToAngle(theta);
}



static bool shouldRush()
{
	return (rmnTime<=RUSHDEPOSUPERDEPO && isRGBcol) || (rmnTime<=RUSHDEPO && (LoadedObjects>=5 || loaded_objects[S]>0));
}

static bool isRushing()
{
	return (rmnTime<=RUSHDEPOSUPERDEPO && going_to_super) || (rmnTime<=RUSHDEPO && depoPhase==2);
}
