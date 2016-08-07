#include<bits/stdc++.h>
using namespace std;

set<char> terminals,nonTerminals;
map<int, pair<char, string> > productions;
map<pair<int, char>, string> table;
string input;

bool isTerminal(char c)
{
    return islower(c) || c=='+' || c=='-' || c=='*' || c=='/' || c=='^' || c=='$';
}

void parse()
{
	stack<char> stk;
	int la = 0, len = input.size();
	stk.push('0'); 
	while(!stk.empty() && la < len)
	{
		if(table[make_pair(stk.top() - '0', input[la])][0] == 'A')
		{
			cout<<"String is parsed successfully.\n";
			return;
		}
		else if(table[make_pair(stk.top() - '0',input[la])][0] == 'S' )
		{
			int s = stk.top() - '0', n = stoi(table[make_pair(s, input[la])].substr(1));
			stk.push(input[la]), stk.push(n + '0');
			la++;
		}
		else if(table[make_pair(stk.top() - '0', input[la])][0] == 'R')
		{
			int p = stoi(table[make_pair(a1,input[la])].substr(1));
			if(productions.find(p) != productions.end())
			{
				cout<<productions[p].first<<" -> "<<productions[p].second<<"\n";
				for(int i=0; i < productions[p].second.length() * 2; i++)
					stk.pop();
			}
			int s = stk.top()-'0';
			stk.push(productions[a2].first), stk.push(table[make_pair(s, productions[p].first)][0]);
		}
		else
		{
			cout<<"Error in parsing.\n";
			return;
		}
	}
}

int main()
{
    int n,m, num_states;
    string tab_val;
    char ch;
    scanf("%d", &n);
    for(int j = 0; j < n; ++j){
        char var;
        cin>>var;
        string y;
        cin>>y;
        if(!isTerminal(var))
		nonTerminals.insert(var);
        productions[j+1] = make_pair(var,y);
        for(char c : y)
        {
		if(isTerminal(c))
			terminals.insert(c);
        }
    }

    cin>>num_states;
    for(int i=0;i<num_states;i++)
    {
		cin>>m;
		for(int j=0;j<m;j++)
		{
			cin>>ch;
			cin>>tab_val;
			table[make_pair(i,ch)] = tab_val;
		}
    }

    cin>>input;

    input = input+string(1, '$');
    terminals.insert('$');

    parse();
    return 0;
}
/*

3
S AA
A aA
A b
7
4
a S3
b S4
A 2
S 1
1
$ A
3
a S3
b S4
A 5
3
a S3
b S4
A 6
3
a R3
b R3
$ R3
1
$ R1
3
a R2
b R2
$ R2
aabb




2
S 1 AA
A 3 aA b #

2
S 1 AA
A 2 aA b

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

5
S 1 ABCDe
A 2 a #
B 2 b #
C 1 c
D 2 d #

3
S 2 dA aB
A 2 bA c
B 2 bB c

not slr  (RR conflict)
2
S 2 A a
A 1 a

SR Conflict
3
S 2 S+T T
T 2 TV V
V 3 V* a b

*/
