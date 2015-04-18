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
    /// Interaction logic for BatteriesStatus.xaml
    /// </summary>
    public partial class BatteriesStatus : UserControl
    {
        private int width,height;
        public BatteriesStatus(int numCols, int numBatteries)
        {
            UserControl control = new UserControl();
            int bWidth = 50;
            int bHeight = 80;

            int numRows = numBatteries / numCols;

            height = bHeight * numRows + 50;
            width =bWidth*numCols+10;

            this.Height = height;
            this.Width = width;

            InitializeComponent();
            for (int c = 0; c < numCols; c++){
                ColumnDefinition column = new ColumnDefinition() { Width = new GridLength(bWidth) };
                    grid.ColumnDefinitions.Add(column);
            }
            for (int r = 0; r < numRows; r++)
            {
                RowDefinition row = new RowDefinition() { Height = new GridLength(bHeight) };
                    grid.RowDefinitions.Add(row);
            }           
            for (int b = 0; b < numBatteries; b++)
            {
                BatteryStatus status = new BatteryStatus(b);
                status.VoltageText.FontSize = 12;
                status.CurrentText.FontSize = 12;
                grid.Children.Add(status);
                Grid.SetColumn(status, b % numCols);
                Grid.SetRow(status, b / numCols);
            }
        }


       
    }
}

