#include <EasyButton.h>
#include <FastLED.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#define NUM_LEDS 200
#define LED_PIN 7
#define ROWS 20
#define COLUMNS 10

const int buttonPin = 2;
EasyButton pauseButton(2, 10, true, true);//pause, start, play

CRGB leds[NUM_LEDS];
CRGB storeLeds[NUM_LEDS];
int grid[COLUMNS][ROWS];
LiquidCrystal_I2C lcd(0x27, 16, 2);
CRGB colors[7] = {CRGB::Cyan, CRGB::Blue, CRGB::OrangeRed, CRGB::Yellow, CRGB::Green, CRGB::Purple, CRGB::Red}; // I, J, L, O, S, T, Z

CRGB landingPage[20][10] = 
{
  {CRGB::Blue, CRGB::Blue, CRGB::Purple, CRGB::Purple, CRGB::Purple, CRGB::Cyan, CRGB::Cyan, CRGB::Cyan, CRGB::Cyan, CRGB::Red},
  {CRGB::Blue, CRGB::Yellow, CRGB::Yellow, CRGB::Purple, CRGB::Black, CRGB::Black, CRGB::Yellow, CRGB::Yellow, CRGB::Red, CRGB::Red},
  {CRGB::Blue, CRGB::Yellow, CRGB::Yellow, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Yellow, CRGB::Yellow, CRGB::Red, CRGB::OrangeRed},
  {CRGB::Cyan, CRGB::Cyan, CRGB::Cyan, CRGB::Cyan, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::OrangeRed, CRGB::OrangeRed, CRGB::OrangeRed},
  {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black},
  {CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Yellow, CRGB::Yellow, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Purple, CRGB::Black},
  {CRGB::Yellow, CRGB::Yellow, CRGB::OrangeRed, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Purple, CRGB::Purple, CRGB::Cyan},
  {CRGB::OrangeRed, CRGB::OrangeRed, CRGB::OrangeRed, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Green, CRGB::Purple, CRGB::Cyan},
  {CRGB::Yellow, CRGB::Yellow, CRGB::Red, CRGB::Red, CRGB::Green, CRGB::Green, CRGB::Purple, CRGB::Green, CRGB::Green, CRGB::Cyan},
  {CRGB::Yellow, CRGB::Yellow, CRGB::Red, CRGB::Green, CRGB::Green, CRGB::Purple, CRGB::Purple, CRGB::Purple, CRGB::Green, CRGB::Cyan},
};

