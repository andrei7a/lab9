#include<iostream> 
int  MAX = 10;
int MIN = 0;
using namespace std;

template<class Type>
class  Set {
	
public:
	
	class Error_index{
	public:
		int index;
		Error_index(int i) :index(i) {}
	};
	class Divide_by_zero{};
	class Big_num{};
	class Small_num{};



	Type *mass = (Type*)malloc(0); 
	int num = 0;

	Set() {}

	template <class Type>
	Set(int num, Type n ...)
	{
		
		Type *temp = &n;

		for (int i = 0; i < num; i++)
		{
			mass = (Type*)realloc(mass, sizeof(Type)*(++this->num));
			mass[this->num - 1] = *temp;
			temp++;
		}
	}

	friend ostream& operator << (ostream& output, Set& temp)
	{
		for (int i = 0; i < temp.num; i++)
		{
			output << temp.mass[i] << " ";
		}
		return output;
	}


	friend void operator >> <Type>(istream& input, Set&	temp)
	{
		Type *N = (Type*)malloc(0);
		int n = 0;
		
		Type tempInt = 0;
	
		input >> tempInt;
			
		do
		{
			try 
			{
				if (tempInt > MAX)
				{
					throw Big_num();
				}
				if (tempInt < MIN)
				{
					throw Small_num();
				}
				N = (Type*)realloc(N, sizeof(Type)*++n);
				N[n - 1] = tempInt;
				input >> tempInt;
			}
			catch(Big_num)
			{
				cout << "Very big number" << endl;
				input >> tempInt;
			}
			catch (Small_num)
			{
				cout << "Very small number" << endl;
				input >> tempInt;
			}
		} 
		while (tempInt != -1);
		temp.mass = N;
		temp.num = n;
	}


	template <class Type> friend void operator += (Set& temp, Type tempNum)
	{
		temp.mass = (Type*)realloc(temp.mass, sizeof(Type)*++temp.num);
		temp.mass[temp.num - 1] = tempNum;
	}





	friend  Set  operator + <Type>(Set<Type>& x, Set<Type>& y) {
		Set<Type> temp(x);
		bool flag = 0;
		for (int i = 0; i < y.num; i++)
		{
			for (int j = 0; j < x.num; j++)
			{
				if (y.mass[i] == x.mass[j])
				{
					flag = 1;
				}
			}
			if (flag == 0)
			{
				temp += y.mass[i];
			}
			else
			{
				flag = 0;
			}
		}
		return temp;
	}

	operator int()
	{
		return this->num;
	}



	Type &operator[] (int i) {
		if (i >= this->num) { throw Error_index(i);}
		return this->mass[i];
	}

	friend  bool  operator <= (Set& x, Set& y) {
		bool flag = 0;
		bool globalFlag = 1;
		for (int i = 0; i < y.num; i++)
		{
			for (int j = 0; j < x.num; j++)
			{
				if (y.mass[i] == x.mass[j])
				{
					flag = 1;
				}
			}
			if (flag == 0) { globalFlag = 0; }
			else { flag = 0; }
		}

		for (int i = 0; i < x.num; i++)
		{
			for (int j = 0; j < y.num; j++)
			{
				if (x.mass[i] == y.mass[j])
				{
					flag = 1;
				}
			}
			if (flag == 0) { globalFlag = 0; }
			else { flag = 0; }
		}

		return globalFlag;
	}
};


template <class Temp>
Temp avg(Set<Temp>& x)
{
	Temp sum = 0;
	for (int i = 0; i < x.num; i++)
	{
		sum += x.mass[i];
	}
	if (x.num == 0)throw Set<Temp>::Divide_by_zero();
	return (sum / x.num);
}

void main() {

	cout << "-----------Working with double-----------" << endl;
	Set<double> a;
	cin >> a;

	Set<double> b;
	cin >> b;

	Set<double> c;


	cout << endl;
	cout << "A: " << a << endl;
	cout << "B: " << b << endl;
	c = (a + b);
	cout << "A+B: " << c << endl;
	cout << "A<=B: ";
	if (a <= b)
	{
		cout << "True" << endl;
	}
	else
	{
		cout << "False" << endl;
	}
	try {
		cout << "A[3]: " << a[2] << endl;
	}
	catch (Set<double>::Error_index e) {
		cout << "Element with index " << e.index << " not found" << endl;
	}
	cout << "Int(A): " << int(a) << endl;
	cout << "AVG(A): " << avg(a);



	cout << "-----------Working with Int-----------" << endl;
	Set <int> a1;
	cin >> a1;

	Set <int> b1;
	cin >> b1;

	Set<int> c1;


	cout << endl;
	cout << "A: " << a1 << endl;
	cout << "B: " << b1 << endl;
	c1 = (a1 + b1);
	cout << "A+B: " << c1 << endl;
	cout << "A<=B: ";
	if (a1 <= b1)
	{
		cout << "True" << endl;
	}
	else
	{
		cout << "False" << endl;
	}
	try {
		cout << "A[4]: " << a1[2] << endl;
	}
	catch(Set<int>::Error_index e){
		cout << "Element with index " << e.index << " not found"<<endl;
	}

	cout << "Int(A): " << int(a1) << endl;
	try 
	{
		cout << "AVG(A): " << avg(a1);
	}
	catch (Set<int>::Divide_by_zero)
	{
		cout << "Divide by zero"<<endl;
	}
}