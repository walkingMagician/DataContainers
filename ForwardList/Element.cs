using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ForwardList
{
    internal class Element<T>
    {
        public T Data { get; set; } // значение
        public Element<T> pNext { get; set; } // следующий элемент
        // constructor
        public Element(T Data, Element<T> pNext = null)
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
