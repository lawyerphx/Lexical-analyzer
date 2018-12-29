#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(),(x).end()
#define se second
#define fi first
#define debug(x) cerr << #x << " = " << x << endl;
#define rep(i,s,t) for(int i=(s);i<=(t);i++)
#define rrep(i,s,t) for(int i=(s);i>=(t);i--)
#define SZ(x) ((int)(x).size())
#define pb push_back
#define mp make_pair
#define N 1010
typedef pair<int,char> PII;
typedef long long ll;
//ll powmod(ll x,ll n) {ll re=1; for(;n;n>>=1,x=x*x%P) if(n&1) re=re*x%P; return re; }
ll gcd(ll a,ll b) {return b? gcd(b,a%b):a;}
//head

map<pair<int,char>, pair<int,char>> trans;
stack<int> st;	//标号 
stack<double> val;	//标号
stack<bool> typ;	//数值类型 
char sta[] = {'-','S','E','E','E','T','T','T','F','F','F'};
string lexx[] = {"", "E'->E", "E->E+T", "E->E-T",
	"E->T", "T->T*F", "T->T/F", "T->F", "F->(E)",
	"F->num", "F->num.num"};
int len[] = {0,1,3,3,1,3,3,1,3,1,3};	//需要修改 

inline double Next_lexme(bool &isreal)	//从词法分析器中得到下一个词法单元 
{
	static char ch='#';
	double ans=0,tmp=1;
	if(ch=='#') ch = getchar();
	isreal=0;
	if(isdigit(ch))
	{
		ans=ch-'0';
		while(isdigit(ch = getchar()) || ch=='.')
		{
			if(ch=='.') isreal=1;
			else
			{
				if(isreal) ans += (ch-'0')*tmp;
				else ans=ans*10+ch-'0';
			}
			if(isreal) tmp/=10;
		}
	}
	else
	{
		if(ch=='\n') ch='$';
		ans=-(int)ch;
		ch='#';
	}
	return ans;
}

inline void add(int x,char tp,char nt,int val)
{
	trans[{x,tp}] = {val,nt};
}

void init_SLR()	//建立SLR表格 
{
	//Action
	add(0,'(','S',5), add(0,'N','S',4);
	add(1,'+','S',9), add(1,'-','S',11), add(1,'$','A',0);
	add(2,'+','R',4), add(2,'-','R',4), add(2,')','R',4), add(2,'$','R',4), add(2,'*','S',14), add(2,'/','S',15);
	add(3,'+','R',7), add(3,'-','R',7), add(3,'*','R',7), add(3,'/','R',7), add(3,')','R',7), add(3,'$','R',7);
	add(4,'+','R',9), add(4,'-','R',9), add(4,'*','R',9), add(4,'/','R',9), add(4,')','R',9), add(4,'$','R',9), add(4,'.','S',6);
	add(5,'(','S',5), add(5,'N','S',4);
	add(6,'N','S',8);
	add(7,'+','S',9), add(7,'-','S',11), add(7,')','S',13);
	add(8,'+','R',10), add(8,'-','R',10), add(8,'*','R',10), add(8,'/','R',10), add(8,')','R',10), add(8,'$','R',10);
	add(9,'(','S',5), add(9,'N','S',4);
	add(10,'+','R',2), add(10,'-','R',2), add(10,')','R',2), add(10,'$','R',2), add(10,'*','S',14), add(10,'/','S',15);
	add(11,'(','S',5), add(11,'N','S',4);
	add(12,'+','R',3), add(12,'-','R',3), add(12,')','R',3), add(12,'$','R',3), add(12,'*','S',14), add(12,'/','S',15);
	add(13,'+','R',8), add(13,'-','R',8), add(13,'*','R',8), add(13,'/','R',8), add(13,')','R',8), add(13,'$','R',8);
	add(14,'(','S',5), add(14,'N','S',4);
	add(15,'(','S',5), add(15,'N','S',4);
	add(16,'+','R',5), add(16,'-','R',5), add(16,'*','R',5), add(16,'/','R',5), add(16,')','R',5), add(16,'$','R',5);
	add(17,'+','R',6), add(17,'-','R',6), add(17,'*','R',6), add(17,'/','R',6), add(17,')','R',6), add(17,'$','R',6);
	
	//Goto
	add(0,'E','S',1), add(0,'T','S',2), add(0,'F','S',3);
	add(5,'E','S',7), add(5,'T','S',2), add(5,'F','S',3);
	add(9,'T','S',10), add(9,'F','S',3);
	add(11,'T','S',12), add(11,'F','S',3);
	add(14,'F','S',16);
	add(15,'F','S',17);
}

double a[N];
bool b[N];

int main()
{
	init_SLR();
	int now = 0;
	bool op=0;
	st.push(now);
	while(1)
	{
		double nt = Next_lexme(op);
		char tpc;
		if(nt>=0) tpc='N';
		else tpc=-(int)nt;
	//	debug(nt);
	//	debug(op);
		if(!trans.count({now,tpc}))
		{
			puts("Error!!");
			return 0;
		}
		
		while(1)
		{
			PII tp=trans[{now,tpc}];
			cout << "执行"<<tp.se<<tp.fi<<endl;
			//尝试应用SLR表格进行转移
				
			if(tp.se=='A')
			{
				cout << "计算结果为 "<<val.top();
				cout << "类型为 "<< (typ.top()? "double":"integer") << endl;
				//输出正确结果，进行类型分析 
				return 0;
			}
			else if(tp.se=='S')
			{
				st.push(now = tp.fi);
				if(tpc=='N') val.push(nt);
				else val.push(-1);
				typ.push(op);
				break; 
			}
			else
			{
				int i=tp.fi, tmp=len[i];
				char ss = sta[i];
				int tot=0;
				while(tmp--)
				{
					a[++tot] = val.top();
					b[tot] = typ.top();
					val.pop();
					st.pop();
					typ.pop();
				}
				PII nx = {st.top(), ss};
				cout << "语法产生式为 " << lexx[i] << endl;
				if(!trans.count(nx))
				{
					puts("prog error detected!");
					exit(0);
				}
				double ans=0;
				bool opt=0;
				now = trans[{st.top(),ss}].fi;
				if(i==2) ans = a[3]+a[1], opt=b[3]|b[1];
				else if(i==3) ans=a[3]-a[1], opt=b[3]|b[1];
				else if(i==5) ans=a[3]*a[1], opt=b[3]|b[1];
				else if(i==6) ans=a[3]/a[1], opt=b[3]|b[1];
				else if(i==8) ans=a[2], opt=b[2];
				else ans=a[1], opt=b[1];
				cout << "当前自底向上归约式的值为" << ans;
				cout << " 类型：" << (opt? "double":"integer") << endl;
				st.push(now);
				val.push(ans);
				typ.push(opt);
			}
		//	cout << endl;
		}
	}
	return 0;
}
