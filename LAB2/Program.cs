using System;
using System.Collections.Generic;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            int ns;
            int nt;
            int mlen = 0;
            string[,] nfa;
            string[,] dfa;
            List<string> check = new List<string>();
            check.Add("0");
            ns = Convert.ToInt32(Console.ReadLine());
            nt = Convert.ToInt32(Console.ReadLine());
            nfa = new string[nt, ns];
            dfa = new string[100, ns];
            
            //Creating NFA
            for (int i = 0; i < nt; i++)
            {
                for (int j = 0; j < ns; j++)
                {
                    Console.Write("(q" + i + ", " + Convert.ToChar(97 + j) + ") -> q");
                    nfa[i, j] += Console.ReadLine();
                    if (nfa[i, j] == "-")
                        nfa[i, j] = "";
                    if (nfa[i, j].Length > 1 && !check.Contains(nfa[i, j]))
                    {
                        check.Add(nfa[i, j]);
                        if (mlen < nfa[i, j].Length)
                            mlen = nfa[i, j].Length;
                    }
                }
            }
            
            
            // NFA -> DFA
            int len = check.Count;

            for (int i = 0; i < len; i++)
            {
                string tmp = check[i];
                for (int j = 0; j < ns; j++)
                {
                    for (int k = 0; k < tmp.Length; k++)
                    {
                        if(dfa[i, j] == null)
                            dfa[i, j] = nfa[Int32.Parse(tmp.Substring(k, 1)), j];
                        else
                        if (!dfa[i, j].Contains(nfa[Int32.Parse(tmp.Substring(k, 1)), j]))
                            dfa[i, j] += nfa[Int32.Parse(tmp.Substring(k, 1)), j]; 
                        
                        
                    }

                    if (dfa[i, j].Length > 1 && !check.Contains(dfa[i, j]))
                    {
                        check.Add(dfa[i, j]);
                        len++;
                        if (mlen < dfa[i, j].Length)
                            mlen = dfa[i, j].Length;
                    }
                }
            }

            
            //DFA Printing
            mlen = mlen * 2;
            Console.WriteLine("DFA");
            
            for (int i = 0; i < mlen; i++)
                Console.Write(' ');
            Console.Write(" | ");
            
            for (int i = 0; i < ns; i++)
            {
                Console.Write(Convert.ToChar(97 + i));
                for (int j = 0; j < mlen - 1; j++)
                {
                    Console.Write(' ');
                }
                Console.Write(" | ");
            }
            Console.WriteLine();
            
            for (int i = 0; i < check.Count; i++)
            {
                
                for (int k = 0; k < check[i].Length; k++)
                {
                    Console.Write("q"+check[i].Substring(k, 1));
                }

                for (int k = 0; k < mlen - check[i].Length * 2; k++)
                {
                    Console.Write(' ');
                }
                Console.Write(" | ");
                
                for (int j = 0; j < ns; j++)
                {
                    if (dfa[i, j] == null || dfa[i, j] == "")
                    {
                        Console.Write("-");
                        for (int k = 0; k < mlen - 1; k++)
                        {
                            Console.Write(' ');
                        }
                    }
                    else
                    {
                        for (int k = 0; k < dfa[i, j].Length; k++)
                        {
                            Console.Write("q" + dfa[i, j].Substring(k, 1));
                        }

                        for (int k = 0; k < mlen - dfa[i, j].Length * 2; k++)
                        {
                            Console.Write(' ');
                        }
                    }
                    Console.Write(" | ");
                }
                Console.WriteLine();
                
            }
        }
    }
}