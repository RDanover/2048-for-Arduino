#include <LiquidCrystal.h>


// Array of Output Pin variables, set to the pins being used
const int rs = 4, en = 5, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int xAxis = A0; 
const int yAxis = A1;
const int joystickButton = 2;

const int xAxis_median = 450; // Adjust this if needed
const int yAxis_median = 450;
int score =0;
int flag =0;
int gameflag=0;
int gameboard [2][8]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//

byte Sixteen [8]={
  B11111,
  B11001,
  B10101,
  B10011,
  B10101,
  B11001,
  B10101,
  B11111};
  
byte ThirtyTwo [8]={
  B11111,
  B11011,
  B11011,
  B10101,
  B10101,
  B11011,
  B11011,
  B11111
};

byte SixtyFour [8]={
  B11111,
  B10001,
  B11111,
  B10001,
  B11111,
  B10001,
  B11111,
  B11111
};

byte OneTwentyEight [8]={
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte TwoFiftySix [8]={
  B11111,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B11111
};

byte FiveTwelve [8]={
  B11111,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11111
};

byte OneThousandTwentyFour [8]={
  B11111,
  B10101,
  B10101,
  B10101,
  B10101,
  B10101,
  B10101,
  B11111
};

byte TwoThousandFortyEight [8]={
  B11111,
  B11011,
  B10101,
  B11011,
  B10101,
  B11011,
  B10101,
  B11111
};

int randomNumGen(int m,int M){
  int seed = analogRead(0);
  int num = (seed%(M-m))+ m;//this creates a range that is inclusive of the minimum and exclusive of the maximum
  if(num<0){
    num*=-1;
  }
  return num;
}

void spawnTile(int d){
  int topRow [8]= {-1,-1,-1,-1,-1,-1,-1,-1};
  int topRowI =0;
  int bottomRow [8]= {-1,-1,-1,-1,-1,-1,-1,-1};
  int bottomRowI =0;
  int TopI=-1;
  int BotI=-1;
  if(d==1||d==4){//spawn a tile in the bottom row if possible
    
        for(int c=0;c<8;c++){
          if(gameboard[1][c]==0){
            bottomRow[bottomRowI]=c;
            bottomRowI++;
          }
        }
        if(bottomRowI==0){
           for(int d=0;d<8;d++){
              if(gameboard[0][d]==0){
                topRow[topRowI]=d;
                topRowI++;
              }
          }
          if(topRowI==0){
            return;
          }
          else{
            TopI=randomNumGen(0,topRowI);
            gameboard[0][topRow[TopI]]=2;
          }
        }
        else{
          BotI=randomNumGen(0,bottomRowI);
          gameboard[1][bottomRow[BotI]]=2;
        }

  }
  else if (d==3||d==2){//spawn a tile in the top row if possible
       for(int c=0;c<8;c++){
          if(gameboard[0][c]==0){
            topRow[topRowI]=c;
            topRowI++;
          }
        }
        if(topRowI==0){
           for(int d=0;d<8;d++){
              if(gameboard[1][d]==0){
                bottomRow[bottomRowI]=d;
                bottomRowI++;
              }
          }
          if(bottomRowI==0){
            return;
          }
          else{
            BotI=randomNumGen(0,bottomRowI);
            gameboard[1][bottomRow[BotI]]=2;
          }
        }
        else{
          TopI=randomNumGen(0,topRowI);
          gameboard[0][topRow[TopI]]=2;
        }
  }
  
}

void MergeTiles(int d){//check to see if the game has been lost or combines tiles if possible
  flag=-1;
  for (int r=0;r<2;r++){
    for(int c=0;c<8;c++){
        if(c<7&&flag<0){
          if(gameboard[r][c]==gameboard[r][c+1]){
            flag=0;
          }
        }
        if(r<1&&flag<0){
          if(gameboard[r][c]==gameboard[r+1][c]){
            flag=0;
          }
        }
        
        if(c<7){
          if(gameboard[r][c]==gameboard[r][c+1]&&d==4){//left merge
            gameboard[r][c]=gameboard[r][c]+gameboard[r][c+1];
            gameboard[r][c+1]=0;
            score+=gameboard[r][c];
          }
          else if(gameboard[r][c]==gameboard[r][c+1]&&d==2){//right merge
            gameboard[r][c+1]=gameboard[r][c]+gameboard[r][c+1];
            gameboard[r][c]=0;
            score+=gameboard[r][c+1];
          }
        }
        if(r<1){
          if(gameboard[r][c]==gameboard[r+1][c]&&d==1){//up merge
            gameboard[r][c]=gameboard[r][c]+gameboard[r+1][c];
            gameboard[r+1][c]=0;
            score+=gameboard[r][c];
          }
          else if(gameboard[r][c]==gameboard[r+1][c]&&d==3){//down merge
            gameboard[r+1][c]=gameboard[r][c]+gameboard[r+1][c];
            gameboard[r][c]=0;
            score+=gameboard[r+1][c];
          }
        }

    }
  }
}

void moveGameboard(int d){//move the gameboard according to the movement input
      int LAI=-1;
      if(d==1){//move board up
          for(int c=0;c<8;c++){
              if(gameboard[0][c]==0){
                gameboard[0][c]= gameboard[1][c];
                gameboard[1][c]= 0;
              }
          }
      }
      else if(d==3){//move board down
        for(int c=0;c<8;c++){
              if(gameboard[1][c]==0){
                gameboard[1][c]= gameboard[0][c];
                gameboard[0][c]= 0;
              }
          }
      }
      else if(d==2){//move board right
        int topRow [8]= {0,0,0,0,0,0,0,0};
        int topRowI =0;
        int bottomRow [8]= {0,0,0,0,0,0,0,0};
        int bottomRowI =0;
        
        for(int c=0;c<8;c++){
              if(gameboard[0][c]!=0){
                topRow[topRowI]=gameboard[0][c];
                gameboard[0][c]=0;
                topRowI++;
              }
        }
        for(int d=0;d<8;d++){
              if(gameboard[1][d]!=0){
                bottomRow[bottomRowI]=gameboard[1][d];
                gameboard[1][d]=0;
                bottomRowI++;
              }
        }
        topRowI--;
        bottomRowI--;
        for(int e=7;e>=0;e--){
            if(topRowI>=0){
              gameboard[0][e]=topRow[topRowI];
              topRowI--;
            }
            else{
              gameboard[0][e]=0;
            }
        }
        for(int f=7;f>=0;f--){
            if(bottomRowI>=0){
              gameboard[1][f]=bottomRow[bottomRowI];
              bottomRowI--;
            }
            else{
              gameboard[1][f]=0;
            }
        }
        
      }
      else if(d==4){//move board left
        int topRow [8]= {0,0,0,0,0,0,0,0};
        int topRowI =0;
        int bottomRow [8]= {0,0,0,0,0,0,0,0};
        int bottomRowI =0;
        
        for(int c=0;c<8;c++){
              if(gameboard[0][c]!=0){
                topRow[topRowI]=gameboard[0][c];
                gameboard[0][c]=0;
                topRowI++;
              }
        }
        for(int d=0;d<8;d++){
              if(gameboard[1][d]!=0){
                bottomRow[bottomRowI]=gameboard[1][d];
                gameboard[1][d]=0;
                bottomRowI++;
              }
        }

        for(int e=0;e<8;e++){
            gameboard[0][e]=topRow[e];
        }
        for(int f=0;f<8;f++){
            gameboard[1][f]=bottomRow[f];
        }
      }

}

void updateGameboard(){//prints the gameboard to the screen
  lcd.clear();
  for (int r=0;r<2;r++){
    for(int c=0;c<8;c++){
      if(gameboard[r][c]!=0){
         lcd.setCursor(c,r);
         if(gameboard[r][c]==2){
          lcd.print("2");
         }
         if(gameboard[r][c]==4){
          lcd.print("4");
         }
         else if(gameboard[r][c]==8){
           lcd.print("8");
         }
          else if(gameboard[r][c]==16){
          lcd.write(byte(0));
         }
          else if(gameboard[r][c]==32){
           lcd.write(byte(1));
         }
          else if(gameboard[r][c]==64){
           lcd.write(byte(2));
         }
          else if(gameboard[r][c]==128){
           lcd.write(byte(3));
         }
          else if(gameboard[r][c]==256){
          lcd.write(byte(4));
         }
          else if(gameboard[r][c]==512){
           lcd.write(byte(5));
         }
          else if(gameboard[r][c]==1024){
           lcd.write(byte(6));
         }
          else if(gameboard[r][c]==2048){
           lcd.write(byte(7));
           flag = 1;
         }
      }

    }
  }
}

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
    
} task;
int delay_gcd;



