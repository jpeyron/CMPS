/************************************************************************/
/*																		*/
/*	CMPS.cpp	--	Driver for Compass				        	        */
/*																		*/
/************************************************************************/
/*	Author: 	Jon Peyron												*/
/*	Copyright (c) 2015, Digilent Inc, All rights reserved		        */
/************************************************************************/
/*  Module Description: 												*/
/*																		*/
/*		This the PmodCMPS CPP file									    */
/*																		*/
/************************************************************************/
/*  	Revision History:												*/
/*                                                                      */
/*     	6/12/2015(JonP): created	                                    */
/*																		*/
/************************************************************************/
/*																		*/
/*		Various functionality could be added to further the library     */
/*      such as:                                                        */
/*       - incorporating accelerometer info to allow for compass        */
/*		   being used with any orientation	                            */
/*		 - incorporating gyroscope info to allow for compass            */
/*		   being used with any orientation						        */								
/*																		*/
/*		For the PmodCMPS datasheet, refer to:							*/
/*   	http://www51.honeywell.com/aero/common/documents/               */
/*      myaerospacecatalog-documents/Defense_Brochures-documents/       */
/*		MC5883L_3-Axis_Digital_Compass_IC.pdf		                    */
/*																		*/
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
/*  Foundation, Inc.,51 Franklin St, Fifth Floor, Boston, MA  02110-1301*/ 
/*  USA                                                                 */
/************************************************************************/


/* ------------------------------------------------------------ */
/*				Include File Definitions						*/
/* ------------------------------------------------------------ */
#include <CMPS.h>

#define PI 3.14159265 // value of PI

//lookup table for degrees from 301 to 360
int degree_301_360[] = {  
     360,360,360,360,359,359,359,359,358,358,358,358,357,357,357,357,356,
	 356,356,356,355,355,355,355,354,354,354,354,353,353,353,353,352,352,
	 352,352,351,351,351,351,350,350,350,350,349,349,349,349,348,348,348,
	 348,347,347,347,347,346,346,346,346,345,345,345,345,344,344,344,344,
	 343,343,343,343,342,342,342,342,341,341,341,341,340,340,340,340,339,
	 339,339,339,338,338,338,338,337,337,337,337,336,336,336,336,335,335,
	 335,335,334,334,334,334,333,333,333,333,332,332,332,332,331,331,331,
	 331,330,330,330,330,329,329,329,329,328,328,328,328,327,327,327,327,
	 326,326,326,326,325,325,325,325,324,324,324,324,323,323,323,323,322,
	 322,322,322,321,321,321,321,320,320,320,320,319,319,319,319,318,318,
	 318,318,317,317,317,317,316,316,316,316,316, 315,315,315,315,315,314,
	 314,314,314,314,314,313,313,313,313,313,312,312,312,312,312,311,311,
	 311,311,311,310,310,310,310,310,309,309,309,309,309,309,308,308,308,
	 308,308,308,307,307,307,307,307,307,306,306,306,306,306,306,305,305,
	 305,305,305,305,304,304,304,304,304,304,304,303,303,303,303,303,303,
	 303,302,302,302,302,302,302,302,301,301,301,301,301,301,301,301,301,
	 301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,
	 301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,
	 301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,
	 301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,
	 301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,
	 301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,
	 301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301,301
	};

