#include <map>
#include <deque>
#include <cstring>
#include <string>
#include <cassert>
#include <iostream>
#include <algorithm>
#include "def_lex.h"

using namespace std;

class Token_Flow
{
};

struct package
//analyzer ���ص���Ϣ�� 
{
	bool success;
	string token, property;
};


string StoN(int x)
//������ת��Ϊ�ַ��� 
{
	string ans;
	for(;x;x/=10) ans.push_back(x%10+'0');
	reverse(ans.begin(),ans.end());
	return ans;
}

/*
state = 0 : 	start
state = 100:  	out 
*/
class analyzer
//�ʷ������� 
{
	private:
		
		int Error_num;
		//���������Լ�����ĸ�����Ϣ
		
		int line, site;
		int _line, _site;
		//��ǰ���к����кţ������汾 
		
		int state, last_state;
		//��ǰ״̬��״̬ת�Ʊ��еı��
		//���һ������End��״̬�ı�� 
		
		char other = (char)(2);
		//����ת���ַ���other 
		
		deque<char> char_flow;
		//�����ַ������� 
		
		map< pair<int,char> , int> state_trans;
		//״̬ת��ͼ 
		
		void F(int x,char y,int z)
		//��״̬ͼ�м���һ���� 
		{
			state_trans[{x,y}] = z;
		}

		char Get_char()
		//�ӻ������� / �ļ��еõ� char 
		{
			char ans;
			if(char_flow.empty())
			{
				ans = getchar();
				if(ans=='\n') site = 0, line++;
				else site++;
			}
			else
			{
				ans = char_flow.back();
				char_flow.pop_back();
			}
			return ans;
		}

		string cur;	//��ǰ�ĵ��� 

		void Back_Push(char ch)
		//���ַ�ch���ƽ��������  
		{
			char_flow.push_back(ch);
		}
		
		string get_Token()
		//ͨ�� last state �õ�Token 
		{
			switch(last_state)
			{
				case 0:		return "special symbol";
				case 1: 	return "name";
				case 2: 	return "integer";
				case 4:		return "float";
				case 7:		return "E-number";
				case 23: 	return "character";
				case 24: 	return "string";
				case 27: 	return "one_row_comment";
				case 29:	return "multi_row_comment";
				default:	return "operator";
			}
		}

		void Raise_Error(int state)
		//�����쳣�����쳣���Ľ������ private ��
		{
			if(state == -1) Error_num = -1;
			else if(state == 1) Error_num = 0;
			else if(state == 3 || state == 5 || state == 6) Error_num = 1;
			else if(state == 23) Error_num = 3;
			else assert(false);
			char_flow.clear();
			//û�д���ȴ������raise error 
		}
		
		bool check_other(int x)
		//��鵱ǰ other �Ƿ���eat���� 
		{
			return x==21 || x==24 || x==27 || x==28 || x==29;
		}
		
		int check_keyword(string tmp)
		//��� tmp �Ƿ��йؼ������� 
		{
			if(tmp == "auto") return 1;
			if(tmp == "int") return 1;
			if(tmp == "char") return 1;
			if(tmp == "float") return 1;
			if(tmp == "double") return 1;
			if(tmp == "long") return 1;
			if(tmp == "unsigned") return 1;
			if(tmp == "true") return 2;
			if(tmp == "false") return 2;
			if(tmp == "if") return 3;
			if(tmp == "else") return 3;
			if(tmp == "break") return 4;
			if(tmp == "return") return 4;
			if(tmp == "goto") return 4;
			if(tmp == "while") return 5;
			if(tmp == "for") return 5;
			if(tmp == "do") return 5;
			if(tmp == "typedef") return 6;
			if(tmp == "sizeof") return 6;
			if(tmp == "operator") return 6;
			if(tmp == "struct") return 6;
			if(tmp == "const") return 6;
			if(tmp == "using") return 6;
			if(tmp == "namespace") return 6;
			if(tmp == "include") return 6;
			if(tmp == "define") return 6;
			return 0;
		}
		
		void move(char ch)
		//�ƶ�״̬ 
		{
			int tmp = state;
			if(state != End) last_state = state;
			//����������� : any 
			if(state == 22) { state = 23; return; }
			if(state == 25) { state = 24; return; }
			if(state_trans.count({state,ch})) state = state_trans[{state,ch}];
			// ����ת�� 
			else if(state_trans.count({state,other}))
			// other/other* ����� 
			{
	//			cerr << "state " << (int)ch << endl;
				char cht = ch;
				//a copy of ch
				ch = other;
				state = state_trans[{state,ch}];
				if(!check_other(tmp))
				{
					if(tmp) Back_Push(cht);
					cur.pop_back();
				}
				//���Ϊ other*�� ����һ���ַ� 
			}
			else
			// �쳣���֣������쳣��������ʣ���ַ���������ȡ 
			{
				Raise_Error(state);
				state = End;
			}
		}
		
	public:
		
		string token, property; 
		//�����ӿ��� ���Ǻ���𣬱�ţ� 
		
		void openfile(string ss)
		//����Ӧ���ļ�,���뵽 analyzer��
		{
			freopen(ss.c_str(),"r",stdin);
			state = 0;
			line = 1, site = 1;
			char_flow.clear();
		}
		
		//ת��ͼ�� other �����ַ� 
		void Build_Graph()
		{
			//branch 0 : ��Ч�ַ� 
			F(0,other,0);
			
			//branch 1 : name 
			F(0,'_',1), F(1,'_',1);
			rep(t,0,25) F(0,t+'a',1), F(0,t+'A',1), F(1,t+'a',1), F(1,t+'A',1);
			F(1,other,End);
			rep(t,'0','9') F(1,t,1);
			
			//branch 2 : ���� 
			rep(t,'0','9')
			{
				F(0,t,2), F(2,t,2), F(3,t,4), F(4,t,4);
				F(5,t,7), F(6,t,7), F(7,t,7);
			}
			F(2,'.',3), F(2,'E',5), F(2,'e',5), F(2,other,End);
			F(4,other,End), F(4,'E',5), F(4,'e',5);
			F(5,'+',6), F(5,'-',6), F(7,other,End);
			
			//branch 3 :  <, <=, <<=
			//branch 4 : >, >=, >>=
			F(0,'<',8), F(8,'=',End), F(8,'<',19), F(19,'=',End);
			F(8,other,End), F(19,other,End);
			F(0,'>',9), F(9,'=',End), F(9,'>',20), F(20,'=',End);
			F(9,other,End), F(20,other,End);
			
			//branch 5
			F(0,'=',10), F(10,'=',End);
			F(10,other,End);
			
			//branch 6
			F(0,'!',11), F(11,'=',End);
			
			//branch 7
			F(0,'+',12), F(12,'+',End), F(12,'=',End), F(12,other,End);
			
			//branch 8
			F(0,'-',13), F(13,'-',End), F(13,'=',End), F(13,'>',End), F(13,other,End);
			
			//branch 9,10
			F(0,'%',14), F(0,'*',14), F(14,'=',End), F(14,other,End);
			//15 loss
			
			//branch 11, 12
			F(0,'|',16), F(16,'=',End), F(16,'|',End), F(16,other,End);
			F(0,'&',17), F(17,'=',End), F(17,'&',End), F(17,other,End);
			
			//branch 13
			F(0,'^',18), F(18,'=',End), F(18,other,End);
			
			//branch 14
			F(0,'~',End), F(0,'[',End), F(0,']',End);
			F(0,'.',End), F(0,'(',End), F(0,')',End);
			F(0,',',End), F(0,'?',End), F(0,':',End);
			F(0,'{',End), F(0,'}',End), F(0,';',End);
			
			//branch 15
			F(0,'\'',21), F(21,'\\',22), F(23,'\'',End);
			F(21,other,23);
			
			//branch 16
			F(0,'\"',24), F(24,'\\',25), F(24,other,24), F(24,'\"',End);
			
			//branch 17
			F(0,'/',26), F(26,'/',27), F(27,other,27), F(27,'\n',End);
			F(26,'*',28), F(28,other,28), F(28,'*',29), F(29,other,28), F(29,'/',End);
			F(26,other,End);
			debug("graph -- build -- over")
		}
		//special : 22->23 / 25->24: any
		//special : other for 21, 24, 27, 28, 29 eats a character
		
		package getItem()
		//����һ�����ﲢ��������Ϣ 
		//Ҫ�����ĩβ���Ͽո� 
		{
			char ch;
			package ans;
			_line = line, _site = site; 
			Error_num = -2;
			puts("--------------------");
			state = 0;
			while(state!=End)
			{
				ch = Get_char(); 
		//		cerr << state << " trans " << (int)ch << endl;
				if(ch==EOF)
				//�������ļ���β 
				{
					Raise_Error(-1);
					break;
				}
				cur.push_back(ch);
				move(ch);
			}
		//	debug(state); 
			if(Error_num == -2)
			{
				ans.token = get_Token();
				ans.success = true;
				ans.property = cur;
				if(ans.token == "name")
				{
					int t = check_keyword(ans.property);
					if(t==1) ans.token = "type_name";
					else if(t==2) ans.token = "bool_constant";
					else if(t==3) ans.token = "logical_structure";
					else if(t==4) ans.token = "exc_control";
					else if(t==5) ans.token = "loop_control";
					else if(t==6) ans.token = "keyword";
				}
			}
			else ans.success = false;
			cur.clear();
			return ans;
		}
		
		string getError()
		//��ȡ������Ϣ 
		{
			string ans = "Error detected at line " + StoN(_line) + ", " + StoN(_site+1) + "th character";
			switch(Error_num)
			{
				case -2: ans = "";								break;	//û�д� 
				case -1: ans = "EOF"; 							break;	//����EOF 
				case 0: ans = ans + "������/�������������� : "; break;
				case 1: ans = ans + "���ֶ������ : "; 			break;
				case 2: ans = ans + "������ַ� : "; 			break;
				case 3: ans = ans + "��ƥ��ĵ�����"; 			break;
				case 4: ans = ans + "��ƥ���˫����"; 			break;
				case 5: ans = ans + "����� // �÷�";			break;
				case 6: ans = ans + "�Ƿ�����"; 				break;
				default : ans = ans + "δ֪����";
			}
			return ans;
		}
};

