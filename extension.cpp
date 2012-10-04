/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod RunSystemCommand Extension
 * Copyright (C) 2004-2008 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#include "extension.h"

/**
 * @file extension.cpp
 * @brief Implement extension code here.
 */
RunSystemCommand g_RunSystemCommand;		/**< Global singleton for extension's main interface */
SMEXT_LINK(&g_RunSystemCommand);

cell_t RunSystemCommand(IPluginContext *pContext, const cell_t *params);
std::string *execute(const char *command, const char *arg);

sp_nativeinfo_t Natives[] = 
{
  {"RunSystemCommand",  RunSystemCommand},
  {NULL,      NULL},
};

void RunSystemCommand::SDK_OnAllLoaded()
{
  sharesys->AddNatives(myself, Natives);
}

cell_t RunSystemCommand(IPluginContext *pContext, const cell_t *params)
{
  char *cmd;
  pContext->LocalToString(params[1], &cmd);
  g_pSM->LogMessage(myself, "input command: %s", cmd);

  char *arg;
  pContext->LocalToString(params[2], &arg);
  g_pSM->LogMessage(myself, "input args: %s", arg);

  std::string *result = execute(cmd, arg);
  pContext->StringToLocal(params[3], params[4], result->c_str());
  delete result;
  return 1;
}

std::string *execute(const char *command, const char *arg)
{
  std::string *input = new std::string();

  // fd[0] = read
  // fd[1] = write
  int fd[2];
  pipe(fd);
  pid_t pid = fork();
  if(pid == -1){
    perror("Error");
    exit(EXIT_FAILURE);
  }

  sigignore(SIGCLD);
  if(pid == 0){
    close(STDOUT_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    execlp(command, command, arg, NULL);
    perror("execlp error");
    exit(0);
  }else{
    int status = 0;
    //printf("waiting for child process\n");
    waitpid(pid, &status, WUNTRACED);
    /*
    printf("status: %d\n", status);
    if(WIFEXITED(status)){
      printf("exit status = %d\n", WEXITSTATUS(status));
    }else{
      printf("exit abnormally\n");
    }
    */
    close(fd[1]);
    char buff[256]="";
    while(true){
      int num = read(fd[0], buff, 256);
      if(num == -1){
        perror("reading error!!");
        return NULL;
      }
      if(num == 0){
        return input;
      }
      *input += buff;
    }
  }
}

