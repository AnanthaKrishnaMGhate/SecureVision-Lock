#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Keypad.h>
#include <Servo.h>
#include <EEPROM.h>

/* -------- TFT -------- */
#define TFT_CS 53
#define TFT_DC 49
#define TFT_RST 48
Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

/* -------- SERVO -------- */
#define SERVO_PIN 9
#define LOCK_POS 0
#define UNLOCK_POS 90
Servo lockServo;

/* -------- BUZZER -------- */
#define BUZZER_PIN 8

/* -------- ULTRASONIC -------- */
#define TRIG_PIN 11
#define ECHO_PIN 12

/* -------- KEYPAD -------- */
const byte ROWS=4;
const byte COLS=4;
char keys[ROWS][COLS]={
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte rowPins[ROWS]={22,24,26,28};
byte colPins[COLS]={30,32,34,36};
Keypad keypad=Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);

/* -------- PASSWORD -------- */
#define PASS_ADDR 0
String password="";
const String MASTER_KEY="951478632";

/* -------- SOUND -------- */
void keyTone(){ tone(BUZZER_PIN,2500,30); }
void successMelody(){
 int n[]={1000,1400,1800};
 for(int i=0;i<3;i++){ tone(BUZZER_PIN,n[i],120); delay(150);}
}
void errorAlarm(){
 for(int i=0;i<2;i++){ tone(BUZZER_PIN,250,300); delay(350);}
}

/* -------- DISPLAY UTIL -------- */
void center(String txt,int y,uint16_t c,int s){
 int x=(320-txt.length()*s*6)/2;
 tft.setCursor(x,y);
 tft.setTextColor(c);
 tft.setTextSize(s);
 tft.print(txt);
}

/* -------- EMOJIS -------- */
void happy(){
 tft.fillCircle(160,150,30,ILI9341_GREEN);
 tft.fillCircle(150,145,4,ILI9341_BLACK);
 tft.fillCircle(170,145,4,ILI9341_BLACK);
 for(int x=-10;x<=10;x+=4)
   tft.fillCircle(160+x,165,2,ILI9341_BLACK);
}

void angry(){
 tft.fillCircle(160,150,30,ILI9341_RED);
 tft.fillCircle(150,150,4,ILI9341_BLACK);
 tft.fillCircle(170,150,4,ILI9341_BLACK);
 tft.drawLine(145,165,175,165,ILI9341_BLACK);
}

void lockIcon(uint16_t c){
 tft.fillRect(120,160,80,60,c);
 tft.drawCircle(160,160,25,c);
 tft.fillRect(135,160,50,25,ILI9341_BLACK);
}

void unlockIcon(uint16_t c){
 tft.fillRect(120,160,80,60,c);
 tft.drawCircle(185,160,25,c);
}

/* -------- RADAR -------- */
void radarAnim(){
 tft.fillScreen(ILI9341_BLACK);
 center("STANDBY",40,ILI9341_CYAN,2);
 for(int r=10;r<80;r+=10){
   tft.drawCircle(160,150,r,ILI9341_DARKGREY);
   delay(30);
 }
}

/* -------- ULTRASONIC -------- */
float distance(){
 digitalWrite(TRIG_PIN,LOW); delayMicroseconds(2);
 digitalWrite(TRIG_PIN,HIGH); delayMicroseconds(10);
 digitalWrite(TRIG_PIN,LOW);
 long dur=pulseIn(ECHO_PIN,HIGH);
 return dur*0.034/2;
}

/* -------- INPUT -------- */
String getInput(String msg){
 String input="";
 tft.fillScreen(ILI9341_BLACK);
 center(msg,40,ILI9341_WHITE,2);
 tft.setCursor(100,110);

 while(true){
   char k=keypad.getKey();
   if(k){
     if(k>='0'&&k<='9'){input+=k;tft.print("*");keyTone();}
     if(k=='#') return input;
     if(k=='*' && input.length()>0) input.remove(input.length()-1);
   }
 }
}

/* -------- EEPROM -------- */
void savePass(String p){
 for(int i=0;i<4;i++) EEPROM.write(PASS_ADDR+i,p[i]);
}
String loadPass(){
 String p="";
 for(int i=0;i<4;i++){
   char c=EEPROM.read(PASS_ADDR+i);
   if(c<'0'||c>'9') return "";
   p+=c;
 }
 return p;
}

/* -------- MASTER RESET -------- */
void masterReset(){
 tft.fillScreen(ILI9341_BLACK);
 center("MASTER RESET",50,ILI9341_YELLOW,2);
 successMelody();
 delay(1200);
 password=getInput("NEW PASS");
 password=password.substring(0,4);
 savePass(password);
}

/* -------- SETUP -------- */
void setup(){
 pinMode(TRIG_PIN,OUTPUT);
 pinMode(ECHO_PIN,INPUT);
 pinMode(BUZZER_PIN,OUTPUT);

 tft.begin();
 tft.setRotation(1);

 lockServo.attach(SERVO_PIN);
 lockServo.write(LOCK_POS);

 password=loadPass();
 if(password==""){
   password=getInput("SET PASS");
   password=password.substring(0,4);
   savePass(password);
 }
}

/* -------- LOOP -------- */
void loop(){

 radarAnim();

 if(distance()>25) return;

 successMelody();

 String entered=getInput("ENTER PASS");

 if(entered==MASTER_KEY){ masterReset(); return;}

 if(entered==password){
   tft.fillScreen(ILI9341_BLACK);
   center("ACCESS OK",40,ILI9341_GREEN,2);
   happy();
   unlockIcon(ILI9341_GREEN);
   successMelody();
   lockServo.write(UNLOCK_POS);

   while(true){
     String l=getInput("LOCK PASS");
     if(l==MASTER_KEY){ masterReset(); break;}
     if(l==password){
       lockServo.write(LOCK_POS);
       successMelody();
       break;
     }else{
       center("WRONG",200,ILI9341_RED,2);
       angry();
       errorAlarm();
     }
   }
 }
 else{
   tft.fillScreen(ILI9341_BLACK);
   center("DENIED",40,ILI9341_RED,2);
   angry();
   errorAlarm();
 }
}
