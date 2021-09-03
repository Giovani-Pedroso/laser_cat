//libs inclusion
#include <Servo.h>
#include <Arduino.h>

//Decrease this value to increase the speed of the servos
#define DELAY_SERVOS 38 // 


//lazer pin
#define LAZER 9

// define que area o lazer ira percorrer altere esses valores 
//de acordo com seu comodo

//Change this values to adjust the 
//the lazer's action area
#define LIMITE_X_INICIAL 20//70//
#define LIMITE_X_FINAL 90//120//

#define LIMITE_Y_INICIAL 90//45//
#define LIMITE_Y_FINAL 120//13090//

#define MAX_LENGTH_X LIMITE_X_FINAL-LIMITE_X_INICIAL
#define MAX_LENGTH_Y LIMITE_Y_FINAL-LIMITE_Y_INICIAL

int max_x=MAX_LENGTH_X ;
int max_y=MAX_LENGTH_Y; 
void line(uint8_t size, uint8_t direction);
void action_area();

Servo servo_y;
Servo servo_x;


uint8_t pos_x= MAX_LENGTH_X/2;
uint8_t pos_y= MAX_LENGTH_Y/2;

int lengthsX[6] = {max_x/1, max_x/2, max_x/4, 
                   max_x/8, max_x/16, max_x/32};

int lengthsY[6] = {max_y/1, max_y/2, max_y/4, 
                       max_y/8, max_y/16, max_y/32};


void setup() {


  //define which I/Os will be use by the servos
  servo_y.attach(2);
  servo_x.attach(3);

  //config the lazer's I/O as output
  pinMode(LAZER,OUTPUT);

  //turn on the lazer
  digitalWrite(LAZER ,1);
  Serial.begin(9600);
  Serial.print("max x: ");
  Serial.println(max_x/4);


  Serial.print("max Y: ");
  Serial.println(max_y/4);

  for(int i =0;i<6;i++) Serial.println(lengthsX[i]);
  Serial.println();
  //Serial.println();
  for(int i =0;i<6;i++) Serial.println(lengthsX[i]);

  Serial.end();
  
}

void loop() {


  int X=random(6);  
  int D=random(4);


  /*
   comment the function line(X, D); and uncomment the
   function action_area(); to see the lazer's action area   
   */
   
  line(X, D);
  //action_area();

}

void action_area(){
  int x=LIMITE_X_INICIAL;
  int y=LIMITE_Y_INICIAL;

  servo_x.write(LIMITE_X_INICIAL);
  servo_y.write(LIMITE_Y_INICIAL);
  
  
  for(;x<LIMITE_X_FINAL;x++){
    servo_x.write(x);
    delay(DELAY_SERVOS);
  }

  for(;y<LIMITE_Y_FINAL;y++){
    servo_y.write(y);
    delay(DELAY_SERVOS);
  }

  for(;x>LIMITE_X_INICIAL;x--){
    servo_x.write(x);
    delay(DELAY_SERVOS);
  }

  for(;y>LIMITE_Y_INICIAL;y--){
    servo_y.write(y);
    delay(DELAY_SERVOS);
  }



}


void line(uint8_t size, uint8_t direction){
  

  Serial.print("size");
  Serial.println(size);

  if(direction == 0){
    for(uint8_t i=0;i!=lengthsX[size] ;i++,pos_x-- ){




      servo_x.write(pos_x);
      if(pos_x<= LIMITE_X_INICIAL){

        Serial.print("I: ");
        Serial.println(i);
        Serial.print("S: ");
        Serial.println(lengthsY[size]);

        Serial.print("break");
          break;

      } 
      delay(DELAY_SERVOS);
    }
  }
  
  
  else if(direction == 1){
    for(uint8_t i=0; i!=lengthsX[size] ;i++,pos_x++ ){
      servo_x.write(pos_x);
      if(pos_x>= LIMITE_X_FINAL){

        Serial.print("I: ");
        Serial.println(i);
        Serial.print("S: ");
        Serial.println(lengthsY[size]);

        Serial.print("break");
          break;

      } 
      delay(DELAY_SERVOS);
    }
  }

  else if(direction == 2){
    for(uint8_t i=0; i!=lengthsY[size] ;i++ ,pos_y-- ){
      servo_y.write(pos_y);
      if(pos_y<= LIMITE_Y_INICIAL) {
        
        Serial.print("I: ");
        Serial.println(i);
        Serial.print("S: ");
        Serial.println(lengthsY[size]);

        Serial.print("break");
          break;

      }  
      delay(DELAY_SERVOS);
    }
  }

  else if(direction == 3){
    for(uint8_t i=0; i!=lengthsY[size] ;i++, pos_y++ ){
      servo_y.write(pos_y);
      if(pos_y>= LIMITE_Y_FINAL){

        Serial.print("I: ");
        Serial.println(i);
        Serial.print("S: ");
        Serial.println(lengthsY[size]);
        Serial.print("break");
        break;

      } 
      delay(DELAY_SERVOS);
    }
  }
  
}
