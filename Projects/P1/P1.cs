// Alen Ovalles
// P1.cs
// 4/4/2023
// CPSC 3200

// Driver file that will run all the functions to demostrate how 
// the lumen class runs and works. Creating an object from lumen 
// class, and will run all of the functions regarding it.
// Will ask the client for the the size of each lumen object with a 
// given range of (1 - 10), if the client doesn't enter within the 
// range, a lumen object with a default size 5 will be created instead

using System;
namespace P1
{
    public class P1
    {
        static void Main(string[] args)
        {

            int size1, size2, size3;

            Console.WriteLine("");
            Console.WriteLine("Choice a size between 1 - 10:");
            size1 = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("");
            Console.WriteLine("Choice a size between 1 - 10:");
            size2 = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("");
            Console.WriteLine("Choice a size between 1 - 10:");
            size3 = Convert.ToInt32(Console.ReadLine());
            
            Lumen[] obj = new Lumen[]
            {
                new Lumen(size1),
                new Lumen(size2),
                new Lumen(size3),
            };

            Console.WriteLine("");
            Console.WriteLine("Checking the status of each lumen");
            Console.WriteLine(obj[0].isActive());
            Console.WriteLine(obj[1].isActive());
            Console.WriteLine(obj[2].isActive());

            Console.WriteLine("");
            Console.WriteLine("Calling glow function for the first lumen");
            Console.WriteLine(obj[0].glow());
            Console.WriteLine(obj[0].glow());
            Console.WriteLine(obj[0].glow());
            Console.WriteLine("");
            Console.WriteLine("Calling glow function for the second lumen");
            Console.WriteLine(obj[1].glow());
            Console.WriteLine(obj[1].glow());
            Console.WriteLine(obj[1].glow());
            Console.WriteLine("");
            Console.WriteLine("Calling glow function for the third lumen");
            Console.WriteLine(obj[2].glow());
            Console.WriteLine(obj[2].glow());
            Console.WriteLine(obj[2].glow());
            Console.WriteLine("");
            Console.WriteLine("Reset first lumen object");
            Console.WriteLine(obj[0].reset());
            Console.WriteLine("");
            Console.WriteLine("Reset second lumen object");
            Console.WriteLine(obj[1].reset());
            Console.WriteLine("");
            Console.WriteLine("Reset third lumen object");
            Console.WriteLine(obj[2].reset());
            Console.WriteLine("");
        }
    }
}
