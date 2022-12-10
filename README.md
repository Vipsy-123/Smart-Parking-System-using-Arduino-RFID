# Smart-Parking-System-using-Arduino-RFID

THIS WAS MY SECOND YEAR MINI PROJECT FOR ANALOG AND DIGITAL ELECTRONICS


        SMART PARKING SYSTEM ENABLES YOU A SECURE PROCESS FOR PARKING OF OWNER'S VEHICLES WITHOUT ANY INTRUSION OF UNKNOWN VEHICLES.
 *      RFID SENSOR WILL SENSE ONLY REGISTERED RFID TAGS AND REJECT THE UNKNOWN TAGS BY PLAYING BUZZER SOUND.
 *      WHEN A TAG IS ACCEPTED, BARRIER ATTACHED TO SERVO MOTOR WILL OPEN AND VEHICLE WILL BE ALLOWED TO ENTER PARKING AREA. 
 *      IF PARKING SLOTS ARE AVAILABLE  BARRIER WILL ALLOW THE VEHICLES IN ,ELSE IF PARKING SLOTS ARE NOT AVAILABLE BARRIER WILL STAY DOWN. 
 *      LCD SCREEN WILL SHOW AVAILABLE PARKING SLOTS. 
 *      IR SENSOR IS ATTACHED TO EACH PARKING SLOT.
 *      WHEN ALL IR SENSORS ARE DETECTED THEN PARKING IS FULL AND LCD SCREEN WILL SHOW 'PARKING FULL.' AND BARRIER WILL STAY DOWN.


 COMPONENTS USED :
 *      RFID SENSOR RC522   X 1
 *      RFID TAGS           X 2
 *      IR SENSOR           X 2
 *      LCD SCREEN          X 1
 *      SERVO MOTOR         X 1
 *      ACTIVE BUZZER       X 1
 *      ARDUINO UNO         X 1
 *      ARDUINO USB CABLE   X 1
 *      JUMPER WIRES
 *      POTENTIOMETER

NOTE :
*As digital pins of arduino were full due to LCD display and RFID sensor pins, Analog pins were used to give signals to IR sensors and active buzzer.
*The values for Analogwrite for IR sensor were Hardcoded accordingly.
*There is Unique ID for each RFID tag.
*Please use recommended Github library to get RFID id for your tag and add it in your Arduino code.
