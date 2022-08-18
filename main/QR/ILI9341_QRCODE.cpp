#include <Arduino.h>
#include "ILI9341_QRCODE.h"
#include "qrencode.h"

#define piexl_size 2
//#define ILI9341_BLACK       0x0000      /*   0,   0,   0 */
//#define ILI9341_WHITE       0xFFFF      /* 255, 255, 255 */

ILI9341_QRcode::ILI9341_QRcode(Adafruit_ILI9341 *TFTLCD)
{
	this->LCD = TFTLCD;
}

void ILI9341_QRcode::QR_Code_create(String message, int display_x, int display_y )
{
	if(message.length() > 260)
	{
		Serial.println("Message lenght over 260 char!!");
	}
	else
	{
		Serial.println("Start Create QR Code.....");
		// create QR code
  		message.toCharArray((char *)strinbuf,260);
  		qrencode();
  		
  		for (byte x = 0; x < WD; x++) 
  		{
    			for (byte y = 0; y < WD; y++) 
    			{
      				if ( QRBIT(x,y) &&  QRBIT((x+1),y)) 
      				{
        				// black square on top of black square
					Serial.print("@");
        				LCD->fillRect(display_x+(x*piexl_size),display_y+(y*piexl_size),piexl_size,piexl_size,ILI9341_BLACK);
      				}
      				if (!QRBIT(x,y) &&  QRBIT((x+1),y)) 
      				{
        				// white square on top of black square
					Serial.print(" ");
        				LCD->fillRect(display_x+(x*piexl_size),display_y+(y*piexl_size),piexl_size,piexl_size,ILI9341_WHITE);
      				}
      				if ( QRBIT(x,y) && !QRBIT((x+1),y)) 
      				{
        				// black square on top of white square
					Serial.print("@");
        				LCD->fillRect(display_x+(x*piexl_size),display_y+(y*piexl_size),piexl_size,piexl_size,ILI9341_BLACK);
      				}
      				if (!QRBIT(x,y) && !QRBIT((x+1),y)) 
      				{
        				// white square on top of white square
					Serial.print(" ");
        				LCD->fillRect(display_x+(x*piexl_size),display_y+(y*piexl_size),piexl_size,piexl_size,ILI9341_WHITE);
      				}
    			}
    			Serial.println();
  		}
  		Serial.println();
	}
}