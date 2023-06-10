#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Edge
{
public:
    int v, w;

    Edge(int v, int w) //v = vertices , w = weight 
    {
        this->v = v;
        this->w = w;
    }
};

void addEdge(vector<vector<Edge>>&graph , int u , int v , int w){
    graph[u].push_back(Edge(v,w));
    graph[v].push_back(Edge(u,w));
}

void display(vector<vector<Edge>>&graph, int v)
{
    for(int i = 0 ; i < v ; i++){
        cout<<i<<"->"<<" ";
        for(Edge e : graph[i]){
           cout<<"{"<<e.v <<","<<e.w<<"}";
        }
        cout<<endl;
    }
}

int findEdge(vector<vector<Edge>> &graph, int u, int v){  // u -> v 
    for (int i = 0; i < u; i++)
    {
        Edge e = graph[u][i];
            if(e.v == v) return i;
        }
    return -1;
}

void removeEdge(vector<vector<Edge>> &graph, int u, int v) //2 point ke beech ke connection 
{
    int x = findEdge(graph , u , v);
    graph[u].erase(graph[u].begin()+x);
    int y = findEdge(graph, v, u);
    graph[v].erase(graph[v].begin() + y);
}

void removeVtx(vector<vector<Edge>> &graph, int u) //uss point se saare connection 
{
   for(int i = graph[u].size() - 1;i >= 0 ; i--){ //started from behind just to avoid shifting problem 
       Edge e = graph[u][i]; 
       removeEdge(graph , u , e.v);
   }
}

bool hasPath(vector<vector<Edge>> &graph, int src, int dest, vector<bool> &vis){
     
    if(src == dest) return true;

    bool res = false;
    vis[src] = true;
    for(Edge e : graph[src]){
        if(!vis[e.v]){
           res = res || hasPath(graph , e.v , dest , vis); 
        }
    }
    return res;
}

int allPath(vector<vector<Edge>> &graph, int src, int dest, vector<bool> &vis, string psf){
    if (src == dest){
        cout<<psf<<dest<<endl;
        return 1;
    }

    int count = 0;
    vis[src] = true;
    for (Edge e : graph[src])
    {
        if (!vis[e.v])
        {
            count += allPath(graph, e.v, dest, vis, psf + to_string(src));
        }
    }
    vis[src] = false;
    return count;
}

 void preOrder(vector<vector<Edge>> &graph, int src,vector<bool> &vis, int wsf, string psf) //wsf = weight soo far
{
    cout << to_string(src) << " -> "<< (psf + to_string(src)) << "@" << to_string(wsf) << endl;
    vis[src] = true;
    for (auto e : graph[src])
    {
        if (!vis[e.v])
        {
            preOrder(graph, e.v, vis, wsf + e.w, psf + to_string(src));
        }
    }

    vis[src] = false;
}

void postOrder(vector<vector<Edge>> &graph, int src, vector<bool> &vis, int wsf, string psf)
{
    vis[src] = true;
    for (auto e : graph[src])
    {
        if (!vis[e.v])
        {
            postOrder(graph, e.v, vis, wsf + e.w, psf + to_string(src));
        }
    }
    cout << to_string(src) << " -> " << (psf + to_string(src)) << "@" << to_string(wsf) << endl;
    vis[src] = false;
}

class pair_ {
    public:
    int heavyPath = 0;
    string psf = "";

    pair_()
    {
    }

    pair_ (int heavyPath , string psf){
        this -> heavyPath = heavyPath;
        this -> psf = psf;
    }
};

pair_ heavyPath_01(vector<vector<Edge>> &graph, int src, int dest, vector<bool> &vis){
    
    if(src == dest){
        pair_ base(0 , to_string(src) + "");
        return base;
    }
    vis[src] = true;
    pair_ myAns(-1 , "");

        for (Edge e : graph[src])
        { 
            if (!vis[e.v])
            {
            pair_ resAns = heavyPath_01(graph, e.v, dest, vis);

            if (resAns.heavyPath != -1 && resAns.heavyPath + e.w > myAns.heavyPath)
            {
                myAns.heavyPath = resAns.heavyPath + e.w;
                myAns.psf = to_string(src) + resAns.psf;
            }
          }
        }
        vis[src] = false;
        return myAns;
}

pair_ lightestPath_01(vector<vector<Edge>> &graph, int src, int dest, vector<bool> &vis)
{

}

void hamintonainPathAndCycle(vector<vector<Edge>> & graph, int src, int osrc, int edgeCount, vector<bool> &vis, string psf, vector<string> &ans)
    {
        if (edgeCount == graph.size() - 1)
        {
            psf += to_string(src);
            int idx = findEdge(graph, src, osrc);
            if (idx != -1)
                psf.insert(psf.size(), "*");

            ans.push_back(psf);
            return;
        }

        vis[src] = true;
        for (Edge e : graph[src])
        {
            if (!vis[e.v])
                hamintonainPathAndCycle(graph, e.v, osrc, edgeCount + 1, vis, psf + to_string(src), ans);
        }
        vis[src] = false;
    }

    void constructGraph()
    {
        int V = 7; // Edge
        vector<vector<Edge>> graph(V, vector<Edge>());
        addEdge(graph, 0, 1, 10);
        addEdge(graph, 0, 3, 10);
        addEdge(graph, 1, 2, 10);
        addEdge(graph, 2, 3, 40);

        // addEdge(graph, 2, 7, 2);
        // addEdge(graph, 2, 8, 4);
        // addEdge(graph, 7, 8, 3);

        addEdge(graph, 3, 4, 2);
        addEdge(graph, 4, 5, 2);
        addEdge(graph, 4, 6, 8);
        addEdge(graph, 5, 6, 3);

        addEdge(graph, 0, 6, 3);

        // display(graph , 7);
        // removeEdge(graph , 0 , 1);
        // removeVtx(graph , 1);
        vector<bool> vis(V);
        vector<string> ans;
        //int res = allPath(graph, 0, 6, vis, " ");
       // cout << res;

        // hamintonainPathAndCycle(graph, 0, 0, 0, vis, " ", ans);
        // for (auto ele : ans)
        // {
        //     cout << ele << endl;
        // }
       pair_ ans1 = heavyPath_01(graph, 0, 6, vis);
       cout << ans1.heavyPath << " @ " << ans1.psf << endl;
        // cout << myAns.heavyPath << " " << myAns.psf << endl;
    }


    int main()
    {
        constructGraph();
        return 0;
    }