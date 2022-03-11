void analog_signal_read(){
  
    // Channel 0 (C0 pin - binary output 0,0,0,0)
    digitalWrite(S0,LOW); digitalWrite(S1,LOW); digitalWrite(S2,LOW); digitalWrite(S3,LOW);
    sensor0 = analogRead(SIG);
    //read soil value
    soilRead(sensor0);
  
    // Channel 1 (C1 pin - binary output 1,0,0,0)
    digitalWrite(S0,HIGH); digitalWrite(S1,LOW); digitalWrite(S2,LOW); digitalWrite(S3,LOW);
    sensor1 = analogRead(SIG);
    //read the light sensor
    check_light(sensor1);
  
    // Channel 2 (C2 pin - binary output 0,1,0,0)
    digitalWrite(S0,LOW); digitalWrite(S1,HIGH); digitalWrite(S2,LOW); digitalWrite(S3,LOW);
    sensor2 = analogRead(SIG);
    
    //read battery voltage
    battery_level(sensor2);
  
    Serial.print("Sensor 0 : ");Serial.print(moisture_percentage);Serial.println("%");          /* state value for soil sensor */
    Serial.print("Sensor 1 : ");Serial.println(sensor1);          /* state value for light sensor */
    Serial.print("Sensor 2 : ");Serial.println(sensor2);          /* state value for battery sensor */
   
  
    delay(1000); 
  }

 float soilRead(float soilvalue){
  
  moisture_percentage = ( 100.00 - (soilvalue/1023.00) * 100.00  );

  //Serial.print("Soil Moisture(in Percentage) = ");
  //Serial.print(moisture_percentage);
  //Serial.println("%");
    //moisture_percentage=20.0;
   return moisture_percentage;
  
  }

 float battery_level(float voltage){
  
  // vOUT = map(voltage,0,1023, 0, 2500) + offset;// map 0-1023 to 0-2500 and add correction offset
   //vOUT /=100;// divide by 100 to get the decimal values

   vin = (voltage * 5.0) / 1024.0;
   //vOUT = vin / (R2/(R1+R2));
   vOUT = 4.23;
   Serial.print("Voltage: ");                                                          
   Serial.print(vOUT);//print the voltge
   Serial.println("V");

    return vOUT;
  }

  void control_water(){

    if(moisture_percentage < 50){
      motor_value= 1;
      Serial.print("Motor ON");
      }else {
        motor_value= 0;
        Serial.print("Motor OFF");
        }
    
    }


    void check_light(float light ){
      
       light_presentage = light/100;
      if(light_presentage>50){
        solar_status="Battery Charge Using Solar";
        }else{
          solar_status="Light Intencity Low";
          }
      
      }
