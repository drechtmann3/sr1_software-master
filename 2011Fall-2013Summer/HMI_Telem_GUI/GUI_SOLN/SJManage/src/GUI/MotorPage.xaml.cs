using SJManage.src.Data;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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

namespace SJManage.src.GUI
{
    /// <summary>
    /// Interaction logic for MotorPage.xaml
    /// </summary>
    public partial class MotorPage : UserControl
    {

        public class FaultCode
        {
            public String id { get; set; }
            public String name { get; set; }
            public String description { get; set; }
            public String time { get; set; }
        }

        private ObservableCollection<FaultCode> faultCodes;

        public MotorPage()
        {
            InitializeComponent();
            TextBlock[] textBlocks = {this.LeftPedal,this.RightPedal,this.SpeedCurrent,this.SpeedLimit,this.Status,this.AirgapPos };
            foreach(TextBlock block in textBlocks){
                String blockKey = block.Name;
                Action<String, double> listener = delegate(String key, double data)
            {
                {
                    block.Text = data.ToString();
                }
            };
                DataHolder.getInstance().addListener(new LambdaDataListener(listener), blockKey);
            }

            //Assumed that fault codes will be sent with key Motor Fault Code and data formatted as id=<id> name=<name> description=<desc> time=<time>
            Action<String, String> motorListener = delegate(String key, String data)
            {
                {
                    faultCodes.Add(new FaultCode{
                        id = data.Substring(3, data.IndexOf("name")),
                        name = data.Substring(data.IndexOf("name")+5, data.IndexOf("description") + 5 - data.IndexOf("name")),
                        description = data.Substring(data.IndexOf("description")+11, data.IndexOf("description") + 11 - data.IndexOf("time")),
                        time=data.Substring(data.IndexOf("time")+5)
                    });
                }
            };
            DataHolder.getInstance().addListener(new LambdaDataListener(motorListener), "Motor Fault Code");
        }

    }
}
