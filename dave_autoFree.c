#pragma config(StandardModel, "RVW Buggybot")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int speedvalue = 60;
int turnSpeed = 15;
short facing = 0;  //direction robot is facing
short gyro1 = 0;
short openPath = 35;
short stopNow = 25;
short stopCloser = 15;
short son1 = 0;
short bigTurn = 159;
short medTurn = 79.5;
short minTurn = 39;
short micTurn = 19;
const int padlen = 8;
short padson1[padlen];


void goBackward()
{
	backward(0.1, rotations, speedvalue);
}

void readSensor()
{
	waitUntilMotorStop(leftMotor);
	waitUntilMotorStop(rightMotor);
	son1 = SensorValue(sonar);
	gyro1 = SensorValue(gyro);
}

void checkTooClose()
{
	son1 = SensorValue(sonar);
	if (son1 < stopCloser)
	{
		goBackward();
	}
}


void goLeft(short amt)
{
	checkTooClose();
	turnLeft(amt, degrees, turnSpeed);
	readSensor();

}

void goRight(short amt)
{
	checkTooClose();
	turnRight(amt, degrees, turnSpeed);
	readSensor();

}

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


void getPadding()
{
	for (int i1 = 0; i1 < padlen; i1++)
  {
     goRight(medTurn);
     padson1[i1] = son1;
  }
}


void proceed()
{
	int ct1 = 0;
	facing = SensorValue(gyro);

	while (SensorValue(sonar) > stopNow)
	{
		resetTimer(T1);
		ct1 = 0;
		while ((SensorValue(sonar) > stopNow) & (ct1 < 5000))
		{
			goForward();
			ct1 = getTimer(T1, milliseconds);
		}
		getPadding();
	}
}


bool lookRight()
{
	bool found = true;
	son1 = SensorValue(sonar);
	while ((son1 < openPath))
	{
		if (SensorValue(gyro) > (facing + 500))
		{
			found = false;
			break;
		}

		goRight(minTurn);

		son1 = SensorValue(sonar);
	}
	return found;
}


void lookFarRight()
{

	son1 = SensorValue(sonar);
	while ((son1 < openPath))
	{
  	goRight(minTurn);

		son1 = SensorValue(sonar);
	}
}


bool lookLeft()
{
	bool found = true;
	goLeft(minTurn);

	son1 = SensorValue(sonar);
	if (son1 < openPath)
	{
		found = false;
	}
	return found;
}


bool firstLook()
{
	bool found = true;
	goRight(bigTurn);

	if (son1 < openPath)
	{
		goLeft(bigTurn * 2);

		if (son1 < openPath)
		{
			goRight(bigTurn); //back to orig heading
			found = false;
		}
	}
	return found;
}


bool secondLook()
{
	bool found = true;
	goRight(medTurn);

	if (son1 < openPath)
	{
		goRight(medTurn);


		if (son1 < openPath)
		{
			goLeft(bigTurn);
			goLeft(medTurn);

			if (son1 < openPath)
			{
				goLeft(medTurn);
				if (son1 < openPath)
				{
					found = false;
					goRight(bigTurn);  //return to orig
				}
			}
		}
	}
	return found;
}




void lookAround()
{
	son1 = SensorValue(sonar);

	if (firstLook() != true)
	{
		getCloser();
		if (secondLook() != true)
		{
			if (lookRight() != true)
			{
				if (lookLeft() != true)
				{
					lookFarRight();
				}
			}
		}
	}
}


void whichWay()
{
	lookAround();
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
