#pragma once

#include "Arduino.h" 

class MotorController{

  private:
  
    int _M1_D1; 
    int _M1_D2;
    int _M2_D1;
    int _M2_D2;
    
  public:
  
    MotorController(int m1d1, int m1d2, int m2d1, int m2d2){
      
      _M1_D1 = m1d1;
      _M1_D2 = m1d2;
      _M2_D1 = m2d1;
      _M2_D2 = m2d2;
      
    }

    MotorController(){

      _M1_D1 = 1;
      _M1_D2 = 2;
      _M2_D1 = 3;
      _M2_D2 = 4;

      
    }

    ~MotorController(){
      
    }

    void moveTo(int motorDirection, int motorSpeed){
      
      if(motorDirection == 1){
    
        analogWrite(_M1_D1, motorSpeed);
        analogWrite(_M1_D2, 0);
        analogWrite(_M2_D1, motorSpeed);
        analogWrite(_M2_D2, 0);
        
      } else if(motorDirection == 3){
    
        analogWrite(_M1_D1, motorSpeed);
        analogWrite(_M1_D2, 0);
        analogWrite(_M2_D1, 0);
        analogWrite(_M2_D2, motorSpeed);
        
      } else if(motorDirection == 4){
    
        analogWrite(_M1_D1, 0);
        analogWrite(_M1_D2, motorSpeed);
        analogWrite(_M2_D1, motorSpeed);
        analogWrite(_M2_D2, 0);
        
      } else if(motorDirection == 2){
    
        analogWrite(_M1_D1, 0);
        analogWrite(_M1_D2, motorSpeed);
        analogWrite(_M2_D1, 0);
        analogWrite(_M2_D2, motorSpeed);
        
      } else if(motorDirection == 0) {
    
        analogWrite(_M1_D1, 0);
        analogWrite(_M1_D2, 0);
        analogWrite(_M2_D1, 0);
        analogWrite(_M2_D2, 0);
            
      }
    
    }
    
    void fullStop(){
    
      analogWrite(_M1_D1, 0);
      analogWrite(_M1_D2, 0);
      analogWrite(_M2_D1, 0);
      analogWrite(_M2_D2, 0);
      delay(10);
      
    }
      
};
