#include<bits/stdc++.h>
using namespace std;
char cmd[310];
int main()
{
	string rgx, file;
	cin >> rgx >> file;
	string c = "egrep " + rgx + " " + file;
	strcpy(cmd, c.c_str());
	system(cmd);
	return 0;
}
/*

abb*
input.txt

*/
