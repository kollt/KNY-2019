#include "stdafx.h"

namespace In
{

	IN getin(wchar_t infile[], wchar_t outfile[])
	{
		int currentLine = 0, currentCol = 0;
		IN info{ 0, 0, 0, nullptr, IN_CODE_TABLE };					//uniform инициализация (альтернатива == списки инициализации)
		std::ifstream in(infile);									//открывает файл для чтения
		std::ofstream out(outfile);									//открывает файл для записи
		if (!out.is_open())											//проверка на открытие файла иначе ошибка
			throw ERROR_THROW(110);
		if (!in.is_open())											//проверка на открытие файла иначе ошибка
			throw ERROR_THROW(110);
		std::string fulltext;
		std::string temp;
		while (!in.eof())											//пока открыт файл
		{
			info.lines++;											//считаем кол-во линий
			std::getline(in, temp);									//запись строки в tеmp
			temp += "\n";											//знак окончания строки
			fulltext += temp;
		}
		info.text = new unsigned char[fulltext.size()];			//выделяем память для текста
		unsigned char * ptmp = info.text;							//указатель на участок пямати
		for (int i = 0; i < fulltext.size(); ++i)
		{
			if (info.code[(unsigned char)fulltext[i]] == IN::F) //Если символ является запрещённым => ошибка
			{
				throw ERROR_THROW_IN(111, currentLine, currentCol)
			}
			else if (info.code[(unsigned char)fulltext[i]] == IN::I) // Если символ является игнорируемым 
				++info.ignor;
			else if (info.code[(unsigned char)fulltext[i]] == IN::T || info.code[(unsigned char)fulltext[i]] == IN::S)// Если разрешенный символ 
			{
				*ptmp = fulltext[i];
				++ptmp;
			}
			else													//Если не указан символ ,  увелич счетчик игнорируемых элементов на 1
			{
				*ptmp = info.code[(unsigned char)fulltext[i]];
				++ptmp;
			}
			if (fulltext[i] == '\n')								//если конец строки, увелич счетчик строки на 1 
			{
				++currentLine;
				currentCol = 0;
			}
			else
				++currentCol;
		}
		*ptmp = IN_CODE_ENDL;//признак конца строки

		int size = 0;
		while (info.text[size] != '\0') {
			size++;
		}
		info.size = size;
		info.size = strlen((char*)info.text);			//количество символо = количество всех элем - \n
		out.close();
		in.close();
		return info;
	}
}