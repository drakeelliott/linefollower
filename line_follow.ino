    // 2.678 - Lab 10: Motor Speed Control Template
    // Global declarations (accessible to all functions).
    // Based on the Arduino connections shown 1n the handout.
    // Note that pins 11 (PWMA) and 5 (PWMB) are both Arduino PWM pins.

  const int AIN1  = 10;
  const int AIN2  = 9;
  const int PWMA  = 11;
  const int BIN1  = 7;
  const int BIN2  = 6;
  const int PWMB  = 5;
  const int STDBY = 8;
  int blackTH = 500;
  int driveSp = 200;
  int rotateSp = 200;
 
    void setup()  {
        pinMode(AIN1, OUTPUT);
        pinMode(AIN2, OUTPUT);
        pinMode(BIN1, OUTPUT);
        pinMode(BIN1, OUTPUT);
        pinMode(PWMA, OUTPUT);
        pinMode(PWMB, OUTPUT);
        pinMode(STDBY, OUTPUT);
        digitalWrite(STDBY, HIGH);
        Serial.begin(9600);
       
    }

    void loop()   {
         int vL = analogRead(A1);
         int vC = analogRead(A2);
         int vR = analogRead(A3);
         Serial.print(vL);
         Serial.print(" ");
         Serial.print(vC);
         Serial.print(" ");
         Serial.println(vR);
         int turn = 0;

        drive(driveSp,driveSp);
        turn = 0;
        if (vL < blackTH && vC < blackTH && vR < blackTH){ // if sees all white, checks both directions
          while (vL < blackTH && vC < blackTH && vR < blackTH){ //while all white, continue to check
            vL = analogRead(A1);
            vC = analogRead(A2);
            vR = analogRead(A3);
          for (int i = 0; i < 500; i++){ // check right first, at any point throughout turn, should be able to detect black and break
              drive(driveSp+50,-rotateSp);
              delay(1);
              vL = analogRead(A1);
              vC = analogRead(A2);
              vR = analogRead(A3);
              if (vL > blackTH || vC > blackTH || vR > blackTH){
                break;
              }
          }
          if (vL > blackTH || vC > blackTH || vR > blackTH){
                break;
          }
          for (int i = 0; i < 1000; i++){ // check left now
              drive(-rotateSp,driveSp+50);
              delay(1);
              vL = analogRead(A1);
              vC = analogRead(A2);
              vR = analogRead(A3);
              if (vL > blackTH || vC > blackTH || vR > blackTH){
                break;
           }
          }
          if (vL > blackTH || vC > blackTH || vR > blackTH){
                break;
          }
          for (int i = 0; i < 750; i++){ // back right
              drive(driveSp+50,-rotateSp);
              delay(1);
           }
           for (int i = 0; i < 750; i++){ // move forward
              drive(driveSp,driveSp);
              delay(1);
              vL = analogRead(A1);
              vC = analogRead(A2);
              vR = analogRead(A3);
              if (vL > blackTH || vC > blackTH || vR > blackTH){
                break;
            }
           }
           if (vL > blackTH || vC > blackTH || vR > blackTH){
                break;
            }
          }
        }

        if (vL < blackTH) {
          turn = 50;
        while (vL < blackTH){ // turn right if left sees white 
          drive(driveSp+turn,rotateSp-turn);
          turn += 5;
          delay(5);
          vL = analogRead(A1);
          vC = analogRead(A2);
          vR = analogRead(A3);
          if (vL > blackTH){
            break; 
          } else if (vL < blackTH && vC < blackTH && vR < blackTH){
            return;
          }
        } 
       }
        turn = 0;
        drive(100,100);

        if (vR < blackTH){
          turn = 50;
        while (vR < blackTH){ // turn left if right sees white 
          drive(rotateSp-turn,driveSp+turn);
          turn += 5;
          delay(5);
          vL = analogRead(A1);
          vC = analogRead(A2);
          vR = analogRead(A3);
          if (vR > blackTH){
            break;
          } else if (vL < blackTH && vC < blackTH && vR < blackTH){
            return;
          }
        }
       }
        turn = 0;
        drive(driveSp,driveSp);

        
    }
    
void motorWrite(int motorSpeed, int xIN1, int xIN2, int PWMx)
{
 
  if (motorSpeed > 0)          // it's forward
  {  digitalWrite(xIN1, LOW);
     digitalWrite(xIN2, HIGH);
  }
  else                         // it's reverse
  {  digitalWrite(xIN1, HIGH);
     digitalWrite(xIN2, LOW);
  } 

    motorSpeed = abs(motorSpeed);
    motorSpeed = constrain(motorSpeed, 0, 255);   // Just in case...
    analogWrite(PWMx, motorSpeed);
}

void drive (int speedL, int speedR) {
  motorWrite(speedL, AIN1, AIN2, PWMA);
  motorWrite(speedR, BIN1, BIN2, PWMB);
  
}
