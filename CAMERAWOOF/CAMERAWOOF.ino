
#include "setup.h"

void setup() {
  CLKPR = 0x80; 
  CLKPR = 0;

  initializeScreenAndCamera();
}

void loop() {
  processFrame();
}
