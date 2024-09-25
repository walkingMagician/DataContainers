#define HOME
using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ForwardList
{
    internal class Program
    {
        static void Main(string[] args)
        {
#if HOME
            Random rand = new Random(0);
            Console.Write("введите размер списка: ");
            int n = Convert.ToInt32(Console.ReadLine());
            ForwardList list = new ForwardList();
            for (int i = 0; i < n; i++)
            { 
                list.push_back(rand.Next(100));
            }
            list.push_back(123);
            list.print();

            //Console.Write("Введите индекс добавляемого элемента: ");
            //int index = Convert.ToInt32(Console.ReadLine());
            //Console.Write("Введите значение добавляемого элемента: ");
            //int value = Convert.ToInt32(Console.ReadLine());
            //list.insert(value, index);
            list.erase(3);
            //list.push_front(456);
#endif

            /*ForwardList new_list = new ForwardList() { 3, 5, 8, 13, 21, 45, 12, 45, 155 };
            //new_list.print();
            foreach (int i in new_list)
            {
                Console.Write(i + "\t");
            }
            Console.WriteLine();*/
        }
    }
}

// 72      81      76      55      20