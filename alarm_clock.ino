#include <TM1637Display.h>
#include <uRTCLib.h>

#define CLK 3
#define DIO 4

// Pins
#define ALARM_MODE_PIN 2
#define HOUR_INC_PIN 5
#define ENTER_PIN 6
#define BUZZER_PIN 9
#define POT_PIN A0 

int time;

// REAL alarm values
int alarmHour = 0;
int alarmMin = 0;

// TEMP values used for alarm or clock setting
int tempHour = 0;
int tempMin = 0;

int alarm;
int buzzer = BUZZER_PIN; 

// Buzz control
bool buzz = true;
unsigned long lastBeep = 0;
bool buzzerState = false;
unsigned long modeSwitchTime = 0; 

// States
// 0 = normal, 1 = alarm set, 2 = clock set
int mode = 0;
bool justEntered = false;
bool justExitedSetMode = false;

// Variables that were previously implicitly declared or missing
int alarmModestate;
int hourIncstate;
int enterState;
int potValue; 
//---------------------------------------------------------

const uint8_t allON[] = {0xff,0xff,0xff,0xff};

// --- Custom Display Segments ---
// ALA -> A L A _
const uint8_t ALA_SEG[] = {
  0x77, // A
  0x38, // L
  0x77, // A
  0x00  // blank
};

// SET -> S E T _
const uint8_t SET_SEG[] = {
  0x6D, // S
  0x79, // E
  0x78, // T
  0x00  // blank
};

// TIME -> T I M E
const uint8_t TIME_SEG[] = {
  0x78, // T
  0x06, // I
  0x37, // M (combination for M)
  0x79  // E
};
// ------------------------------

uRTCLib rtc(0x68);
TM1637Display display(CLK, DIO);

void setup() {
  URTCLIB_WIRE.begin();
  // rtc.set(0, 39, 11, 2, 3, 11, 25); 

  display.setBrightness(5);

  pinMode(ALARM_MODE_PIN, INPUT_PULLUP);
  pinMode(HOUR_INC_PIN, INPUT_PULLUP);
  pinMode(ENTER_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {

  rtc.refresh();
  int hour = rtc.hour();
  int minute = rtc.minute();
  time = hour * 100 + minute;
  unsigned long now = millis();

  // NOTE: This non-blocking tone stop is still useful for general tone cleanup.
  if (modeSwitchTime > 0 && now - modeSwitchTime >= 50) {
    noTone(BUZZER_PIN);
    modeSwitchTime = 0;
  }

  // Read buttons (using defined pin names for clarity)
  int alarmModestate = digitalRead(ALARM_MODE_PIN);
  int hourIncstate = digitalRead(HOUR_INC_PIN);
  int enterState = digitalRead(ENTER_PIN);

  // ----------------------------------------------------
  // MODE CYCLING: Press Mode -> 1 -> 2 -> 0 -> 1 -> ...
  // ----------------------------------------------------
  if (alarmModestate == LOW) {
    mode++;
    if (mode > 2) mode = 0;

    justEntered = true;
    
    // --- MODE ENTRY BEEP ---
    tone(BUZZER_PIN, 1000); 
    delay(50);             // Beep for 50 milliseconds
    noTone(BUZZER_PIN);    // Stop the tone immediately
    // -----------------------
    
    delay(250); // Main Debounce
  }

  // ---------------------------------------------------------
  // MODE 0: NORMAL CLOCK MODE
  // ---------------------------------------------------------
  if (mode == 0) {
    
    // Display "TIME" when returning from set mode
    if (justExitedSetMode) {
      
      // --- NEW: Exit Mode Beep (Higher pitch for success/return) ---
      tone(BUZZER_PIN, 1500); 
      delay(50);              
      noTone(BUZZER_PIN);     
      // -----------------------------------------------------------
      
      display.setSegments(TIME_SEG);
      delay(700);
      justExitedSetMode = false;
    }

    display.showNumberDecEx(time, 0b01000000, true, 4, 0);

    // stop ringing
    if (enterState == LOW) {
      buzz = false;
      noTone(buzzer);
    }

    // alarm ringing logic
    if (time == alarm && buzz) {
      if (now - lastBeep >= 500) {
        lastBeep = now;
        buzzerState = !buzzerState;

        if (buzzerState) tone(buzzer, 500);
        else noTone(buzzer);
      }
    }

    return; 
  }

  // ---------------------------------------------------------
  // MODES 1 & 2 SHARE SAME UI
  // ---------------------------------------------------------
  if (justEntered) {

    if (mode == 1) { 
      // Display "ALA" for Alarm Set
      display.setSegments(ALA_SEG);
      delay(700);
      tempHour = alarmHour;
      tempMin  = alarmMin;
    } 
    else if (mode == 2) {
      // Display "SET" for Clock Set
      display.setSegments(SET_SEG);
      delay(700);
      tempHour = hour;
      tempMin  = minute;
    }

    justEntered = false;
  }

  // show current editable number
  int temp = tempHour * 100 + tempMin;
  display.showNumberDecEx(temp, 0b01000000, true, 4, 0);

  // minute via potentiometer
  potValue = analogRead(POT_PIN); // Reads A0
  tempMin = map(potValue, 0, 1023, 0, 59);

  // hour increment button
  if (hourIncstate == LOW) {
    tempHour++;
    if (tempHour > 23) tempHour = 0;
    delay(200);
  }

  // ENTER saves values
  if (enterState == LOW) {

    if (mode == 1) {
      // save alarm
      alarmHour = tempHour;
      alarmMin  = tempMin;
      alarm = alarmHour * 100 + alarmMin;
      buzz = true;
    }

    else if (mode == 2) {
      // save clock time
      rtc.set(0, tempMin, tempHour, 0, 0, 0, 0);
    }

    justExitedSetMode = true; // Set flag to display TIME
    mode = 0;   
    delay(200);
  }
}