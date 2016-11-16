/* 
Template type deduction:
	General problem:

	template<typename T>
	void f(ParamType param);
	f(expr);					// deduce T and ParamType from expr
								// T - the deduced type; ParamType - often different from T (e.g. const T&)

	Three general cases:
	1) ParamType is a reference or pointer, but not a universal reference
	2) ParamType is a universal reference
	3) ParamType is neither reference nor pointer

	Ad 1) {
		template<typename T>
		void f(T& param);

			  int  x = 22;		// int
		const int  cx = x;		// copy of int
		const int& rx = x;		// ref to const view of int

		f(x);					// T == int; param's type == int&
		f(cx);					// T == const int; param's type == const int&
		f(rx);					// T == const int; param's type == const int&
		=========================================================================

		template<typename T>
		void f(const T& param);

			  int  x = 22;		// int
		const int  cx = x;		// copy of int
		const int& rx = x;		// ref to const view of int

		f(x);					// T == int; param's type == const int&
		f(cx);					// T == const int; param's type == const int&
		f(rx);					// T == const int; param's type == const int&
		=========================================================================

		template<typename T>
		void f(T* param);

			  int  x = 22;		// int
		const int* pcx = x;		// ptr to const view of int

		f(&x);					// T == int; param's type == int*
		f(pcx);					// T == const int; param's type == const int*	
		=========================================================================
!!!		Same works for auto:
			  int  x = 22;		// as before
		const int  cx = x;		// as before
		const int& rx = x;		// as before

		auto& v1 = x;			// v1's type == int& (auto == int)
		auto& v2 = cx;			// v2's type == const int& (auto == const int)
		auto& v3 = rx;			// v3's type == const int& (auto == const int)

		const auto& v4 = x;		// v4's type == const int& (auto == int)
		const auto& v5 = cx;	// v5's type == const int& (auto == const int)
		const auto& v6 = rx;	// v6's type == const int& (auto == const int)
	}
	Ad 2) {						// universal references
		template<typename T>
		void f(T&& param);		// Treated like 'normal' reference parameters, except:
								// if expr is lvalue with deduced type E, T deduced as E&
								// => reference-collapsing yields type E& for param.

			  int  x = 22;		// as before
		const int  cx = x;		// as before
		const int& rx = x;		// as before

		f(x);					// x is lvalue => T == int&, param's type == int &
		f(cx);					// cx is lvalue => T == const int&, param's type == const int&
		f(rx);					// rx is lvalue => T == const int&, param's type == const int&
		f(22);					// 22 is rvalue => no special handling; T == int, param's type == int&&
	}
	Ad 3) {						// by-value parameters
		template<typename T>
		void f(T param);		// As before, if expr's type is a reference, ignore that
								// if expr is const or volatile, ignore that
								// T is the result

			  int  x = 22;		// as before
		const int  cx = x;		// as before
		const int& rx = x;		// as before

		f(x);					// T == int, param's type == int 
		f(cx);					// T == int, param's type == int
		f(rx);					// T == int, param's type == int
		=========================================================================
!!!		Non-reference non-pointer autos:
			  int  x = 22;		// as before
		const int  cx = x;		// as before
		const int& rx = x;		// as before

		auto v1 = x;			// v1's type == int (auto == int)
		auto v2 = cx;			// v2's type == int (auto == int)
		auto v3 = rx;			// v3's type == int (auto == int)

		//Again, expr's reference-/const-qualifiers always dropped in deducing T
		// - auto never deduced to be reference
		// -- It must be manually added
		// --- if present, use by-reference rulesets
		auto v4 = rx;			// v4's type == int
		auto& v5 = rx;			// v5's type == const int&
		auto&& v6 = rx;			// v6's type == const int& (rx is lvalue)
	}


	================================================================================
	const exprs vs. exprs containing const

	void someFunc(const int * const param1,			//const ptr to const
				  const int *	    param2,			//ptr to const
					    int *       param3)			//ptr to non-const
	{
		auto p1 = param1;			// p1's type == const int * (param1's constness ignored)
		auto p2 = param2;			// p2's type == const int *
		auto p3 = param3;			// p3's type == int *
	}

	From earlier:
	+ if expr is const or volatile, ignore that

	Commonly phrased as:
	+ Top-level const/volatile is ignored (only applied to passed by value - passed by ref doesn't get ignored)

	=========================================================================================
	=========================================================================================
	Lambda Capture Type Deduction:
1)	{
		const int cx = 0;
		auto lam = [cx] {};
		...
	}
	//corresponds to hidden class:
	class UpToTheCompiler11 {
	private:
		const int cx;		// by value -> yet cv qualifiers are retained (although totally independent copy)
		...
	};
	=====================================================================================
2)	{
		const int cx = 0;
		auto lam = [cx = cx]{ ... };	// "init-capture"
		...
	}
	//corresponds to hidden class:
	class UpToTheCompiler14 {
	private:
		int cx;
	}
	=====================================================================================
3)	{
	int cx = 0;
	auto lam = [cx] {};
	...
	}
	//corresponds to hidden class:
	class UpToTheCompiler11 {
	public:
		void operator()() const { cx = 10; }		// error because const operator
	private:
		int cx;		// by value -> yet cv qualifiers are retained (although totally independent copy)
	...
	};
	=====================================================================================
4)	{
	const int cx = 0;
	auto lam = [cx] mutable { cx = 10; }
	...
	}
	//corresponds to hidden class:
	class UpToTheCompiler {
	public:
		void operator()() { cx = 10; }	// no const operator because mutable
	private:
		const int cx;		// by value -> yet cv qualifiers are retained (although totally independent copy)
	...
	};
	=====================================================================================
	=====================================================================================
	Checking if deduced types are those which we think they are:
			
	template<typename T>				// declaration for TD;
	class TD;							// TD == "type displayer"

	template<typename T>				// template w/types
	void f(T& param)					// of interest
	{
		TD<T> tType;					// cause T to be shown
		TD<decltype(param)> paramType;	// ditto for params's type
		...
	}

	Compilation will fail and the compiler will throw the type of T and param
	============================================================================
	============================================================================
	decltype(auto) f(x)
	{
		return retVal;			// returns type like int
	}

	decltype(auto) f'(x)
	{
		return (retVal);		// returns ref to retVal e.g. int& - which may be local - disaster!!
	}
	auto f''(x)					// auto never deduces reference type for auto