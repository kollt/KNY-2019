#include "stdafx.h"
namespace Error
{
	/*Серии ошибок   0-99		 системные ошибки
					 100-109	 ошибки параметров
					 110-119	 ошибки открытия и чтения файлов
	*/
	ERROR errors[ERROR_MAX_ENTRY] =  //таблица ошибок
	{
		ERROR_ENTRY(0,"Недопустимый код ошибки"), //код ошибки вне диапазона 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1,"Системный сбой"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100,"Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,"Превышена длинна входного параматра"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110,"Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111,"Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112,"Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY_NODEF(113),ERROR_ENTRY_NODEF(114),ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120),ERROR_ENTRY_NODEF10(130),ERROR_ENTRY_NODEF10(140),ERROR_ENTRY(150,"Ошибка на этапе лексического анализатора"),ERROR_ENTRY(151,"Превышена максимальная длина строки"),
		ERROR_ENTRY(152,"Слишком большое число"),ERROR_ENTRY_NODEF(153),ERROR_ENTRY_NODEF(154),ERROR_ENTRY_NODEF(155),ERROR_ENTRY_NODEF(156),
		ERROR_ENTRY_NODEF(157),ERROR_ENTRY_NODEF(158),ERROR_ENTRY_NODEF(159),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200),ERROR_ENTRY(201,"Нельзя перевести пустую строку в число"),ERROR_ENTRY(202,"Сравнение разных типов"),ERROR_ENTRY(203,""),ERROR_ENTRY(204,""),ERROR_ENTRY(205,""),
		ERROR_ENTRY(206,""),ERROR_ENTRY(207,""),ERROR_ENTRY(208,""),ERROR_ENTRY(209,""),ERROR_ENTRY(209,""),ERROR_ENTRY_NODEF10(210),ERROR_ENTRY_NODEF10(220),ERROR_ENTRY_NODEF10(230),
		ERROR_ENTRY_NODEF10(240),ERROR_ENTRY_NODEF10(250),ERROR_ENTRY_NODEF10(260),
		ERROR_ENTRY_NODEF10(270),ERROR_ENTRY_NODEF10(280),ERROR_ENTRY_NODEF10(290),
		ERROR_ENTRY_NODEF100(300),ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600,"Неверная структура программы"),
		ERROR_ENTRY(601,"Ошибочный оператор"),
		ERROR_ENTRY(602,"Ошибка в выражении"),
		ERROR_ENTRY(603,"Ошибка в параметрах функции"),
		ERROR_ENTRY(604,"Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(605,"Ошибочное выражение"),ERROR_ENTRY(606,"Ошибка в параметре функции touint"),ERROR_ENTRY(607,"Ошибка в структуре ifelse"),ERROR_ENTRY(608,"Тип функции и возвращаемый тип не совпадают"),
		ERROR_ENTRY(609,"Ошибка в параметре result"),ERROR_ENTRY(610,"Ожидалась переменная типа bool"),ERROR_ENTRY(611,"Вложенные if/else недоступны"),ERROR_ENTRY(612,"Использование не объявленной переменной"),	
		ERROR_ENTRY(613,"Несоответствие типов при присвоении"),	ERROR_ENTRY(614,"Битовые операции возможны только над переменными/литералами типа uint"),ERROR_ENTRY(615,"Повторное объявление переменной"),
		ERROR_ENTRY(616,"Объявление переменной, которая является функцией"),ERROR_ENTRY(617,"Название переменной совпадает с названием функции"),ERROR_ENTRY(618,"Неверный возвращаемый тип функции"),
		ERROR_ENTRY(619,"Функция не может возращать сама себя"),ERROR_ENTRY(620,"Количество передаваемых параметров не соответствует с описанной функцией"),ERROR_ENTRY(621,"Несоответствие типов передаваемых параметров"),
		ERROR_ENTRY(622,"Превышено количество точек входа"),ERROR_ENTRY(623,"Main не может вернуть значение"),ERROR_ENTRY(624,"Ошибка параметров функции transkate, неверный тип параметра"),
		ERROR_ENTRY(625,"Данная система счисления недоступна"),ERROR_ENTRY(626,"Нельзя объявлять переменные в блоках if/else"),ERROR_ENTRY(627,"Нет точек входа"),ERROR_ENTRY(628,"Неверная структура вызова функции"),
		ERROR_ENTRY(629,"Отрицательное число"),ERROR_ENTRY(630,"В строке могут быть только цифры"),
		ERROR_ENTRY_NODEF10(640),ERROR_ENTRY_NODEF10(650),ERROR_ENTRY_NODEF10(660),
		ERROR_ENTRY_NODEF10(670),ERROR_ENTRY_NODEF10(680),ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700),ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id)
	{
		ERROR *a = new ERROR;
		int i = 1;
		if (id > ERROR_MAX_ENTRY || id <= 0) {
			*a = errors[0];
		}
		else {
			while (id != abs(errors[i].id)) {
				i++;
			}
			*a = errors[i];
		}
		return *a;
	}
	ERROR geterrorin(int id, int line = -1)
	{
		ERROR *a = new ERROR;
		*a = geterror(id);
		a->index.line = line;
		return *a;
	}
};