using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SJManage.src.Data
{
    /// <summary>
    /// This class stores all information received from the racecar and makes it accessible to other code through DataListeners.
    /// It may also store other values calcualted within this program that are made globally usable.
    /// </summary>
    internal class DataHolder
    {
        private Dictionary<String, double> numberData;
        private Dictionary<String, String> textData;
        private Dictionary<String, List<DataListener>> listeners;

        private static DataHolder instance;

        public static DataHolder getInstance()
        {
            if (instance == null)
                instance = new DataHolder();
            return instance;
        }

        private DataHolder()
        {
            numberData = new Dictionary<string, double>();
            textData = new Dictionary<string, string>();
            listeners = new Dictionary<string, List<DataListener>>();
        }

        public void addListener(DataListener listener, params String[] keys)
        {
            foreach (String key in keys)
                addListener(key, listener);
        }

        public void addListener(DataListener listener, List<String> keys)
        {
            foreach (String key in keys)
                addListener(key, listener);
        }

        public void addListener(String key, DataListener listener)
        {
            if (!listeners.ContainsKey(key))
            {
                List<DataListener> newList = new List<DataListener>();
                newList.Add(listener);
                listeners.Add(key, newList);
            }
            else
            {
                getListenerList(key).Add(listener);
            }
        }

        public List<DataListener> getListenerList(String key)
        {
            List<DataListener> listenerList;
            listeners.TryGetValue(key, out listenerList);
            return listenerList;
        }

        public void setData(String key, String value)
        {
            textData.Add(key, value);
            if (listeners.ContainsKey(key))
            {
                List<DataListener> listenerList = getListenerList(key);
                foreach (DataListener listener in listenerList)
                    listener.notifyNewData(key, value);
            }
        }

        public void setData(String key, double value)
        {
            numberData.Add(key, value);
            if (listeners.ContainsKey(key))
            {
                List<DataListener> listenerList = getListenerList(key);
                foreach (DataListener listener in listenerList)
                    listener.notifyNewData(key, value);
            }
        }

        public double getNumberData(String key)
        {
            double value;
            numberData.TryGetValue(key, out value);
            return value;
        }

        public String getTextData(String key)
        {
            String value;
            textData.TryGetValue(key, out value);
            return value;
        }
    }
}
