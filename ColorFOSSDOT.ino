
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <ReticleA.h>
#include <prig1.h>
#include <prig2.h>
#include <PredatorReticle.h>
#include <xwingReticle.h>
#include <AcogRet.h>
#include <HelloKitty.h>
#include <squareRetBlkWht.h>
#include <blueSquare.h>
#include <squareRtgreen.h>
#include <EEPROM.h>

#define EEPROM_SIZE 3


  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_CS        0
  #define TFT_RST        1 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         2





// OPTION 2 lets you interface the display using ANY TWO or THREE PINS,
// tradeoff being that performance is not as fast as hardware SPI above.
// #define TFT_MOSI 1  // Data out
// #define TFT_SCLK 0  // Clock out

// For ST7735-based displays, we will use this call
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST); //when you use mosi(any2)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST); //wow so much faster than above

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
String message="blueballs";
char buf[30];

float p = 3.1415926;

int buttonPin = 21;
int curClick = 1;

class MyCallbacks: public BLECharacteristicCallbacks {
  String value = "";
    void onWrite(BLECharacteristic *pCharacteristic) {
      value = pCharacteristic->getValue();
      for(int i = 0; i < value.length();i++){
        
        buf[i] = (char)value[i];
        
      }
      
    
    }

};
int reticlePosX = 0;
int reticlePosY = 0;


void setup(void) {
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test"));
   // initialize EEPROM with predefined size
  EEPROM.begin(EEPROM_SIZE);
 pinMode(buttonPin,INPUT);
//tft.initR(INITR_GREENTAB); 
  curClick = EEPROM.read(0);
  reticlePosX = EEPROM.read(1);
  reticlePosY = EEPROM.read(2);
//tft.initR(INITR_MINI160x80);
//tft.invertDisplay(true);
  // OR use this initializer (uncomment) if using a 0.96" 160x80 TFT:
  //tft.initR(INITR_MINI160x80);  // Init ST7735S mini display
  // OR use this initializer (uncomment) if using a 0.96" 160x80 TFT with 
  // plug-in FPC (if you see the display is inverted!)
  tft.initR(INITR_MINI160x80_PLUGIN);  // Init ST7735S mini display
 BLEDevice::init("UglyOptic");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE 
                                       );
  pCharacteristic->setValue("where is it");
   pCharacteristic->addDescriptor(new BLE2902());
  pCharacteristic->setCallbacks(new MyCallbacks());
 
      
    
  
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();


  // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
  // Note that speed allowable depends on chip and quality of wiring, if you go too fast, you
  // may end up with a black screen some times, or all the time.
  //tft.setSPISpeed(40000000);

  Serial.println(F("Initialized"));

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
 // delay(500);

tft.setRotation(3);
// tft.invertDisplay(true);
//   delay(10000);


  

//   // tft print function!
//   //tftPrintTest();
//   tft.drawRGBBitmap(-15, 45, prig1, 160, 80);
//   delay(10000);

//   // a single pixel
//  // tft.drawPixel(tft.width()/2, tft.height()/2, ST77XX_GREEN);
//    tft.drawRGBBitmap(-15, 45, prig2, 160, 80);
//   delay(10000);

//   // line draw test
//   testlines(ST77XX_YELLOW);
//   delay(500);

//   // optimized lines
//   testfastlines(ST77XX_RED, ST77XX_BLUE);
//   delay(500);

//   testdrawrects(ST77XX_GREEN);
//   delay(500);

//   testfillrects(ST77XX_YELLOW, ST77XX_MAGENTA);
//   delay(500);

//   tft.fillScreen(ST77XX_BLACK);
//   testfillcircles(10, ST77XX_BLUE);
//   testdrawcircles(10, ST77XX_WHITE);
//   delay(500);

//   testroundrects();
//   delay(500);

//   testtriangles();
//   delay(500);

//   mediabuttons();
//   delay(500);

//   Serial.println("done");
//   delay(1000);
PickAReticleToShow();
}


