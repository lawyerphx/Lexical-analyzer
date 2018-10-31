#include    "analyzer.h"
#include <bits/stdc++.h>
using namespace std;
//head

int main()
{
	analyzer solver;
	solver.openfile("src.c");
	solver.Build_Graph();
	
	while(true)
	{
		auto item = solver.getItem();
		if(!item.success)
		{
			if(solver.getError() == "EOF")
				break;
			else cout << "Error detected : " + solver.getError() + '\n' << endl;
		}
		else
			cout << "token:" << item.token << '\t' << "property:" << item.property << endl;
	}
	cout << "\n\n";
	return 0;
}
