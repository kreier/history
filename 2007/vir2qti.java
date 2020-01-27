﻿// -------------------------------------------------
// vir2qti.java
// Konvertierung der WESPHOA Messdaten im
// VIR-Format zu qti für qtiplot
// Aufruf: java vir2qti [quelldatei]
// -------------------------------------------------

import java.io.*;

class vir2qti 
{
  static double lese(RandomAccessFile src)
  {
    String inhalt = "";
  	try
	{
		inhalt = src.readLine();
    }
	catch ( IOException e ) { e.printStackTrace(); }
	return Double.parseDouble( inhalt );
  }

  static String leseZ(RandomAccessFile src)
  {
    String inhalt = "";
  	try
	{
		inhalt = src.readLine();
    }
	catch ( IOException e ) { e.printStackTrace(); }
	return inhalt;
  }
  
  public static void main(String args[])
  {
    String usage = "Aufruf: java vir2qti [quelldatei]";
    String quelle = "", ziel = "";
    String linie  = "----------------------------------------------------";

    switch( args.length )
    {
      case 0:				// keine Quelldatei angegeben
        System.out.print( "Bitte geben Sie den Namen der Quelldatei an: ");
        BufferedReader tastatur = new BufferedReader(new InputStreamReader(System.in));
	try
	{
	  quelle = tastatur.readLine();
	} catch ( IOException e ) { e.printStackTrace(); }
        if( quelle == "" )
        {
           System.err.println("Keine Quelldatei angegeben!");
        }
        break;

      case 1: 				// Dateinamen angegeben
        quelle = args[0];
        break;

      default:				// falscher Aufruf des Programms
        System.err.println ( usage );
    }
    if( !quelle.endsWith(".VIR") )
    { 					// Dateiname ohne Endung?
      quelle += ".VIR";			// dann wird Endung angefügt
    }
	RandomAccessFile vir;		// Quelldatei
	try
	{
		vir = new RandomAccessFile ( quelle , "r" );	//Öffnen
	}
	catch ( IOException e ) 
	{ 
		System.err.println("Die Datei " + quelle + " kann nicht gefunden werden.\n");
		return;
	}
	
	int zeilen = (int) lese( vir );		//Anzahl der Datenzeilen
	float [ ] [ ] data = new float[ 6 ] [ zeilen ];
	for(int i=0; i<zeilen; i++)			// Einlesen der Messwerte
	{
		data[1][i] = (int) lese( vir );
	}

	int sweeps = (int) lese( vir );	// Einlesen der Parameter zu den Messdaten
	int minCounts = (int) lese( vir );
	int maxCounts = (int) lese( vir );
	double theta = lese( vir );
	double minE = lese( vir );		//linke Intervallgrenze Energie
	double maxE = lese( vir );		//rechte Intervallgrenze
	double Elampe1 = lese( vir );
	double Elampe2 = lese( vir );
	double deltaE = lese( vir );	//Energieauflösung deltaE / dE meV
	double a10 = lese( vir );
	String DatumZeit = leseZ( vir );
	String EDC = leseZ( vir );
	String Material = leseZ( vir );
	double phi = lese( vir );
	double Epass = lese( vir );
	String beschreibung1 = leseZ( vir );
	String beschreibung2 = leseZ( vir );

	System.out.println("-----------------------------------------------------------");
	System.out.println("In der Datei "+quelle+" sind folgende Messdaten enthalten:");
	System.out.println("            " + beschreibung1 );
	System.out.println("            " + beschreibung2 );
	System.out.println("Es wurden " + zeilen + " Kanäle gemessen zwischen " + minE + " eV und " + maxE + " eV.");
	System.out.println("Messung erfolgte am " + DatumZeit);
	System.out.print("-----------------------------------------------------------");
	
	// Aufbau der data[x][y] :
	// 1. Spalte: [X]-Werte in eV
	// 2. Spalte: gemessene Counts zu diesem Energiewert
	// 3. Spalte: normierte Messwerte auf Integralwert 1
	// 4. Spalte: Shirley-Untergrund
	// 5. Spalte: Shirley-Untergrund reskaliert
	// 6. Spalte: geglättetes Spektrum

	double step = (maxE-minE)/(zeilen-1);
	for(int i=0;i<zeilen;i++) // richtige Energiewerte in Spalte X eintragen
	{
		data[0][i] = (float)(step * i) + (float)minE;
	}
	float summe = 0;
	for (int i=0;i<zeilen;i++) //         Intensitätsintegral
	{
		summe += data[1][i];
	}
	for(int i=0;i<zeilen;i++) //          Normierung der Messwerte - spalte 3
	{
		data[2][i] = data[1][i] / summe;
	}
	data[3][zeilen-1] = 0;
	for(int i=2;i<=zeilen;i++) //          Shirley-Untergrund herstellen
	{
		data[3][zeilen-i] = data[3][zeilen-i+1] + data[1][zeilen-i];
	}
	//       geglättetes Spektrum nach Spalte 6
	for(int i=0;i<zeilen;i++) { data[5][i] = data[1][i];  }
	int mean1 = 0 , mean2 = 0;
	for(int i=0;i<5;i++)  //              Ränder 5 Pixel Noise auf 10 % senken
	{
		mean1 += (int) data[5][i];
		mean2 += (int) data[5][zeilen-i-1];
	}
	mean1 = (int) mean1 * 9 / 50;
	mean2 = (int) mean2 * 9 / 50;
	for(int i=1;i<5;i++)
	{
		data[5][i] = mean1 + data[5][i]/10;
		data[5][zeilen-i] = mean2 + data[5][zeilen-i]/10;
	}
	int maximum = 0;
	int maxatE = 0;
	for(int i=5;i<zeilen-6;i++) //        alle Daten glätten
	{
		data[5][i] = (6*data[5][i] + 4*(data[5][i-1]+data[5][i+1]) +
              2*(data[5][i-2]+data[5][i-3]+data[5][i+2]+data[5][i+3]) +
                  (data[5][i-4]+data[5][i-5]+data[5][i+4]+data[5][i+5]))/ 26;
		if(data[5][i] > maximum)
		{
			maximum = (int) data[5][i];
			maxatE = i;
		}
	}
	int minimum = maximum;
	int minatE = 0;
	for(int i=maxatE;i<zeilen/3;i++)  //  Minimum suchen im linken Drittel des Spektrums für
	{								//  Normierung des Shirley-Untergrundes und dessen Abzug
		if(data[5][i]<minimum)
		{
			minimum = (int) data[5][i];
			minatE = i;
		}
	}
	float rescale = data[5][minatE]/data[3][minatE];
	if(data[5][maxatE]<(data[3][maxatE]*rescale)) // nicht Maximum durch Shirley löschen
	{
		rescale = data[5][maxatE]/data[3][maxatE];
	}
	for(int i=0;i<zeilen;i++) //          Shirley-Untergrund reskalieren
	{
		data[3][i] = data[3][i] * rescale;
	}
	for(int i=0;i<zeilen;i++) //          geglättete Daten ohne Shirley-Untergrund
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

	// Ausgabe in qti-Datei
	ziel = quelle.substring( 0, quelle.length()-3) + "qti";
	RandomAccessFile qti = null;
    try
    {
		qti = new RandomAccessFile( ziel , "rw" );
		qti.writeBytes("QtiPlot 0.8.6 project file \n");
		qti.writeBytes("<windows>	1\n");
		qti.writeBytes("<table>\n");
		qti.writeBytes("Tabelle1	" + zeilen + "	6	14.08.2006 13:42:22\n");
		qti.writeBytes("geometry	5	38	700	500	active\n");
		qti.writeBytes("header	eV[X]	counts[Y]	Normiert[Y]	Shirley[Y]	oU[Y]	smooth[Y]	\n");
		qti.writeBytes("ColWidth	100	100	100	100	100	100	\n");
		qti.writeBytes("<com>\n");
		qti.writeBytes("</com>\n");
		qti.writeBytes("ColType	0;0/6	0;0/6	0;0/6	0;0/6	0;0/6	0;0/6	\n");
		qti.writeBytes("Comments							\n");
		qti.writeBytes("Windowlabel		" + quelle + "\n");
		qti.writeBytes("<data>\n");
		for(int i=0;i<zeilen;i++)
		{
		qti.writeBytes( i + "	" + data[0][i] + "	" + data[1][i] + "	" + data[2][i]
        + "	" + data[3][i] + "	" + data[4][i] +  "	" + data [5][i] + "\n");
		}
		qti.writeBytes("</data>\n");
		qti.writeBytes("</table>\n");
		qti.writeBytes("<log>\n");
		qti.writeBytes("</log>\n");
	}
    catch( IOException e ) { System.err.println( e ); }
    finally {
      if ( qti != null )
        try { qti.close(); } catch ( IOException e ) { e.printStackTrace(); }
    }
  }
}

