#include<bits/stdc++.h>
using namespace std;
string alphabet;
map<pair<int, char>, vector<int>> m;
const int N = 100;
bool final[N];
int main()
{
    int states, alphabets;
    cin >> states >> alphabets;
    for(int i = 0; i < alphabets; ++i)
        cin>>alphabet[i];
    for(int i = 0; i < states; ++i)
    {
        for(int j = 0; j < alphabets; ++j)
        {
            int c;
            cin>>c;
            for(int k = 0; k < c; ++k)
            {
                int v;
                cin>>v;
                m[make_pair(i, alphabet[j])].push_back(v);
            }
        }
    }
    int f, ac;
    cin>>f;
    for(int i = 0; i < f; ++i)
        cin >> ac, final[ac] = true;
    printf("\t\t");
    for(int i = 0; i < alphabets; ++i)
        printf("%c\t", alphabet[i]);
    printf("\n");
    for(int i = 0; i < (1 << states); ++i)
    {
        bool accept = false;
        for(int k = 0; k < states; ++k)
            if(i & (1 << k))
                accept |= final[k];
        if(accept)
            printf("*");
        printf("%d\t\t", i);
        for(int j = 0; j < alphabets; ++j)
        {
            set<int> st;
            for(int k = 0; k < states; ++k)
            {
                if(i & (1 << k))
                {
                    vector<int> add = m[make_pair(k, alphabet[j])];
                    for(int l = 0; l < add.size(); ++l)
                        st.insert(add[l]);
                }
            }
            int aa = 0;
            for(set<int> :: iterator it = st.begin(); it != st.end(); ++it)
                aa |= (1 << (*it));
            printf("%d\t", aa);
        }
        printf("\n");
    }
    return 0;
}
