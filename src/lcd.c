#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <softTone.h>

#define I2C_ADDR  0x27  // I2C device address

#define LCD_CHR  1	// Mode - Sending data
#define LCD_CMD  0	// Mode - Sending command

#define LINE1  0x80	// 1st line
#define LINE2  0xC0	// 2nd line

#define LCD_BACKLIGHT  0x08	//on
// LCD_BACKLIGHT = 0x00 # off

#define ENABLE  0b00000100 // Enable bit

#define TRIG_PIN 0      //초음파 센서 Trig 핀
#define ECHO_PIN 1      //초음파 센서 Echo 핀

#define SPKR	6	//Gpio 25
#define TOTAL	3

void lcd_init(void);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);

// added by Lewis
void typeInt(int i);
void typeFloat(float myFloat);
void lcdLoc(int line);	// move cursor
void ClrLcd(void);	// clr LCD return home
void typeln(const char *s);
void typeChar(char val);
int fd;	// seen by all subroutines

int sori[] = {1100, 1200, 1319 };

void warnstart()
{
        int i;

	softToneCreate(SPKR);
	
	for (i = 0; i < TOTAL; ++i){

       		softToneWrite(SPKR, sori[i]);
		delay(300);
	}
        
}
void Danger()
{
	int i;

	softToneCreate(SPKR);

	for (i = 0; i < TOTAL; ++i){

		softToneWrite(SPKR, sori[i]);
		delay(50);
	}
	
}



float getDistance(){
        digitalWrite(TRIG_PIN, LOW);
        delayMicroseconds(2);

        digitalWrite(TRIG_PIN, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIG_PIN, LOW);

        while (digitalRead(ECHO_PIN) == LOW);
        long startTime = micros();
        while (digitalRead(ECHO_PIN) == HIGH);
        long travelTime = micros() - startTime;

        float distance = travelTime / 58.0;
}



int main()
{
	if (wiringPiSetup() == -1) exit (1);

	fd = wiringPiI2CSetup(I2C_ADDR);

	//printf("fd = %d", fd);
	
	lcd_init(); // Setup LCD
	

        pinMode(TRIG_PIN, OUTPUT);
        pinMode(ECHO_PIN, INPUT);
	pinMode(SPKR, OUTPUT);

	char array1[] = "       Be";
	char array2[] = "     Careful!";
	char array3[] = "     Stop!!";
	char array4[] = "   Don't move";

        while(1){
                delay(200);

                float distance = getDistance();
                printf("Distance: %4.2f(cm)\n", distance);

                if (distance > 10 && distance <= 20){
                        ClrLcd();
                        lcdLoc(LINE1);
                        typeln(array1);
                        lcdLoc(LINE2);
                        typeln(array2);
			
			warnstart();
			delay(100);
		}else if (distance <= 10){
			ClrLcd();
			lcdLoc(LINE1);
			typeln(array3);
			lcdLoc(LINE2);
			typeln(array4);

			Danger();
			delay(100);
				
       		}else{
			lcd_byte(0x01, LCD_CMD);	//LCD Reset	
			softToneWrite(SPKR, 0);
			delay(100);
		 }
	}
	return 0;

}

void typeFloat(float myFloat){
	char buffer[20];
	sprintf(buffer, "%4.2f", myFloat);
	typeln(buffer);
}

void typeInt(int i){
	char array1[20];
	sprintf(array1, "%d", i);
	typeln(array1);
}

void ClrLcd(void){
	lcd_byte(0x01, LCD_CMD);
	lcd_byte(0x02, LCD_CMD);
}

void lcdLoc(int line){
	lcd_byte(line, LCD_CMD);
}

void typeChar(char val){
	lcd_byte(val, LCD_CHR);
}

void typeln(const char *s){

	while( *s ) lcd_byte(*(s++), LCD_CHR);
}

void lcd_byte(int bits, int mode){
	
	int bits_high;
	int bits_low;

	bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT ;
	bits_low = mode | (bits << 4) | LCD_BACKLIGHT ;

	wiringPiI2CReadReg8(fd, bits_high);
	lcd_toggle_enable(bits_high);

	wiringPiI2CReadReg8(fd, bits_low);
	lcd_toggle_enable(bits_low);
}

void lcd_toggle_enable(int bits) {
	delayMicroseconds(500);
	wiringPiI2CReadReg8(fd, (bits | ENABLE));
	delayMicroseconds(500);
	wiringPiI2CReadReg8(fd, (bits & ~ENABLE));
	delayMicroseconds(500);
}

void lcd_init(){
	//instalise display
	lcd_byte(0x33, LCD_CMD);
	lcd_byte(0x32, LCD_CMD);
	lcd_byte(0x06, LCD_CMD);
	lcd_byte(0x0C, LCD_CMD);
	lcd_byte(0x28, LCD_CMD);
	lcd_byte(0x01, LCD_CMD);
	delayMicroseconds(500);
}


