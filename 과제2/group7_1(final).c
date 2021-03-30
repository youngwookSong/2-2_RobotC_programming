#pragma config(Sensor, S1,     c1,             sensorEV3_Color)
#pragma config(Sensor, S2,     c2,             sensorEV3_Color)
#pragma config(Sensor, S3,     c3,             sensorEV3_Color)
#pragma config(Motor,  motorB,          lm,            tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rm,            tmotorEV3_Large, PIDControl, driveRight, encoder)
#define DIFF 10

int nMotorSpeedSetting = 30;
int vertex=0, count=0, row=0, val, r=0, c = 0, result =0 ;

int S[6][6], dt[6][6];


#define Black 1
#define Blue 2
#define Green 3
#define Yellow 4
#define Red 5
#define White 6
#define Brown 7

//print array S
void printgraph3()
{
    char c;
    for (int y = 0; y<5; y++) {
        for(int x = 0; x<5; x++){

            displayStringAt( (x+1) * 10 , 100 - (y+1)*10, "%d", S[y][x]);
        }
    }
    sleep(5000);

}

//print 'o', 'x'
void printgraph()
{
    char c;
    for (int y = 0; y<5; y++) {
        for(int x = 0; x<5; x++){
            if (S[y][x] == -1) c = 'X';
            else if(S[y][x] == 1 ) c = 'O';
            else c = '+';

            displayStringAt( (x+1) * 10 , 100 - (y+1)*10, "%c", c);
        }
    }
    sleep(5000);
}


void stopMotor()
{
   setMotorSpeed(lm, 0);
   setMotorSpeed(rm, 0);
}

void go()
{
   val = 4;//7
   for(int i=0; i<4; i++)
     {
        if(getColorName(c2)==Red)
        {
           if(row%2==0) S[row][count]=1;
           else S[row][4-count]=1;
           displayBigTextLine(3, "col : %d", getColorName(c2));
        }
        else if (getColorName(c2)==Blue)
        {
           if(row%2==0) S[row][count]=-1;
           else S[row][4-count]=-1;
           displayBigTextLine(3, "col : %d", getColorName(c2));
        }
        else
        {
          displayBigTextLine(3, "col : %d", getColorName(c2));
        }
      }

    if(getColorName(c2) == Black) {
      setMotorSpeed(lm, nMotorSpeedSetting - val);
      setMotorSpeed(rm, nMotorSpeedSetting + val);
    }
    else {
      setMotorSpeed(lm, nMotorSpeedSetting + val);
      setMotorSpeed(rm, nMotorSpeedSetting - val);
    }
      if(row!=4)
    {
         if(getColorName(c1)== Black || getColorName(c3)==Black){

          vertex++;
          playTone(440,20);
          nMotorSpeedSetting=10; //change
         sleep(80);}
       else
       {
          vertex =0;
          nMotorSpeedSetting=30; //change
       }
     }
     else
     {
        if(getColorName(c1)== Black){

          vertex++;
          playTone(440,20);
          nMotorSpeedSetting=10; //change
         sleep(80);}
       else
       {
          vertex =0;
          nMotorSpeedSetting=30; //change
       }
     }
   if(vertex == 1) {count++; //displayBigTextLine(5, "%d", count);
   }
}

void turnLeft()
{
   setMotorSpeed(lm, 40);
   setMotorSpeed(rm, 40);
   sleep(150);


   while(getColorName(c1) > Black)
   {
      setMotorSpeed(lm, -nMotorSpeedSetting * 6/10);
      setMotorSpeed(rm, +nMotorSpeedSetting * 6/10);
      sleep(10);
   }
   while(getColorName(c2) > Black)
   {
      setMotorSpeed(lm, -nMotorSpeedSetting * 6/10);
      setMotorSpeed(rm, nMotorSpeedSetting * 6/10);
   }
   sleep(100);
   setMotorSpeed(lm,0);
   setMotorSpeed(rm,0);
   sleep(100);
}

void turnRight()
{
   setMotorSpeed(lm, 40);
   setMotorSpeed(rm, 40);
   sleep(150);

   while(getColorName(c3) > Black)
   {
      setMotorSpeed(lm, nMotorSpeedSetting * 6/10);
      setMotorSpeed(rm, -nMotorSpeedSetting * 6/10);
      sleep(10);
   }
   while(getColorName(c2) > Black)
   {
      setMotorSpeed(lm, nMotorSpeedSetting * 6/10);
      setMotorSpeed(rm, -nMotorSpeedSetting * 6/10);
      //sleep(5);
   }
   sleep(100);
   setMotorSpeed(lm,0);
   setMotorSpeed(rm,0);
   sleep(100);
}

