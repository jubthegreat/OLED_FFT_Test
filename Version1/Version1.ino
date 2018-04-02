//Inspiration taken from site linked below
//https://www.norwegiancreations.com/2017/08/what-is-fft-and-how-can-you-implement-it-on-an-arduino/


#include <arduinoFFT.h>
#include <defs.h>
#include <types.h>

#define fsamp 8000 //Sampling frequency defined here
#define fftsize 64 //Size of the FFT blocks defined here
#define SCL_FREQUENCY 0x02

arduinoFFT FFT = arduinoFFT();

struct comp{ //Define a complex structure
  double re=0;
  double im=0;
};
typedef struct comp Comp;

Comp C[fftsize];
unsigned int Tsamp;
unsigned long microsecondcounter;

void setup() { 
  Serial.begin(115200); //Initialise Baud Rate
  Tsamp=(1/fsamp)*1000000; //Define sampling period in microseconds
}

void loop() {
  
  for(int i=0; i<fftsize; i++){  //Input data from analogue read with implemented 'sampling interrupt'
    microsecondcounter=micros();
   C[i].re=sin(2*PI*1000*micros());
   // C[i].re=analogRead(0);
    C[i].im=0;

    while(microsecondcounter < microsecondcounter+Tsamp);
  }

 FFT.Windowing(C.re, fftsize, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
 FFT.Compute(C.re, C.im, fftsize, FFT_FORWARD);
 FFT.ComplexToMagnitude(C.re, C.im, fftsize);
 
 Serial.println("Computed magnitudes:");
 PrintVector(C.re, (samples >> 1), SCL_FREQUENCY);

}
