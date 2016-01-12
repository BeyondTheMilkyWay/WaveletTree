using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BioInf_Dragicevic
{
    class Run
    {
        static void Main(string[] args)
        {
            if (args.Length < 3)
            {
                Console.WriteLine("Number of arguments must be more than 3!");
                System.Environment.Exit(1);
            }
            string fileContent = Parser.readFasta(args[0]);
            //initialize and build tree
            Tree tree = new Tree(fileContent);
            Console.WriteLine("BUILT");
            string result = "";
            //run command
            if (args[1] == "select")
            {
                result = "select(" + args[2] + ", " + args[3] + ") = " + tree.select(Int32.Parse(args[2]), args[3][0]);
            }
            else if (args[1] == "rank")
            {
                result = "rank(" + args[2] + ", " + args[3] + ") = " + tree.rank(Int32.Parse(args[2]), args[3][0]);
            }
            else if (args[1] == "access")
            {
                result = "access(" + args[2] +") = " + (char)tree.access(Int32.Parse(args[2]));
            }
            System.IO.File.WriteAllText(@"result.txt", result);
        }
    }
}
