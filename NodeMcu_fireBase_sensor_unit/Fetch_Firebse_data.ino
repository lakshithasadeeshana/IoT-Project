//void fetctfirebase(){
//  
//    if (Firebase.getString(motorData, "/FirebaseIOT/LiveData/Motor")){
//    Serial.println(motorData.stringData());
//
//    String motorvalue =motorData.stringData();
// 
//    if (motorvalue == "1") {
//      Serial.println("Motor ON");
//    //digitalWrite(motorpin, HIGH);
//    delay(100);
//    Firebase.setString(motorData, "/FirebaseIOT/LiveData/Motor","0");
//    }
//  else {
//    //digitalWrite(motorpin, LOW);
//    Serial.println("Motor OFF");
//    
//    }
//  }else{
//    Serial.println("No Reeding From Firebase");
//    }
//  
//  }
