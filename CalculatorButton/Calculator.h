#pragma once
#include <vector>
namespace benson
{
	enum Operator {
		add, subtraction, multipli, division
	};

	class ExpressionUnit {
	public:
		double value;
		Operator op;
		bool isOperator;
	};

	class BufferManager {
	public:

		std::wstring GetStrValue()
		{
			return L"";
		}

		bool AppendNumber(int number)
		{
			return false;
		}

		bool AppendPoint()
		{
			return false;
		}

		//改变正负
		void switchPosNag()
		{

		}

		bool popBack()
		{
			return false;
		}

		void clear()
		{

		}

	private:
		bool HasPoint()
		{
			return false;
		}

	private:
		std::vector<char> buffer;
		bool isNagative;
	};


	class Calulator {
	public:
		bool AddNumber(double value)
		{
			return false;
		}

		bool AddOperator(Operator op)
		{
			return false;
		}

		bool IsCurrentOp()
		{
			return false;
		}

		std::wstring GetExpressionString()
		{

			return L"";
		}

		double GetResult()
		{
			return 0.0;
		}

		void clear()
		{
			expression.clear();
			buffer.clear();
		}

		BufferManager buffer;

	private:

		std::vector<ExpressionUnit> expression;

	};

}