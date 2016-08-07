#include<bits/stdc++.h>
using namespace std;

map<char, vector<string>> productions, allproductions;
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
    if(f == '#')
    {
        ret.insert('#');
    }
    else if(isTerminal(f))
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
map<pair<char, char>, vector<string>> ll1table;
set<char> terminals, nonterminals;
int main()
{
    int n;
    scanf("%d", &n);
    for(int j = 0; j < n; ++j){
        char var;
        cin>>var;
        nonterminals.insert(var);
        int m;
        cin>>m;
        vector<string> p, cp;
        string y;
        for(int i = 0; i < m; ++i)
        {
            cin>>y;
            if(y == "#")
            {
                nullable[var] = true;
            }
            else
            {
                cp.push_back(y);
                for(char c : y)
                    if(isTerminal(c))
                        terminals.insert(c);
            }
            p.push_back(y);
        }
        allproductions[var] = p;
        productions[var] = cp;
    }
    terminals.insert('$');
    computefirst();

    follow['S'] = {'$'};

    computefollow();

    for(char nt : nonterminals)
    {
        for(string pro : allproductions[nt])
        {
            set<char> firsts = rec(pro);
            for(char t : firsts)
            {
                if(t == '#')
                {
                    for(char c : follow[nt])
                    {
                        ll1table[make_pair(nt, c)].push_back(pro);
                    }
                }
                else
                {
                    ll1table[make_pair(nt, t)].push_back(pro);
                }
            }
        }
    }

    for(char nt : nonterminals)
    {
        cout<<"nonterminal "<<nt<<" :"<<endl;
        for(char t : terminals)
        {
            cout<<t<<" --> ";
            for(string p : ll1table[make_pair(nt, t)])
                cout<<" "<<p;
            cout<<endl;
        }
    }
    return 0;
}
/*
3
S 2 aB #
B 2 bC #
C 2 cS #

3
S 1 AB
A 2 a #
B 2 b #

*/
