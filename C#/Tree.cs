﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BioInf_Dragicevic
{
    class Tree
    {
        Node root;

        public Tree(string content)
        {
            root = buildTree(content, null);
            List<byte> bits = new List<byte>();
        }
        private Node buildTree(string content, Node parent)
        {
            Node currentNode = new Node();
            List<Char> alphabet = new List<Char>();
            List<byte> bits = new List<byte>();
            //find alphabet
            for (int i = 0; i < content.Length; i++)
            {
                if (!alphabet.Contains(content[i]))
                {
                    alphabet.Add(content[i]);
                }
            }
            alphabet.Sort();
            int alphabetHalf = alphabet.Count / 2;
            //add 0 and 1 values
            for (int i = 0; i < content.Length; i++)
            {
               if(alphabet.IndexOf(content[i]) < alphabetHalf) {
                   bits.Add(0);
               }
               else
               {
                   bits.Add(1);
               }
            }
            //set variables to current node
            currentNode.valuesList = bits;
            currentNode.alphabet = alphabet;
            currentNode.parent = parent;
            //build children
            if (!(alphabet.Count <= 2))
            {
                StringBuilder childZeroContent = new StringBuilder();
                StringBuilder childOneContent = new StringBuilder();
                for (int i = 0; i < content.Length; i++)
                {
                    char tempChar = content[i];
                    byte tempValue = bits[i];
                    if (tempValue == 0)
                    {
                        childZeroContent.Append(tempChar);
                    }
                    else
                    {
                        childOneContent.Append(tempChar);
                    }
                }
                currentNode.childZero = buildTree(childZeroContent.ToString(), currentNode);
                currentNode.childOne = buildTree(childOneContent.ToString(), currentNode);
            }
            return currentNode;
        }
        
        public int rank(int count, char symbol) {
            return root.getRank(count+1, symbol);
        }

        public int access(int position)
        {
            return root.access(position);
        }

        public int select(int count, char symbol)
        {
            int letterIndex = root.alphabet.IndexOf(symbol);
            Node currentNode = this.root;

            while (true)
            {
                if (currentNode.childOne == null)
                {
                    break;
                }
                int alphSize = currentNode.alphabet.Count;
                int alphHalf = currentNode.alphabet.Count / 2;
                letterIndex = currentNode.alphabet.IndexOf(symbol);

                if (letterIndex < alphHalf)
                {
                    currentNode = currentNode.childZero;
                }
                else
                {
                    currentNode = currentNode.childOne;
                }
            }

            return select(currentNode, symbol, count - 1);
        }

        private int select(Node node, char symbol, int occurrenceNum)
        {
            if (occurrenceNum < 0)
            {
                return -1;
            }
            int alphSize = node.alphabet.Count;
            int alphHalf = alphSize / 2;

            byte value = node.alphabet.IndexOf(symbol) < alphHalf ? (byte)0 : (byte)1;

            int index = -1;
            int count = 0;
            for (int i = 0; i < node.valuesList.Count; i++)
            {
                if (node.valuesList[i] == value)
                {
                    count++;
                }
                if (count == occurrenceNum + 1)
                {
                    index = i;
                    break;
                }
            }


            if (node.parent == null)
            {
                return index;
            }
            else
            {
                return select(node.parent, symbol, index);
            }
        }
    }
}