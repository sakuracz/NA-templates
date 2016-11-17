template<typename T>				// declaration for TD;
class TD;							// TD == "type displayer"

template<typename T>				// template w/types
void f(T& param)					// of interest
{
	TD<T> tType;					// cause T to be shown
	TD<decltype(param)> paramType;	// ditto for params's type
}


int main()
{
	int j = 1;
	const int &i = j;
	f(i);
}