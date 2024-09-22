using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ForwardList
{
    internal class ForwardList<T>:IEnumerable
    {
        Element<T> Head;
        public uint Size { get; private set; }
        public IEnumerator GetEnumerator() => new Enumerator<T>(Head);
        public void Add(T Data) => push_back(Data);
        
        //constructor
        public ForwardList()
        {
            Head = null;
            Console.WriteLine($"LConstructor:\t {GetHashCode()}");  
        }

        //destructor
        ~ForwardList()
        {
            Console.WriteLine($"LDestructor:\t {GetHashCode()}");
        }

        public void Clear()
        {
            while ( Head != null ) pop_back();
            Head = null;
        }

        // methods
        // adding elements
        public void push_back(T Data)
        {
            if (Head == null) push_front(Data);
            else
            {
                Element<T> Temp = Head;
                while (Temp.pNext != null)
                    Temp = Temp.pNext;
                Element<T> New = new Element<T>(Data);
                Temp.pNext = New;
                Size++;
            }
        }

        public void push_front(T Data)
        {
            Head = new Element<T>(Data, Head);

            /*
            // 1) создаём новый элемент 
            Element New = new Element(Data);

            // 2) подключаем новый элемент к списку 
            New.pNext = Head;

            // 3) смещаем голову на новый элемент 
            Head = New;
            */
            Size++;
        }

        public void insert(T Data, int Index)
        {
            if (Index > Size) return;
            if (Index == 0) push_front(Data);
            else
            {// 1) доходим до нужного элемента  
                Element<T> Temp = Head;
                for (int i = 0; i < Index - 1; i++)
                    Temp = Temp.pNext;

                // 2) создаём новый элемент
                Element<T> New = new Element<T>(Data);

                // 3) включаем элемент в список 
                New.pNext = Temp.pNext;
                Temp.pNext = New;
                Size++;
            }
        }

        // removing elements
        public void pop_front() 
        {
            Head = Head.pNext; // 2) исключаем элемент из списка
            Size--;
        }

        public void pop_back()
        {
            if (Head == null) return;
            else if (Head.pNext == null) pop_front();
            else
            {


                Element<T> Temp = Head;
                while (Temp.pNext.pNext != null)
                    Temp = Temp.pNext;
                Temp.pNext = null;
                Size--;
            }
        }

        public void erase(int Index)
        {
            if (Index > Size) return;
            if (Index == 0) pop_front();
            else
            {
                Element<T> Temp = Head;
                for(int i = 0;i < Index - 1;i++)    Temp = Temp.pNext;
                Temp.pNext = Temp.pNext.pNext;
                Size--;
            }
        }
        

        public void print()
        { 
            Element<T> Temp = Head; // temp - итератор
            // итератор - это указатель про помощи которого можно получить доступ к структуры данных
            while (Temp != null)
            {
                Console.Write($"{Temp.Data}\t");
                Temp = Temp.pNext; // это переход на следующий элемент
            }
            Console.WriteLine();
        }

    }
}
