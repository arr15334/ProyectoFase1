/*
  UVG - Algoritmos y Estructuras de Datos
  Integrantes: Rodrigo Arriaza, Sebastian Galindo y Alejandro Chaclan
  
  Basado en el codigoIR Roaming.c
  "Use IR LEDs,IR receivers and PING to detect obstacles while roaming.""

*/

#include "simpletools.h"                        // Library includes
#include "abdrive.h"
#include "ping.h"                             // Include ping header
#include "abcalibrate.h"  

int irLeft, irRight,distance;                            // IR variables

int main()                                      // main function
{

  pause(2000);
  low(26);                                      // D/A0 & D/A1 to 0 V
  low(27);

  drive_setRampStep(12);                        // Max step 12 ticks/s every 20 ms
//INICIO del algoritmo de follow right wall
  while(1)
  {
    freqout(11, 1, 38000);                      // Check left & right objects
    irLeft = input(10);

    freqout(1, 1, 38000);
    irRight = input(2);
    distance = ping_cm(8);  
    
    
    if(irRight == 1){
        drive_goto(42,42);
        pause(1000);              
        drive_goto(28,-28);                 
        pause(1000);
        drive_goto(30,30); 
        drive_rampStep(50,50);                    
    }else if(distance>20){                          
        drive_rampStep(30, 30);             
      }else{
        pause(1000);                                  
        drive_goto(-25,28);            
        pause(1000);            
    }
  }
}
