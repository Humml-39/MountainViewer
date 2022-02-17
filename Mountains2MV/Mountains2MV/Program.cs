using System;
using System.IO.Ports;
using System.Threading;
using System.IO;
using System.Collections.Generic;
namespace Mountains2MV
{
    class Program
    {
        public static void Main()
        {
            //Startgruß
            Console.WriteLine("Welcome to Mountain2MV");
            Console.WriteLine("----------------------");

            int length = 0; //Anzahl aller Berge

            Console.WriteLine("Data Source (CSV):"); //Welche Datei?
            string path1 = Console.ReadLine();


            try //Prüfen ob die Eingabe richitg verläuft
            {
                var reader = new StreamReader(File.OpenRead(@path1)); //Öffnen der CSV
                Console.WriteLine("Path OK");

                //Liste der aller Bergnamen, -höhen und Position (Längen- und Breitengrad)
                List<string> name = new List<string>();
                List<string> lon = new List<string>();
                List<string> lat = new List<string>();
                List<string> alt = new List<string>();

                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine(); //Auslesen der Zeile
                    var values = line.Split(','); //Absppeichern der Werte auf die Variable, trennung durch ","

                    name.Add(values[0]); //Bergname wird hinzugefügt
                    lon.Add(values[1]); //Längengrad wird hinzugefügt
                    lat.Add(values[2]); //Breitengrad wird hinzugefügt
                    alt.Add(values[3]); //Höhe wird hinzugefügt

                    length++; //Die Anzahl der Berge wird inkrementiert
                }

                Console.WriteLine("Where to Save:"); //Speicherort abfrage
                string path = Console.ReadLine() + "\\mountains.cpp"; //Speicherort+Name

                StreamWriter writer = new StreamWriter(@path); //Erstellen einer neuen Datei

                //Ab hier: schreibt C++-Code....
                writer.WriteLine("#include \"mountains.h\"");
                writer.WriteLine("#include \"arduino.h\"");
                writer.WriteLine("");
                writer.WriteLine("int mountains_length = " + length + ";");
                writer.WriteLine("");
                writer.WriteLine("mountain mountains[] = {");

                for (int i = 0; i < length; i++) //Schleife für jeden Berg
                {
                    writer.WriteLine("    {\"" + name[i] + "\"," + lat[i] + "," + lon[i] + "," + alt[i] + "},");
                }

                writer.WriteLine("};");
                writer.Close();
                //Fertig mit der Datei

                Console.WriteLine("mountains.cpp has been created");
                Console.ReadKey();
            }
    
            catch //Falls ein Problem auftritt --> Fehlermeldung
            {
                Console.WriteLine("Error!");
                Console.Write("Is the Path correct?");
                Console.ReadKey();
            }
        }

    }
}
