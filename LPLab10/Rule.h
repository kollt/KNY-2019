#pragma once
#include "stdafx.h"
#define GRB_ERROR_SERIES 600
#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	Greibach greibach(
		NS('S'), // стартовый символ
		TS('$'), //дно стека      
		9,									  // количество правил
		Rule(
			NS('S'),
			GRB_ERROR_SERIES + 0,    // неверная структура программы
			22,                                // 
			Rule::Chain(6, TS('g'), TS('{'), NS('N'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(14, TS('u'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('C'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('u'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('C'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(14, TS('h'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('C'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('h'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('C'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(14, TS('b'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('C'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('b'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('C'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(14, TS('u'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), TS('r'), NS('C'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('u'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), TS('r'), NS('C'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(14, TS('h'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), TS('r'), NS('C'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('h'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), TS('r'), NS('C'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(14, TS('b'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), TS('r'), NS('C'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('b'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), TS('r'), NS('C'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(5, TS('g'), TS('{'), NS('N'), TS('}'), TS(';')),
			Rule::Chain(5, TS('g'), TS('{'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(13, TS('u'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('r'), NS('C'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(12, TS('u'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('r'), NS('C'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(13, TS('h'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('r'), NS('C'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(12, TS('h'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('r'), NS('C'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(13, TS('b'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('r'), NS('C'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(12, TS('b'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('r'), NS('C'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(4, TS('g'), TS('{'), TS('}'), TS(';'))
		),
		Rule(
			NS('N'),
			GRB_ERROR_SERIES + 1,    // конструкции в функциях
			27,
			Rule::Chain(5, TS('d'), TS('u'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(5, TS('d'), TS('b'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(5, TS('d'), TS('h'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(7, TS('d'), TS('u'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(7, TS('d'), TS('b'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(7, TS('d'), TS('h'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(6, TS('d'), TS('u'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(6, TS('d'), TS('b'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(6, TS('d'), TS('h'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(9, TS('i'), TS('='), TS('n'), TS('('), NS('C'), TS(','), NS('C'), TS(')'), TS(';')),
			Rule::Chain(10, TS('i'), TS('='), TS('n'), TS('('), NS('C'), TS(','), NS('C'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), TS('h'), NS('C'), TS(';')),
			Rule::Chain(6, TS('i'), TS('='), TS('h'), NS('C'), TS(';'), NS('N')),
			Rule::Chain(2, TS('o'), NS('Q')),
			Rule::Chain(4, TS('d'), TS('u'), TS('i'), TS(';')),
			Rule::Chain(4, TS('d'), TS('b'), TS('i'), TS(';')),
			Rule::Chain(4, TS('d'), TS('h'), TS('i'), TS(';')),
			Rule::Chain(3, TS('r'), NS('C'), TS(';')),
			Rule::Chain(3, TS('r'), NS('C'), TS(';'), NS('N')),
			Rule::Chain(6, TS('c'), TS('i'), TS(','), TS('l'), TS(';'), NS('N')),
			Rule::Chain(5, TS('c'), TS('i'), TS(','), TS('l'), TS(';')),
			Rule::Chain(4, TS('p'), NS('C'), TS(';'), NS('N')),
			Rule::Chain(3, TS('p'), NS('C'), TS(';')),
			Rule::Chain(6, TS('p'), NS('C'), TS(','), TS('x'), TS(';'), NS('N')),
			Rule::Chain(5, TS('p'), NS('C'), TS(','), TS('x'), TS(';'))
		),
		Rule(
			NS('Q'),
			GRB_ERROR_SERIES + 7,    // ошибка в if
			8,                                // 
			Rule::Chain(11, TS('('), TS('i'), TS(')'), TS('['), NS('N'), TS(']'), TS('e'), TS('['), NS('N'), TS(']'), NS('N')),
			Rule::Chain(10, TS('('), TS('i'), TS(')'), TS('['), NS('N'), TS(']'), TS('e'), TS('['), NS('N'), TS(']')),
			Rule::Chain(9, TS('('), TS('i'), TS(')'), TS('['), TS(']'), TS('e'), TS('['), TS(']'), NS('N')),
			Rule::Chain(8, TS('('), TS('i'), TS(')'), TS('['), TS(']'), TS('e'), TS('['), TS(']')),
			Rule::Chain(10, TS('('), TS('i'), TS(')'), TS('['), TS(']'), TS('e'), TS('['), NS('N'), TS(']'), NS('N')),
			Rule::Chain(9, TS('('), TS('i'), TS(')'), TS('['), TS(']'), TS('e'), TS('['), NS('N'), TS(']')),
			Rule::Chain(10, TS('('), TS('i'), TS(')'), TS('['), NS('N'), TS(']'), TS('e'), TS('['), TS(']'), NS('N')),
			Rule::Chain(9, TS('('), TS('i'), TS(')'), TS('['), NS('N'), TS(']'), TS('e'), TS('['), TS(']'))
		),
		Rule(
			NS('C'),
			GRB_ERROR_SERIES + 9,    // ошибка в resulu
			2,                                // 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l'))
		),

		Rule(
			NS('D'),
			GRB_ERROR_SERIES + 2,    // ошибка в resulu
			4,                                // 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M'))
		),
		Rule(
			NS('E'),
			GRB_ERROR_SERIES + 2,    // ошибка в выражении
			9,                                // 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(3, TS('i'), TS('('), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))
		),
		Rule(
			NS('F'),
			GRB_ERROR_SERIES + 3,    // ошибка в параметрах функции
			6,                                // 
			Rule::Chain(2, TS('u'), TS('i')),
			Rule::Chain(2, TS('b'), TS('i')),
			Rule::Chain(2, TS('h'), TS('i')),
			Rule::Chain(4, TS('u'), TS('i'), TS(','), NS('F')),
			Rule::Chain(4, TS('b'), TS('i'), TS(','), NS('F')),
			Rule::Chain(4, TS('h'), TS('i'), TS(','), NS('F'))
		),
		Rule(
			NS('W'),
			GRB_ERROR_SERIES + 4,    // ошибка в параметрах вызываемой функции 
			4,                                // 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(
			NS('M'),
			GRB_ERROR_SERIES + 5,    // оператор
			4,								  //
			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(2, TS('~'), NS('M')),
			Rule::Chain(1, TS('~')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M'))
		)
	);
}