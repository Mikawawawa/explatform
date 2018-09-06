#ifndef __ONECONSOLE_H
#define __ONECONSOLE_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "oneGUI.h"

typedef struct
{
	int (*init)(void);
	void (*write)(const char *);
	void (*write_line)(const char *);
	int (*print)(char *fmt, ...);
	void (*clear)(void);
}consoleInfoTypedef;

extern consoleInfoTypedef console;

#endif /* __ONECONSOLE_H */
