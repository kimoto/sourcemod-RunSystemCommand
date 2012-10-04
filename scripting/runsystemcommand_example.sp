#pragma semicolon 1
#include <sourcemod>
#include <runsystemcommand>
#define PLUGIN_VERSION "1.0.0"

public Plugin:myinfo =  
{
  name = "test",
  author = "kimoto",
  description = "test",
  version = PLUGIN_VERSION,
  url = "http://kymt.me/"
};

public OnPluginStart()
{
  RegServerCmd("system", Command_System, "Execute System Command", ADMFLAG_RCON);
}

public Action:Command_System(args)
{
  new String:cmd[256];
  if(args >= 1){
    GetCmdArg(1, cmd, sizeof(cmd));
  }else{
    LogMessage("invalid argument");
    return;
  }

  new String:arg[256];
  if(args >= 2){
    GetCmdArgString(arg, sizeof(arg));
    Format(arg, sizeof(arg), "%s", arg[strlen(cmd) + 1]);
  }

  decl String:dest[1024];
  RunSystemCommand(cmd, arg, dest, sizeof(dest));
  PrintToServer(dest);
}
