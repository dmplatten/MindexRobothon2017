#pragma config(StandardModel, "RVW Buggybot")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int speedvalue = 40;
int turnSpeed = 15;
short gyro1 = 0;
short facing = 0;  //direction robot is facing
short north = 0;
short south = 0;
short east = 0;
short west = 0;
short openPath = 30;

void goSlightLeft()
{
		turnLeft(5, degrees, turnSpeed);
}

void goSlightRight()
{
		turnRight(5, degrees, turnSpeed);
}

void goRight()
{
		turnRight(159, degrees, turnSpeed);
}

void goLeft()
{
		turnLeft(159, degrees, turnSpeed);
}

void goForward()
{
		forward(0.049, seconds, speedvalue);
}


void proceed()
{
	while (SensorValue(sonar) > 19)
	{
		goForward();
	}

}


void faceEast()
{
		while ((gyro1 < 895) | (gyro1 > 905))
		{
			gyro1 = SensorValue(gyro);
			if (gyro1 > 900)
			{
				if ((gyro1 - 900) > 800)
				{
					goLeft();
				}
				else
				{
					goSlightLeft();
				}
			}
			else
			{
				if ((900 - gyro1) > 800)
				{
					goRight();
				}
				else
				{
					goSlightRight();
				}
			}
		}
}

void faceSouth()
{
		while ((gyro1 < 1795) | (gyro1 > 1805))
		{
			gyro1 = SensorValue(gyro);
			if (gyro1 > 1800)
			{
				if ((gyro1 - 1800) > 800)
				{
					goLeft();
				}
				else
				{
					goSlightLeft();
				}
			}
			else
			{
				if ((1800 - gyro1) > 800)
				{
					goRight();
				}
				else
				{
					goSlightRight();
				}
			}
		}
}

void faceWest()
{
		while ((gyro1 < 2695) | (gyro1 > 2705))
		{
			gyro1 = SensorValue(gyro);
			if (gyro1 > 2700)
			{
				if ((gyro1 - 2700) > 800)
				{
					goLeft();
				}
				else
				{
					goSlightLeft();
				}
			}
			else
			{
				if ((2700 - gyro1) > 800)
				{
					goRight();
				}
				else
				{
					goSlightRight();
				}
			}
		}
}

void faceNorth()
{
		while ((gyro1 < -5) | (gyro1 > 5))
		{
			gyro1 = SensorValue(gyro);
			if (gyro1 > 0)
			{
				if ((gyro1 - 0) > 800)
				{
					goLeft();
				}
				else
				{
					goSlightLeft();
				}
			}
			else
			{
				goSlightRight();
			}
		}
}

void resumeDirection()
{
	//turn to original direction robot was facing
	if (facing > 2500)
	{
		faceWest();
	}
	else if (facing > 1600)
	{
		faceSouth();
	}
	else if (facing > 700)
	{
		faceEast();
	}
	else
	{
		faceNorth();
	}
}

void lookAround()
{
		facing = gyro1;  //store direction facing

		faceNorth();
		north = SensorValue(sonar);
		faceEast();
		east = SensorValue(sonar);
		faceSouth();
		south = SensorValue(sonar);
		faceWest();
		west = SensorValue(sonar);

		resumeDirection();
}

void whichWay()
{

	lookAround();

	if (gyro1 > 2500) //facing west
	{
		//try to go north
		if (north > openPath)
		{
			faceNorth();
		}
		else if (west > openPath)
		{
			faceWest();
		}
		else if (south > openPath)
		{
			faceSouth();
		}
		else if (east > openPath)
		{
			faceEast();
		}

	}
	else if (gyro1 > 1600) //facing south
	{
		//try to go west


		if (west > openPath)
		{
			faceWest();
		}
		else if (south > openPath)
		{
			faceSouth();
		}
		else if (east > openPath)
		{
			faceEast();
		}
		else if (north > openPath)
		{
			faceNorth();
		}
	}
	else if (gyro1 > 700) //facing east
	{
		//try to go south
		if (south > openPath)
		{
			faceSouth();
		}
		else if (east > openPath)
		{
			faceEast();
		}
		else if (north > openPath)
		{
			faceNorth();
		}
		else if (west > openPath)
		{
			faceWest();
		}
	}
	else if (gyro1 < 100) //facing north
	{
		//try to go east
		if (east > openPath)
		{
			faceEast();
		}
		else if (north > openPath)
		{
			faceNorth();
		}
		else if (west > openPath)
		{
			faceWest();
		}
		else if (south > openPath)
		{
			faceSouth();
		}
	}
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
