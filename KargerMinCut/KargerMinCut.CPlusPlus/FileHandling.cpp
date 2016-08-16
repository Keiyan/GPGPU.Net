#include "stdafx.h"
#include "MinCutProblem.h"

std::vector<int>* ReadFile(const char * fileName, size_t amountOfNodes, size_t & width)
{
    FILE * file = NULL;
    fopen_s(&file, fileName, "r");
    if (!file) return NULL;

    std::vector<int>* result = new std::vector<int>[amountOfNodes];

    char c = fgetc(file);
    int readInt = 0;
    bool startOfLine = true;
    int VerticeId = 0;
    size_t lineWidth = 0;
    while (c != EOF)
    {
        if (c == '\n')
        {
            if (lineWidth > width) width = lineWidth;
            readInt = 0;
            VerticeId = 0;
            lineWidth = 0;
            startOfLine = true;
        }
        else if (c == '\t')
        {
            if (startOfLine)
            {
                VerticeId = readInt - 1;
            }
            else
            {
                result[VerticeId].push_back(readInt - 1);
                lineWidth++;
            }
            readInt = 0;
            startOfLine = false;
        }
        else
        {
            readInt *= 10;
            readInt += c - '0';
        }
        c = fgetc(file);
    }

    fclose(file);
    file = NULL;

    for (size_t i = 0; i < amountOfNodes; i++)
    {
        while (result[i].size() < width) result[i].push_back(-1);
    }

    return result;
}