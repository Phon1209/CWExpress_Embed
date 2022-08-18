#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

class ILI9341_QRcode
{
	private:
		Adafruit_ILI9341 *LCD;
		//void render(int x, int y, int color);

	public:
		ILI9341_QRcode(Adafruit_ILI9341 *TFTLCD);
		void QR_Code_create(String message, int display_x, int display_y );
};