CRGB pausePage[20][10] = {
  {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
  {CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black},
};

//0-line 1-L 2-reverse L 3-square 4-squig 5-T 6-rev squig
int shapes[7][4][4][4] = 
{
  {
    {
      {0,0,0,0},
      {1,1,1,1},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,1,0},
      {0,0,1,0},
      {0,0,1,0},
      {0,0,1,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {1,1,1,1},
      {0,0,0,0}
    },
    {
      {0,1,0,0},
      {0,1,0,0},
      {0,1,0,0},
      {0,1,0,0}
    }
  },
  {
    {
      {0,0,1,0},
      {1,1,1,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,1,0,0},
      {0,1,0,0},
      {0,1,1,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {1,1,1,0},
      {1,0,0,0},
      {0,0,0,0}
    },
    {
      {1,1,0,0},
      {0,1,0,0},
      {0,1,0,0},
      {0,0,0,0}
    }
  },
  {
    {
      {1,0,0,0},
      {1,1,1,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,1,1,0},
      {0,1,0,0},
      {0,1,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {1,1,1,0},
      {0,0,1,0}
    },
    {
      {0,1,0,0},
      {0,1,0,0},
      {1,1,0,0},
      {0,0,0,0}
    }
  },
  {
    {
      {0,1,1,0},
      {0,1,1,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,1,1,0},
      {0,1,1,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,1,1,0},
      {0,1,1,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,1,1,0},
      {0,1,1,0},
      {0,0,0,0},
      {0,0,0,0}
    }
  },
  {
    {
      {0,1,1,0},
      {1,1,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,1,0,0},
      {0,1,1,0},
      {0,0,1,0},
      {0,0,0,0} 
    },
    {  
      {0,0,0,0},
      {0,1,1,0},
      {1,1,0,0},
      {0,0,0,0}
    },
    {
      {1,0,0,0},
      {1,1,0,0},
      {0,1,0,0},
      {0,0,0,0}
    }
  },
  {
    {
      {0,1,0,0},
      {1,1,1,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,1,0,0},
      {0,1,1,0},
      {0,1,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {1,1,1,0},
      {0,1,0,0},
      {0,0,0,0}
    },
    {
      {0,1,0,0},
      {1,1,0,0},
      {0,1,0,0},
      {0,0,0,0}
    }
  },
  {
    {
      {1,1,0,0},
      {0,1,1,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,1,0},
      {0,1,1,0},
      {0,1,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {1,1,0,0},
      {0,1,1,0},
      {0,0,0,0}
    },
    {
      {0,1,0,0},
      {1,1,0,0},
      {1,0,0,0},
      {0,0,0,0}
    }
  }
};

// LCD Characters
byte playChar[] = {
  B10000,
  B11000,
  B11100,
  B11110,
  B11111,
  B11100,
  B11000,
  B10000
};

byte line[] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte L[] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B11111
};

byte reverseL[] = {
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B11111
};

byte Square[] = {
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
  B00000
};

byte squig[] = {
  B00000,
  B11000,
  B01000,
  B01100,
  B00000,
  B00000,
  B00000,
  B00000
};

byte T[] = {
  B00000,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100,
  B00000,
  B00000
};

byte revsquig[] = {
  B00000,
  B00011,
  B00010,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000
};

// STATES
int GAMESTATE = 0; // 0 -> Title, 1-> InGame, 2-> Pause Menu, 3 -> StartGameTransition, 4-> StopGameTransition
bool stillFlag;
int pointer; // 0-> Resume, 1-> Title Screen

// Input Stuff
int inputX;
int inputY;
int buttonCounterX;
int threshold = 500;
int isSwitchPressed;
int isButtonClicked;

// Global parameters
int startPosX = 3;
int startPosY = 21;
int index;
int nextIndex;
int dir;
int posX;
int posY;

int normalDelay = 1000;
int acceleratedDelay = 100;
int currentDelay;
long score=0;
long currHighScore;
bool isPlaying=1;

int GetLEDIndex(int x, int y)
{
  if (x%2 == 0) return ROWS*x + y;
  return ROWS*(x+1) - y - 1; 
} 

void transition(CRGB color)
{
    for (int j = 0; j < ROWS/2; j++)
    {
      for (int i = 0; i < COLUMNS; i++)
      {
        leds[GetLEDIndex(i,j)] = color;
        leds[GetLEDIndex(i,ROWS-j-1)] = color;
      }
      delay(50);
      FastLED.show();
    }
    for (int j = ROWS/2-1; j > -1; j--)
    {
      for (int i = 0; i < COLUMNS; i++)
      {
        leds[GetLEDIndex(i,j)] = CRGB::Black;
        leds[GetLEDIndex(i,ROWS-j-1)] = CRGB::Black;
      }
      delay(50);
      FastLED.show();
    }
}

bool posCheck()//int index, int dir, int posX, int posY)
{
  int n = 4;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (shapes[index][dir][i][j] == 0) continue;
      int absPosX = posX + j;
      int absPosY = posY - i;
      if (absPosY >= ROWS && absPosX < COLUMNS && absPosX >= 0 && absPosY >= 0) return true;
      if (absPosX >= COLUMNS || absPosX < 0 || absPosY < 0 || grid[absPosX][absPosY] != 0)
      {
        return false;
      }
    }
  }
  return true;
}

void clearshape()//int index, int dir, int posX, int posY)
{
  int n = 4;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (shapes[index][dir][i][j] == 0|| posY - i >= ROWS) continue;
      leds[GetLEDIndex(posX+j, posY-i)] = CRGB::Black;
    }
  }
}

void drawshape()//int index, int dir, int posX, int posY)
{
  int n = 4;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (shapes[index][dir][i][j] == 0 || posY - i >= ROWS) continue;
      leds[GetLEDIndex(posX+j, posY-i)] = colors[index];
    }
  }
}

void addToGrid()//int index, int dir, int posX, int posY)
{
  int n = 4;
  for (int i = 0; i <n; i++)
  {
    for (int j = 0; j< n; j++)
    {
      if (shapes[index][dir][i][j] == 1) 
      {
        grid[posX+j][posY-i] = 1;
        leds[GetLEDIndex(posX+j,posY-i)] = colors[index];
      }
    }
  }
}

void moveLeft()
{
  clearshape();
  posX--;
  if (!posCheck())
  {
    posX++;
  }
  drawshape();
  FastLED.show();
}
void moveRight()
{
  clearshape();
  posX++;
  if (!posCheck())
  {
    posX--;
  }
  drawshape();
  FastLED.show();
}
void rotate()
{
  clearshape();
  dir = (dir + 1) % 4;
  if (!posCheck())
  {
    dir = dir?dir-1:3;
  }
  drawshape();
  FastLED.show();
}

void checkForLines()
{
  for (int j = ROWS-1; j >-1; j--)
  {
    if (hasLine(j))
    {
      deleteLine(j);
      rowDown(j);
    }
  }
}

bool hasLine(int j)
{
  for (int i = 0; i < COLUMNS; i++)
  {
    if (grid[i][j] == 0) return false;
  }
  return true;
}

