// Berechnung von Primzahlen
// auch bei groﬂen Werten tauchen Wertepaare
// um ein Vielfaches von 6 auf - sie stehen
// untereinander!!

#include <iostream>
#include <math.h>

using namespace std;

int main()
{
  int ende = 1000 , primzahl = 1 , spalte = 5;
  float i = 0 , j = 0 ,vergleich = 0;
  string leer = "     ";

  cout << "\n Berechnen von Primzahlen - mit systematischer Ausgabe" << endl;
  cout << "\n Berechnung bis zum Endwert: ";
  cin  >> ende;
  if (ende < 30) ende = 200; 
  if (ende > 10000000) ende = 1000;
  if (ende > 100000) leer = "      ";

  cout << "\n Berechnen der Primzahlen bis " << ende << endl;
  cout << "\n" << leer << " 2   3" << leer << "5" << leer << "7 ";
  for ( i = 9 ; i < ende ; i = i + 2)
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
      if ( i < 100000 & ende > 100000) cout << " ";
      if ( i < 10000) cout << " ";
      if ( i < 1000) cout << " ";
      if ( i < 100) cout << " ";
      cout << i << " ";
    }
    else cout << leer << " ";
    spalte = spalte + 1;
    if (spalte == 13)
    {
      cout << "\n";
      spalte = 1;
    }
  }
  cout << "\n";
}
