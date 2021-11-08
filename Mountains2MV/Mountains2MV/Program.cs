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

            Console.WriteLine("Reading CSV...");
            int length = 0;
            var reader = new StreamReader(File.OpenRead(@"C:\Users\johih\Downloads\vorarlberg_clean.csv"));
            List<string> name = new List<string>();
            List<string> lon = new List<string>();
            List<string> lat = new List<string>();
            List<string> alt = new List<string>();
            while (!reader.EndOfStream)
            {
                var line = reader.ReadLine();
                var values = line.Split(',');

                name.Add(values[0]);
                lon.Add(values[1]);
                lat.Add(values[2]);
                alt.Add(values[3]);

                length++;
            }
            string path = @"D:\mountains.cpp";

            StreamWriter writer = new StreamWriter(path);

            writer.WriteLine("#include \"mountains.h\"");
            writer.WriteLine("#include \"arduino.h\"");
            writer.WriteLine("");
            writer.WriteLine("int mountains_length = 12;");
            writer.WriteLine("");
            writer.WriteLine("mountain mountains[] = {");

            for(i)
            writer.WriteLine("    {"+name+","+lon+","+lat+","+alt+"},");

            writer.Close();

            Console.WriteLine("mountains.cpp has been created");


        }

    }
}
