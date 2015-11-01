#define lmotorf 5
#define lmotorb 6
#define rmotorf 10
#define rmotorb 11
#define irleft 2
#define ircentre 3
#define irright 4 
#define Switch 13

int goStraight = 500;
int rotateTime = 1500;
int i=0;
char ar[20],c;
void fun(); 
int left=0; 
int centre=0;
int right=0;


void setup() {
  pinMode (irleft, INPUT);
  pinMode (ircentre, INPUT);
  pinMode (irright, INPUT); 
  pinMode (lmotorf, OUTPUT);
  pinMode (lmotorb, OUTPUT);
  pinMode (rmotorf, OUTPUT);
  pinMode (rmotorb, OUTPUT);
  left = digitalRead (irleft);
centre = digitalRead (ircentre);
right = digitalRead (irright);

 
}
// switch open
void loop() 
{
  if(digitalRead(Switch) != 0)
  {
    left = digitalRead (irleft);
    centre = digitalRead (ircentre);
    right = digitalRead (irright);

    if(digitalRead (irleft) == 1 && digitalRead (ircentre) == 0 && digitalRead (irright) == 1)
    {
      moveForward();
    }
    if(digitalRead (irleft) == 0 && digitalRead (ircentre) == 0 && digitalRead (irright) == 1)     // L intersection: Left side
    {
      while (digitalRead (irleft) == 0 && digitalRead (ircentre) == 0 && digitalRead (irright) == 1)     // delay Gostraight
      {
        moveForward();
      }
      delay(goStraight);
      turnLeft();
      delay(rotateTime);
    }
 
    if(digitalRead (irleft) == 1 && digitalRead (ircentre) == 0 && digitalRead (irright) == 0)          // L intersection: right side
    {
      while (digitalRead (irleft) == 1 && digitalRead (ircentre) == 0 && digitalRead (irright) == 0)
      {
        moveForward();
      
      delay(goStraight);

      if (digitalRead (irleft) == 1 && digitalRead (ircentre) == 0 && digitalRead (irright) == 1)            // If straight line detected break out of if braces
      {
        break;
      }
      turnRight();
      delay (rotateTime);
      }
    }
 
    if(digitalRead (irleft) == 0 && digitalRead (ircentre) == 0 && digitalRead (irright) == 0)    // T interseection
    {
      while (digitalRead (irleft) == 0 && digitalRead (ircentre) == 0 && digitalRead (irright) == 0){
        moveForward();
    }
    delay(goStraight);
    turnLeft();
    delay(rotateTime); 
  } 
 
  if(digitalRead (irleft) == 1 && digitalRead (ircentre) == 1 && digitalRead (irright) == 1)   // dead End
  {
    turnBack();
  }

}

  else           // Main Run
  {
  
  while(ar[i]!='\0')
  { 
    if(digitalRead (irleft) == 0 || digitalRead (irright) == 0)      // Check For intersection
    {
      if(digitalRead (irleft) == 0)         
      {
        if(digitalRead (ircentre) == 0)
        {
          if(ar[i]=='l')
          {
            turnLeft();
            i++;
          }
          if(ar[i]=='r')
          {
            turnRight();
            i++;
          }
          if(ar[i]=='s')
          {
            moveForward();
            i++;
          }
        }
        else
        {
          if(digitalRead (irright) == 0)
          {
            digitalWrite (lmotorf, LOW);
            digitalWrite (lmotorb, LOW);
            digitalWrite (rmotorf, LOW);
            digitalWrite (rmotorb, LOW);
          }
        }
      }
      else
      {
        if(digitalRead (irright)== 0)
        { 
          if(ar[i]=='l')
          { 
            turnLeft();
            i++;
          }
          if(ar[i]=='r')
          {
            turnRight();
            i++;
          }
          if(ar[i]=='s')
          {
            moveForward();
            i++;
          }
        }
      }
    }
  }
}
}




void moveForward()
{
  digitalWrite (lmotorf, HIGH);      // digitalRead (irleft) Motor Forward
  digitalWrite (lmotorb, LOW);
  digitalWrite (rmotorf, HIGH);      // Right Motor Forward
  digitalWrite (rmotorb, LOW);
  ar[i]='s';
  fun();
  i++;
}

void turnLeft()
{
  
  digitalWrite (lmotorf, LOW);      // Left Motor Backward
  digitalWrite (lmotorb, HIGH);
  digitalWrite (rmotorf, HIGH);     // Right Motor Forward
  digitalWrite (rmotorb, LOW);
  ar[i]='l';
  fun();
  i++;  
}
 
void turnRight()
{
  
  digitalWrite (lmotorf, HIGH);    // Left Motor forward 
  digitalWrite (lmotorb, LOW);
  digitalWrite (rmotorf, LOW);    //Right Motor backward
  digitalWrite (rmotorb, HIGH);
  ar[i]='r';
  fun();
  i++;
}



void turnBack()
{
  ar[i]='u';
  fun();
  i++;
  turnRight();
  delay (2 * rotateTime);
}




void fun()
{
  if(ar[i-1]=='u')
  {
    if(ar[i]=='l')
    {
        if(ar[i-2]=='l')
        {
        c='s';
        }
        if(ar[i-2]=='r')
        {
        c='u';
        }
        if(ar[i-2]=='s')
        {
        c='r';
        }
      }
      if(ar[i]=='r')
    {
        if(ar[i-2]=='l')
        {
        c='u';
        }
        if(ar[i-2]=='r')
        {
        c='s';
        }
        if(ar[i-2]=='s')
        {
        c='l';
        }
    }
    if(ar[i]=='s')
    {
        if(ar[i-2]=='l')
        {
        c='r';
        }
        if(ar[i-2]=='r')
        {
        c='l';
        }
        if(ar[i-2]=='s')
        {
        c='u';
        }
  }
  ar[i-2]=c;
  i=i-1;
}

}


