# Programming in 2000

In September I started to study physics at the Humboldt Universität zu Berlin. Missing a lot of mathematical background I had to catch up on simple tasks like calculus and algebra. Even the concept of integrals or differentiation was new to me.

Connecting this new field to programming the first program I wrote in C++ was about an integral. Here from October 2000:

''' cpp
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
'''

Later I created a CLI version for linear regression. Now easily included in calculators and spreadsheet software, but it was different at the beginning of the new millenia.

