#pragma once

#include <cstdint>
#include <string>

namespace bv
{
	enum struct Token : uint64_t
	{
		/// <summary>
		/// Returns the absolute value of the passed variable.
		/// </summary>
		ABS,
		AND,
		CALL,
		CASE,
		DATA,
		DEF,
		DIV,
		ELSE,
		END,
		ENDCASE,
		ENDIF,
		ENDWHILE,
		ENDPROC,
		EOR,
		ERROR,
		EVAL,
		FALSE,
		FOR,
		GET,
		GOSUB,
		GOTO,
		IF,
		INPUT,
		INSTR,
		INT,
		LEN,
		LET,
		LOCAL,
		MOD,
		NEXT,
		NOT,
		OF,
		OR,
		OTHERWISE,
		PI,
		PRINT,
		PRIVATE,
		READ,
		REM,
		REPEAT,
		RETURN,
		RND,
		SGN,
		SQR,
		STEP,
		STR$,
		STRING$,
		SUM, 
		SWAP,
		THEN,
		TO,
		TOP,
		TRUE,
		UNTIL,
		VAL,
		WAIT,
		WHEN,
		WHILE,
	};
}
