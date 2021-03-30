#pragma config(Sensor, S1,     c1,             sensorEV3_Color)
#pragma config(Sensor, S2,     c2,             sensorEV3_Color)
#pragma config(Sensor, S3,     c3,             sensorEV3_Color)
#pragma config(Motor,  motorB,          lm,            tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rm,            tmotorEV3_Large, PIDControl, driveRight, encoder)
#define DIFF 10

int nMotorSpeedSetting = 30;
int vertex=0, count=0, row=0, val, r=0, c = 0, result =0 ;
int totalred=0;
int S[6][6];
int red[5];
int red_2[5];
int X=4, Y=4;
int x=4, y=4;


#define Black 1
#define Blue 2
#define Green 3
#define Yellow 4
#define Red 5
#define White 6
#define Brown 7


int SS[5][5] = { 0, 5, 0, 5, 0,
            0, -3, 0, -3, -3,
            0, 5, 0, 0, 0,
            0, 0, -3, -3, 5,
            0, 0, 0, 5, 0 };
/*
void printgraph()
{
    char c;
    for (int y = 0; y<5; y++) { //y<6
        for(int x = 0; x<5; x++){ //y<6
            if (S[y][x] == -1) c = 'X';
            else if(S[y][x] == +1 ) c = 'O';
            else c = '+';

            displayStringAt( (x+1) * 10 , 100 - (y+1)*10, "%c", c);
        }
    }
    sleep(10000);

}*/

void printgraph()
{
    for (int y = 0; y<5; y++) {
        for(int x = 0; x<5; x++){
            displayStringAt( (x+1) * 10 , 100 - (y+1)*10, "%d", S[y][x]);
        }
    }
    sleep(10000);

}
//to check final result score we made this function
void scoreResult(){
   if(getColorName(c2)==Red){
      result += 1;
   }
   else if(getColorName(c2)==Blue){
      result -= 1;
   }
}

void stopMotor()
{
   setMotorSpeed(lm, 0);
   setMotorSpeed(rm, 0);
}

void go()
{
   val = 7;
   if(getColorName(c2) == Red)
   {
      if (row % 2 == 0) S[row][count] = 5;
      else S[row][4-count] = 5 ;
      totalred++;
      //playTone(440, 20); sleep(100);
   }
   else if (getColorName(c2) == Blue)
   {
      if (row % 2 == 0) S[row][count] = -3;
      else S[row][4-count] = -3 ;
      //playTone(400, 20); sleep(100);
   }

    if(getColorName(c2) == Black) {
      setMotorSpeed(lm, nMotorSpeedSetting - val);
      setMotorSpeed(rm, nMotorSpeedSetting + val);
    }
    else {
      setMotorSpeed(lm, nMotorSpeedSetting + val);
      setMotorSpeed(rm, nMotorSpeedSetting - val);
    }
    //if (getColorName(c1) == Black || getColorName(c3) == Black) vertex++;
    //else vertex = 0;
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
     /*if(X==0)//plus
     {
        if(getColorName(c1)== Black || getColorName(c3)==Black)
        {
           vertex++;
          playTone(440,20);
          nMotorSpeedSetting=10; //change
         sleep(80);}
       else
       {
          vertex =0;
          nMotorSpeedSetting=30; //change
       }
     }*/


   if(vertex == 1) {count++; //displayBigTextLine(5, "%d", count);
   }
}

void turnLeft()
{
   /*setMotorSpeed(lm, 40);
   setMotorSpeed(rm, 40);
   sleep(150);*/


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
   /*setMotorSpeed(lm, 40);
   setMotorSpeed(rm, 40);
   sleep(150);*/

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
                  if(row%2==0) S[row][count]=5;
                  else S[row][4-count]=5;
                  totalred++;
               }
               else if (getColorName(c2)==Blue)
               {
                  if(row%2==0) S[row][count]=-3;
                  else S[row][4-count]=-3;
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
                  if(row%2==0) S[row][count]=5;
                  else S[row][4-count]=5;
                  totalred++;
                  //playTone(440,20);
                  //sleep(80);
               }
               else if(getColorName(c2)==Blue)
               {
                  if(row%2==0) S[row][count]=-3;
                  else S[row][4-count]=-3;
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
            setMotorSpeed(lm,35);
            setMotorSpeed(rm,30);
            sleep(400);
            turnRight();
         }
         else
         {
            while(getColorName(c1)==White) go();
            setMotorSpeed(lm,30);
            setMotorSpeed(rm,35);
            sleep(400);
            turnLeft();
         }
         row++;
         count=0;
         //setMotorSpeed(lm,-30);
         //setMotorSpeed(rm,-30);
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
           setMotorSpeed(lm, 20); //30
            setMotorSpeed(rm, 20);//30
            sleep(900); //400
            //sleep(300);
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
            setMotorSpeed(lm, 20); //30
            setMotorSpeed(rm, 20);//30
            sleep(700); //400
            break;
        }
    }
    //scoreResult();
}

