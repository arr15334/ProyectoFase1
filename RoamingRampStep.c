/*
  IR Roaming.c

  Use IR LEDs and IR receivers to detect obstacles while roaming.

*/

#include "simpletools.h"                        // Library includes
#include "abdrive.h"
#include "ping.h"                             // Include ping header
#include "abcalibrate.h"

int irLeft, irRight,distance, cont;                            // IR variables

int main()                                      // main function
{
   //Se hace una pausa de 2 segundos antes de que el robot empiece a moverse
   pause(2000);
   low(26);                                      // D/A0 & D/A1 to 0 V
   low(27);

   drive_setRampStep(12);                        // Max step 12 ticks/s every 20 ms

   while(1)
   {
      //Se configura el sensor infrarrojo derecho
      freqout(11, 1, 38000);                      // Check left & right objects
      irLeft = input(10);

      //Se configura el sensor infrarrojo izquierdo
      freqout(1, 1, 38000);
      irRight = input(2);

      //Se configura el sensor frontal
      distance = ping_cm(8);

      //Primero se revisa si se detecta un objeto a la derecha
      if(irRight == 1){
         //Se mueve una corta ditancia para adelante
         drive_goto(30,30);
         cont = 0;
         while (cont < 3) {
            cont++;
            pause(5);
         }

         //El robot gira aproximadamente 90° a la derecha
         drive_goto(28,-28);
         cont = 0;
         while (cont < 62) {
            cont++;
            pause(5);
         }

         //Se vuelve a mover una corta distancia para adelante
         drive_goto(30,30);
         while (cont < 3) {
            cont++;
            pause(5);
         }
      //Si no encuentra nada a la derecha, se mueve hacia adelante si no hay un objeto a menos de 8cm
      }else if(distance>8){
         drive_rampStep(80, 80);
      //En caso que no se pueda mover para la derecha o para adelante, gira 90° a la izquierda
      }else{
         drive_speed(-25,28);
         cont = 0;
         while (cont < 147) {
            cont++;
            pause(5);
         }
      }
   }
}
