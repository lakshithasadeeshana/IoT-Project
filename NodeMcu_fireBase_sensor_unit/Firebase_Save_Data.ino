void sensorUpdate(){
// "set" use for overide previous value "push" use for keep record
 // using this you can keep record
//     Firebase.setString(firebaseDataLive,"/LiveData/Temperature", String(t));
//     Firebase.setString(firebaseDataLive,"/LiveData/Humidity", "23.5");
//     Firebase.setString(firebaseDataLive,"/LiveData/Count", String(count));
//     Firebase.setString(firebaseDataLive,"/LiveData/Preasure",String(p));

     // using this you can override previous value with new Value

    float h = dht.readHumidity();
    float t = dht.readTemperature();         
    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");

  if (Firebase.setFloat(firebaseData,"/FirebaseIOT/Live_data/"+ node_id +"/temperature", t))
  {
    Serial.println("PASSED");
  }
  else
  {
   Serial.println("FAILED");
    
  }
  if (Firebase.setFloat(firebaseData,"/FirebaseIOT/Live_data/"+ node_id +"/humidity",h))
  {
    Serial.println("PASSED");
  }
  else
  {
   Serial.println("FAILED");
    
  }
    if (Firebase.setFloat(firebaseData,"/FirebaseIOT/Live_data/"+ node_id +"/voltage", vOUT))
  {
    Serial.println("PASSED");
    
  }
  else
  {
    Serial.println("FAILED");
    
  }
      if (Firebase.setFloat(firebaseData,"/FirebaseIOT/Live_data/"+ node_id +"/light",light_presentage))
  {
    Serial.println("PASSED");
    
  }
  else
  {
    Serial.println("FAILED");
    
  }
       if (Firebase.setFloat(firebaseData,"/FirebaseIOT/Live_data/"+ node_id +"/moisture", moisture_percentage))
  {
    Serial.println("PASSED");
    
  }
  else
  {
    Serial.println("FAILED");
    
  }
       if (Firebase.setFloat(firebaseData,"/FirebaseIOT/Live_data/"+ node_id +"/motor_status", motor_value))
  {
    Serial.println("PASSED");
    
  }
  else
  {
    Serial.println("FAILED");
    
  }
         if (Firebase.setString(firebaseData,"/FirebaseIOT/Live_data/"+ node_id +"/solar_status", solar_status))
  {
    Serial.println("PASSED");
    
  }
  else
  {
    Serial.println("FAILED");
    
  }

  //
 
}


void keep_record_firebase(){
  
    float h = dht.readHumidity();
    float t = dht.readTemperature(); 
  
    if (Firebase.setFloat(firebaseData,"/FirebaseIOT/Keep_record/"+ node_id +"/"+ date_time +"/temperature", t))
  {
    Serial.println("Keep record PASSED");
    
  }
  else
  {
    Serial.println("Keep record FAILED");
    
  }
      if (Firebase.setFloat(firebaseData, "/FirebaseIOT/Keep_record/"+ node_id +"/"+ date_time +"/humidity",h))
  {
    Serial.println("Keep record PASSED");
    
  }
  else
  {
    Serial.println("Keep record FAILED");
    
  }
        if (Firebase.setFloat(firebaseData,"/FirebaseIOT/Keep_record/"+ node_id +"/"+ date_time +"/humidity",h))
  {
    Serial.println("Keep record PASSED");
    
  }
  else
  {
    Serial.println("Keep record FAILED");
    
  }

          if (Firebase.setFloat(firebaseData,"/FirebaseIOT/Keep_record/"+ node_id +"/"+ date_time +"/voltage", vOUT))
  {
    Serial.println("Keep record PASSED");
    
  }
  else
  {
    Serial.println("Keep record FAILED");
    
  }
            if (Firebase.setFloat(firebaseData,"/FirebaseIOT/Keep_record/"+ node_id +"/"+ date_time +"/light",light_presentage))
  {
    Serial.println("Keep record PASSED");
    
  }
  else
  {
    Serial.println("Keep record FAILED");
    
  }

              if (Firebase.setFloat(firebaseData,"/FirebaseIOT/Keep_record/"+ node_id +"/"+ date_time +"/moisture", moisture_percentage))
  {
    Serial.println("Keep record PASSED");
    
  }
  else
  {
    Serial.println("Keep record FAILED");
    
  }

                if (Firebase.setFloat(firebaseData,"/FirebaseIOT/Keep_record/"+ node_id +"/"+ date_time +"/motor_status", motor_value))
  {
    Serial.println("Keep record PASSED");
    
  }
  else
  {
    Serial.println("Keep record FAILED");
    
  }

                if (Firebase.setString(firebaseData,"/FirebaseIOT/Keep_record/"+ node_id +"/"+ date_time +"/solar_status", solar_status))
  {
    Serial.println("Keep record PASSED");
    
  }
  else
  {
    Serial.println("Keep record FAILED");
    
  }
  
  }