void deleteLine(int j)
{
  score+=100;
  for (int i = 0; i < COLUMNS; i++)
  {
    grid[i][j] = 0;
    leds[GetLEDIndex(i,j)] = CRGB::Black;
    FastLED.show();
    delay(100);
  }
}

void rowDown(int row)
{
  for (int j = row; j < ROWS-1; j++)
  {
    for (int i = 0; i< COLUMNS; i++)
    {
      grid[i][j] = grid[i][j+1];
      grid[i][j+1] = 0;
      leds[GetLEDIndex(i,j)] = leds[GetLEDIndex(i,j+1)];
      leds[GetLEDIndex(i,j+1)] = CRGB::Black;
    }
    
  }
  FastLED.show();
}

void(* resetFunc) (void) = 0;

void setup() 
{
  pointer = 0;
  stillFlag = false;
  GAMESTATE = 0;
  isSwitchPressed = false;
  inputX = 0;
  inputY = 0;
  buttonCounterX = threshold;
  randomSeed(analogRead(0));
  // index = random(7);
  nextIndex = random(7);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0,playChar);
  lcd.createChar(1,line);
  lcd.createChar(2,L);
  lcd.createChar(3,reverseL);
  lcd.createChar(4,Square);
  lcd.createChar(5,squig);
  lcd.createChar(6,T);
  lcd.createChar(7,revsquig);
  dir = 0;
  dir = dir?dir-1:3;
  posX = startPosX;
  posY = startPosY;
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
  pauseButton.begin();
  for (int i = 0; i < COLUMNS; i++)
  {
    for (int j = 0; j < ROWS; j++)
    {
      grid[i][j] = 0;
    }
  }
  currentDelay = normalDelay;
  currHighScore = readLongFromEEPROM(100);
  // writeLongIntoEEPROM(100, score);
}


void writeLongIntoEEPROM(int address, long number)
{ 
  EEPROM.write(address, (number >> 24) & 0xFF);
  EEPROM.write(address + 1, (number >> 16) & 0xFF);
  EEPROM.write(address + 2, (number >> 8) & 0xFF);
  EEPROM.write(address + 3, number & 0xFF);
}
long readLongFromEEPROM(int address)
{
  return ((long)EEPROM.read(address) << 24) +
         ((long)EEPROM.read(address + 1) << 16) +
         ((long)EEPROM.read(address + 2) << 8) +
         (long)EEPROM.read(address + 3);
}
bool checkGameOver()
{
  for(int i=0;i<COLUMNS;i++)
  {
    if(grid[i][ROWS-1]==1)
      return true;
  }
  return false;
}

void mainloop() 
{  
  clearshape();
  posY -= 1;
  if (!posCheck())//index, dir, posX, posY)) 
  {
    posY += 1;
    addToGrid();//index, dir, posX, posY);
    checkForLines();
    index = nextIndex;
    nextIndex = random(7);
    posX = 3;
    posY = startPosY;
  }
  if(checkGameOver())
  {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("GAME OVER!");
    for(int j=0;j<ROWS;j++)
    {
      for (int i = 0; i < COLUMNS; i++)
      {
        grid[i][j] = 0;
        leds[GetLEDIndex(i,j)] = CRGB::Black;
      }
    }
    isPlaying=0;
    GAMESTATE = 4;
    // long highScore = readLongFromEEPROM(100);
    // if(score>highScore)
    // {  
    //   writeLongIntoEEPROM(100, score);
    //   currHighScore = highScore;
    // }
    delay(2000);

    lcd.clear();
    
  }
  drawshape();//index, dir, posX, posY);
  FastLED.show();
}

