using System;
using System.Collections.Generic;
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
    internal class DataGatherer
    {
        protected DataHolder holder = DataHolder.getInstance();

        public void getNewData() { }//TODO

    }
}
