#pragma once
#include <vector>
#include <sstream>
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
		BufferManager() { clear(); }

		std::wstring GetStrValue()
		{
			std::wstring str;
			str += (isNagative ? L"-" : L"");
			for (auto&c : buffer)
				str += c;
			return str;
		}

		double getValue()
		{
			return _wtof(GetStrValue().c_str()) * (isNagative?-1:1);
		}

		bool AppendNumber(int number)
		{
			if (number < 0 || number>9)
				return false;
			else
			{
				buffer.push_back(L'0' + number);
				return true;
			}
		}

		bool AppendPoint()
		{
			if (HasPoint(GetStrValue()))
				return false;
			buffer.push_back(L'.');
			return true;
		}

		//改变正负
		void switchPosNag()
		{
			isNagative = !isNagative;
		}

		bool popBack()
		{
			if (buffer.empty())
				return false;

			buffer.pop_back();

			return true;
		}

		void clear()
		{
			buffer.clear();
			isNagative = false;
		}

		void TrimZeroTail(std::wstring& s)
		{
			if (s.empty())
				return;

			if (HasPoint(s))
			{
				std::wstring s2 = s;
				size_t i = s2.find_last_not_of(L'0');
				s2 = s2.substr(0, i+1);

				if (s2.back() == L'.')
					s2.pop_back();
				s = s2;
			}
		}


	private:
		bool HasPoint(std::wstring& str)
		{
			for (auto& c : str)
			{
				if (c == L'.')
					return true;
			}
			return false;
		}

	private:
		std::vector<wchar_t> buffer;
		bool isNagative;
	};


	class Calculator {
	public:
		Calculator() { clear(); }

		bool AddNumber(double value)
		{
			ExpressionUnit u;
			u.value = value;
			u.isOperator = false;

			if (expression.empty())
			{
				expression.push_back(u);
			}
			else
			{
				if (expression.back().isOperator)
					expression.push_back(u);
				else
					return false;
			}

			return false;
		}

		bool AddOperator(Operator op)
		{
			ExpressionUnit u;
			u.op = op;
			u.isOperator = true;

			if (expression.empty())
			{
				ExpressionUnit u0;
				u0.value = 0.0;
				u0.isOperator = false;
				expression.push_back(u0);

				expression.push_back(u);
			}
			else
			{
				if (expression.back().isOperator)
				{
					expression.pop_back();
				}

				expression.push_back(u);
			}

			isCurrentOp = true;

			return false;
		}

		bool IsCurrentOp()
		{
			return isCurrentOp;
		}
		void SetCurrentOpStatus(bool value)
		{
			isCurrentOp = value;
		}

		std::wstring GetExpressionString()
		{
			if (expression.empty())
				return L"";

			std::vector<ExpressionUnit> exp = expression;
			//if (exp.back().isOperator)
			//	exp.pop_back();

			std::wstring str;
			for (auto& e : exp)
			{
				std::wstring s;
				if (e.isOperator)
				{
					switch (e.op)
					{
					case Operator::add: s = L"+"; break;
					case Operator::subtraction: s = L"-"; break;
					case Operator::multipli: s = L"*"; break;
					case Operator::division: s = L"/"; break;
					default:
						break;
					}
				}
				else
				{
					s = doubleToPerfectString(e.value);
				}
				str += L" ";
				str += s;
			}

			return str;
		}

		double GetResult()
		{
			double value = 0;
			Operator op = Operator::add;

			for (auto& u : expression)
			{
				if (u.isOperator)
					op = u.op;
				else
				{
					switch (op)
					{
					case Operator::add: value += u.value; break;
					case Operator::subtraction: value -= u.value; break;
					case Operator::multipli: value *= u.value; break;
					case Operator::division: value /= u.value; break;
					default:
						break;
					}
				}
			}

			return value;
		}

		void clear()
		{
			expression.clear();
			buffer.clear();
			isCurrentOp = false;
		}

		std::wstring doubleToPerfectString(double v)
		{
			wchar_t str[1024];
			swprintf_s(str, L"%f", v);
			std::wstring s = str;
			buffer.TrimZeroTail(s);
			return s;
		}

		void SaveLastResult(std::wstring& s)
		{
			lastResult = s;
		}

		BufferManager buffer;

	private:
		std::vector<ExpressionUnit> expression;
		bool isCurrentOp;

		std::wstring lastResult = L"0";
	};

}