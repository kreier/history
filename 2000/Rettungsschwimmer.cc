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
