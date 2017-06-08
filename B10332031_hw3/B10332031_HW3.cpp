#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>

using namespace std;

int RSA(int input);//RSA盞 
int getPrime();//眔借计 
int square_multiply(int base, int pow);//square multiply计笲衡 
string toBinary(int n);//秈锣传秈 
int mul_inv(int a, int b);
int chinese_remainder(int *n, int *a, int len);//い瓣緇Α﹚瞶 
bool miller_rabin(int n);//絋粄琌借计簍衡猭 
int gcd(int m, int n);//璸衡程そ计 

int main()
{
	srand(time(NULL));
	int input;
	cin>>input;
	cout<<RSA(input);
}
int square_multiply(int base, int pow)//square multiply计笲衡 
{
	int ans=base;
	string power=toBinary(pow);
	for(int i=1;i<power.size();i++)
	{
		ans=ans*ans;
		if(power[i]=='1')
		{
			ans=ans*base;
		}
	}
	return ans;
}
string toBinary(int n)//秈锣传秈 
{
    string r;
    while(n!=0) 
	{
		r=(n%2==0 ?"0":"1")+r; n/=2;
	}
    return r;
}
int mul_inv(int a, int b)
{
	int b0 = b, t, q;
	int x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}
 
int chinese_remainder(int *n, int *a, int len)//い瓣緇Α﹚瞶 
{
	int p, i, prod = 1, sum = 0;
 
	for (i = 0; i < len; i++) prod *= n[i];
 
	for (i = 0; i < len; i++) {
		p = prod / n[i];
		sum += a[i] * mul_inv(p, n[i]) * p;
	}
 
	return sum % prod;
}
bool miller_rabin(int n)//量竡ざ残т借计よ猭 
{
	bool is_prime=true;
	int m, k, a, b;
	for(int i=1;;i++)
	{
		if((n-1)%square_multiply(2,i)==0&&((n-1)/square_multiply(2,i))%2!=0)
		{
			m=(n-1)/square_multiply(2,i);
			k=i;
			//cout<<"m="<<m<<endl<<"k="<<k<<endl;
		}
		else if((n-1)%square_multiply(2,i)==0&&((n-1)/square_multiply(2,i))%2==0)
		{
			continue;
			//cout<<"continue"<<endl;
		}
		else
		{
			//cout<<"break"<<endl;
			break;
		}
	}
	a=rand()%(n-3)+2;
	//cout<<"a="<<a<<endl;
	b=square_multiply(a,m)%n;
	//cout<<"b="<<b<<endl;
	if(b!=1&&b!=n-1)
	{
		int i=1;
		while(i<k&&b!=n-1)
		{
			b=square_multiply(b,2)%n;
			if(b==1)
			is_prime=false;
			i=i+1;
		}
		if(b!=n-1)
		is_prime=false;
	}
	//cout<<is_prime<<endl;
	return is_prime;
}
int gcd(int m, int n) //т程そ计 
{
    while(n != 0) 
	{ 
        int r = m % n; 
        m = n; 
        n = r; 
    } 
    return m;
}
int RSA(int input)//RSA盞 
{
	int a=getPrime();
	int b=getPrime();
	int n=a*b;
	int phi=(a-1)*(b-1);
	int e;
	int d;
	for(int i=2;i<phi;i++)
	{
		if(gcd(i, phi)==1)
		{
			e=i;
			break;
		}
	}
	for(int i=2;i<phi;i++)
	{
		if((i*e)%phi==1)
		{
			d=i;
			break;
		}
	}
	cout<<"Prime1 ="<<a<<endl;
	cout<<"Prime2 ="<<b<<endl;
	cout<<"Public key e ="<<e<<endl;
	cout<<"Private key d ="<<d<<endl;
	return square_multiply(input, e)%n;
}
int getPrime()//眔借计 
{
	int prime;
	while(true)
	{
		prime=rand()%100000000;
		if(miller_rabin(prime))
		{
			break;
		}
	}
	return prime;
}
