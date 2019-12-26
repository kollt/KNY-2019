#include "stdafx.h"


unsigned char** Devider(In::IN in)		// формирование массива строк, состоящего из лексем
{
	unsigned char** word = new unsigned char* [max_world];
	for (int i = 0; i < max_world; i++)
		word[i] = new unsigned char[size_world] {NULL};
	bool Lit = false;
	int j = 0;
	for (int i = 0, k = 0; i < in.size; i++, k++)
	{
		if (in.text[i] == '\'')
			Lit = !Lit;
		if (in.text[i] == '\'' && !Lit) {
			word[j][k] = in.text[i];
			word[j][k + 1] = IN_CODE_ENDL;
			j++;
			k = -1;
			continue;
		}
		if (in.text[i] != ' ' && in.code[(unsigned char)in.text[i]] != In::IN::S || Lit)
			word[j][k] = in.text[i];
		else if (in.code[(unsigned char)in.text[i]] == In::IN::S) {
			if (k > 0) {
				word[j][k] = IN_CODE_ENDL;
				j++;
			}
			word[j][0] = in.text[i];
			word[++j][1] = IN_CODE_ENDL;
			k = -1;
		}
		else {
			word[j][k] = IN_CODE_ENDL;
			j++;
			k = -1;
		}
	}
	for (int i = 0; i < j; i++)
		if (word[i][0] == '\0') {
			for (int k = i; k < j - 1; k++)
				word[k] = word[k + 1];
			j--;
			i--;
		}
	word[j] = NULL;
	return word;
}