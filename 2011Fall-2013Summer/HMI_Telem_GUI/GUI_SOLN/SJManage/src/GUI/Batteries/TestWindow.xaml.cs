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
    /// Interaction logic for TestWindow.xaml
    /// </summary>
    public partial class TestWindow : Window
    {
        public TestWindow()
        {

            InitializeComponent();

            UserControl control = new BatteriesStatus(4,16);
            this.grid.Children.Add(control);

            this.Width = control.Width;
            this.Height = control.Height;

        }
    }
}
