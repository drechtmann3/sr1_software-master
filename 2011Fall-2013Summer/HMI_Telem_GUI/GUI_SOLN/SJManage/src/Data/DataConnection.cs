using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SJManage.src.Data
{
    /// <summary>
    /// This class and its subclasses will implement the functionality of actually getting data from the racecar or elsewhere.
    /// This data will be stored in DataHolder.
    /// TODO: write class
    /// </summary>
    internal class DataConnection
    {
        protected static DataHolder holder = DataHolder.getInstance();
        private const String SEPERATOR = "|";
        private const String PORTNAME = "COM1";
        private const int BAUD = 19000;
        private const Parity PARITY = Parity.Even;
        private static SerialPort PORT = new SerialPort(PORTNAME, BAUD, PARITY);

        public static void openPort()
        {
            if (!PORT.IsOpen)
            {
                PORT.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);

                PORT.Open();
            }
        }
    
    private static void DataReceivedHandler(
                        Object sender,
                        SerialDataReceivedEventArgs e)
    {
        SerialPort sp = (SerialPort)sender;
        String indata = sp.ReadExisting();
        String[] parts = indata.Split(SEPERATOR.ToCharArray());
        double number;
        bool isNum = double.TryParse(parts[1], out number);
        if(isNum)
            DataHolder.getInstance().setData(parts[0], number);
        else
            DataHolder.getInstance().setData(parts[0], parts[1]);
    }

    public static void close()
    {
        if (PORT.IsOpen)
            PORT.Close();
    }


    }
}
