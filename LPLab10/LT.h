#pragma once
#include "stdafx.h"
#include "Log.h"
#define LEXEMA_FIXSIZE	1			// ������������� ������ �������
#define LT_MAXSIZE		4096		// ������������ ���������� ����� � ������� ������
#define LT_TI_NULLIDX	0xfffffff	// ��� �������� ������� ���������������
#define LEX_UNIC     	'u'	// ������� ��� unsigned integer
#define LEX_BOOL		'b'	// ������� ��� BOOL
#define LEX_CHAR		'h'	// ������� ��� CHAR
#define LEX_ID			'i'	// ������� ��� ��������������
#define LEX_LITERAL		'l'	// ������� ��� ��������
#define LEX_FUNCTION	'f'	// ������� ��� function
#define LEX_DECL	    'd'	// ������� ��� Decl
#define LEX_RT		    'r'	// ������� ��� rt
#define LEX_PRINT		'p'	// ������� ��� print
#define LEX_GENL	    'g'	// ������� ��� Genl
#define LEX_IF		    'o' // ������� ��� =
#define LEX_ELSE		'e' // ������� ��� =
#define LEX_SEMICOLON	';'	// ������� ��� ;
#define LEX_COMMA		','	// ������� ��� ,
#define LEX_LEFTWALL	'['	// ������� ��� [
#define LEX_RIGHTWALL	']'	// ������� ��� [
#define LEX_LEFTBRACE	'{'	// ������� ��� {
#define LEX_BRACELET	'}'	// ������� ��� }
#define LEX_LEFTTHESIS	'('	// ������� ��� (
#define LEX_RIGHTTHESIS	')'	// ������� ��� )
#define LEX_CONVERT	    'h'	// ������� ��� touint
#define LEX_AND		    '&'	// ������� ��� &
#define LEX_OR		    '%'	// ������� ��� %
#define LEX_NOT		    '~'	// ������� ��� ~
#define LEX_PLUS		'+'	// ������� ��� +
#define LEX_MIN		    '-'	// ������� ��� -
#define LEX_XOR		    '^'	// ������� ��� ^
#define LEX_OPERATOR	'v'	// ������� ��� ����������
#define LEX_EQUAL		'=' // ������� ��� =
#define LEX_CMP 'n'

namespace LT		// ������� ������
{
	struct Entry	// ������ ������� ������
	{
		unsigned char lexema;	// �������
		int sn;							// ����� ������ � �������� ������
		int idxTI;						// ������ � ������� ��������������� ��� LT_TI_NULLIDX
	};

	struct LexTable						// ��������� ������� ������
	{
		int maxsize;					// ������� ������� ������ < LT_MAXSIZE
		int size;						// ������� ������ ������� ������ < maxsize
		Entry* table;					// ������ ����� ������� ������
	};

	LexTable Create(		// ������� ������� ������
		int size			// ������� ������� ������ < LT_MAXSIZE
	);

	void Add(				// �������� ������ � ������� ������
		LexTable& lextable,	// ��������� ������� ������
		Entry entry			// ������ ������� ������
	);

	Entry GetEntry(			// �������� ������ ������� ������
		LexTable& lextable,	// ��������� ������� ������
		int n				// ����� ���������� ������
	);

	void Delete(LexTable& lextable);	// ������� ������� ������ (���������� ������)

	Entry writeEntry(					// ��������� ������ ������� ������
		Entry& entry,
		unsigned char lexema,
		int indx,
		int line
	);

	void showTable(LexTable lextable, Log::LOG& log);	// ����� ������� ������
};