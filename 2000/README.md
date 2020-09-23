# Programming in 2000

In September I started to study physics at the Humboldt Universität zu Berlin. Missing a lot of mathematical background I had to catch up on simple tasks like calculus and algebra. Even the concept of integrals or differentiation was new to me.

## First program in C++

Connecting this new field to programming the first program I wrote in C++ was about an integral. Here from October 2000:

``` cpp
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
```

Later I created a CLI version for linear regression. Now easily included in calculators and spreadsheet software, but it was different at the beginning of the new millenia.

## Snellius law

The objective was reframed as a life guard trying to save a swimmer while being faster on land than in water. What's the fastest trajectory?

``` cpp
// Berechnung des Rettungsschwimmerweges
//
// Ein Mensch am Strand sieht einen Schwimmer in Not und will ihn retten.
// Retter und Schwimmer sind jeweils d = 50 m (lotrecht) vom Ufer entfernt. Die
// seitliche Versetzung betrage s = 100 m. Der Retter kann zehnmal schneller
// laufen als schwimmen. Er startet deshalb nicht in der direkten Sichtlinie zum
// Schwimmer, sondern wählt einen anderen Winkel alpha zum Lot, um die Zeit zur
// Rettung minimal zu halten. Es handle sich um ein stehendes Gewässer.
//

#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

long double wert(double);

int main()
{
  int anzahldurchlauf = 13;
  int durchlauf;

  double c = 0;

  double i = 0 ; 
  double derzeitbestes = 50;
  double bestes = 50;
  double b = 0; 

  cout << "\n Optimaler Weg für den Retter des Schwimmers " << endl;
  cout << " -------------------------------------------" << endl;
  cout << endl;

  for ( durchlauf = 0 ; durchlauf < anzahldurchlauf ; durchlauf++ )
  {
    for ( i = -5 ; i <= 5 ; i++)
    {
      c = (i / pow( 10 ,  durchlauf - 1 ) );
      b = bestes + c;
      if ( wert( b ) < wert( derzeitbestes ) )
      {
        derzeitbestes = b;
      }
    }
    bestes = derzeitbestes;
    cout.fixed;
    cout << setprecision(13) << "  " << setw(2) << durchlauf + 1 << ". Durchlauf, bestes b : " << bestes << endl;
  }
  cout << endl;
  return 0;
}

long double wert( double x )
{
  return (10 * sqrt( 2500 + x * x ) + sqrt( 2500 + ( 100 - x ) * ( 100 - x ) ) );  
}
```

## Linear regression

This example gives you the error in the coefficients __a__ and __b__ of ```f(x) = ax + b``` as well:

``` cpp
// ein C++ zum Geradenausgleich

#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>

using namespace std;

#define cls   (cout << "\033[2J")
#define locate(z,s) (cout << "\033["<< z <<';'<< s <<'H')
#define hoch  (cout << "\033[1A")
#define rechts(r)   (cout << "\033["<< r <<'C')

double eingabe();

int main()
{
  cls;
  locate(0,0);
  cout << "\n  Geradenausgleich" << endl;
  cout << "  ----------------\n" << endl;

//  Zunächst die Daten einlesen

  double daten[2][100];
  double x =  1;
  int    i = -1;

  while(x != 0)
  {
    i++;
    cout << " x-Wert: ";
    daten[0][i] = eingabe();
    x = daten [0][i];
    hoch; rechts(20);
    cout << " y-Wert: ";
    if(x != 0)
      daten[1][i] = eingabe();
  }

//  Auswertung der Daten - nur die y-Daten sind fehlerbehaftet

  cout << "\n\n Koeffizienten der Funktion y = ax + b " << endl;

  int n=i;
  float D = 0;
  float summe_x = 0;
  float summe_y = 0;
  float summe_xy = 0;
  float summe_xquadrat = 0;
  float summe_vquadrat = 0;
  float a, b, sy, sa, sb;

  for(i = 0 ; i < n ; i++) summe_x  += daten [0][i];
  for(i = 0 ; i < n ; i++) summe_y  += daten [1][i];
  for(i = 0 ; i < n ; i++) summe_xy += daten[0][i]*daten[1][i];
  for(i = 0 ; i < n ; i++) summe_xquadrat += daten[0][i]*daten[0][i];

  D = n * summe_xquadrat - summe_x * summe_x;

  a = (n * summe_xy - summe_x * summe_y) / D;

  b = (summe_xquadrat * summe_y - summe_xy * summe_x) / D;

  for(i = 0 ; i < n ; i++)
  {
    summe_vquadrat += (a*daten[0][i] + b - daten[1][i])*(a*daten[0][i] + b - daten[1][i]);
  }

  sy = sqrt (summe_vquadrat/(n-2));

  sa = sy * sqrt(n / D);

  sb = sy * sqrt(summe_xquadrat / D);
  if (D == 0)
     cout << "\n Aus den eingegebenen Daten kann a und b nicht bestimmt werden. :-(\n" << endl;
  else
  {
    cout << "\n a = " << a << " plusminus " << sa << endl;
    cout << " b = " << b << " plusminus " << sb << endl << "\n ";
  }
}

double eingabe()
{
  
  string zahlenstring="";

//  Erst einmal etwas eingeben:

  cin >> zahlenstring;
  cin.sync();
  cin.clear();

// Ist irgendwo sowas wie ein Komma oder Punkt?

  int    i    = 0;
  float  k    = 1;
  double zahl = 0;
  int dezpunkt = zahlenstring.length() + 1;

  for( i = 0 ; i < zahlenstring.length() ; i++)
  {
    if(zahlenstring[i] == 46) dezpunkt = i;
    if(zahlenstring[i] == 44) dezpunkt = i;
  }
  if(dezpunkt != zahlenstring.length() +1)
     zahlenstring.erase(dezpunkt,1);
  else
     dezpunkt -= 1;
  for( i = 0 ; i < (dezpunkt-1) ; i++ ) k *= 10;
  for( i = 0 ; i < zahlenstring.length() ; i++)
  {
    zahl += k*(zahlenstring[i] - 48); 
    k /= 10;
  }

  return (zahl);
}
```


## Further examples

[calculating prime numbers](Primzahlberechnung.cc)
[convert data files from .vir to .qti](vir2qti.cpp)
[updated calculation of prime numbers](prim2.cc)
