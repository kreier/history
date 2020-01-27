// -------------------------------------------------
// vir2qti.cpp
// Konvertierung der WESPHOA Messdaten im
// VIR-Format zu qti f�r qtiplot
// Aufruf: vir2qti [quelldatei]
// -------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

float dataz();
string datas();

char usage[] = "Aufruf: vir2qti [quelldatei]";
bool ok = true;

fstream f;

int main(int argc, char *argv[])
{
  char   ziel[256]   = "",
         quelle[256] = "";
  string linie(60,'-');

  switch( argc )
  {
  case 1:     // keine Quelldatei angegeben
    cout << "Bitte geben Sie den Namen der "
            "Quelldatei an: ";
    cin.getline( quelle, 256 );
    if( strlen(quelle) == 0 )
    {  cerr << "Keine Quelldatei angegeben!" << endl;
       return 1;
    }
    break;

  case 2:     // Dateinamen angegeben
    strcpy(quelle,argv[1]);
    break;

  default:   // falscher Aufruf des Programms
    cerr << usage << endl;
    return 2;
  }
  if( quelle[strlen(quelle)-4]!='.' && quelle[strlen(quelle)-1]!='R')
  {                          // Dateiname ohne Endung?
    strcat(quelle, ".VIR");  // dann wird Endung angef�gt
  }

  f.open( quelle , ios::in);  // �ffnen der Quelldatei
  if(!f)
  {
    cerr << "Die Datei " << quelle << " kann nicht ge�ffnet werden." << endl;
    return 2;
  }
  int zeilen = int(dataz());  // erste Zeile ist Anzahl der Datenzeilen
  float data[6][zeilen];
  for(int i=0; i<zeilen; i++)  // Einlesen der Messwerte
  {
    data[1][i] = dataz();
  }
  float a1 = dataz();  // Einlesen der Parameter zu den Messdaten
  float minCounts = dataz();
  float maxCounts = dataz();
  float a4 = dataz();
  float minE = dataz();
  float maxE = dataz();
  float Elampe1 = dataz();
  float Elampe2 = dataz();
  float a9 = dataz();
  float a10 = dataz();
  string DatumZeit = datas();
  string a12 = datas();
  string a13 = datas();
  string a14 = datas();
  string a15 = datas();
  string beschreibung1 = datas();
  string beschreibung2 = datas();
  cout << linie << endl;
  cout << "In der Datei " << quelle << " sind folgende Messdaten enthalten:" << endl;
  cout << "               " << beschreibung1 << endl;
  cout << "               " << beschreibung2 << endl;
  cout << "Es wurden " << zeilen << " Kan�le gemessen zwischen " << minE << " eV und ";
  cout << maxE << " eV." << endl;
  cout << "Messung erfolgte am " << DatumZeit << endl;
  cout << linie << endl;
  f.close();

  // Aufbau der data[x][y] :
  // 1. Spalte: [X]-Werte in eV
  // 2. Spalte: gemessene Counts zu diesem Energiewert
  // 3. Spalte: normierte Messwerte auf Integralwert 1
  // 4. Spalte: Shirley-Untergrund
  // 5. Spalte: Shirley-Untergrund reskaliert
  // 6. Spalte: gegl�ttetes Spektrum

  float step = (maxE-minE)/(zeilen-1);
  for(int i=0;i<zeilen;i++) // richtige Energiewerte in Spalte X eintragen
  {
    data[0][i] = minE + step * i;
  }
  float summe = 0;
  for (int i=0;i<zeilen;i++) //         Intensit�tsintegral
  {
    summe += data[1][i];
  }
  for(int i=0;i<zeilen;i++) //          Normierung der Messwerte - spalte 3
  {
    data[2][i] = data[1][i] / summe;
  }
  data[3][zeilen] = 0;
  for(int i=1;i<=zeilen;i++) //          Shirley-Untergrund herstellen
  {
    data[3][zeilen-i] = data[3][zeilen-i+1] + data[1][zeilen-i];
  }
  //       gegl�ttetes Spektrum nach Spalte 6
  for(int i=0;i<zeilen;i++) { data[5][i] = data[1][i];  }
  int mean1 = 0 , mean2 = 0;
  for(int i=0;i<5;i++)  //              R�nder 5 Pixel Noise auf 10 % senken
  {
    mean1 += int(data[5][i]);
    mean2 += int(data[5][zeilen-i]);
  }
  mean1 = int (mean1 * 9 / 50);
  mean2 = int (mean2 * 9 / 50);
  for(int i=1;i<5;i++)
  {
    data[5][i] = mean1 + data[5][i]/10;
    data[5][zeilen-i] = mean2 + data[5][zeilen-i]/10;
  }
  int maximum = 0;
  int maxatE = 0;
  for(int i=5;i<zeilen-5;i++) //        alle Daten gl�tten
  {
    data[5][i] = (6*data[5][i] + 4*(data[5][i-1]+data[5][i+1]) +
                  2*(data[5][i-2]+data[5][i-3]+data[5][i+2]+data[5][i+3]) +
                  (data[5][i-4]+data[5][i-5]+data[5][i+4]+data[5][i+5]))/ 26;
    if(data[5][i] > maximum)
    {
      maximum = int(data[5][i]);
      maxatE = i;
    }
  }
  int minimum = maximum;
  int minatE = 0;
  for(int i=maxatE;i<zeilen/3;i++)  //  Minimum suchen im linken Drittel des Spektrums f�r
  {                                  //  Normierung des Shirley-Untergrundes und dessen Abzug
    if(data[5][i]<minimum)
    {
      minimum = int(data[5][i]);
      minatE = i;
    }
  }
  float rescale = data[5][minatE]/data[3][minatE];
  if(data[5][maxatE]<(data[3][maxatE]*rescale)) // nicht Maximum durch Shirley l�schen
  {
    rescale = data[5][maxatE]/data[3][maxatE];
  }
  for(int i=0;i<zeilen;i++) //          Shirley-Untergrund reskalieren
  {
    data[3][i] = data[3][i] * rescale;
  }
  for(int i=0;i<zeilen;i++) //          gegl�ttete Daten ohne Shirley-Untergrund
  {
    if(data[3][i] > data[5][i])
    {
      data[4][i] = 1;
    }
    else
    {
      data[4][i] = data[5][i] - data[3][i];
    }
  }

  strcpy (ziel, quelle);
  ziel[strlen(ziel)-3]='q';
  ziel[strlen(ziel)-2]='t';
  ziel[strlen(ziel)-1]='i';

  // Ausgabe in qti-Datei
  ofstream qti( ziel );
  qti << "QtiPlot 0.8.6 project file \n";
  qti << "<windows>	1\n";
  qti << "<table>\n";
  qti << "Tabelle1	" << zeilen << "	6	14.08.2006 13:42:22\n";
  qti << "geometry	5	38	700	500	active\n";
  qti << "header	eV[X]	counts[Y]	Normiert[Y]	Shirley[Y]	oU[Y]	smooth[Y]	\n";
  qti << "ColWidth	100	100	100	100	100	100	\n";
  qti << "<com>\n";
  qti << "</com>\n";
  qti << "ColType	0;0/6	0;0/6	0;0/6	0;0/6	0;0/6	0;0/6	\n";
  qti << "Comments							\n";
  qti << "Windowlabel		" << argv[0] << endl;
  qti << "<data>\n";
  for(int i=0;i<zeilen;i++)
  {
    qti << i << "	" << data[0][i] << "	" << data[1][i] << "	" << data[2][i]
        << "	" << data[3][i] << "	" << data[4][i] <<  "	" << data [5][i] << "\n";
  }
  qti << "</data>\n";
  qti << "</table>\n";
  qti << "<log>\n";
  qti << "</log>\n";
  qti.close();
  return 0;
}
float dataz()
{
  char datastrg[256]="";
  float valuez=0;
  if(!f.eof()) { f.getline (datastrg,sizeof(datastrg)); }
  istringstream istr (datastrg);
  istr >> valuez;
  return valuez;
}
string datas()
{
  char text[256]="";
  if(!f.eof()) { f.getline (text,sizeof(text)); }
  if(text == "") { strcpy(text," "); }
  return text;
}