const unsigned short tasksNum = 2;
task tasks[tasksNum];

enum SM1_States { StartScreen,Play2048,Win2048,Lose2048,Reset2048 };
int SM1_Tick(int state){
  switch(state){ // State transitions
    case StartScreen:
      if(digitalRead(joystickButton)==LOW){
        state=Play2048;
        lcd.clear();
        spawnTile(randomNumGen(1,5));
        spawnTile(randomNumGen(1,5));
        updateGameboard();
        gameflag=1;
      }
      break;
    case Play2048:
      if(digitalRead(joystickButton)==LOW){
        state=Reset2048;
        gameflag=0;
      }
      else if(flag==1){
        state=Win2048;
        gameflag=0;
      }
      else if(flag==-1){
        state=Lose2048;
        gameflag=0;
      }
      break;
    case Win2048:
      if(digitalRead(joystickButton)==LOW){
        state=Reset2048;
      }
      break;
    case Lose2048:
      if(digitalRead(joystickButton)==LOW){
        state=Reset2048;
      }
      break;
    case Reset2048:
        state=StartScreen;
      break;
  }
  
  switch(state){ // State Actions
    case StartScreen:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("2048");
      lcd.setCursor(0,1);
      lcd.print("Button: Play");
      break;
    case Play2048:
        if(analogRead(xAxis) > xAxis_median+100){//down
          
          moveGameboard(3);
          MergeTiles(3);
          moveGameboard(3);
          spawnTile(3);
          updateGameboard();
        }
        else if(analogRead(xAxis) < xAxis_median){//up
          
          moveGameboard(1);
          MergeTiles(1);
          moveGameboard(1);
          spawnTile(1);
          updateGameboard();
        }
        else if(analogRead(yAxis) > (yAxis_median+100)){//left
          
          moveGameboard(4);
          MergeTiles(4);
          moveGameboard(4);
          spawnTile(4);
          updateGameboard();
        }
        else if(analogRead(yAxis) < (yAxis_median)){//right
          
          moveGameboard(2);
          MergeTiles(2);
          moveGameboard(2);
          spawnTile(2);
          updateGameboard();
        }

      break;
    case Win2048:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.write("YOU WIN :)");
      break;
    case Lose2048:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.write("YOU LOSE :(");
      break;
    case Reset2048:
      lcd.clear();
      lcd.setCursor(0,0);
      flag=0;
      score=0;
      for(int r=0;r<2;r++){
        for(int c=0;c<8;c++){
          gameboard [r][c]=0;
        }
      }
      break;
  }
  return state;
}

