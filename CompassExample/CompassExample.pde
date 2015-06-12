/************************************************************************/
/*									*/
/*  CompassExample.pde	-- Example Sketch for CMPS			*/
/*									*/
/************************************************************************/
/*  Author:	Jon Peyron						*/
/*  Copyright (c) 2015, Digilent Inc.  	    				*/
/************************************************************************/
/*                                                                      */
/*  This library is free software; you can redistribute it and/or       */
/*  modify it under the terms of the GNU Lesser General Public          */
/*  License as published by the Free Software Foundation; either        */
/*  version 2.1 of the License, or (at your option) any later version.  */
/*                                                                      */
/*  This library is distributed in the hope that it will be useful,     */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of      */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU   */
/*  Lesser General Public License for more details.                     */
/*                                                                      */
/*  You should have received a copy of the GNU Lesser General Public    */
/*  License along with this library; if not, write to the Free Software */
/*  Foundation, Inc.,51 Franklin St, Fifth Floor, Boston, MA 02110-1301 */ 
/*  USA                                                                 */
/********************************************************************** */
/*  Module Description:							*/
/*									*/
/*  This sketch is an example on on how to use the CMPS to get degrees  */
/*  and direction with the CMPS library.                                */
/*                                                                      */
/************************************************************************/
/*  Revision History:							*/
/*									*/
/*  6/12/2015(Jon P): Created                                           */
/*									*/
/************************************************************************/
/************************************************************************/
/*  Board Support:                       				*/
/*  ChipKIT PRO MX4:                  I2C #2 J6 (Top)                   */
/*                                              			*/
/************************************************************************/



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

