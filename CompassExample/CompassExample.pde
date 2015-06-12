#include <CMPS.h>


/*
CMPS with I2C example. This will display directions pmod CMPS compass
*/
// the sensor communicates using I2C, so include the library:
 #include <Wire.h> 


CMPS myCMPS;


void setup(){
   
        Serial.begin(9600);
        // starts I2C communication and sets the compass's settings
        myCMPS.init();
}

void loop(){
        int i;//used in for loop
        char numStr[6]; // used to get declination
        char* direction; // used to get direction
        float degree; // used to get degree
        float offset = 0.0;  // default is Magnetic north. pullman Wa ia currently 14.38
        //you can find the Magnetic declination where you are at web sites like
        // "http://www.ngdc.noaa.gov/geomag/declination.shtml"
        Serial.println("Please enter the Magnetic declination at your location");
        Serial.println("East is positive and West is negative:  ");
        delay(5000);
        // read the characters from the buffer into a character array
        for( i = 0; i < 6; ++i ) {
        numStr[i] = Serial.read();
        }
    
        //terminate the string with a null prevents atof reading too far
        numStr[i] = '\0';
    
        //read character array until non-number, convert to double
        offset = atof(numStr);
        
        Serial.print("The Magnetic Declination is: ");
        Serial.println(offset);
        Serial.print("\n");
        Serial.print("\n");
        delay(1000);
        
        while(1){  
        // gets the adjusted degree
        degree = myCMPS.get_adjusted_degree(offset);
          
        Serial.println(degree);
        // gets the direction
        direction = myCMPS.getDirection(degree);
       
        Serial.println(direction);
       
        Serial.print("\n");
        Serial.print("\n");
 
        delay(1000);// slow down loop
        }//end of while


}// end of loop

