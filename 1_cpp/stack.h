

class mystack
{
public:
	static int count;
	const int max_size;
private:
	int top;
	int* data;

public:
	mystack(int size = 1024);
	~mystack();
	
	static int getcount();

	mystack& operator<<(int value)
	{
		push(value);
		return *this;
	}

	mystack& operator>>(int& value)
	{
		value = pop();
		return *this;
	}

	void init();
	int isempty();
	void push(int value);
	int pop();
};

