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
typedef pair<int,int> PII;
typedef long long ll;
//ll powmod(ll x,ll n) {ll re=1; for(;n;n>>=1,x=x*x%P) if(n&1) re=re*x%P; return re; }
ll gcd(ll a,ll b) {return b? gcd(b,a%b):a;}
//head
int main()
{
	freopen("src.c","r",stdin);
	char ch;
	while(ch = getchar(), ch!=EOF) putchar(ch), cout<<' '<<(int)ch<<endl;
}