void goRight() //I modify opposite of goLeft()
{
    c++;
    count = 0;
    turnRight();
    setMotorSpeed(lm,0);
    setMotorSpeed(rm,0);
    sleep(1000);
    //to call turnRight 1 time we turn 90 degree(My thought)
    if(X!=0){
    turnRight();}
    //so we call one more time to turn 90 degree more
    while(true)
    {
        go();
        if(count == 1)
        {
            setMotorSpeed(lm, 20);
            setMotorSpeed(rm, 20);
            sleep(700);
            turnLeft();
            setMotorSpeed(lm,0);
                setMotorSpeed(rm,0);
                sleep(100);
                if(X!=0){
            turnLeft();}
            break;
        }
    }
    //scoreResult();
}

int min_list_index() //red
{
  int min=red[0];
  int index=0;
  for(int i=1;i<5;i++)
  {
    if(red[i]<min)
    {
      min=red[i];
      index=i;
    }
  }
  return index;
}

/*int min_list_index2()//red_2
{
  int min=red_2[0];
  int index=0;
  for(int i=1;i<5;i++)
  {
    if(red_2[i]<min)
    {
      min=red_2[i];
      index=i;
    }
  }
  return index;
}*/

int not_nine_index() //¿A¸￥AE ºIAI °E≫c
{
  int ind=0;
  for (int i=4;i>=0;i--)
  {
    if(red[i]!=9)
    {
      ind=i;
      return ind;
    }
  }
  return ind;
}

int make_9()
{
  for(int i=0;i<5;i++)
  {
    red[i]=9;
  }
  return 0;
}


void gogo()
{
  while (x!=X || y!= Y)
  {
    if(X!=0 && SS[X-1][Y]==-3)//¸¸¾a A§¿
      {
        if(Y<y)
        {
           goRight();
           Y++;
           result -=1;
        }
        else
        {
           goLeft();
           Y--;
           result -=1;
        }
      }
     else if (x<X){ //when go up
         goUp();
         X--;
         result -=1;
     }
     else if(x>X){
         goDown();
         X++;
         result -=1;
     }
     else if(y<Y){//when go left
         goLeft();
         Y--;
         result -=1;
     }
     else if(y>Y){//when go right
         goRight();
    
         Y++;
         result -=1;
     }
  }
}

task main()
{

   while(getButtonPress(1) == 0) sleep(10);
    //displayBigTextLine(5, "%d", count); sleep(10);
    /*completeSearch();
    printgraph();

    setMotorSpeed(lm, 0);
    setMotorSpeed(rm, 0);
    sleep(1000);

    setMotorSpeed(lm, 20);
    setMotorSpeed(rm, 20);
    sleep(1000);
    setMotorSpeed(lm, 20);
    setMotorSpeed(rm, -20);
    sleep(400);
    turnRight();*/
    // setMotorSpeed(lm, -20);
    // setMotorSpeed(rm, 20);
    // sleep(1650); //we will need Uturn modify sleep time
    //turnRight(); if Uturn is not correct just add this function

    count = row = 0;

    make_9();
    int cnt=0;
    for (int rr =4; rr >=0 ; rr--)
    {
      for(int cc=4;cc>=0;cc--)
      {
        if(SS[rr][cc]==5)
        {
           int aa=Y-cc;
           if(aa<0)
              {
                aa=aa*-1;
              }
          red[cc]=aa;
          cnt++;
        }
      }

      while(cnt>0)
      {

        int ind=min_list_index();
        
        x=rr;
        if(x==0) //¸¶Ao¸· Ca¿¡ ÆÐA¡°¡ 2°³ AI≫oAO´U¸e
        {  
           ind=not_nine_index();
          y=ind;
        }
        else
        {
          y=ind;
        }
     
        gogo();

        result +=SS[X][Y];
        red[ind]=9;
        SS[x][y]=-3;

        cnt--;
        totalred--;
        
        displayBigTextLine(5,"re : %d",result);

      }
      
    }
    x=0;
    y=0;
    gogo();
    stopMotor();
   eraseDisplay();
   displayBigTextLine(5,"final : %d",result);sleep(1000); //this is display final score
    //displayBigTextLine(5,"%d",dt[4][4]);
    //print final score. if it is wrong change to dt[0][0] or dt[5][5] or dt[6][6]
    //playTone(240,20); sleep(200);

    while(getButtonPress(1)==0) sleep(10);
}