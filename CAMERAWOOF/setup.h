

#ifndef CAMERAWOOF_SETUP_H
#define CAMERAWOOF_SETUP_H

/*
 * EXAMPLE = 2
 *  Use LiveOV7670Library class that processes data pixel by pixel
 *  sends data to TFT during each pixel reading loop.
 *  VGA can not be used with line buffer since there is no
 *  time (no blank lines) to do something useful with a buffered line
 *
 *  EXAMPLE = 3
 *  Reads data from LiveOV7670Library and send it over UART to computer
 *  Java application for receiving picture from UART
 *  https://github.com/indrekluuk/ArduinoImageCapture
 */

 #define EXAMPLE 3

 void initializeScreenAndCamera();
 void processFrame();

 #endif //CAMERAWOOF_SETUP_H
