#include "heap_priority_queue.hpp"
#include "dynamic_array_list.hpp"

#include <limits>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

////////////////////////
/// Data Types
///
struct AdjVtx
{
    AdjVtx(){}
    AdjVtx(int v, int w)
    {
        vtx = v;
        wgt = w;
    }

    AdjVtx(const AdjVtx& oth)
    {
        vtx = oth.vtx;
        wgt = oth.wgt;
    }

    AdjVtx& operator=(const AdjVtx& rhs)
    {
        if (this != &rhs)
        {
            vtx = rhs.vtx;
            wgt = rhs.wgt;
        }

        return *this;
    }

    bool operator<(const AdjVtx& rhs)
    {
        return (wgt < rhs.wgt);
    }

    bool operator>(const AdjVtx& rhs)
    {
        return (wgt > rhs.wgt);
    }

    int vtx;
    int wgt;
};

typedef std::vector<AdjVtx> AdjVtxList;
typedef DynamicArrayList<AdjVtxList> Graph;
////////////////////////

bool readGraph(const std::string& fname, Graph& gph, std::string& errmsg);
bool writPaths(const std::string& fname, DynamicArrayList<int> paths, std::string& errmsg);
void findShtPth(Graph gph, DynamicArrayList<int>& pthLen);

int main(int argc, char *argv[])
{
    Graph gph;
    std::string errmsg;

    if (readGraph("graph.csv", gph, errmsg))
    {
        DynamicArrayList<int> pthLen;
        findShtPth(gph, pthLen);

        if (writPaths("weight.csv", pthLen, errmsg))
            std::cout << "\tGraph shortest paths calculed and writed to file weight.csv\n";
        else
            std::cout << errmsg << std::endl;
    }
    else{ std::cout << errmsg << std::endl; }
}

/**
 * @brief readGraph
 * @param fname
 * @param gph
 * @return
 */
bool readGraph(const std::string& fname, Graph& gph, std::string& errmsg)
{
    bool success = false;
    std::ifstream file(fname);

    if (file.is_open())
    {
        int vtxcount = 0;
        std::string line;

        while (std::getline(file, line, '\n'))
        {
            AdjVtxList adjList;

            std::stringstream ss(line);
            std::string strv, strw;

            while (std::getline(ss, strv, ','))
            {
                std::getline(ss, strw, ',');

                int vtx = std::atoi(strv.c_str());
                int wgt = std::atoi(strw.c_str());
                adjList.push_back( AdjVtx(vtx,wgt) );
            }

            gph.insert(vtxcount++, adjList);
        }

        file.close();
        success = true;
    }
    else{ errmsg = "File Error: cannot open file " + fname; }

    return success;
}

/**
 * @brief writePaths
 * @param fname
 * @param paths
 * @return
 */
bool writPaths(const std::string& fname, DynamicArrayList<int> paths, std::string& errmsg)
{
    bool success = false;
    std::ofstream file(fname);

    if (file.is_open())
    {
        int i;
        for (i = 0; i < paths.getLength() - 1; ++i)
            file << paths.getEntry(i) << ',';
        file << paths.getEntry(i) << std::endl;

        file.close();
        success = true;
    }
    else { errmsg = "File Error: cannot open file " + fname; }

    return success;
}

/**
 * @brief findShrPth
 * @param gph
 * @param pthLen
 */
void findShtPth(Graph gph, DynamicArrayList<int>& pthLen)
{
    std::size_t nvertex = gph.getLength();

    //init. path lenght for each vertex
    pthLen.clear();
    for (int i = 0; i < nvertex; ++i)                       //foreach vi
        pthLen.insert(i, std::numeric_limits<int>::max());   //init. path length is maximun int

    //suport queue
    HeapPriorityQueue<AdjVtx> acuPthQueue;
    acuPthQueue.add(AdjVtx(0, 0));    //add start vertex v0 to the queue

    //track enqueued vertex
    DynamicArrayList<bool> enqueued;
    enqueued.insert(0, true);       //zero vertex already enqueued

    for (int i = 1; i < nvertex; ++i)
        enqueued.insert(i, false);

    while (!acuPthQueue.isEmpty())
    {
        //get and remove lowest priority vertex
        AdjVtx curVtx = acuPthQueue.peek();
        acuPthQueue.remove();
        enqueued.setEntry(curVtx.vtx, false);

        //update current vertex path length, if correspond
        if (curVtx.wgt < pthLen.getEntry(curVtx.vtx))
            pthLen.setEntry(curVtx.vtx, curVtx.wgt);

        //adjacent vertices to current vertex
        AdjVtxList adjList = gph.getEntry(curVtx.vtx);

        for (int i = 0; i < adjList.size(); ++i)
        {
            AdjVtx adjVtx = adjList[i];
            int tentPthLen = pthLen.getEntry(curVtx.vtx) + adjVtx.wgt;

            if (tentPthLen < pthLen.getEntry(adjVtx.vtx))
            {
                if (!enqueued.getEntry(adjVtx.vtx))
                {
                    acuPthQueue.add( AdjVtx(adjVtx.vtx, tentPthLen) );
                    enqueued.setEntry(adjVtx.vtx, true);
                }

                pthLen.setEntry(adjVtx.vtx, tentPthLen);
            }
        }
    }
}
