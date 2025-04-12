#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

pair<unordered_map<int, vector<int>>, vector<vector<int>>> readInput(string file)
{
    ifstream stream(file);
    unordered_map<int, vector<int>> graph;
    vector<vector<int>> pagesList;
    string line;

    if(!stream)
    {
        cerr << "Failed to open input file" << endl;
        return {graph, pagesList};
    }

    // Page ordering rules
    while(true)
    {
        getline(stream, line);

        if(line.empty())
            break;

        stringstream lineStream(line);
        int page, nextPage;

        lineStream >> page;
        lineStream.ignore(1, '|');
        lineStream >> nextPage;
        graph[page].push_back(nextPage);
    }

    // Page numbers of each update
    while(!stream.eof())
    {
        getline(stream, line);

        if(line.empty())
            continue;

        stringstream lineStream(line);
        vector<int> pages;
        int page;

        while(!lineStream.eof())
        {
            lineStream >> page;
            lineStream.ignore(1, ',');
            pages.push_back(page);
        }
        
        pagesList.push_back(pages);
    }

    stream.close();
    return {graph, pagesList};
}

bool isValid(unordered_map<int, vector<int>>& graph, vector<int>& pages)
{
    int n = pages.size();

    for(int i = 1; i < n; i++)
    {
        vector<int>& nextPages = graph[pages[i]];

        for(int j = 0; j < i; j++)
        {
            if(find(nextPages.begin(), nextPages.end(), pages[j]) != nextPages.end())
                return false;
        }
    }

    return true;
}

long run(string file)
{
    pair<unordered_map<int, vector<int>>, vector<vector<int>>> input = readInput(file);
    unordered_map<int, vector<int>> graph = input.first;
    vector<vector<int>> pagesList = input.second;
    long middleSum = 0;

    for(vector<int>& pages : pagesList)
    {
        if(isValid(graph, pages))
            middleSum += pages[pages.size() / 2];
    }

    return middleSum;
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cerr << "Missing input file" << endl;
        return 1;
    }

    cout << "----- AOC 2024 DAY 05 : PART 1 -----" << endl;

    for(int i = 1; i < argc; i++)
        cout << argv[i] << ": " << run(argv[i]) << endl;

    return 0;
}