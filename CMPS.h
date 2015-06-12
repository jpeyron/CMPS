/************************************************************************/
/*																		*/
/*	CMPS.h	--	Driver for Compass				             	        */
/*																		*/
/************************************************************************/
/*	Author: 	Jon Peyron												*/
/*	Copyright (c) 2015, Digilent Inc, All rights reserved		        */
/************************************************************************/
/*  Module Description: 												*/
/*																		*/
/*		This the PmodCMPS H file									    */
/*																		*/
/************************************************************************/
/*  	Revision History:												*/
/*                                                                      */
/*     	6/12/2015(JonP): created	                                    */
/*																		*/
/************************************************************************/
/*	Needs work:															*/
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



#if !defined(CMPS_H)
#define CMPS_H

#include <Wire.h>
#include <math.h>

/* -------------------------------------------------------------------- */
/*					Miscellaneous Declarations					        */
/* -------------------------------------------------------------------- */

	/*  Data Registers
	*/
	//You can look at the data sheet here to change any of the settings
	//http://www51.honeywell.com/aero/common/documents/myaerospacecatalog-documents/Defense_Brochures-documents/HMC5883L_3-Axis_Digital_Compass_IC.pdf
	//Sensor's setting register:
	const uint8_t writeReg = 0x1e;  // The 7-bit address of the PmodCMPS will be 0x1E
	const uint8_t regA = 0x70;  //Normal measurement configuration (Default)
	const int8_t  regB = 0x20;  // gain(Default)
	const uint8_t regMode = 0x00; //Mode:0x00 is continuous 0x01 is single measurement

/* -------------------------------------------------------------------- */
/*					Object Class Declarations					        */
/* -------------------------------------------------------------------- */

class CMPS
{
	public:
	    CMPS();
		void init();//set up I2C and set CMPS control registers
		float get_adjusted_degree(float offset); // get adjusted degree
		char* getDirection(float degree);//returns the direction
	private:	
		int getX();// gets the x axis value		
		int getY();// gets the y axis value
		int getZ();// gets the z axis value
		void reSetRegister();// resets the register to the x MSB
		float getDegree(int x, int y);	//translates the x and y axis to degree format
		char* findDirection(float degree);//	translates the degree into a direction
		int twosToBin(int input);// converts a negative twos compliment value 
		int getData(int reg1, int reg2);// masking and shifting to create an integer value
			
	
};

#endif //CMPS_H