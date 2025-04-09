#include <Elegoo_TFTLCD.h> 
#include <Elegoo_GFX.h>

#include "qrcode.h"
 
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GRAY    0x8410
#define ORANGE  0xFD00

#define TS_MINX 120
#define TS_MINY 80
#define TS_MAXX 920
#define TS_MAXY 905

#define XP 8
#define YP A3
#define XM A2
#define YM 9

int pixel_size = 10; 
int x_offset = 50;
int y_offset = 15;

#define MAX_STRINGS 99   // Set maximum number of strings you want (adjust as needed)

Elegoo_TFTLCD tft(A3, A2, A1, A0, A4); // (LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET)

void setup() {
    // Set up screen and serial connection
    Serial.begin(115200);
    tft.reset();
    tft.begin(0x9341); // LCD driver identifier
    tft.setRotation(3); 

    tft.fillScreen(WHITE); //wipe the screen first

}

void loop() {
  
  
  Serial.println("Enter a sentence:"); // enter a sentance

  // Wait until data is available in the serial buffer
  while (Serial.available() == 0) {
    // Do nothing, just wait
  }
  
  String inputStr = Serial.readString();

  Serial.print("You entered: ");
  Serial.println(inputStr);

  String result[MAX_STRINGS]; // Array of strings to hold the output
  int strLength = inputStr.length();
  int index = 0;
  // Loop to split the string into chunks of 16 characters
  for (int i = 0; i < strLength; i += 16) {
    result[index] = inputStr.substring(i, i + 16); // Get a substring from i to i+16
    index++;
    
    if (index >= MAX_STRINGS) {
      break;  // Prevent overflow if there are too many chunks
    }
  }

  for (int i = 0; i < index; i++) {
    // data processing
    int str_len = result[i].length() + 1; 
    char charArrayData[str_len];
    result[i].toCharArray(charArrayData, str_len);
    
    // Create the QR code
    tft.fillScreen(WHITE); //wipe the screen
    QRCode qrcode;
    uint8_t qrcodeData[qrcode_getBufferSize(3)];
    qrcode_initText(&qrcode, qrcodeData, 1, ECC_LOW, charArrayData);
  
    
    // Display the QR code
    for (uint8_t y = 0; y < qrcode.size; y++) {
        // displaying on screen
        for (uint8_t x = 0; x < qrcode.size; x++) {
            if (qrcode_getModule(&qrcode, x, y) == 1) {
              tft.fillRect(x*pixel_size+x_offset,y*pixel_size+y_offset, pixel_size, pixel_size, BLACK);
            }
        }
    }
    delay(700);
  }
  
    tft.fillScreen(WHITE); //wipe the screen first
} 

// Four score and seven years ago our fathers brought forth on this continent, a new nation, conceived in Liberty, and dedicated to the proposition that all men are created equal.
