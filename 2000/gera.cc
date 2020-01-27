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
