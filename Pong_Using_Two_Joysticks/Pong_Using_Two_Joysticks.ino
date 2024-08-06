#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int joystick1Y = A1;
const int joystick2Y = A3;

int paddle1Y = SCREEN_HEIGHT / 2;
int paddle2Y = SCREEN_HEIGHT / 2;
const int paddleWidth = 2;
const int paddleHeight = 10;

int ballX = SCREEN_WIDTH / 2;
int ballY = SCREEN_HEIGHT / 2;
int ballSpeedX = 2;
int ballSpeedY = 2;
const int ballSize = 2;

int score1 = 0;
int score2 = 0;

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int joy1Y = analogRead(joystick1Y);
  int joy2Y = analogRead(joystick2Y);

  // Map joystick movement to paddle movement
  paddle1Y = map(joy1Y, 0, 1023, 0, SCREEN_HEIGHT - paddleHeight);
  paddle2Y = map(joy2Y, 0, 1023, 0, SCREEN_HEIGHT - paddleHeight);

  // Update ball position
  ballX += ballSpeedX;
  ballY += ballSpeedY;

  // Ball collision with top and bottom
  if (ballY <= 0 || ballY >= SCREEN_HEIGHT - ballSize) {
    ballSpeedY = -ballSpeedY;
  }

  // Ball collision with paddles
  if ((ballX <= paddleWidth && ballY >= paddle1Y && ballY <= paddle1Y + paddleHeight) ||
      (ballX >= SCREEN_WIDTH - paddleWidth - ballSize && ballY >= paddle2Y && ballY <= paddle2Y + paddleHeight)) {
    ballSpeedX = -ballSpeedX;
  }

  // Ball out of bounds
  if (ballX <= 0) {
    score2++;
    resetBall();
  } else if (ballX >= SCREEN_WIDTH) {
    score1++;
    resetBall();
  }

  // Display paddles, ball, and score
  display.clearDisplay();
  display.fillRect(0, paddle1Y, paddleWidth, paddleHeight, SSD1306_WHITE);
  display.fillRect(SCREEN_WIDTH - paddleWidth, paddle2Y, paddleWidth, paddleHeight, SSD1306_WHITE);
  display.fillRect(ballX, ballY, ballSize, ballSize, SSD1306_WHITE);
  
  display.setCursor(0, 0);
  display.print("P1: ");
  display.print(score1);
  display.setCursor(SCREEN_WIDTH - 30, 0);
  display.print("P2: ");
  display.print(score2);

  display.display();
  delay(50);
}

void resetBall() {
  ballX = SCREEN_WIDTH / 2;
  ballY = SCREEN_HEIGHT / 2;
  ballSpeedX = -ballSpeedX;
}
