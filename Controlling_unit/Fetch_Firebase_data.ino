void fetctfirebase(){
  
    if (Firebase.getFloat(motorData, "/FirebaseIOT/Live_data/"+ node_id +"/motor_status")){
    Serial.println(motorData.floatData());
    motorvalue =motorData.floatData();
    
    if (Firebase.getFloat(motorData, "/FirebaseIOT/Live_data/"+ node_id +"/motor_delay")){
      Serial.print("Water Motor Delay : ");
      Serial.println(motorData.floatData());
      motordelay =motorData.floatData();

    if (motorvalue == 1) {
    Serial.println("Water Motor ON");
    digitalWrite(motorpin, HIGH);
    delay(motordelay);
    }
  else if (motorvalue == 0){
    digitalWrite(motorpin, LOW);
    Serial.println("Water Motor OFF");
    
   } else{
    digitalWrite(motorpin, LOW);
    Serial.println("Water Motor OFF");
    
   }
    }
  }else{
    Serial.println("No Reeding From Firebase Water Motor");
    }

//////////////////////
    if (Firebase.getFloat(motorData, "/FirebaseIOT/Live_data/"+ node_id +"/fertilizer_status")){
    Serial.println(motorData.floatData());
    motorvalue2 =motorData.floatData();
    
    if (Firebase.getFloat(motorData, "/FirebaseIOT/Live_data/"+ node_id +"/fertilizer_delay")){
      Serial.print("Fertilizer Delay : ");
      Serial.println(motorData.floatData());
      fertilizerdelay =motorData.floatData();

    if (motorvalue2 == 1) {
    Serial.println("Fertilizer Motor ON");
    digitalWrite(motorpin2, HIGH);    
    }
  else if (motorvalue2 == 0){
    digitalWrite(motorpin2, LOW);
    Serial.println("Fertilizer Motor OFF");
    
   } else {
    digitalWrite(motorpin2, LOW);
    Serial.println("Fertilizer Motor OFF");
    
   }
    }
  }else{
    Serial.println("No Reeding From Firebase Fertilizer Motor");
    }

}

//
//      if (Firebase.getFloat(motorData, "/FirebaseIOT/Live_data/"+ node_id +"/motor_status2")){
//    Serial.println(motorData.floatData());
//
//    motorvalue2 =motorData.floatData();
// 
//    if (motorvalue2 == 1) {
//    Serial.println("Fertilizer Motor ON");
//    digitalWrite(motorpin2, HIGH);
//    delay(2000);
//    Firebase.setFloat(motorData, "/FirebaseIOT/Live_data/"+ node_id + "/motor_status2",0);
//    Serial.println("Fertilizer Motor OFF");
//    digitalWrite(motorpin2, LOW);
//    }
//  else {
//    digitalWrite(motorpin2, LOW);
//    Serial.println("Fertilizer Motor OFF");
//    
//    }
//  }else{
//    Serial.println("No Reeding From Firebase Fertilizer");
//    }
//  
//  }
