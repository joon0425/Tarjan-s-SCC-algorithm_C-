// 1-based(vertex) Strongly-Connected-Component(SCC) algorithm
#include <bits/stdc++.h>
using namespace std;
#define maxV 10010
#define maxE 100010
#define fn1(i,n) for(int (i)=0;(i)++<(n);)
#define fn(i,n) for(int (i)=0;(i)<(n);(i)++)
#define all(n) (n).begin(),(n).end()
vector<int> adj[maxV];
int nV,nE,order,visitOrder[maxV];
bool isScc[maxV];
stack<int> st;
vector<vector<int>> SCC;
int FindScc(int v){ // return the min value of order of visits
    int minOrder=visitOrder[v]=++order;
    st.push(v);
    for(auto& child:adj[v]){
        if(!visitOrder[child])minOrder=min(minOrder,FindScc(child));
        else if(!isScc[child])minOrder=min(minOrder,visitOrder[child]);
    }
    if(minOrder==visitOrder[v]){ // if min value of child-vertexes' order of visits(it mean that child-vertexes connected with this vertex;"cycle")
        vector<int> newScc;
        for(;;){
            int component=st.top();st.pop();
            isScc[component]=1;
            newScc.push_back(component);
            if(component==v)break;
        }
        SCC.push_back(newScc);
    }
    return minOrder;
}
bool comp(vector<int> &a,vector<int> &b){return a[0]<b[0];}
bool comp1(int &a,int &b){return a<b;}
int main(){
    cin>>nV>>nE;
    fn(i,nE){
        int a,b;cin>>a>>b;
        adj[a].push_back(b);
    }
    fn1(i,nV)if(!visitOrder[i])FindScc(i);
    cout<<SCC.size()<<'\n';
    for(auto& i:SCC)sort(all(i));
    sort(all(SCC),comp);
    for(auto& i:SCC){
        for(auto& x:i)cout<<x<<' ';
        cout<<"-1\n";
    }
}