enum SM2_States { SM2_INIT,SM2_updateScore};
int SM2_Tick(int state){
  switch(state){ // State transitions/actions
    case SM2_INIT:
      state=SM2_updateScore;
      break;
    case SM2_updateScore:
      if(gameflag==1){
      lcd.setCursor(8,0);//
      lcd.print("|");
      lcd.setCursor(8,1);//
      lcd.print("|");
      lcd.setCursor(9,0);//
      lcd.print("0000000");
      if(score<=9){
        lcd.setCursor(15,0);
        lcd.print(score);
      }
      else if(score<=99){
        lcd.setCursor(14,0);
        lcd.print(score);
      }
      else if(score<=999){
        lcd.setCursor(13,0);
        lcd.print(score);
      }
      else if(score<=9999){
        lcd.setCursor(12,0);
        lcd.print(score);
      }
      else if(score<=99999){
        lcd.setCursor(11,0);
        lcd.print(score);
      }
      else if(score<=999999){
        lcd.setCursor(10,0);
        lcd.print(score);
      }
      else if(score<=9999999){
        lcd.setCursor(9,0);
        lcd.print(score);
      }
      else{
        lcd.setCursor(9,0);
        lcd.print("9999999");
      }
      }
      break;
  }
  return state;
}

void setup() {


  unsigned char i = 0;
  tasks[i].state = StartScreen;
  tasks[i].period = 400;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_Tick;
  i++;
  tasks[i].state = SM2_INIT;
  tasks[i].period = 200;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;
  pinMode(joystickButton,INPUT_PULLUP);
  
  delay_gcd = 200; // GCD
  lcd.begin(16,2);//Possibly change this
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.createChar(0,Sixteen);
  lcd.createChar(1,ThirtyTwo);
  lcd.createChar(2,SixtyFour);
  lcd.createChar(3,OneTwentyEight);
  lcd.createChar(4,TwoFiftySix);
  lcd.createChar(5,FiveTwelve);
  lcd.createChar(6,OneThousandTwentyFour);
  lcd.createChar(7,TwoThousandFortyEight);
}


void loop() {
  // put your main code here, to run repeatedly:
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
      
     }
   }
  delay(delay_gcd); // GCD.
}