void loop()
{
  isButtonClicked = false;
  if (digitalRead(2) == HIGH)
  {
    isSwitchPressed = false;
  }
  else if(!isSwitchPressed)
  {
    isSwitchPressed = true;
    isButtonClicked = true;
  }


  int horizontal = analogRead(A0);
  int vertical = analogRead(A1);

  if (GAMESTATE == 0)
  {
    if (!stillFlag)
    {
      // Set the LEDs first
      for (int i = 0; i < ROWS; i++)
      {
        for (int j = 0; j < COLUMNS; j++)
        {
          leds[GetLEDIndex(j,i)] = landingPage[ROWS - i - 1][j];
        }
      }
      FastLED.show();
      index = nextIndex; 
      nextIndex = random(7);
      dir = 0;
      dir = dir?dir-1:3;
      posX = startPosX;
      posY = startPosY;
      score = 0;
      isPlaying = true;
      lcd.setCursor(0,0);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(5,0);
      lcd.print("TETRIS");
      lcd.setCursor(2,1);
      lcd.print("PRESS START!");
      stillFlag = true;
    }
    if (isButtonClicked) 
    {
      GAMESTATE = 3;
      stillFlag = false;
    }
  }
  else if (GAMESTATE == 3)
  {
    if (!stillFlag)
    {
      lcd.setCursor(0,0);
      //lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(3,1);
      lcd.print("LOADING...");
      stillFlag = true;
    }

    transition(CRGB::White);
    GAMESTATE = 1;
    stillFlag = false;
  }
  else if (GAMESTATE == 4)
  {
    if (!stillFlag)
    {
      lcd.setCursor(0,0);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(3,1);
      lcd.print("LOADING...");
      stillFlag = true;
    }
    long highScore = readLongFromEEPROM(100);
    if(score>highScore)
    {  
      writeLongIntoEEPROM(100, score);
      currHighScore = score;
    }
    transition(CRGB::Red);
    score = 0;
    GAMESTATE = 0;
    stillFlag = false;
  }
  else if (GAMESTATE == 1)
  {
    if (!stillFlag)
    {
      lcd.setCursor(0,0);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("                ");
      stillFlag = true;
    }

    if (isButtonClicked) 
    {
      if (pointer == 0) 
      {
        isPlaying = !isPlaying;
        if(isPlaying)
        {
          for(int i=0;i<NUM_LEDS;i++)
          {  
            leds[i] = storeLeds[i];
            storeLeds[i] = CRGB::Black;
          }
        }
        lcd.setCursor(0,0);
        lcd.print("                ");
        lcd.setCursor(0,1);
        lcd.print("                ");
      }
      else 
      {
        GAMESTATE = 4;
        stillFlag = false;
        for(int j=0;j<ROWS;j++)
        {
          for (int i = 0; i < COLUMNS; i++)
          {
            grid[i][j] = 0;
          }
        }
        // long highScore = readLongFromEEPROM(100);
        // if(score>highScore)
        // {   
        //   writeLongIntoEEPROM(100, score);
        //   currHighScore = highScore;
        // }
      }
      if (!isPlaying)
      {

        for (int i = 0; i< NUM_LEDS; i++)
        {
          storeLeds[i] = leds[i];
        }
        for (int i = 0; i < ROWS; i++)
        {
          for (int j = 0; j < COLUMNS; j++)
          {
            leds[GetLEDIndex(j,i)] = pausePage[ROWS - i - 1][j];
          }
        }
      FastLED.show();
        pointer = 0;
        lcd.setCursor(0, 0);
        lcd.print("                ");
        lcd.setCursor(0,1);
        lcd.print("                ");
        lcd.setCursor(2,0);
        lcd.print("RESUME");
        lcd.setCursor(2,1);
        lcd.print("EXIT");
      }
    }

    if (isPlaying)
    {
      lcd.setCursor(0, 0);
      lcd.print(" ");
      lcd.setCursor(0, 0);
      lcd.write(nextIndex+1);
      lcd.print("  ");
      lcd.print("Score: ");
      lcd.print(score); 
      lcd.setCursor(0, 1);
      lcd.print("Hi : ");
      lcd.print(currHighScore); 
    }
    else
    {
      if (pointer == 0) 
      {
        lcd.setCursor(0,1);
        lcd.print(" ");
        lcd.setCursor(0,0);
      }
      else 
      {
        lcd.setCursor(0,0);
        lcd.print(" ");
        lcd.setCursor(0,1);
      }
      lcd.write(0);
      if (vertical > 600) pointer = 1;
      else if (vertical < 50) pointer = 0;
    }

    if ((horizontal > 600 && (inputX != 1 || buttonCounterX <= 0)) && isPlaying)
    {
      if (inputX != 1) buttonCounterX = threshold;
      moveRight();
      inputX = 1;
    } 
    else if ((horizontal < 50 && (inputX != -1 || buttonCounterX <= 0)) && isPlaying)
    {
      if (inputX != -1) buttonCounterX = threshold;
      moveLeft();
      inputX = -1;
    } 
    else if (50 < horizontal && horizontal < 600)
    {
      buttonCounterX = threshold;
      inputX = 0;
    }

    if (vertical > 600 && isPlaying)
    {
      currentDelay = acceleratedDelay;
      // inputY = 1;
    }
    else if ((vertical < 50 && inputY != -1) && isPlaying)
    {
      rotate();
      inputY = -1;
    }
    else
    {
      if (50 < vertical && vertical < 600) inputY = 0;
      currentDelay = normalDelay;
    }  
  }

  EVERY_N_MILLIS(100)
  {
    if (GAMESTATE == 1)
    {
      buttonCounterX -= 100;
      if (buttonCounterX < 0) buttonCounterX = 0;
    }
  }

  EVERY_N_MILLIS_I(timingObj, normalDelay)
  {
    if (GAMESTATE == 1)
    {
      if(currentDelay==acceleratedDelay && isPlaying)
        score+=20;
      timingObj.setPeriod(currentDelay);
      if(isPlaying) mainloop();
    }
  };
}
