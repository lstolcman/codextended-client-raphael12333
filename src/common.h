#pragma once

#include "stdafx.h"
#include <WinSock2.h>

#define MAX_MSGLEN              32768       // max length of a message, which may     

typedef enum {
	NA_BOT,
	NA_BAD,                 // an address lookup failed
	NA_LOOPBACK,
	NA_BROADCAST,
	NA_IP,
	NA_IPX,
	NA_BROADCAST_IPX
} netadrtype_t;

typedef enum {
	NS_CLIENT,
	NS_SERVER
} netsrc_t;

typedef struct
{
	netadrtype_t type;
	union
	{
		int _ip;
		unsigned char ip[4];
	};
	unsigned char ipx[10];
	unsigned short port;
} netadr_t;

typedef enum
{
	ERR_FATAL,				// exit the entire game with a popup window
	//ERR_VID_FATAL,		// exit the entire game with a popup window and doesn't delete profile.pid
	ERR_DROP,				// print to console and disconnect from game
	ERR_SERVERDISCONNECT,	// don't kill server
	ERR_DISCONNECT,			// client disconnected from the server
	ERR_NEED_CD,			// pop up the need-cd dialog
	ERR_AUTOUPDATE
} errorParm_t;

typedef void(*Com_Printf_t)(const char*, ...);
extern Com_Printf_t Com_Printf;
typedef void(*Com_DPrintf_t)(const char *, ...);
extern Com_DPrintf_t Com_DPrintf;
typedef void(*Com_Error_t)(int, const char*, ...);
extern Com_Error_t Com_Error;

typedef void(*xfunc)(void);

typedef void(*Cmd_AddCommand_t)(const char*, xfunc);
typedef void(*Cmd_RemoveCommand_t)(const char*);
extern Cmd_AddCommand_t Cmd_AddCommand;
extern Cmd_RemoveCommand_t Cmd_RemoveCommand;

typedef int(*FS_CreatePath_t)(const char *OSPath);
extern FS_CreatePath_t FS_CreatePath;
typedef int (*FS_ComparePaks_t)(char *neededpaks, int len, int dlstring);
extern FS_ComparePaks_t FS_ComparePaks;
typedef int(*FS_ReadFile_t)(const char *qpath, void **buffer);
extern FS_ReadFile_t FS_ReadFile;

char *FS_BuildOSPath(const char *base, const char *game, const char *qpath);
char *va(char *format, ...);
int Q_vsnprintf(char *dest, int size, const char *fmt, va_list argptr);