//lookup table for degrees from 175 to 300
int degree_175_300[]  = {
     300, 300, 300, 300, 300, 300, 299, 299, 299, 299, 299, 299, 298, 298,
	 298, 298, 298, 298, 297, 297, 297, 297, 297, 297, 296, 296, 296, 296, 
	 296, 296, 295, 295, 295, 295, 295, 295, 294, 294, 294, 294, 294, 294,
	 293, 293, 293, 293, 293, 293, 292, 292, 292, 292, 292, 292, 291, 291,
	 291, 291, 291, 291, 291, 290, 290, 290, 290, 290, 290, 289, 289, 289,
	 289, 289, 289, 288, 288, 288, 288, 288, 288, 287, 287, 287, 287, 287,
	 287, 287, 286, 286, 286, 286, 286, 286, 285, 285, 285, 285, 285, 285,
	 284, 284, 284, 284, 284, 284, 283, 283, 283, 283, 283, 283, 282, 282,
	 282, 282, 282, 282, 281, 281, 281, 281, 281, 281, 280, 280, 280, 280,
	 280, 280, 279, 279, 279, 279, 279, 279, 279, 279, 278, 278, 278, 248, 
	 278, 278, 278, 277, 277, 277, 277, 277, 277, 277, 276, 276, 276, 276, 
	 276, 276, 276, 275, 275, 275, 275, 275, 275, 275, 275, 274, 274, 274,
	 274, 274, 274, 274, 273, 273, 273, 273, 273, 273, 273, 273, 273, 272,
	 272, 272, 272, 272, 272, 271, 271, 271, 271, 271, 271, 271, 271, 270, 
	 270, 270, 270, 270, 270, 270, 270, 270, 270, 270, 269, 269, 269, 269,
	 268, 268, 268, 268, 268, 267, 267, 267, 267, 267, 266, 266, 266, 266,
	 265, 265, 265, 265, 265, 264, 264, 264, 264, 264, 263, 263, 263, 263,
	 263, 262, 262, 262, 262, 262, 261, 264, 261, 261, 261, 260, 260, 260, 
	 260, 259, 259, 259, 259, 258, 258, 258, 258, 257, 257, 257, 257, 256, 
	 256, 256, 256, 255, 255, 255, 254, 254, 254, 253, 253, 253, 252, 252, 
	 252, 251, 251, 251, 250, 250, 250, 249, 249, 249, 248, 248, 248, 247,
	 247, 247, 246, 246, 246, 245, 245, 245, 245, 244, 244, 244, 244, 243, 
	 243, 243, 242, 242, 242, 241, 241, 241, 240, 240, 240, 239, 239, 239,
	 239, 238, 238, 238, 237, 237, 237, 237, 236, 236, 236, 236, 235, 235, 
	 235, 234, 234, 234, 233, 233, 233, 232, 232, 232, 231, 231, 231, 230,
	 230, 230, 229, 229, 229, 228, 228, 228, 227, 227, 227, 226, 226, 226, 
	 225, 225, 225, 224, 224, 224, 223, 223, 223, 222, 222, 222, 221, 221, 
	 221, 220, 220, 220, 220, 219, 219, 219, 219, 218, 218, 218, 217, 217,
	 217, 217, 216, 216, 216, 215, 215, 215, 214, 214, 214, 213, 213, 213, 
	 212, 212, 212, 211, 211, 211, 210, 210, 210, 209, 209, 209, 208, 208,
	 208, 207, 207, 207, 206, 206, 206, 206, 205, 205, 205, 205, 204, 204,
	 204, 204, 203, 203, 203, 203, 202, 202, 202, 202, 201, 201, 201, 201,
	 200, 200, 200, 200, 199, 199, 199, 199, 198, 198, 198, 198, 197, 197,
	 197, 197, 196, 196, 196, 196, 195, 195, 195, 195, 194, 194, 194, 194,
	 193, 193, 193, 193, 192, 192, 192, 192, 191, 191, 191, 191, 190, 190, 
	 190, 190, 189, 189, 189, 189, 188, 188, 188, 188, 187, 187, 187, 187,
	 186, 186, 186, 186, 185, 185, 185, 185, 184, 184, 184, 184, 183, 183, 
	 183, 183, 182, 182, 182, 181, 181, 181, 180, 180, 180, 180, 180, 179, 
	 179, 179, 178, 178, 178, 177, 177, 177, 176, 176, 176, 175, 175, 175, 
	 175,175, 175, 175, 175, 175  
	 };

