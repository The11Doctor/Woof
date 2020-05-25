#include "setup.h"
#if EXAMPLE == 3

#include "Arduino.h"
#include "CameraOV7670.h"

static const uint8_t COMMAND_NEW_FRAME = 0x01;
static const uint8_t COMMAND_END_OF_LINE = 0x02;

static const uint16_t COLOR_GREEN = 0x07E0;
static const uint16_t COLOR_RED = 0xF800;

static const uint16_t UART_PIXEL_FORMAT_RGB565 = 1;
static const uint16_t UART_PIXEL_FORMAT_GRAYSCALE = 2;


// resolution and communication speed:
// 4 - 160x120 with 115200 baud
#define UART_MODE 4

#if UART_MODE==4
static const uint16_t lineLength = 160;
static const uint16_t lineCount = 120;
static const uint32_t baud  = 115200;
static const uint32_t uartSendWhileReadingCount  = 4;
static const uint8_t uartPixelFormat = UART_PIXEL_FORMAT_RGB565;
CameraOV7670 camera(CameraOV7670::RESOLUTION_QQVGA_160x120, CameraOV7670::PIXEL_RGB565, 35);
#endif



//Declaration Fonctions pour les Frames
void sendBlankFrame(uint16_t color);
inline void startNewFrame(uint8_t pixelFormat) __attribute__((always_inline));
inline void endOfLine(void) __attribute__((always_inline));
inline void sendNextPixelByte() __attribute__((always_inline));
inline void sendPixelByteH(uint8_t byte) __attribute__((always_inline));
inline void sendPixelByteL(uint8_t byte) __attribute__((always_inline));
inline void sendPixelByteGrayscale(uint8_t byte) __attribute__((always_inline));
inline void pixelSendingDelay() __attribute__((always_inline));


//////////////////////////////////////////

// this is called in Arduino setup() function
void initializeScreenAndCamera() {

  // Enable this for WAVGAT CPUs
  // For UART communiation we want to set WAVGAT Nano to 16Mhz to match Atmel based Arduino
  //CLKPR = 0x80; // enter clock rate change mode
  //CLKPR = 1; // set prescaler to 1. WAVGAT MCU has it 3 by default.
  
  Serial.begin(baud);
  if (camera.init()) { //Appel des méthodes de l'objet camera créé plus haut 
    sendBlankFrame(COLOR_GREEN); //Début de la transmission avec frame rouge
    delay(1000);
  } else {
    sendBlankFrame(COLOR_RED);
    delay(3000);
  }

  TIMSK0 = 0; // disable "millis" timer interrupt
}

/////////////////////////////////////////////////



//Envoi d'une Frame
void sendBlankFrame(uint16_t color) {
  uint8_t colorH = (color >> 8) & 0xFF;
  uint8_t colorL = color & 0xFF;

  startNewFrame(UART_PIXEL_FORMAT_RGB565); //appel de la fonction debut d'une nouvelle frame
  for (uint16_t j=0; j<lineCount; j++) {
    for (uint16_t i=0; i<lineLength; i++) {
      sendPixelByteH(colorH);
      pixelSendingDelay();
      sendPixelByteL(colorL);
      pixelSendingDelay();
    }
    endOfLine();
  }
}





uint8_t lineBuffer [lineLength*2 + 1 + 5];
uint16_t lineBufferIndex = 0;

///////////////////////////////////////////////////

// this is called in Arduino loop() function
void processFrame() {
  startNewFrame(uartPixelFormat);

  camera.waitForVsync();

  for (uint16_t y = 0; y < lineCount; y++) {
  
    lineBufferIndex = 0;
    uint8_t sendWhileReadCounter = 0;

    lineBuffer[0] = 0; // first byte from Camera is half a pixel

    for (uint16_t x = 1; x < lineLength*2+1; x++) {
      // start sending first bytes while reading pixels from camera
      if (uartSendWhileReadingCount > 0) {
        if (sendWhileReadCounter) {
          sendWhileReadCounter--;
        } else {
          sendNextPixelByte();
          sendWhileReadCounter = uartSendWhileReadingCount;
        }
      }

      camera.waitForPixelClockRisingEdge();
      camera.readPixelByte(lineBuffer[x]);
    }

     // send rest of the line
    while (lineBufferIndex < lineLength * 2) {
      sendNextPixelByte();
      pixelSendingDelay();
    }

        endOfLine();
  }
}

////////////////////////////////////////////////////

//
//Fonctions dont les prototypes sont plus haut dans ce fichier 
//


//Début nouvelle Frame
void startNewFrame(uint8_t pixelFormat) {
  UDR0 = 0x00;
  pixelSendingDelay();
  UDR0 = COMMAND_NEW_FRAME;
  pixelSendingDelay();

  // frame width
  UDR0 = (lineLength >> 8) & 0xFF;
  pixelSendingDelay();
  UDR0 = lineLength & 0xFF;
  pixelSendingDelay();

  // frame height
  UDR0 = (lineCount >> 8) & 0xFF;
  pixelSendingDelay();
  UDR0 = lineCount & 0xFF;
  pixelSendingDelay();

  // pixel format
  UDR0 = (pixelFormat);
  pixelSendingDelay();
}


void endOfLine()   {
  UDR0 = 0x00;
  pixelSendingDelay();
  UDR0 = COMMAND_END_OF_LINE;
  pixelSendingDelay();
}


void sendNextPixelByte() {
  if (uartPixelFormat == UART_PIXEL_FORMAT_GRAYSCALE) {
    sendPixelByteGrayscale(lineBuffer[lineBufferIndex]);
    lineBufferIndex += 2;
  } else {
    uint8_t byte = lineBuffer[lineBufferIndex];
    uint8_t isLowPixelByte = lineBufferIndex & 0x01;

    if (isLowPixelByte) {
      sendPixelByteL(byte);
    } else {
      sendPixelByteH(byte);
    }
    lineBufferIndex++;
  }
}


void sendPixelByteH(uint8_t byte) {
  //              RRRRRGGG
  UDR0 = byte | 0b00001000; // make pixel color always slightly above 0 since zero is end of line marker
}

void sendPixelByteL(uint8_t byte) {
  //              GGGBBBBB
  UDR0 = byte | 0b00100001; // make pixel color always slightly above 0 since zero is end of line marker
}

void sendPixelByteGrayscale(uint8_t byte) {
  UDR0 = byte | 0b00000001; // make pixel color always slightly above 0 since zero is end of line marker
}





void pixelSendingDelay() {
  while(!( UCSR0A & (1<<UDRE0)));//wait for byte to transmit
}


#endif
