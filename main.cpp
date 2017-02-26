#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
typedef long long ll;

void print(vector<ll> a);

vector <ll> set_number()
{
	vector <ll> big;
	string temp, stemp;
	for(int i=0; i<18; i++)
	{
		big.push_back(0);
	}

	getline (cin,temp);
	ll m;
	int len = temp.length();
	int s = 0;


	while(len >= 9)
	{
		stemp = temp.substr(s,9);
		m = stoll (stemp,NULL,10);
		s+=9;
		len -=9;
		big.push_back(m);
		big.erase(big.begin());
	}

	stemp = temp.substr(s,len);
		m = stoll (stemp,NULL,10);
		big.push_back(m);
		big.erase(big.begin());
		return big;
}


int size(ll a)
{
	int digits = 0;
	if (a == 0)
		digits = 1;
	while (a)
	{
		a /= 10;
		digits++;
	}
	return digits;
}

void print(vector<ll> a)
{
	int j = 0;
	while (a[j]==0)
	{
		j++;
	}
	int digits;
	for(int i=j; i<17; i++)
	{	// get number of digits in the ll
		 digits = size(a[i]);

		//check if length <9 ==> there is zeros missing
		if(i!=j && i != 0 && i != 17 && digits < 9)
		{
			for (int j=digits; j<9; j++)
				cout << "0";
		}
		cout << a[i] ;
	}
	//last element
	//int	digits= size(a[17]);

	digits = size(a[17]);

	for (int j=digits; j<2; j++)
	{
		//don't add left zero if the last element is the only element
		int l = 0;
		for(int i=0; i<=17;i++)
		{
			if (a[i]==0)
				l++;
		}
		if (l!=17)
			cout << "0";
	}
		cout << a[17] << endl;
}

vector<ll> add(vector<ll> b, vector<ll>a)
{
	vector<ll> result;
	ll temp, carry;

	for(int i=0; i<18; i++)
		{
			result.push_back(0);
		}
	carry = 0;
	for(int i=17; i>=0; i--)
	{

		temp = a[i] + b[i] + carry;

		if (i==17)
		{
			//length of both last elements in the two vectors
			int l_len = (size(a[17])) >= (size(b[17])) ? (size(a[17])) : (size(b[17]));

			//makes sure there is no overflow in number of digits of last element
			string x = "";
			for(int i=0; i<l_len; i++)
			{
				x += "9";
			}

			int nines = atoi(x.c_str());

			if(temp > nines)
			{
				carry = 1;
				temp = temp - (nines + 1);
			}
			else
				carry = 0;
			result[i] = temp;
		}

		else if (i == 0)
			result[i] = temp;


		else if (i<17)
		{
			if (temp > 999999999)
			{
				carry = 1;
				temp = temp - 1000000000;
			}
			else
				carry = 0;
			result[i] = temp;
		}

	}
	return result;
}

vector<ll> sub(vector<ll> a, vector<ll> b)
{
	vector<ll> result;
	ll temp;
	for(int i=0; i<18; i++)
	{
		result.push_back(0);
	}

	for(int i=17; i>=0; i--)
	{
		temp = a[i] - b[i];
		if(i==0)
			result[i] = temp;
		else if(i<17)
		{
			if(temp<0)
			{
				ll carry = 1000000000;
				a[i-1] -= 1;
				a[i] +=carry;
				result[i] = a[i]-b[i];
			}
			else
				result[i] = temp;
		}
		else if (i==17)
		{
			int l_len = (size(a[17])) >= (size(b[17])) ? (size(a[17])) : (size(b[17]));


				//carry of last element
				string x = "1";
				for(int i=0; i<l_len; i++)
				{
					x += "0";
				}

				int carry = atoi(x.c_str());

			if(temp<0)
			{
				a[i-1] -= 1;
				a[i] +=carry;
				result[i] = a[i]-b[i];
			}
			else
				result[i] = temp;
		}
	}
	return result;
}

vector <ll> mul(vector<ll> a, vector<ll> b)
{
	vector<ll> result, sum;
	ll temp;

	for(int i=0; i<18; i++)
	{
		result.push_back(0);
	}
	for(int i=0; i<18; i++)
	{
		sum.push_back(0);
	}


	int l_len = (size(a[17])) >= (size(b[17])) ? (size(a[17])) : (size(b[17]));


	ll carry = 0;
	for(int i=17; i>=0; i--)
	{
		for(int j=17; j>=0; j--)
		{
			temp = a[i] * b[j];
			if( i==17 && j == 17 && size(carry)>2)
			{
				carry = temp/100;
				temp = temp-(carry*100);
			}
			else if(size(carry) > 9)
			{
				carry = temp/1000000000;
				temp = temp-(carry * 1000000000);
			}
			result[j] = temp + carry;

		}
		sum = add(result, sum);
	}
	return sum;
}


int main()
{
	vector<ll> a,b;

	a = set_number();
	b = set_number();
	vector<ll> result = mul(a,b);
	print(result);




	return 0;
}
