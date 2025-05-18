#include <Servo.h>  
#include <LiquidCrystal.h>
#include <Wire.h>           // Include Wire library for I2C communication
#include <RTClib.h>         // Include RTClib library for RTC

Servo servo; // create servo object
RTC_DS3231 rtc;            // Create RTC object (using DS3231 RTC module)
                          // Note: If using DS1307, change to RTC_DS1307 rtc;

// constant variables for pins
const int servoPin = 6;
const int buttonPin = 9;
const int ledPin = 7;
const int buzzerPin = 8;

// other variables
int angle = 0;
int angleIncrement = 45;  // 45 degrees for 4 compartments
int newAngle;
int buttonState;
int movementDelay = 111;  // Modified: ~111ms delay gives us 45 degrees in 5 seconds (45 steps × 111ms ≈ 5000ms)
int debounceDelay = 1000;
unsigned long lastRotationTime = 0; // Track when the last rotation happened

// time variables
int year;
int month;
int day;
int hour;
int minutes;
int seconds;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){ // setup code that only runs once
  pinMode(buttonPin, INPUT); // set button pin as input
  pinMode(ledPin,OUTPUT);    // set LED pin as output
  pinMode(buzzerPin,OUTPUT); // set buzzer pin as output
  digitalWrite(ledPin,LOW);  // make sure LED is off
  digitalWrite(buzzerPin,LOW);  // make sure buzzer is off
  servo.attach(servoPin);    // attach servo object to servoPin
  servo.write(angle);        // set servo to initial angle
  Serial.begin(9600);        // initialize serial for debugging

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Initialize the RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RTC Error!");
    while (1);
  }
  
  // Uncomment the following line to set the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
  // Or set a specific date and time manually:
  // rtc.adjust(DateTime(2024, 4, 12, 8, 59, 50)); // Year, Month, Day, Hour, Minute, Second
}

void loop(){  // code that loops forever
  updateLCD();  // display the current date and time on the screen
  
  buttonState = digitalRead(buttonPin); // read button state
  Serial.println(angle);                // print the servo angle

  // Modified: Rotate every 10 seconds (when seconds is divisible by 10)
  // and only if at least 10 seconds have passed since last rotation
  unsigned long currentTime = millis();
  if(seconds % 10 == 0 && (currentTime - lastRotationTime >= 10000)) {
    lastRotationTime = currentTime; // Update the last rotation time
    
    newAngle = angle + angleIncrement; // increase angle by increment
    if (newAngle <= 180){           // if the new angle is less than or equal to 180, increase angle
      rotateServo(angle, newAngle); // rotate to new angle
      angle = newAngle;             // update current angle
      
      // flash LED and buzzer
      flashLED(4, 150);    // flashLED(number of flashes, delay in milliseconds)
    }
    else{ // if the new angle is greater than 180, reset angle to 0
      rotateServo(angle, 0); // rotate back to 0
      angle = 0;             // update current angle
    }
  }
}

// New function to handle servo rotation with consistent timing
void rotateServo(int startAngle, int endAngle) {
  int steps;
  int stepDirection;
  
  if (endAngle > startAngle) {
    steps = endAngle - startAngle;
    stepDirection = 1;
  } else {
    steps = startAngle - endAngle;
    stepDirection = -1;
  }
  
  int currentPosition = startAngle;
  for (int i = 0; i < steps; i++) {
    currentPosition += stepDirection;
    servo.write(currentPosition);
    Serial.println(currentPosition);
    delay(movementDelay); // This delay gives us ~5 seconds for 45 degrees
  }
}

void flashLED(int numFlashes, int flashDelay){  // alarm function to flash LED and sound buzzer
  lcd.clear();              // clear the LCD screen
  lcd.setCursor(0, 0);      // set cursor to top left
  lcd.print("Take medicine!");  // display message
  for (int i = 0; i<numFlashes; i++){  // loop to flash LED/buzzer numFlashes times
    digitalWrite(ledPin,HIGH);         // turn LED on
    digitalWrite(buzzerPin,HIGH);      // turn buzzer on
    delay(flashDelay);                 // delay
    digitalWrite(ledPin,LOW);          // turn LED off
    digitalWrite(buzzerPin,LOW);       // turn buzzer off
    delay(flashDelay);                 // delay
  }
  // wait for button press - the code will get stuck in this loop until you press the button
  while(digitalRead(buttonPin) == LOW){}; 
  delay(1000);    // delay before clearing screen
  lcd.clear();    // clear screen
}

void updateLCD(){    // function to update LCD screen
  // get current time from the RTC
  DateTime now = rtc.now();
  
  // store current time variables
  year = now.year();
  month = now.month();
  day = now.day();
  hour = now.hour();
  minutes = now.minute();
  seconds = now.second();

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  // print month/day/year (rearrange for different date formats)
  // add leading spaces if month or day are less than 10 to keep spacing consistent
  // (always use 2 characters for month and day)
  if(month<10){   // print extra space if month is less than 10
    lcd.print(" ");
  }
  lcd.print(month);  // print the month
  lcd.print("/");
  if(day<10){        // print extra space if the day is less than 10
    lcd.print(" ");
  }
  lcd.print(day);    // print the day
  lcd.print("/");
  lcd.print(year);   // print the year

  // print time in hh:mm:ss format
  // add leading zeroes if minutes or seconds are less than ten to keep spacing consistent
  lcd.setCursor(0, 1);  // move cursor to second row
  if(hour<10){          // print leading space if hour is less than 10
    lcd.print(" ");
  }
  lcd.print(hour);      // print the hour
  lcd.print(":");
  if(minutes<10){       // print leading zero if minute is less than 10
    lcd.print("0");
  }
  lcd.print(minutes);   // print the minute
  lcd.print(":");
  if(seconds<10){       // print leading zero if second is less than 10
    lcd.print("0");
  }
  lcd.print(seconds);   // print the second
}