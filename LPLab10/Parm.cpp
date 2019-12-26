#include "stdafx.h"
using namespace std;
namespace Parm {
	PARM getparm(int argc, _TCHAR* argv[]) {
		PARM *p = new PARM;
		bool in=false, out= false, log= false;
		for (int i = 1; i < argc; i++)
		{
			if (wcslen(argv[i]) > PARM_MAX_SIZE)
				throw ERROR_THROW(104);
			wchar_t *pos = wcsstr(argv[i], PARM_IN);
			if (pos != NULL)
			{
				in = true;
				pos += wcslen(PARM_IN);
				wcscpy_s(p->in, pos);
				continue;
			}
			pos = wcsstr(argv[i], PARM_OUT);
			if (pos != NULL)
			{
				out = true;
				pos += wcslen(PARM_OUT);
				wcscpy_s(p->out, pos);
				continue;
			}
			pos = wcsstr(argv[i], PARM_LOG);
			if (pos != NULL)
			{
				log = true;
				pos += wcslen(PARM_LOG);
				wcscpy_s(p->log, pos);
				continue;
			}
			
		}
		if (!in) 
			throw ERROR_THROW(100);
		if (!out) {
			wcscpy_s(p->out, p->in);
			wcscat_s(p->out, L"out.txt");
		}
		if (!log) {
			wcscpy_s(p->log, p->in);
			wcscat_s(p->log, L"log.txt");
		}
		return *p;
	}
}