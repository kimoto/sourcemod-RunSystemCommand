#if defined _runsystemcommand_included
 #endinput
#endif
#define _runsystemcommand_included

native RunSystemCommand(String:cmd[], String:arg[], String:dest[], length);

/**
 * Do not edit below this line!
 */
public Extension:__ext_runsystemcommand = 
{
	name = "runsystemcommand",
	file = "runsystemcommand.ext",
#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
	required = 1,
#else
	required = 0,
#endif
};

