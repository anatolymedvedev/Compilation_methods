#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main()
{
	string strsymbols = "!+*()ab";
	string stacksymbols = "ABCTDM!+*()ab";

	string start_sym = "A";
	pair<string, int> p1 = make_pair("!B!", 1);
	pair<string, int> p2 = make_pair("TC", 2);
	pair<string, int> p3 = make_pair("", 3);
	pair<string, int> p4 = make_pair("+TC", 4);
	pair<string, int> p5 = make_pair("MD", 5);
	pair<string, int> p6 = make_pair("", 6);
	pair<string, int> p7 = make_pair("*MD", 7);
	pair<string, int> p8 = make_pair("a", 8);
	pair<string, int> p9 = make_pair("b", 9);
	pair<string, int> p10 = make_pair("(B)", 10);
	pair<string, int> pDROP = make_pair("", 0);
	pair<string, int> pERR = make_pair("", -1);

	pair<string, int> control_table[13][7] = {
		p1,		pERR,	pERR,	pERR,	pERR,	pERR,	pERR,
		pERR,	pERR,	pERR,	p2,		pERR,	p2,		p2,
		p3,		p4,		pERR,	pERR,	p3,		pERR,	pERR,
		pERR,	pERR,	pERR,	p5,		pERR,	p5,		p5,
		p6,		p6,		p7,		pERR,	p6,		pERR,	pERR,
		pERR,	pERR,	pERR,	p10,	pERR,	p8,		p9,
		pDROP,	pERR,	pERR,	pERR,	pERR,	pERR,	pERR,
		pERR,	pDROP,	pERR,	pERR,	pERR,	pERR,	pERR,
		pERR,	pERR,	pDROP,	pERR,	pERR,	pERR,	pERR,
		pERR,	pERR,	pERR,	pDROP,	pERR,	pERR,	pERR,
		pERR,	pERR,	pERR,	pERR,	pDROP,	pERR,	pERR,
		pERR,	pERR,	pERR,	pERR,	pERR,	pDROP,	pERR,
		pERR,	pERR,	pERR,	pERR,	pERR,	pERR,	pDROP
	};

	vector<int> rules_stack;
	//!(a+b)!
	//!a+b!
	//!(a+b)*(a+b)!
	string input_string;
	cin >> input_string;
	cout << endl;
	string st;
	st.append(start_sym);
	int row = 0, column = 0;
	string tmp = "";
	while (!st.empty() && !input_string.empty()) 
	{
		cout << "stack: " << st << " - string: " << input_string;
		row = stacksymbols.find(st[0]);
		column = strsymbols.find(input_string[0]);

		if (control_table[row][column].second > 0) 		//generate
		{
			cout << " action: generate: " << control_table[row][column].second << endl;
			st.erase(0, 1);
			tmp = get<0>(control_table[row][column]);
			st = tmp.append(st);
			rules_stack.push_back(control_table[row][column].second);
		}
		else if (control_table[row][column].second == 0) 	 //drop terminal
		{
			cout << " action: drop terminal" << endl;
			input_string.erase(0, 1);
			st.erase(0, 1);
		}
		else if(control_table[row][column].second < 0)	 //ERROR
		{
			cout << " action: ERROR" << endl;
			return 1;
		}
	}
	cout << "stack: " << st << " string: " << input_string << " action: normal exit" << endl;

	cout << endl << "RULES: ";
	for (int i = 0; i <= rules_stack.size() - 1; i++) 
	{
		cout << rules_stack[i] << ' ';
	}
	cout << endl;

	return 0;
}
