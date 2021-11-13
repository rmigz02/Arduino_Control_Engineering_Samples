// MOTOR SPEED CONTROL L298N MOTOR DRIVER WITH JOYSTICK CONTROL 

// Initialize the necessary variables
int Analog_Input_Pin = A0;
int Reverse_Pin = 3;
int Forward_Pin = 4;
int Speed_Control_Pin = 5;
int Motor_Speed = 0;
  
void setup() {

  // Do not forget to set the BAUD RATE of the serial monitor to 115200
  Serial.begin(115200);

  // Initialize Analog_Input_Pin to be an input
  pinMode(Analog_Input_Pin,INPUT);

  // Initialize motor control polarity pins as outputs
  pinMode(Forward_Pin,OUTPUT);
  pinMode(Reverse_Pin,OUTPUT);

  // Initialize motor speed control pin as output
  pinMode(Speed_Control_Pin,OUTPUT);
  
}

void loop() {

  // Arduino will respond every 100 milliseconds
  delay(100);

  // Print in the serial monitor the status of the motor speed controller
  Serial.println("");
  Serial.print("Analog input value:" );
  Serial.println(analogRead(Analog_Input_Pin));
  Serial.print("Motor speed value: ");
  Serial.println(Motor_Speed);  

  // Note that analog input values obtained can vary from 0 to 1023
  // Analog input value of 0 can mean the joystick is pointed to the lowest
  // Analog input value of 1023 can mean the joystick is pointed to the highest
  // The other way around is also possible
  // For a stationary joystick, its analog input value can be around 511.5 (that is between 0 and 1023)
  // The motor should not move around analog input value 511.5
  // Note that analog input values are always integers

  // Here are the nested if conditions

    if (analogRead(Analog_Input_Pin) > 511.5)
  {
    // These lines of code executes when the analog input value is more than 511.5
    
    // By using the map() function, the motor speed is the fastest when the analog input value is 1023
    // The analog input value will map the value between 0 and 255
    Motor_Speed = map(analogRead(Analog_Input_Pin), 512, 1023, 0, 255);

    // The acceptable value for Motor_Speed is 0 to 255 where 0 is stationary and 255 is the fastest speed
    analogWrite(Speed_Control_Pin,Motor_Speed);

    // The motor must rotate forwards by only setting Forward_Pin to HIGH
    digitalWrite(Reverse_Pin,LOW);
    digitalWrite(Forward_Pin,HIGH); 

    // Print in the serial monitor that the motor is rotating in reverse
    Serial.println("Motor rotating in FORWARD");
    
  }

  
  else if (analogRead(Analog_Input_Pin) < 511.5)
  {
    // These lines of code executes when the analog input value is less than 511.5
    
    // By using the map() function, the motor speed is the fastest when the analog input value is 0
    // The analog input value will map the value between 0 and 255
    Motor_Speed = map(analogRead(Analog_Input_Pin), 511, 0, 0, 255);

    // The acceptable value for Motor_Speed is 0 to 255 where 0 is stationary and 255 is the fastest speed
    analogWrite(Speed_Control_Pin,Motor_Speed);

    // The motor must rotate backwards by only setting Reverse_Pin to HIGH
    digitalWrite(Forward_Pin,LOW); 
    digitalWrite(Reverse_Pin,HIGH);
    
    // Print in the serial monitor that the motor is rotating in reverse
    Serial.println("Motor rotating in REVERSE");
    
  }
}

// Further notes for map() function syntax
// map( value , fromLow , fromHigh , toLow , toHigh)