//lookup table for degrees from 50 to 174	 
int degree_50_174[]  = {
	50,50,50,50,50,51,51,51,51,51,52,52,52,52,52,53,53,53,53,53,54,54,54,54,
	54,55,56,56,56,56,56,57,57,57,57,57,58,58,58,58,58,59,59,59,59,59,60,60,
	60,60,60,61,61,61,61,61,62,62,62,62,62,63,63,63,63,63,64,64,64,64,64,65,
	65,65,65,65,66,66,66,66,66,67,67,67,67,67,68,68,68,68,68,69,70,70,70,70,
	70,71,71,71,71,71,72,72,72,72,72,73,73,73,73,73,74,74,74,74,74,75,75,75,
	75,75,76,76,76,76,76,77,77,77,77,77,78,78,78,78,78,79,79,79,79,79,80,80,
	80,80,80,81,81,81,81,81,82,82,82,82,82,83,83,83,83,83,84,84,84,84,84,85,
	85,85,85,85,86,86,86,86,86,87,87,87,87,87,88,88,88,88,88,89,89,89,89,89,
	90,90,90,90,90,91,91,91,91,91,92,92,92,92,92,93,93,93,93,93,94,94,94,94,
	94,95,95,95,95,95,96,96,96,96,96,97,97,97,97,97,98,98,98,98,98,99,99,99,
	99,99,100,100,100,100,100,101,101,101,101,101,102,102,102,102,102,103,103,
	103,103,103,104,104,104,104,104,105,105,105,105,105,106,106,106,106,106,107,
	107,107,107,107,108,108,108,108,108,109,109,109,109,109,110,110,110,110,110,
	111,111,111,111,111,112,112,112,112,112,113,113,113,113,113,114,114,114,114,
	114,115,115,115,115,115,116,116,116,116,116,117,117,117,117,117,118,118,118,
	118,118,119,119,119,119,119,120,120,120,120,120,121,121,121,121,121,122,122,
	122,122,122,123,123,123,123,123,124,124,124,124,124,125,125,125,125,125,126,
	126,126,126,126,127,127,127,127,127,128,128,128,128,128,129,129,129,129,129,
	130,130,130,130,130,131,131,131,131,131,132,132,132,132,132,133,133,133,133,
	133,134,134,134,134,134,135,135,135,135,135,136,136,136,136,136,137,137,137,
	137,137,138,138,138,138,138,139,139,139,140,140,140,141,141,141,142,142,142,
	143,143,143,144,144,144,144,145,145,145,146,146,146,147,147,147,147,148,148,
	148,148,149,149,149,150,150,150,150,151,151,151,152,152,152,153,153,153,154,
	154,154,155,155,155,156,156,156,157,157,157,158,158,158,159,159,159,159,159,
	160,160,160,161,161,161,162,162,162,163,163,163,164,164,164,164,165,165,165,
	166,166,166,167,167,168,168,168,169,169,169,170,170,170,171,171,172,172,173,
	173,173,174,174, 174,174,174,174,174,174,174,174,174,174, 174, 174, 174, 174
	};
	
//lookup table for degrees from 0 to 49
int degree_0_49[]  = {
	0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5,6,6,6,
	6,6,6,7,7,7,7,7,7,8,8,8,8,8,8,9,9,9,9,9,9,10,10,10,10,10,10,11,11,11,11,11,11,
	12,12,12,12,12,12,13,13,13,13,13,13,14,14,14,14,14,14,15,15,15,15,15,15,16,16,
	16,16,16,16,17,17,17,17,17,17,18,18,18,18,18,18,19,19,19,19,19,19,20,20,20,20,
	20,20,21,21,21,21,21,21,22,22,22,22,22,22,23,23,23,23,23,23,24,24,24,24,24,24,
	25,25,25,25,25,25,26,26,26,26,26,26,27,27,27,27,27,27,28,28,28,28,28,28,29,29,
	29,29,29,29,30,30,30,30,30,30,31,31,31,31,31,31,32,32,32,32,32,32,33,33,33,33,
	33,33,34,34,34,34,34,34,35,35,35,35,35,35,36,36,36,36,36,36,36,37,37,37,37,37,
	37,38,38,38,38,38,38,39,39,39,39,39,39,40,40,40,40,40,40,41,41,41,41,41,41,42,
	42,42,42,42,42,43,43,43,43,43,43,44,44,44,44,44,44,45,45,45,45,45,45,46,46,46,
	46,46,46,47,47,47,47,47,47,48,48,48,48,48,48,49,49,49,49,49,49,49
	};
	
/* ------------------------------------------------------------ */
/*  CMPS
**
**  Parameters:
**    none
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**    Constructor to the class CMPS
*/
/* ------------------------------------------------------------ */

CMPS::CMPS(){	
}

/* ------------------------------------------------------------ */
/*  setRegister()
**
**  Parameters:
**    none
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**   	starts I2C communication and sets the default settings for use
*/
/* ------------------------------------------------------------ */

