#include "stdafx.h"


#define DIV '|'
#define SPACE ' '
#define PLUS '+'
#define MINUS '-'
#define STAR '*'
#define DIRSLASH '/'
#define EQUAL '='

using namespace std;

namespace Lex
{

	LEX lexAnaliz(Log::LOG log, In::IN in)
	{
		LEX lex;
		LT::LexTable lextable = LT::Create(LT_MAXSIZE);
		IT::IdTable idtable = IT::Create(TI_MAXSIZE);
		IT::Entry entryIT;

		unsigned char** word = new unsigned char* [max_world];
		for (int i = 0; i < max_world; i++)
			word[i] = new unsigned char[size_world] {NULL};
		do {
			word = Devider(in);
		} while (word == NULL);

		int indxLex = 0;		// индекс лексемы
		int indexID = 0;		// индекс идент.
		int clit = 1;			// счетчик литералов
		int line = 1;			// номер строки
		int position = 0;			// номер позиции в исходном файле

		unsigned char emptystr[] = "";	// пустая строка
		unsigned char* lvl = new unsigned char[10]{ "" };	// текущий уровень
		unsigned char* tmplvl = new unsigned char[10]{ "" };	// временный уровень
		unsigned char* prevlvl = new unsigned char[10]{ "" };	// предыдущий уровень
		unsigned char* L = new unsigned char[2]{ "L" };
		unsigned char* bufL = new unsigned char[TI_STR_MAXSIZE];
		unsigned char* nameLiteral = new unsigned char[10]{ "" };
		char* charclit = new char[10]{ "" };		// для строковой записи счетчика

		bool Func = false; //флаг для функции
		bool Parm = false; //флаг для параметров


		unsigned char* tr = new unsigned char[2];
		tr[0] = '1';
		tr[1] = '\0';
		unsigned char* fls = new unsigned char[2];
		fls[0] = '0';
		fls[1] = '\0';
		unsigned char** bools = new unsigned char* [2];
		for (int i = 0; i < 2; i++)
			bools[i] = new unsigned char[size_world] {NULL};
		bools[0] = (unsigned char*)"true";
		bools[1] = (unsigned char*)"false";
		int i = 0;
		while (word[i]) {
			if (*(word[i]) == *(bools[0]) && *(word[i] + 1) == *(bools[0] + 1) && *(word[i] + 2) == *(bools[0] + 2) && *(word[i] + 3) == *(bools[0] + 3))
				word[i] = tr;
			else if (*(word[i]) == *(bools[1]) && *(word[i] + 1) == *(bools[1] + 1) && *(word[i] + 2) == *(bools[1] + 2) && *(word[i] + 3) == *(bools[1] + 3) && *(word[i] + 4) == *(bools[1] + 4))
				word[i] = fls;
			i++;
		}
		for (int i = 0; word[i] != NULL; i++, indxLex++)
		{

			bool findSameID = false;

			FST::FST fstLet(word[i], FST_DECL);
			if (FST::execute(fstLet))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_DECL, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstCmp(word[i], FST_CMP);
			if (FST::execute(fstCmp))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_CMP, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstTypeUint(word[i], FST_UNIC);
			if (FST::execute(fstTypeUint))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_UNIC, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);

				entryIT.iddatatype = IT::UNIC; //описываю тип данных идентификатора(численный)
				continue;
			}
			FST::FST fstTypeBool(word[i], FST_BOOL);
			if (FST::execute(fstTypeBool))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_BOOL, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);

				entryIT.iddatatype = IT::BOOL; //описываю тип данных идентификатора(численный)
				continue;
			}
			FST::FST fstIf(word[i], FST_IIIIFFFFF);
			if (FST::execute(fstIf))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_IF, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstConvert(word[i], FST_CONVERT);
			if (FST::execute(fstConvert))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_CONVERT, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstElse(word[i], FST_EIIFF);
			if (FST::execute(fstElse))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_ELSE, LT_TI_NULLIDX, line); //собираю 'запісь'
				LT::Add(lextable, entryLT); //добавляю в таблицу литералов запись
				continue;
			}
			FST::FST fstTypeChar(word[i], FST_CH);
			if (FST::execute(fstTypeChar))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_CHAR, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);

				entryIT.iddatatype = IT::CR; //описываю тип данных идентификатора(строковый)
				_mbscpy(entryIT.value.vstr.str, emptystr); //сразу инициализирую дефолтным значением(пустой строкой)
				continue;
			}
			FST::FST fstFunction(word[i], FST_FUNC);
			if (FST::execute(fstFunction))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_FUNCTION, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				entryIT.idtype = IT::F; //описываю тип идентификатора(функция)
				Func = true; //ставю флаг функции в true
				continue;
			}
			FST::FST fstResult(word[i], FST_RT);
			if (FST::execute(fstResult))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_RT, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstShow(word[i], FST_PRINT);
			if (FST::execute(fstShow))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_PRINT, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstMain(word[i], FST_GENL);
			if (FST::execute(fstMain))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_GENL, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				_mbscpy(prevlvl, lvl); // переношу обасть в предыдущую (из которой ушёл)
				_mbscpy(lvl, word[i]); //захожу в новую область
				continue;
			}
			FST::FST fstIdentif(word[i], FST_ID);
			if (FST::execute(fstIdentif))
			{
				// поиск такого же
				if (Func)	// если функция
				{
					int idx = IT::IsId(idtable, word[i]);	// ищем без лвл
					if (idx != TI_NULLIDX)		// если такой идентификатор уже есть
					{
						LT::Entry entryLT = writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						Func = false; //'выключаем' флаг
						continue;
					}
				}
				else
				{
					int idx = IT::IsId(idtable, word[i]);	// ищем без лвл, а потом с лвл'ом
					if (idx != TI_NULLIDX)		// если такой идентификатор уже есть
					{
						LT::Entry entryLT = writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						Func = false; //'выключаем' флаг
						continue;
					}
					_mbscpy(tmplvl, lvl); //заходім во временныую область
					word[i] = _mbscat(tmplvl, word[i]);
					idx = IT::IsId(idtable, word[i]); //проверяю налічіе id в таблице
					if (idx != TI_NULLIDX)		// если такой идентификатор уже есть
					{
						LT::Entry entryLT = writeEntry(entryLT, LEX_ID, idx, line);
						LT::Add(lextable, entryLT);
						continue;
					}
				}
				LT::Entry entryLT = writeEntry(entryLT, LEX_ID, indexID++, line);
				LT::Add(lextable, entryLT);
				if (Parm) {		// если параметр
					entryIT.idtype = IT::P; //ставлю тип id(параметр)
				}
				else if (!Func) {	// если переменная
					entryIT.idtype = IT::V; //ставлю тип id(литерал)
					if (entryIT.iddatatype == IT::UNIC) //проверяю тип данных id, если инт
						entryIT.value.vint = TI_INT_DEFAULT; //еслі int, то ставлю дефолтом 0
					if (entryIT.iddatatype == IT::CR) {//проверяю тип данных id, если строка
						entryIT.value.vstr.len = 0;//еслі string,то ставлю длинну 0
						memset(entryIT.value.vstr.str, TI_STR_DEFAULT, sizeof(char)); //задаю дефолтное значеніе для строки
					}
				}
				else {		// если функция
					_mbscpy(prevlvl, lvl);
					_mbscpy(lvl, word[i]);
				}

				entryIT.idxfirstLE = indxLex;
				_mbscpy(entryIT.id, word[i]); //записываю в запись название идентификатора
				IT::Add(idtable, entryIT); //заношу запись в таблицу идентификаторов
				Func = false;
				continue;
			}
			FST::FST fstLiteralInt(word[i], FST_INTLIT);
			if (FST::execute(fstLiteralInt))
			{
				if (_mbslen(word[i]) > 10) {
					throw ERROR_THROW_IN(152, line);
				}
				int length = _mbslen(word[i]);
				long long value = 0, max = 4294967295;
				for (int k = 0; k < length; k++) {
					switch (word[i][k])
					{
					case '0':
						value += 0;
						break;
					case '1':
						value += 1 * pow(10, length - k - 1);
						break;
					case '2':
						value += 2 * pow(10, length - k - 1);
						break;
					case '3':
						value += 3 * pow(10, length - k - 1);
						break;
					case '4':
						value += 4 * pow(10, length - k - 1);
						break;
					case '5':
						value += 5 * pow(10, length - k - 1);
						break;
					case '6':
						value += 6 * pow(10, length - k - 1);
						break;
					case '7':
						value += 7 * pow(10, length - k - 1);
						break;
					case '8':
						value += 8 * pow(10, length - k - 1);
						break;
					case '9':
						value += 9 * pow(10, length - k - 1);
						break;
					default:
						break;
					}
					if (value > max) {
						throw ERROR_THROW_IN(152, line);
					}
				}
				// поиск такого же
				for (int k = 0; k < idtable.size; k++)
				{
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L)
					{
						LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lextable, entryLT);
						findSameID = true;
						break;
					}
				}
				if (findSameID)	// если был найден такой же
					continue;
				LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lextable, entryLT);
				entryIT.idtype = IT::L;
				entryIT.system = 10;
				entryIT.iddatatype = IT::UNIC;
				entryIT.value.vint = value;
				entryIT.idxfirstLE = indxLex;
				// формирование имени литерала
				_itoa_s(clit++, charclit, sizeof(char) * 10, 10);	// преобразуем значение счетчика в строку(charclit)
				_mbscpy(bufL, L);	// помещаем в буфер "L"
				word[i] = _mbscat(bufL, (unsigned char*)charclit);	// формируем имя для литерала
				_mbscpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				continue;
			}
			FST::FST fstBinary(word[i], FST_BINARY);
			if (FST::execute(fstBinary))
			{
				long long value = 0;
				int length = _mbslen(word[i]);
				for (int k = length - 1; k > 0; k--)	// перезапись массива, убираем кавычки
					word[i][k] = word[i][k - 1];
				length = _mbslen(word[i]);
				for (int k = 0; k < length; k++)	// перезапись массива, убираем кавычки
					word[i][k] = word[i][k + 1];
				length = _mbslen(word[i]);
				if (_mbslen(word[i]) > 32) {
					throw ERROR_THROW_IN(152, line);
				}
				long long max = 4294967295;
				for (int k = 0; k < length; k++) {
					if (word[i][k] == '1') {
						value += pow(2, length - k - 1);
					}
					if (value > max) {
						throw ERROR_THROW_IN(152, line);
					}

				}
				// поиск такого же
				for (int k = 0; k < idtable.size; k++)
				{
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L)
					{
						LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lextable, entryLT);
						findSameID = true;
						break;
					}
				}
				if (findSameID)	// если был найден такой же
					continue;
				LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lextable, entryLT);
				entryIT.idtype = IT::L ;
				entryIT.iddatatype = IT::UNIC ;
				entryIT.value.vint = value ;
				entryIT.system = 2 ;
				entryIT.idxfirstLE = indxLex;
				// формирование имени литерала
				_itoa_s(clit++, charclit, sizeof(char) * 10, 10);	// преобразуем значение счетчика в строку(charclit)
				_mbscpy(bufL, L);	// помещаем в буфер "L"
				word[i] = _mbscat(bufL, (unsigned char*)charclit);	// формируем имя для литерала
				_mbscpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				continue;
			}
			FST::FST fstOctal(word[i], FST_OCTAL);
			if (FST::execute(fstOctal))
			{
				long long value = 0;
				int length = _mbslen(word[i]);
				for (int k = length - 1; k > 0; k--)	// перезапись массива, убираем кавычки
					word[i][k] = word[i][k - 1];
				length = _mbslen(word[i]);
				for (int k = 0; k < length; k++)	// перезапись массива, убираем кавычки
					word[i][k] = word[i][k + 1];
				length = _mbslen(word[i]);
				long long tmp = 0;
				long long max = 4294967295;
				if (_mbslen(word[i]) > 11) {
					throw ERROR_THROW_IN(152, line);
				}
				for (int k = 0; k < length; k++) {
					switch (word[i][k])
					{
					case '0':
						value += 0;
						break;
					case '1':
						value += 1 * pow(8, length - k - 1);
						break;
					case '2':
						value += 2 * pow(8, length - k - 1);
						break;
					case '3':
						value += 3 * pow(8, length - k - 1);
						break;
					case '4':
						value += 4 * pow(8, length - k - 1);
						break;
					case '5':
						value += 5 * pow(8, length - k - 1);
						break;
					case '6':
						value += 6 * pow(8, length - k - 1);
						break;
					case '7':
						value += 7 * pow(8, length - k - 1);
						break;
					default:
						break;
					}
					if (value > max) {
						throw ERROR_THROW_IN(152, line);
					}
				}
				// поиск такого же
				for (int k = 0; k < idtable.size; k++)
				{
					if (idtable.table[k].value.vint == value && idtable.table[k].idtype == IT::L)
					{
						LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lextable, entryLT);
						findSameID = true;
						break;
					}
				}
				if (findSameID)	// если был найден такой же
					continue;
				LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lextable, entryLT);
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::UNIC;
				entryIT.value.vint = value;
				entryIT.system = 8;
				entryIT.idxfirstLE = indxLex;
				// формирование имени литерала
				_itoa_s(clit++, charclit, sizeof(char) * 10, 10);	// преобразуем значение счетчика в строку(charclit)
				_mbscpy(bufL, L);	// помещаем в буфер "L"
				word[i] = _mbscat(bufL, (unsigned char*)charclit);	// формируем имя для литерала
				_mbscpy(entryIT.id, word[i]);
				IT::Add(idtable, entryIT);
				continue;
			}
			FST::FST fstLiteralString(word[i], FST_STRLIT);
			if (FST::execute(fstLiteralString))
			{
				// запись значения
				int length = _mbslen(word[i]);
				for (int k = 0; k < length; k++)	// перезапись массива, убираем кавычки
					word[i][k] = word[i][k + 1];
				word[i][length - 2] = 0;
				// поиск такого же
				for (int k = 0; k < idtable.size; k++)
				{
					if (!(_mbscmp(idtable.table[k].value.vstr.str, word[i])))
					{
						findSameID = true;
						LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, k, line);
						LT::Add(lextable, entryLT);
						break;
					}
				}
				if (length > 255) {
					throw ERROR_THROW_IN(151, line);
				}
				if (findSameID)	// если был найден такой же
					continue;
				LT::Entry entryLT = writeEntry(entryLT, LEX_LITERAL, indexID++, line);
				LT::Add(lextable, entryLT);
				_mbscpy(entryIT.value.vstr.str, word[i]);	// запись значиния строкового литерала
				entryIT.value.vstr.len = length - 2;		// запись длины строкового литерала
				entryIT.idtype = IT::L;
				entryIT.iddatatype = IT::STRING;
				entryIT.idxfirstLE = indxLex;
				// формирование имени литерала
				_itoa_s(clit++, charclit, sizeof(char) * 10, 10);	// преобразуем значение счетчика в строку(charclit)
				_mbscpy(bufL, L);	// помещаем в буфер "L"
				nameLiteral = _mbscat(bufL, (unsigned char*)charclit);	// формируем имя для литерала (L + charclit)
				_mbscpy(entryIT.id, nameLiteral);
				IT::Add(idtable, entryIT);
				continue;
			}
			FST::FST fstOperator(word[i], FST_OPERATOR);
			if (FST::execute(fstOperator))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_OPERATOR, indexID++, line);
				LT::Add(lextable, entryLT);
				_mbscpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = indxLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				continue; 
			}
			FST::FST fstNot(word[i], FST_NOT);
			if (FST::execute(fstNot))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_NOT, indexID++, line);
				LT::Add(lextable, entryLT);
				_mbscpy(entryIT.id, word[i]);
				entryIT.idxfirstLE = indxLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				continue;
			}
			FST::FST fstSemicolon(word[i], FST_SEMICOLON);
			if (FST::execute(fstSemicolon))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_SEMICOLON, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstComma(word[i], FST_COMMA);
			if (FST::execute(fstComma))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_COMMA, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstLeftBrace(word[i], FST_LEFTBRACE);
			if (FST::execute(fstLeftBrace))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_LEFTBRACE, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstRightBrace(word[i], FST_BRACELET);
			if (FST::execute(fstRightBrace))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_BRACELET, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstRightWall(word[i], FST_RIGHTWALL);
			if (FST::execute(fstRightWall))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_RIGHTWALL, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstLeftWall(word[i], FST_LEFTWALL);
			if (FST::execute(fstLeftWall))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_LEFTWALL, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstLeftThesis(word[i], FST_LEFTTHESIS);
			if (FST::execute(fstLeftThesis))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_LEFTTHESIS, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				if (idtable.table[indexID - 1].idtype == IT::F) //проверяю предыдуўий id, функция ли она
					Parm = true; //ставлю флаг Parm в true
				continue;
			}
			FST::FST fstRightThesis(word[i], FST_RIGHTTHESIS);
			if (FST::execute(fstRightThesis))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_RIGHTTHESIS, LT_TI_NULLIDX, line);
				if (Parm && word[i + 1][0] != LEX_LEFTBRACE && word[i + 2][0] != LEX_LEFTBRACE)		// если после функции нет {
					_mbscpy(lvl, prevlvl);		// возвращаем предыдущую обл. видимости
				Parm = false;
				LT::Add(lextable, entryLT);
				continue;
			}
			FST::FST fstEqual(word[i], FST_EQUAL);
			if (FST::execute(fstEqual))
			{
				LT::Entry entryLT = writeEntry(entryLT, LEX_EQUAL, LT_TI_NULLIDX, line);
				LT::Add(lextable, entryLT);
				continue;
			}
			position += _mbslen(word[i]);
			if (word[i][0] == DIV) { //если мы встретили |(переход на новыю строку)
				line++;
				position = 0;
				indxLex--;
				continue;
			}
			throw ERROR_THROW_IN(150, line);
		}
		lex.idtable = idtable;
		lex.lextable = lextable;
		return lex;
	}
}