#pragma config(StandardModel, "RVW Buggybot")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//#pragma config(Sensor, S3, lightSensor, sensorLightActive)


void goRight()
{
		turnRight(154, degrees, 25);

}

void goLeft()
{
		turnLeft(154, degrees, 25);

}

void goForward()
{
		forward(0.125, rotations, 50);
}



void findLine()
{
	  while (SensorValue(light) > 65)
		{
    		goForward();
		}
		stopAllMotors();
}

task main()
{
		wait1Msec(50);

    goRight();
    forward(2, rotations, 50);
    findLine();

    forward(1, rotations, 50);
    goLeft();
    forward(1, rotations, 50);
    findLine();

    forward(1, rotations, 50);
    goLeft();
    forward(1, rotations, 50);
    findLine();

    forward(1, rotations, 50);
    goRight();
    forward(1, rotations, 50);
    findLine();

    findLine();

    findLine();

    findLine();


    forward(1, rotations, 50);
    goRight();
    findLine();

    forward(1, rotations, 50);
    goRight();
    findLine();



    forward(1, rotations, 50);
    goLeft();
    forward(1, rotations, 50);
    findLine();


    forward(1.25, rotations, 50);
    goLeft();
    findLine();


}
