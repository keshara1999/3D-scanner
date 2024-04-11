#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad_I2C.h>
#include <Keypad.h>
#define I2CADDR 0x20


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char hexaKeys[ROWS][COLS] = {
                            {'1','2','3','A'},
                            {'4','5','6','B'},
                            {'7','8','9','C'},
                            {'*','0','#','D'}
                        }; 
    
byte rowPins[ROWS] = {0,1,2,3};
byte colPins[COLS] = {4,5,6,7};

Keypad_I2C customKeypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, I2CADDR);
Adafruit_SSD1306 display = Adafruit_SSD1306(128,64,&Wire);

long x=0;
int u=0;
int num=0;
int fin_val=0;
long time_begin=0;
long ti=0;
int sec=0;
int minit=0;
int hour=0;
int pec=0;

int dir1 =3;
int steppin1=2;

int dir2 =12;
int steppin2=11;

int levels=0;
int height=0;
int steps=0;
//long point=0;

int val=0;


void setup() {
    Wire.begin( );
    
    customKeypad.begin( );
    
    display.begin(SSD1306_SWITCHCAPVCC,0x3C);
    display.setTextColor(SSD1306_WHITE);
    
    Serial.begin(9600);

    pinMode(dir1,OUTPUT);
    pinMode(steppin1,OUTPUT);
    pinMode(dir2,OUTPUT);
    pinMode(steppin2,OUTPUT);
   
    pinMode(6,OUTPUT);
    pinMode(7,OUTPUT);
    pinMode(8,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(13,OUTPUT);

    pinMode(10,INPUT);
    pinMode(A0,INPUT);
 
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(20,30);
    display.print("Run the PYTHON !");
    display.display();       
}
    
void loop() {
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);

  
if(Serial.available()){
      
    
   u = Serial.read();
      
      if(u=='a'){
          take_value("LEVEL");
          levels = fin_val;
          
          if(levels==0){
             Serial.println(-1);
          }
         if(levels!=0){
             Serial.println(levels);
         }    
      }
      
      
      if(u=='d'){
          take_value("HEIGHT");
          height = fin_val;

          if(height==0){
             Serial.println(-1);
          }
         if(height!=0){
             Serial.println(height);
         } 
      }


      if(u=='b'){
          take_value("STEPS");
          steps = fin_val;

          if(steps==0){
             Serial.println(-1);
          }
         if(steps!=0){
             Serial.println(steps);
         } 
      }
      long point = long(levels)*long(steps);

      
      if(u=='i'){
        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(35,15);
        display.print("Press the");
        display.setTextSize(1);
        display.setCursor(20,40);
        display.print("GREEN BUTTON !");
        
        display.display(); 
        
         if(digitalRead(10)==LOW){
             Serial.println(110);
         }
         if(digitalRead(10)==HIGH){
             Serial.println(111);
             time_begin = millis();
         }   
      }

      
      if(u=='c'){
          display.clearDisplay();
                     
          display.setTextSize(1);
          display.setCursor(0,0);
          display.print("In progress....");
          
          for(int j=0;j<levels;++j){

              digitalWrite(dir2,LOW);
              for(int k=0;k<(400*height/levels);++k){
                  digitalWrite(steppin2,HIGH);
                  delayMicroseconds(100);
                  digitalWrite(steppin2,LOW);
                  delayMicroseconds(100);
              }
            
              digitalWrite(dir1,HIGH);
              for(int i=1;i<3201;++i){
                  if(i%(3200/steps)==0){
                     x=x+1;
                     for(int v=0;v<5;++v){
                         val = analogRead(A0);
                         Serial.println(val);
                     }
                     pec = x*100/point;
                     display.fillRect(0,15,120,60,SSD1306_BLACK);
                     
                     display.setTextSize(1);
                     display.setCursor(0,22);
                     display.print("COMPLETE :");

                     display.setTextSize(2);
                     display.setCursor(70,17);
                     display.print(pec);

                     display.setTextSize(2);
                     display.setCursor(100,17);
                     display.print('%');
                     
                     ti = millis();
                     sec = (ti-time_begin)/1000;
                     if(sec>=60){
                         minit=minit+1;
                         sec=0;
                         time_begin=ti;
                     }
                     
                     if(minit>=60){
                         hour=hour+1;
                         minit =0;
                     }


                     if(hour<10){
                         display.setTextSize(2);
                         display.setCursor(0,45);
                         display.print('0');
                         display.setTextSize(2);
                         display.setCursor(12,45);
                         display.print(hour);
                     }
                     else{ 
                         display.setTextSize(2);
                         display.setCursor(0,45);
                         display.print(hour);
                     }

                     display.setTextSize(2);
                     display.setCursor(22,45);
                     display.print(':');
                     
                     if(minit<10){
                         display.setTextSize(2);
                         display.setCursor(32,45);
                         display.print('0');
                         display.setTextSize(2);
                         display.setCursor(44,45);
                         display.print(minit);
                     }
                     else{
                         display.setTextSize(2);
                         display.setCursor(32,45);
                         display.print(minit);
                     }
                     
                     if(sec<10){
                         display.setTextSize(1);
                         display.setCursor(57,52);
                         display.print('0');
                         display.setTextSize(1);
                         display.setCursor(65,52);
                         display.print(sec);
                     }
                     display.setTextSize(1);
                     display.setCursor(57,52);
                     display.print(sec);
                     
                     display.display();
                  }
                  digitalWrite(steppin1,HIGH);
                  delayMicroseconds(3000);
                  digitalWrite(steppin1,LOW);
                  delayMicroseconds(3000);
              }
          }

          digitalWrite(dir2,HIGH);
          for(int r=0;r<(400*height);++r){
              digitalWrite(steppin2,HIGH);
              delayMicroseconds(500);
              digitalWrite(steppin2,LOW);
              delayMicroseconds(500);
          }
          
          buzz(300);
          buzz(300);
          buzz(300);
          
          display.clearDisplay();
          display.setTextSize(2);
          display.setCursor(42,15);
          display.print("END");
          
            if(hour<10){
               display.setTextSize(2);
               display.setCursor(20,45);
               display.print('0');
               display.setTextSize(2);
               display.setCursor(32,45);
               display.print(hour);
           }
           else{ 
               display.setTextSize(2);
               display.setCursor(20,45);
               display.print(hour);
           }

           display.setTextSize(2);
           display.setCursor(42,45);
           display.print(':');
           
           if(minit<10){
               display.setTextSize(2);
               display.setCursor(52,45);
               display.print('0');
               display.setTextSize(2);
               display.setCursor(64,45);
               display.print(minit);
           }
           else{
               display.setTextSize(2);
               display.setCursor(52,45);
               display.print(minit);
           }         
           
           display.setTextSize(2);
           display.setCursor(74,45);
           display.print(':');

           if(sec<10){
               display.setTextSize(2);
               display.setCursor(84,45);
               display.print('0');
               display.setTextSize(2);
               display.setCursor(96,45);
               display.print(sec);
           }
           
           display.setTextSize(2);
           display.setCursor(84,45);
           display.print(sec);
           
           display.display();
  
      }  
   }
}



void take_value(String data){
    fin_val=-1;
  
    String ln = "Enter the ";
    ln += data;
  
    display.clearDisplay();
     
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print(ln);
  
    display.setTextSize(2);
    display.setCursor(0,40);
    display.print(num);
 
    int customKey = customKeypad.getKey();
   
    if(customKey!=65 and customKey!=42 and customKey){
        buzz(100);
        num = (num*10) +(customKey-48);  
    }
    
    if(customKey==42){
        buzz(100);
        num = num/10;
    } 
    
    if(customKey==65){
         buzz(300);
         fin_val = num; 
         num=0;
    }   
    display.display();   
}

  
void buzz(int t){
    digitalWrite(13,HIGH);
    delay(t);
    digitalWrite(13,LOW);
    delay(t/2);
}
