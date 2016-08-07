#include<bits/stdc++.h>
using namespace std;

map<char, vector<string>> productions;
map<char, bool> nullable;
map<char, set<char>> First, follow;

bool isTerminal(char c)
{
    return islower(c);
}

void mergeset(set<char>& a, set<char> b)
{
    for(char c : b)
    {
        a.insert(c);
    }
}
set<char> rec(string s)
{
    if(s.size() == 0)
        return {};
    char f = s[0];
    set<char> ret;
    if(isTerminal(f))
    {
        ret.insert(f);
    }
    else
    {
        mergeset(ret, First[f]);
        if(nullable[f])
        {
            mergeset(ret, rec(s.substr(1)));
        }
        if(nullable[f] && s.size() == 1)
        {
            ret.insert('#');
        }
    }
    return ret;
}

void computefirst()
{
    bool change = true;
    while(change)
    {
        change = false;
        for(auto it : productions)
        {
            char var = it.first;
            vector<string> prod = it.second;
            for(string s : prod)
            {
                int z = First[var].size();
                mergeset(First[var], rec(s));
                change |= (First[var].size() != z);
            }
        }
    }
}

void computefollow()
{
    bool change = true;
    while(change)
    {
        change = false;
        for(auto it : productions)
        {
            char var = it.first;
            vector<string> prod = it.second;
            for(string s : prod)
            {
                for(int i = 0; i < s.size() - 1; ++i)
                {
                    if(!isTerminal(s[i]))
                    {
                        char f = s[i];
                        set<char> firsts = rec(s.substr(i + 1));
                        for(char c : firsts)
                        {
                            if(c == '#')
                            {
                                int z = follow[f].size();
                                mergeset(follow[f], follow[var]);
                                change |= (follow[f].size() != z);
                                firsts.erase('#');
                                break;
                            }
                        }
                        int z = follow[f].size();
                        mergeset(follow[f], firsts);
                        change |= (follow[f].size() != z);

                    }
                }
                {
                    char f = s.back();
                    if(!isTerminal(f))
                    {

                        int z = follow[f].size();
                        mergeset(follow[f], follow[var]);
                        change |= (follow[f].size() != z);
                    }
                }
            }
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int j = 0; j < n; ++j){
        char var;
        cin>>var;
        int m;
        cin>>m;
        vector<string> p;
        string y;
        for(int i = 0; i < m; ++i)
        {
            cin>>y;
            if(y == "#")
            {
                nullable[var] = true;
            }
            else
                p.push_back(y);
        }
        productions[var] = p;
    }

    computefirst();

    follow['S'] = {'$'};

    computefollow();

    printf("FIRST SETS\n");
    for(auto c : First)
    {
        cout << c.first;
        if(nullable[c.first])
        {
            cout<<" #";
        }
        for(char cc : c.second)
        {
            cout<<" "<<cc;
        }
        cout<<endl;
    }

    printf("FOLLOW SETS\n");
    for(auto c : follow)
    {
        cout << c.first;
        for(char cc : c.second)
        {
            cout<<" "<<cc;
        }
        cout<<endl;
    }
    return 0;
}
/*
2
S 1 AA
A 3 Aa b #

3
S 2 AaAb BbBa
A 1 #
B 1 #

6
S 1 ABCDE
A 2 a #
B 2 b #
C 1 c
D 2 d #
E 2 e #
*/
