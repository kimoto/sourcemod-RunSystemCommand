sourcemod-RunSystemCommand
==========================

Run External Program SourceMod Extension 

Native Function
---------------
    native RunSystemCommand(String:cmd[], String:arg[], String:dest[], length);

SYNOPSYS
--------
    decl String:buffer[256];
    RunSystemCommand("echo", "hello world!", buffer, sizeof(buffer));
    LogMessage(buffer);
      => hello world!

    decl String:buffer[256];
    RunSystemCommand("ls", "-al", buffer, sizeof(buffer));
    LogMessage(buffer);
      => (your current directory file list)

Example
-------
    ./scripting/runsystemcommand_example.sp

