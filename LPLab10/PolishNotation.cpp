#include "stdafx.h"
#include <stack>
namespace PN {
	LT::LexTable PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable) {
		stack <LT::Entry> op;
		stack <LT::Entry> res;
		LT::Entry end;
		bool flag = true;
		end.lexema = '|';
		op.push(end);
		bool func = false;
		int k = lextable_pos, j = 0;
		LT::LexTable str = LT::Create(LT_MAXSIZE);
		LT::LexTable buff = LT::Create(LT_MAXSIZE);
		while (lextable.table[k].lexema!= LEX_SEMICOLON)
		{
			str.table[j] = lextable.table[k];
			k++;
			j++;
		}
		str.table[j].lexema = '|';
		for (int i = 0; i < j+1; i++) {
			if (str.table[i].lexema == LEX_ID) {
				if (idtable.table[str.table[i].idxTI].idtype == IT::F) {
					func = true;
				}
			}
			if (func) {
				if (str.table[i].lexema == LEX_LITERAL || str.table[i].lexema == LEX_ID) {
					res.push(str.table[i]);
				}
				else if (str.table[i].lexema == LEX_RIGHTTHESIS) {
					LT::Entry entryLT = writeEntry(entryLT, '@', LT_TI_NULLIDX, 0);
					res.push(entryLT);
					func = false;
				}
			}
			else if (str.table[i].lexema == LEX_LITERAL || str.table[i].lexema == LEX_ID) {
				res.push(str.table[i]);
			}
			else if (str.table[i].lexema == LEX_OPERATOR) {
				if (idtable.table[(str.table[i].idxTI)].id[0] == LEX_OR) {
					if (op.top().lexema == '|' || op.top().lexema == LEX_LEFTTHESIS)
						op.push(str.table[i]);
					else {
						res.push(op.top());
						op.pop();
						i--;
					}
				}
				else if (idtable.table[(str.table[i].idxTI)].id[0] == LEX_AND  || idtable.table[(str.table[i].idxTI)].id[0] == LEX_XOR) {
					//if (op.top().lexema == '|' || idtable.table[op.top().idxTI].id[0] == LEX_OR || op.top().lexema == LEX_LEFTTHESIS)
							//op.push(str.table[i]);
					if (op.top().lexema == LEX_LEFTTHESIS)
						op.push(str.table[i]);
					else if (op.top().lexema == '|')
						op.push(str.table[i]);
					else if (op.top().lexema == LEX_OPERATOR)
						if (idtable.table[op.top().idxTI].id[0] == LEX_OR)
							op.push(str.table[i]);
					else {
						res.push(op.top());
						op.pop();
						i--;
					}
				}
			}
			else if (str.table[i].lexema == LEX_NOT) {
				res.push(str.table[i]);
			}
			else if (str.table[i].lexema == LEX_LEFTTHESIS)
				op.push(str.table[i]);
			else if (str.table[i].lexema == LEX_RIGHTTHESIS)
				if (op.top().lexema == '|') {
					flag = !flag;
					break;
				}
			else if (op.top().lexema == LEX_LEFTTHESIS)
				op.pop();
			else {
				res.push(op.top());
				op.pop();
				i--;
			}
			else if (str.table[i].lexema == '|') {
				if (op.top().lexema == '|')
					break;
				else if (str.table[i].lexema == LEX_LEFTTHESIS) {
					flag = !flag;
					break;
				}
				else {
					res.push(op.top());
					op.pop();
					i--;
				}
			}
		}
		j = 0;
		if (flag)
			while (res.size()) {
				buff.table[j] = res.top();
				res.pop();
				j++;
			}
		else
			cout << "Error";
		buff.size = j;
		return buff;
	}
}









//#include "stdafx.h"
//#include <stack>
//namespace PN {
//	bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable) {
//		stack <int> op;
//		stack <int> res;
//		bool flag = true;
//		int k = lextable_pos, j = 0;
//		LT::LexTable str = LT::Create(LT_MAXSIZE);
//		while (lextable.table[k].lexema != ';')
//		{
//			str.table[j] = lextable.table[k];
//			k++;
//			j++;
//		}
//		str.table[j].lexema = '|';
//		op.push('|');
//		for (int i = 0; i <= j; i++)
//		{
//			if (str.table[i].lexema == 'i' || str.table[i].lexema == 'l') {
//				res.push(str.table[i].lexema);
//
//			}
//			else if (str.table[i].lexema == 'v') {
//				if (idtable.table[(str.table[i].idxTI)].id[0] == (unsigned)'+' || idtable.table[(str.table[i].idxTI)].id[0] == (unsigned)'-' || idtable.table[(str.table[i].idxTI)].id[0] == (unsigned)'%') {
//					if (op.top() == '|' || op.top() == '(')
//						op.push(idtable.table[(str.table[i].idxTI)].id[0]);
//					else {
//						res.push(op.top());
//						op.pop();
//						i--;
//					}
//				}
//				else if (idtable.table[(str.table[i].idxTI)].id[0] == (unsigned)'*' || idtable.table[(str.table[i].idxTI)].id[0] == (unsigned)'/' || idtable.table[(str.table[i].idxTI)].id[0] == (unsigned)'&') {
//					if (op.top() == '|' || op.top() == '+' || op.top() == '-' || op.top() == '(')
//						op.push(idtable.table[(str.table[i].idxTI)].id[0]);
//					else if (op.top() == '*' || op.top() == '/') {
//						res.push(op.top());
//						op.pop();
//						i--;
//					}
//				}
//			}
//			else if (str.table[i].lexema == '(')
//				op.push(str.table[i].lexema);
//			else if (str.table[i].lexema == ')')
//				if (op.top() == '|') {
//					flag = !flag;
//					break;
//				}
//				else if (op.top() == '(')
//					op.pop();
//				else {
//					res.push(op.top());
//					op.pop();
//					i--;
//				}
//			else if (str.table[i].lexema = '|')
//			{
//				if (op.top() == '|')
//					break;
//				else if (str.table[i].lexema == '(') {
//					flag = !flag;
//					break;
//				}
//				else
//				{
//					res.push(op.top());
//					op.pop();
//					i--;
//				}
//			}
//		}
//		string s;
//		if (flag)
//			while (res.size()) {
//				s += (char)res.top();
//				res.pop();
//			}
//		else
//			cout << "Error";
//		std::reverse(s.begin(), s.end());
//		cout << s;
//		return flag;
//	}
//}