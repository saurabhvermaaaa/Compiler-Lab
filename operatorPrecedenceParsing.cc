#include<bits/stdc++.h>
using namespace std;

map<char, vector<string>> productions;

// -1 <, 0 = ,1 >, 4 NULL

set<char> operators, nonterminals;


bool isOperator(char c)
{
    return islower(c) || (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^') || (c == '%') || (c == '(') || (c == ')');
}
vector<string> ans;
void reduce(char op)
{
    for(char nt : nonterminals)
    {
        for(string prod : productions[nt])
        {
            for(char c : prod)
            {
                if(c == op)
                {
                    ans.push_back(string(1, nt) + " -> " + prod);
                    break;
                }
            }
        }
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    operators.insert('$');
    for(int j = 0; j < n; ++j){
        char var;
        cin>>var;
        nonterminals.insert(var);
        int m;
        cin>>m;
        vector<string> p;
        string y;
        for(int i = 0; i < m; ++i)
        {
            cin>>y;
            for(char c : y)
                if(isOperator(c))
                    operators.insert(c);
            p.push_back(y);
        }
        productions[var] = p;
    }
    int matrix[4][4] = {4, 1, 1, 1,
                        -1, 1, -1, 1,
                        -1, 1, 1, 1,
                        -1, -1, -1, -1};
    map<char, int> pos;
    pos['i'] = 0;
    pos['+'] = 1;
    pos['*'] = 2;
    pos['$'] = 3;
    string in;
    cin>>in;
    in = in + "$";
    stack<char> stk;
    stk.push('$');
    int lookahead = 0;
    bool parse = true;
    while(lookahead < in.size())
    {
        char s = stk.top(), i = in[lookahead];
        if(matrix[pos[s]][pos[i]] == 4)
        {
            parse = false;
            break;
        }
        else if(matrix[pos[s]][pos[i]] <= 0)
        {
            stk.push(i);
            ++lookahead;
        }
        else
        {
            stk.pop();
            reduce(s);
        }
    }
    if(parse && lookahead == in.size() && stk.top() == '$')
    {
        printf("String parsed.\n");
        for(string p : ans)
            cout << p << endl;
    }
    else
    {
        printf("Not parsed.\n");
    }
    return 0;
}
/*
1
E 3 E+E E*E i
i+i*i



*/