void completeSearch()
{
   while(true)
   {
      go();
      if(count == 4)
      {
         if(row==4) return;
         if(row%2==0)
         {
            setMotorSpeed(lm,35);
            setMotorSpeed(rm,30);
            for(int i=0; i<4; i++)
            {
               if(getColorName(c2)==Red)
               {
                  if(row%2==0) S[row][count]=1;
                  else S[row][4-count]=1;
               }
               else if (getColorName(c2)==Blue)
               {
                  if(row%2==0) S[row][count]=-1;
                  else S[row][4-count]=-1;
               }
               //else sleep(90);
            }
            sleep(300); //sleep(400);
            turnRight();
         }
         else
         {
            for(int i=0; i<4; i++) //i<3
            {
               if(getColorName(c2)==Red)
               {
                  if(row%2==0) S[row][count]=1;
                  else S[row][4-count]=1;
                  //playTone(440,20);
                  //sleep(80);
               }
               else if(getColorName(c2)==Blue)
               {
                  if(row%2==0) S[row][count]=-1;
                  else S[row][4-count]=-1;
                  //playTone(440,20);
                  //sleep(80);
               }
               //else sleep(90);
            }
            sleep(300);
            turnLeft();
         }
         if(row%2==0)
         {
            while(getColorName(c3)==White) go();
            setMotorSpeed(lm,30); //decline 5
            setMotorSpeed(rm,25);
            sleep(400);
            turnRight();
         }
         else
         {
            while(getColorName(c1)==White) go();
            setMotorSpeed(lm,25); //decline 5
            setMotorSpeed(rm,30);
            sleep(400);
            turnLeft();
         }
         row++;
         count=0;
         sleep(410);
      }
   }
}

int max(int a, int b)
{
   return a>b ? a:b
}

void goUp()
{
    r--; row++;
    turnRight();
    count = 0;
    while(true)
    {
        go();
        if(count == 1)
        {
            sleep(300);
            turnLeft();
            break;
        }
    }
    //scoreResult();
}

void goDown()
{
    r++; row--;
    turnLeft();
    count = 0;
    while(true)
    {
        go();
        if(count == 1)
        {
            sleep(300);
            turnRight();
            break;
        }
    }
    //scoreResult();
}

void goLeft()
{
    c--;
    count = 0;
    while(true)
    {
        go();
        if(count == 1)
        {
            setMotorSpeed(lm, 30);
            setMotorSpeed(rm, 30);
            sleep(400);
            break;
        }
    }
    //scoreResult();
}


task main()
{
   while(getButtonPress(1) == 0) {    displayBigTextLine(3, "col : %d", getColorName(c2));   }
   while(getButtonPress(1) == 1) {}; eraseDisplay();
    while(getButtonPress(1) == 0) {    displayBigTextLine(3, "col : %d", getColorName(c2));   }
   while(getButtonPress(1) == 1) {}; eraseDisplay();

    completeSearch();


    setMotorSpeed(lm, 0);
    setMotorSpeed(rm, 0);
    sleep(1000);
    printgraph();

    setMotorSpeed(lm, 20);
    setMotorSpeed(rm, 20);
    sleep(1000);

    setMotorSpeed(lm, 20);
    setMotorSpeed(rm, -20);
    sleep(400);

    turnRight();


    count = row = 0;

    for(int i=0;i<5;i++)
       for(int j=0;j<5;j++)
       {
          if(i==0 && j==0)dt[i][j]=S[i][j];
          else if(i==0) dt[i][j]=dt[i][j-1]+S[i][j];
          else if(j==0) dt[i][j]=dt[i-1][j]+S[i][j];
          else dt[i][j]=max(dt[i-1][j], dt[i][j-1])+S[i][j];
       }

    row=0; r=c=4;
    while(r!=0 || c!=0)
    {
       if(r==0) goLeft();
       else if(c==0) goUp();
       else if (dt[r-1][c] > dt[r][c-1]) goUp();
       else goLeft();
      result += S[r][c];
    }

    displayBigTextLine(5,"final score is %d",result); //this is display final score
    //displayBigTextLine(5,"%d",dt[4][4]);
    //print final score. if it is wrong change to dt[0][0] or dt[5][5] or dt[6][6]
    //playTone(240,20); sleep(200);
    stopMotor();
    while(getButtonPress(1)==0) sleep(10);
}