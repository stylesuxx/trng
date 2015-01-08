signed long deltaOne = 0;
signed long deltaTwo = 0;

unsigned long timeOne = 0;
unsigned long timeTwo = 0;

volatile char randomByte = B0;
volatile int currentBit = 0;

void setup() {
  Serial.begin(115200);
  attachInterrupt(0, calculateDeltas, RISING);
}
 
void loop() {
   if(currentBit >= 8) {
     // Byte sized data may be accessed without disabling the interrupts, because it is atomic
     Serial.print(randomByte);
     currentBit = 0;
     randomByte = B0;
   }
}

void calculateDeltas() {
  if(timeOne == 0) {
    timeOne = millis();
  }
  else {
    timeTwo = millis();
    
    if(deltaOne == 0) {
      deltaOne = timeTwo - timeOne;
    }
    else {
      deltaTwo = timeTwo -timeOne;
      
      if(deltaOne > deltaTwo) {
        bitSet(randomByte, currentBit);
      }
      
      timeOne = 0;
      timeTwo = 0;
      
      deltaOne = deltaTwo;
      deltaTwo = 0;
      
      currentBit += 1;
    }
  }
}
