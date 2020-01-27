// Berechnung von Primzahlen

#include <iostream>
#include <math.h>

using namespace std;

int main()
{
  int ende = 1000 , primzahl = 1;
  float i = 0 , j = 0 ,vergleich = 0;

  cout << "\n Berechnen der Primzahlen bis " << ende << endl;
  cout << "\n 2 3 5 7 ";
  for ( i=11 ; i < ende ; i = i + 2)
  {
    primzahl = 1;
    for ( j = 3 ; j <= sqrt ( i ) ; j++)
    {
      vergleich = i / j;
      if ( vergleich == int ( vergleich ) )
      {
        j = i;
        primzahl = 0;
      }
    }
    if ( primzahl == 1 )
    {
      cout << i << " ";
    }
  }
  cout << "\n";
}
