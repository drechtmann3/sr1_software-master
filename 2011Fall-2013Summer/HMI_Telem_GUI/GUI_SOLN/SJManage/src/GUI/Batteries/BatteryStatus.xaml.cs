using SJManage.src.Data;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace SJManage.src.GUI.Batteries
{
    /// <summary>
    /// Interaction logic for BatteryStatus.xaml
    /// </summary>
    public partial class BatteryStatus : UserControl
    {
        private int numBattery;
        private double voltage;
        private double charge;
        private readonly String chargeKey;
        private readonly String voltageKey;

        private const double minGreenVoltage = 90;
        private const double minYellowVoltage = 80;

        private Color Red = Color.FromRgb(0, 255, 0);
        private Color Green = Color.FromRgb(255, 0, 0);
        private Color Yellow = Color.FromRgb(255, 255, 0);
        public BatteryStatus(int numBattery)
        {
            InitializeComponent();
            this.numBattery = numBattery;
            chargeKey = "Current " + numBattery;
            voltageKey = "Voltage " + numBattery;
            
            Action<String, double> listener =delegate(String  key, double data){ 
                if (key.Equals(chargeKey))
                {
                    charge = data;
                    CurrentText.Text = data.ToString();
                }

                if (key.Equals(voltageKey))
                {
                    voltage = data;
                    VoltageText.Text = data.ToString();
                    BatteryBody.Fill = new SolidColorBrush(Red);
                }
            };
            DataHolder.getInstance().addListener(new LambdaDataListener(listener), chargeKey,voltageKey);
            }

       

    }
}
