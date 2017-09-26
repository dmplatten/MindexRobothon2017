#pragma config(StandardModel, "RVW Buggybot")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int speedvalue = 60;
int turnSpeed = 15;
short facing = 0;  //direction robot is facing
short gyro1 = 0;
short openPath = 35;
short stopNow = 25;
short stopCloser = 15;
short medTurn = 79;
const int sonmax = 4;
short sondir[sonmax][2];
short northdir = 0;
short southdir = 0;
short eastdir = 0;
short westdir = 0;
short northdist = 0;
short southdist = 0;
short eastdist = 0;
short westdist = 0;
short godir = 0;

void goForward()
{
	forward(0.049, seconds, speedvalue);
}

void getCloser()
{
	while (SensorValue(sonar) > stopCloser)
	{
		goForward();
	}
}


void goBackward()
{
	backward(0.1, rotations, speedvalue);
}


void faceDirection(short gd)
{
	//gd = gyro direction
	gyro1 = SensorValue(gyro);
	while ((gyro1 < gd - 400) | (gyro1 > gd + 400))
	{
		gyro1 = SensorValue(gyro);
		if (gyro1 < gd - 400)
		{
			turnRight(medTurn, degrees, turnSpeed);
		}
		else if (gyro1 > gd + 400)
		{
			turnLeft(medTurn, degrees, turnSpeed);
		}
	}

	while ((gyro1 < gd - 2) | (gyro1 > gd + 2))
	{
		gyro1 = SensorValue(gyro);
		if (gyro1 < gd - 2)
		{
			turnRight(5, degrees, turnSpeed);
		}
		else if (gyro1 > gd + 2)
		{
			turnLeft(5, degrees, turnSpeed);
		}
	}
}

short getFacingDir(short f1)
{
	short result = 0;

	if ((f1 >= 450) & (f1 < 1350))  //east
  {
   	result = 900;
  }
  else if ((f1 >= 1350) & (f1 < 2250))  //south
  {
   	result = 1800;
	}
	else if ((f1 >= 2250) & (f1 < 3150))  //west
	{
   	result = 2700;
	}
	else  //north
	{
   	result = 0;
	}
	return result;
}



void analyze()
{
	short adir = 0;
	short adist = 0;

	northdir = 0;
	southdir = 0;
	eastdir = 0;
	westdir = 0;

	northdist = 0;
	southdist = 0;
	eastdist = 0;
	westdist = 0;

	for (int i1 = 0; i1 < sonmax; i1++)
  {
  	adir = sondir[i1][1];
  	adist = sondir[i1][0];
    if ((adir >= 450) & (adir < 1350))  //east
    {
    	if (adist > eastdist)
    	{
    		eastdist = adist;
    		eastdir = adir;
    	}
    }
    else if ((adir >= 1350) & (adir < 2250))  //south
    {
    	if (adist > southdist)
    	{
    		southdist = adist;
    		southdir = adir;
    	}
    }
    else if (adir >= 2250 & adir < 3150)  //west
    {
    	if (adist > westdist)
    	{
    		westdist = adist;
    		westdir = adir;
    	}
    }
    else  //north
    {
    	if (adist > northdist)
    	{
    		northdist = adist;
    		northdir = adir;
    	}
    }
  }
}

void superLook()
{
	faceDirection(0);
	sondir[0][0] = SensorValue(sonar);
  sondir[0][1] = SensorValue(gyro);
	for (int i1 = 1; i1 < sonmax; i1++)
  {
  	turnRight(159, degrees, turnSpeed);
  	waitUntilMotorStop(motorA);
  	waitUntilMotorStop(motorB);
    sondir[i1][0] = SensorValue(sonar);
    sondir[i1][1] = SensorValue(gyro);
  }
  faceDirection(facing);
}

short decide()
{
	short ddir;

	switch (getFacingDir(facing))
	{
		case 0:
		{
			if (eastdist > openPath)
			{
				ddir = eastdir;
			}
			else if (northdist > openPath)
			{
				ddir = northdir;
			}
			else if (westdist > openPath)
			{
				ddir = westdir;
			}
			else
			{
				ddir = 9999;
			}
			break;
		}
		case 900:
		{
			if (southdist > openPath)
			{
				ddir = southdir;
			}

			else if (eastdist > openPath)
			{
				ddir = eastdir;
			}
			else if (northdist > openPath)
			{
				ddir = northdir;
			}
			else
			{
				ddir = 9999;
			}
			break;
		}
		case 1800:
		{
			if (westdist > openPath)
			{
				ddir = westdir;
			}

			else if (southdist > openPath)
			{
				ddir = southdir;
			}

			else if (eastdist > openPath)
			{
				ddir = eastdir;
			}
			else
			{
				ddir = 9999;
			}

			break;
		}
		case 2700:
		{
			if (northdist > openPath)
			{
				ddir = northdir;
			}

			else if (westdist > openPath)
			{
				ddir = westdir;
			}

			else if (southdist > openPath)
			{
				ddir = southdir;
			}

			else
			{
				ddir = 9999;
			}
		}
	}
	return ddir;
}

void proceed()
{
	facing = SensorValue(gyro);
	while (SensorValue(sonar) > stopNow)
	{
		goForward();
	}
}

void lookAround()
{
		superLook();
}

void whichWay()
{
	lookAround();
	analyze();
	godir = decide();
	if (godir == 9999)
	{

		getCloser();
		lookAround();
		analyze();
		godir = decide();
		if (godir == 9999)
		{
			getCloser();
			lookAround();
			analyze();
			godir = decide();
			if (godir == 9999)
			{
				godir = facing + 1800;
			}
		}

	}

	faceDirection(godir);
}

task main()
{
	wait1Msec(50);
	while (true)
	{
		whichWay();
		proceed();
	}
}
