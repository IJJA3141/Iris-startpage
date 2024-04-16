#pragma once

// debugger
#define DEBUGGER_UNINITIALIZED "[LUA DEBUGGER] Debugger used before it was initialized"

// lua config
#define ERROR_LUA_CONFIG_NOT_A_TABLE "[LUA CONFIG] config should be a table !"
#define ERROR_LUA_CONFIG_BOOLEAN(NAME) "[LUA CONFIG] " + NAME + " should be a boolean"
#define ERROR_LUA_CONFIG_STRING(NAME) "[LUA CONFIG] " + NAME + " should be a string"
#define ERROR_LUA_CONFIG_NUMBER(NAME) "[LUA CONFIG] " + NAME + " should be a number"