void CMPS::init(){
	
	Wire.begin(); //connects I2C
	Wire.beginTransmission(writeReg); //starts communication with CMPS
	Wire.write(0x00); //Register A
	Wire.write(regA ); //normal measurement
	Wire.write(0x01); //Register B
	Wire.write(regB); //gain  
	Wire.write(0x02);// Mode Register
	Wire.write(regMode);// continuous measurement mode
	Wire.endTransmission(); // end transmission 

}


/* ------------------------------------------------------------ */
/*  get_adjusted_degree()
**
**  Parameters:
**    float offset - Magnetic declination
**
**  Return Value:
**    float degree - adjusted degree 
**
**  Errors:
**    none
**
**  Description:
**   	gets the x,y and z values, resets the register, 
**      gets the degree and then adjusts got the Magnetic declination   
*/
/* ------------------------------------------------------------ */

float CMPS::get_adjusted_degree(float offset){
	
	float degree;	

	int x,y,z; 

	Wire.requestFrom(0x1e, 6); //request data from 6 registers
	while(Wire.available()) //while there is a byte to receive
	{   
		x = getX();
		z = getZ();
		y = getY(); 
	}
	reSetRegister();// sets register back to first register to read
	//gets initial degree

	degree = getDegree(x,y);

	//adding in the declination
	degree = degree + offset; 
	 
	if(offset > 0)
	{
		//if declination is  positive
		if(degree > 360 ) degree = degree -360;
		//if declination is negative  	 
	}else if(offset < 0)
	{
		//if declination is negative				
		if(degree < 0) degree = (360 + degree);	 
	}
     
	 return degree;
}

/* ------------------------------------------------------------ */
/*  getDirection()
**
**  Parameters:
**    float degree - adjusted degree
**
**  Return Value:
**    char * Direction - the direction
**
**  Errors:
**    none
**
**  Description:
**   	gets the direction
**      calls the private function findDir to get the direction
*/ 
/* ------------------------------------------------------------ */
 
char* CMPS::getDirection(float degree){
     
	 char* direction;
	 //gets the direction
	 direction = findDirection(degree);
	 
	 return direction;
}

/* ------------------------------------------------------------ */
/*  getDegree()
**
**  Parameters:
**    int x, int y  - x and y grid coordinates
**
**  Return Value:
**    float degree - initial degree   
**
**  Errors:
**    none
**
**  Description:
**   	 converts the x and y values into degree
*/
/* ------------------------------------------------------------ */

float CMPS::getDegree(int x, int y){
	
	//degree value
	float degree;
		
	// degree 305 -360
	if(x>0 && y > 0)
	{
	
	degree =  degree_301_360[x];

	//degree 175-300
	}else if( x > 0  && y < 0)
	{	
	
	y = y * -1;

	degree = degree_175_300[y];

	//degree 50-175
	}else if( x < 0  && y < 0)
	{

	y = y * -1;
	x = x * -1;

	degree = degree_50_174[y];

	//degree 0-45
	}else if( x < 0  && y > 0)
	{
	
	x = x * -1;
	degree = degree_0_49[x];
	
	}

	return degree;
}

/* ------------------------------------------------------------ */
/*  findDirection()
**
**  Parameters:
**   float degree- final degree with declination added
**
**  Return Value:
**    char* direction - direction   
**
**  Errors:
**    none
**
**  Description:
**   	converts degree value to a direction
*/
/* ------------------------------------------------------------ */

char* CMPS::findDirection(float degree){
  
	char* direction;
	//converts the degree to a direction
	if(degree > 0 && degree <= 22.5)       direction =  "Direction: NORTH";
	if(degree > 22.5 && degree <= 67.5)    direction =  "Direction: NORTH EAST";
	if(degree > 67.5 && degree <= 112.5)   direction =  "Direction: EAST";
	if(degree > 112.5 && degree <= 157.5)  direction =  "Direction: SOUTH EAST";
	if(degree > 157.5 && degree <= 202.5)  direction =  "Direction: SOUTH";
	if(degree > 202.5 && degree <= 247.5)  direction =  "Direction: SOUTH WEST";
	if(degree > 247.5 && degree <= 292.5)  direction =  "Direction: WEST";
	if(degree > 292.5 && degree <= 337.5)  direction =  "Direction: North WEST";
	if(degree > 337.5 && degree <= 360.5)  direction =  "Direction: NORTH";

	return direction;
}

