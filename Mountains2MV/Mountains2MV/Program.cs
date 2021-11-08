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
            Console.WriteLine("Finished!");
            Console.WriteLine("----------------------------");
            int length = 0;
            Console.WriteLine("Data Source (CSV):");
            string path1 = Console.ReadLine();
            try
            {
                var reader = new StreamReader(File.OpenRead(@path1));

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
                Console.WriteLine("Where 2 Save:");
                string path = Console.ReadLine() + "\\mountains.cpp";
                //string path = @"D:\mountains.cpp";

                StreamWriter writer = new StreamWriter(@path);

                writer.WriteLine("#include \"mountains.h\"");
                writer.WriteLine("#include \"arduino.h\"");
                writer.WriteLine("");
                writer.WriteLine("int mountains_length = " + length + ";");
                writer.WriteLine("");
                writer.WriteLine("mountain mountains[] = {");

                for (int i = 0; i < length; i++)
                {
                    writer.WriteLine("    {\"" + name[i] + "\"," + lat[i] + "," + lon[i] + "," + alt[i] + "},");
                }

                writer.WriteLine("};");
                writer.Close();

                Console.WriteLine("mountains.cpp has been created");
                Console.ReadKey();
            }
    
            catch
            {
                Console.Write("Invalid Path");
                Console.ReadKey();
            }
}

    }
}
