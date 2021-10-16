using System;
using System.IO.Ports;
using System.Threading;
using System.IO;
using System.Collections.Generic;
namespace Mountains2MV
{
    class Program
    {
        
        static SerialPort _serialPort;
        public static void Main()
        {
        

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
            /*//*****Ausgabe*********
           for(int i=0; i<length; i++)
           {
               Console.WriteLine(name[i] + "|" + lon[i] + "|" + lat[i] + "|" + alt[i]);
           }
           Console.WriteLine("Zum Beenden drücken");
           Console.Read();
           */
            _serialPort = new SerialPort();
            _serialPort.PortName = "COM10";//Set your board COM 
            _serialPort.BaudRate = 9600;
            _serialPort.Open();
            string d, a;
            //_serialPort.Write("Start,");
            //Console.WriteLine(_serialPort.ReadLine());
            while (true)
            {
                d = _serialPort.ReadLine();
                Console.WriteLine(d);
                if (d == "Start\r")
                {      
                    for (int i = 0; i < length; i++)
                    {
                        _serialPort.Write("st,");

                        _serialPort.Write(name[i]);
                        _serialPort.Write(",");
                        a = _serialPort.ReadLine();
                        Console.WriteLine(a);
                        _serialPort.Write(lon[i]);
                        _serialPort.Write(",");
                        a = _serialPort.ReadLine();
                        Console.WriteLine(a);
                        _serialPort.Write(lat[i]);
                        _serialPort.Write(",");
                        a = _serialPort.ReadLine();
                        Console.WriteLine(a);
                        _serialPort.Write(alt[i]);
                        _serialPort.Write(",");
                        a = _serialPort.ReadLine();
                        Console.WriteLine(a);
                        _serialPort.Write(name[i]);
                        _serialPort.Write(",");
                        a = _serialPort.ReadLine();
                        Console.WriteLine(a);
                        _serialPort.Write(lon[i]);
                        _serialPort.Write(",");
                        a = _serialPort.ReadLine();
                        Console.WriteLine(a);
                        _serialPort.Write(lat[i]);
                        _serialPort.Write(",");
                        a = _serialPort.ReadLine();
                        Console.WriteLine(a);
                        _serialPort.Write(alt[i]);
                        _serialPort.Write(",");
                        a = _serialPort.ReadLine();
                        Console.WriteLine(a);
                        a = _serialPort.ReadLine();
                        Console.WriteLine(a);

                        if (a != "OK\r")
                        {
                            i--;
                            Thread.Sleep(1000);
                        }
                        
                    }
                    break;
                }
            }
            Console.WriteLine();
            Console.WriteLine("Click any button to close");
            Console.Read();
            
        }

    }
}