/* ------------------------------------------------------------ */
/*  reSetRegister()
**
**  Parameters:
**    none
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**  puts back to the first register x_A to read info from  
*/
/* ------------------------------------------------------------ */

void CMPS::reSetRegister(){
	//sets the next register to be read back to the first register X MSB
	Wire.beginTransmission(0x1e);
	Wire.write(0x03);
	Wire.endTransmission();
}

/* ------------------------------------------------------------ */
/*  getX()
**
**  Parameters:
**    none
**
**  Return Value:
**    int result - an integer value of the read X data from getData
**
**  Errors:
**    none
**
**  Description:
**   	call getData with the x_A and x_B registers and return that value
*/
/* ------------------------------------------------------------ */

int CMPS::getX(){
	
	int result;	
	int x_A;
	int x_B;
	//get data from x data register
	
	x_A = Wire.receive();// x  MSB register
    x_B = Wire.receive();// x  LSB register
	  
	result = getData(x_A, x_B);	
	
	//process to achieve desired reading
	
	return result;
}

/* ------------------------------------------------------------ */
/*  getY()
**
**  Parameters:
**    none
**
**  Return Value:
**    int result - an integer value of the read Y data from getData
**
**  Errors:
**    none
**
**  Description:
**   	call getData with the y_A and y_B registers and return that value
*/
/* ------------------------------------------------------------ */

int CMPS::getY(){	
	
	int result;	
	int y_A;
	int y_B;
	
	//get data from y data register
	y_A = Wire.receive();// y  MSB register
    y_B = Wire.receive();// y  LSB register
	
	result = getData(y_A, y_B);	
	
		
	return result;
}

/* ------------------------------------------------------------ */
/*  getZ()
**
**  Parameters:
**    none
**
**  Return Value:
**    int result - an integer value of the read Z data from getData
**
**  Errors:
**    none
**
**  Description:
**   	call getData with the z_A and z_B registers and return that value
*/
/* ------------------------------------------------------------ */

int CMPS::getZ(){	
	
	int result;	
	int z_A;
	int z_B;
	
	//get data from z data register
	
	z_A = Wire.receive();// z  MSB register
    z_B = Wire.receive();// z  LSB register
	  
	result = getData(z_A, z_B);	
	
	return result;
}

/* ------------------------------------------------------------ */
/*  getData()
**
**  Parameters:
**    	reg1 - first register to read from. the high data value which contains 
**		the 3 MSBs
**		reg2 - second register to read from. the low data value which contains
**		the 8 LSBs
**
**  Return Value:
**    int result - an integer value of the combined data in the two registers
**
**  Errors:
**    none
**
**  Description:
**   	get Data is used to get the 11 bit x,y,z that come from 2 registers
**		from the compass. The function spits out a signed integer value
*/
/* ------------------------------------------------------------ */

int CMPS::getData(int reg1, int reg2){
	
	//create variable to be returned
	int buffer = 0;
	int result = 0;	
	int sign = 0;
	
	//store Data high into result
	buffer = reg1;
	
	//Shift over 8 to make room for lower bits
	buffer = buffer << 8;

	//store Data low into 8 LSB
	buffer = buffer | reg2;
	
	if(buffer >= 0x8000){// If negative
		sign = 1;
		buffer = twosToBin(buffer);
	}
	
	//Get rid of first 4 bits
	result = buffer & 0x07ff;

	if(sign == 1){
		result = 0 - result;
	}
	
	return result;	

}

/* ------------------------------------------------------------ */
/*  twosToBin()
**
**  Parameters:
**   integer 
**
**  Return Value:
**    returns a 16 bit unsigned integer with the positive value of the negative twos compliment
**
**  Errors:
**    none
**
**  Description:
**   	This function converts a negative twos compliment value and preforms a bitwise flip and subtracts
**		one to return the positive int value.
*/
/* ------------------------------------------------------------ */

int CMPS::twosToBin(int input){	
	
	//flip all 11 bits
	input = input ^ 0x07ff;
	
	//subtract 1 to get binary
	input = input - 1;
	
	return input;	
}

