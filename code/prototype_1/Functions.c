#include "Functions.h"

bool RunPrintName(struct Option opt)
{
	if(opt.OptionName != "")
		printf("%s", opt.OptionName);
	else
		return FALSE;

return TRUE;
}