void loop() {
  int buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
   if (digitalRead(buttonPin) == HIGH)  {
          curClick += 1;
          PickAReticleToShow();
          if (curClick > 6){
              
              curClick = 1;
          }
   }
      
  // tft.invertDisplay(true);
  // delay(500);
  // tft.invertDisplay(false);
  // delay(500);
 if(buf[0] == 'r'){
        if(reticlePosX > -16){
     
          reticlePosX -=1;
          buf[0] = ' ';
          PickAReticleToShow();
        }
      }
      if(buf[0] == 'l'){
        if(reticlePosX < 16){
          
          reticlePosX +=1;
          buf[0] = ' ';
        PickAReticleToShow();
        }
      }

      if(buf[0] == 'u'){
        if(reticlePosY < 35){
         
          reticlePosY -=1;
          buf[0] = ' ';
         PickAReticleToShow();
        }
      }

      if(buf[0] == 'd'){
        if(reticlePosY > -35){
          
          reticlePosY +=1;
          buf[0] = ' ';
         PickAReticleToShow();
        }
      }

      if(buf[0] == 'm'){
        if(reticlePosY > -35){
          
          reticlePosY = 25;
          reticlePosX = 0;
          buf[0] = ' ';
         PickAReticleToShow();
        }
      }
}

void PickAReticleToShow(){
  if(curClick == 2 ){
      SquareReticle();//white sqaure black bkg
  }else if(curClick == 3 ){
    PrigGif();
    //Predator();
  }else if(curClick == 4 ){
     SquareRetBlkWht();
    //Xwing();
  }else if(curClick == 5 ){
    Acog();
  }else if(curClick == 6 ){
    KittyHello();
  }else{
    GreenSquare();
   
  }
   // save the reticle state in flash memory
    EEPROM.write(0, curClick);
    EEPROM.write(1, reticlePosX);
    EEPROM.write(2, reticlePosY);
    EEPROM.commit();
}

void SquareReticle(){
  
        // large block of text
  tft.fillScreen(ST77XX_BLACK);
 tft.drawRGBBitmap(reticlePosX, reticlePosY, squareRetWhiteRed, 160, 80);
}

void SquareRetBlkWht(){
  //squareRetBlkWht
    tft.fillScreen(ST77XX_BLACK);
 tft.drawRGBBitmap(reticlePosX, reticlePosY, squareRetBlkWht, 160, 80);
}

void RedSquare(){
  //blueSquare
   tft.fillScreen(ST77XX_BLACK);
 tft.drawRGBBitmap(reticlePosX, reticlePosY, blueSquare, 160, 80);
}

void GreenSquare(){
  //squareRtgreen
   tft.fillScreen(ST77XX_BLACK);
 tft.drawRGBBitmap(reticlePosX, reticlePosY, squareRtgreen, 160, 80);
}

void Predator(){
 // tft.invertDisplay(true);
         // large block of text
  tft.fillScreen(ST77XX_BLACK);
  tft.drawRGBBitmap(reticlePosX, reticlePosY, PredatorReticle, 160, 80);
}

void Xwing(){
  //xwingReticle
   // tft.invertDisplay(true);
         // large block of text
  tft.fillScreen(ST77XX_BLACK);
  tft.drawRGBBitmap(reticlePosX, reticlePosY, xwingReticle, 160, 80);
}


void Acog(){
  //xwingReticle
   // tft.invertDisplay(true);
         // large block of text
  tft.fillScreen(ST77XX_BLACK);
  tft.drawRGBBitmap(reticlePosX, reticlePosY, AcogRet, 160, 80);
}

void KittyHello(){
  //xwingReticle
   // tft.invertDisplay(true);
         // large block of text
  tft.fillScreen(ST77XX_BLACK);
  tft.drawRGBBitmap(reticlePosX, reticlePosY, HelloKitty, 160, 80);
}

void PrigGif(){
   //prig pointing prig1
   
  //  tft.invertDisplay(true);
         // large block of text
  //tft.fillScreen(ST77XX_BLACK);
 tft.drawRGBBitmap(reticlePosX, reticlePosY, prig1, 160,80);
  delay(400);
  //tft.fillScreen(ST77XX_BLACK);
  tft.drawRGBBitmap(reticlePosX, reticlePosY, prig2, 160,80);
  delay(400);
   int buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
   if (digitalRead(buttonPin) == HIGH)  {
          curClick += 1;
          PickAReticleToShow();
          if (curClick > 6){
              
              curClick = 1;
          }
   }else{
     PrigGif();
   }
 
}


