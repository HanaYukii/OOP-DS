#include<bits/stdc++.h>
using namespace std;
int main()
{
    int indeg[51],n,m,ansn,used[51];
    deque<int> g[51];
    fstream fp;
    fp.open("TP_Sort_0516316.txt",ios::out);
    while(cin>>n)
    {
        map<int,int>mp,mp2;
        ansn=0;
        memset(used,0,sizeof(used));
        memset(indeg,0,sizeof(indeg));
        for(int i=0;i<n;i++)
        {
            int add;
            cin>>add;
            g[i].clear();
            mp[i]=add;
            mp2[add]=i;
        }
        cin>>m;
        for(int i=0;i<m;i++)
        {
            string s;
            int add1,add2;
            cin>>add1>>s>>add2;
            g[mp2[add2]].push_back(mp2[add1]);
            indeg[mp2[add1]]++;
        }
        for(int i=0;i<n;i++)
        {
            if(indeg[i]==0&&!used[i])
            {
                used[i]=1;
                ansn++;
                cout<<mp[i]<<' ';
                fp<<mp[i]<<' ';
                for(int j=0;j<g[i].size();j++)
                {
                    indeg[g[i][j]]--;
                }
            }
            if(ansn==n)
                break;
            else if(i==n-1)
                i=-1;

        }
        cout<<endl;
        fp<<endl;
    }
    fp.close();
}
