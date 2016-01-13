using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BioInf_Dragicevic
{
    class Node
    {
        public List<Char> alphabet;
        public List<byte> valuesList;
        public Node childZero;
        public Node childOne;
        public Node parent;

        public int getRank(int count, char symbol)
        {
            byte value = alphabet.IndexOf(symbol) < (alphabet.Count / 2) ? (byte)0 : (byte)1;
            int numberOfValues = 0;
            for (int i = 0; i < count; i++)
            {
                if (valuesList[i] == value) {
                    numberOfValues++;
                }
            }
            if (childZero == null)
            {
                return numberOfValues;
            }
            if (value == 0)
            {
                return childZero.getRank(numberOfValues, symbol);
            } else {
                return childOne.getRank(numberOfValues, symbol);
            }
        }

        public char access(int count)
        {
            byte value = valuesList[count];
            if (childOne == null)
            {
                return value == 0 ? alphabet[0] : alphabet[1];
            }
            int numOfValues = 0;
            for (int i = 0; i < count; i++)
            {
                if (valuesList[i] == value)
                {
                    numOfValues++;
                }
            }
            if (value == 0)
            {
                return childZero.access(numOfValues);
            }
            else
            {
                return childOne.access(numOfValues);
            }

        }
    }
}
