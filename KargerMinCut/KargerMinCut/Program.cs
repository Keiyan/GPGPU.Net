using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KargerMinCut
{
    class Program
    {
        static int Main(string[] args)
        {
            var amountOfNodes = ReadFile("kargerMinCut.txt").Count;

            Stopwatch watch = new Stopwatch();
            watch.Start();

            var iterationCount = amountOfNodes * amountOfNodes * 3;
            List<int> results = new List<int>();
            Parallel.For(0, iterationCount, i =>
            {
                var data = ReadFile("kargerMinCut.txt");
                results.Add(Contract(data));
            });

            watch.Stop();

            Console.WriteLine("Edge count is " + results.Min());
            Console.WriteLine("Time is " + watch.ElapsedMilliseconds + " milliseconds");

            return results.Min();
        }

        private static int Contract(IList<IList<int>> data)
        {
            int a = 0, b = 0;
            for (int i = 0; i < data.Count - 2; i++)
            {
                FindEdge(data, ref a, ref b);
                Merge(data, a, b);
            }

            return data[a].Count;
        }

        private static void Merge(IList<IList<int>> data, int a, int b)
        {
            for (int i = 0; i < data.Count; i++)
            {
                for (int j = 0; j < data[i].Count; j++)
                {
                    if (data[i][j] == b) data[i][j] = a;
                }
            }
            foreach (var item in data[b])
            {
                if(item != a) data[a].Add(item);
            }
            data[b].Clear();
        }

        private static Random r = new Random();
        private static void FindEdge(IList<IList<int>> data, ref int a, ref int b)
        {
            do
            {
                a = r.Next(data.Count);
            } while (data[a].Count == 0);

            b = data[a][r.Next(data[a].Count)];
        }

        static private IList<IList<int>> ReadFile (string fileName)
        {
            List<IList<int>> result = new List<IList<int>>();
            using (var stream = File.OpenText(fileName))
            {
                var elements = stream.ReadLine().Split('\t');
                result.Add(new List<int>());
                for (int i = 1; i < elements.Length - 1; i++)
                {
                    result.Last().Add(int.Parse(elements[i]));
                }
            }

            return result;
        }
    }
}
