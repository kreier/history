// mein erstes C++ Programm

#include <iostream>
#include <math.h>

using namespace std;

int main()
{
  int i = 0 , anzahl = 0;  
  float summe = 0;

  cout << "\n Berechnen der Näherung des Integrals f(x)=sin(x) zwischen 0 und pi" << endl;
  cout << "\n Anzahl der zu berechnenden Istwerte: ";
  cin  >> anzahl;
  if (anzahl < 2) anzahl = 2; 
  for( i = 0 ; i < anzahl ; i++)
  {
    summe = summe + sin ( M_PI / ( 2 * anzahl ) + ( M_PI * i ) / anzahl );
  }
  summe = summe / anzahl * M_PI;
  cout << "\n Die Näherung nach " << anzahl << " Berechnungen beträgt: " << summe << endl;
  cout << "\n";
}
