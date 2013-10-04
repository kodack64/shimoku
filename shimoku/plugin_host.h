#ifndef _PLUGIN_HOST_H
#define _PLUGIN_HOST_H

#include "plugin.h"

typedef Plugin* (CALLBACK* FUNC_CREATE_INSTANCE)(void);
typedef void (CALLBACK* FUNC_DESTROY_INSTANCE)(void);
typedef void (CALLBACK* FUNC_GET_NAME)(char*);

#endif _PLUGIN_HOST_H