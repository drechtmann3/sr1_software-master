using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SJManage.src.Data
{
    interface DataListener
    {
        void notifyNewData(String key, String value);
        void notifyNewData(String key, double data);
    }

    class LambdaDataListener : DataListener
    {
        private Action<String, String> textFunc;
        private Action<String, double> numberFunc;

        public LambdaDataListener(Action<String, String> textFunc, Action<String, double> numberFunc)
        {
            this.textFunc = textFunc;
            this.numberFunc = numberFunc;
        }


        public LambdaDataListener(Action<String, double> numberFunc) : this(null, numberFunc) { }
        public LambdaDataListener(Action<String, String> textFunc) : this(textFunc, null) { }

        public void notifyNewData(String key, String data)
        {
            if (textFunc != null)
                textFunc(key, data);
        }

        public void notifyNewData(String key, double data)
        {
            if (numberFunc != null)
                numberFunc(key, data);
        }
    }
}
