﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BioInf_Dragicevic
{
    static class Parser
    {
        public static string readFasta(string fileName)
        {
            StringBuilder fileContent = new StringBuilder();
            string line;
            // Read the file and display it line by line.
            System.IO.StreamReader file =
               new System.IO.StreamReader(fileName);
            while ((line = file.ReadLine()) != null)
            {
                if (line.StartsWith(">"))
                {
                    continue;
                }
                fileContent.Append(line);
            }
            file.Close();
            return fileContent.ToString();
        }
    }
}