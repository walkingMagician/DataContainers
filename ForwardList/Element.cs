using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ForwardList
{
    internal class Element
    {
        public int Data { get; set; } // значение
        public Element pNext { get; set; } // следующий элемент
    
        // constructor
        public Element(int Data, Element pNext = null)
        {
            this.Data = Data;
            this.pNext = pNext;
            Console.WriteLine($"Econstructor:\t {GetHashCode()}");
        }

        // destructor
        ~Element()
        {
            Console.WriteLine($"EDestructor:\t {GetHashCode()}");
        }
    }
}
