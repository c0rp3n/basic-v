#pragma once

#include <cstdint>

namespace bv
{
    /// <summary>
    /// Value for each of the lexemes.
    /// </summary>
    enum struct Lexeme : uint64_t
    {
        /// <summary>
        /// Data Type String, a squence of chars surround by "".
        /// </summary>
        String,
        /// <summary>
        /// Data Type Real, two sets of numbers seperated by a period.
        /// </summary>
        Real,
        /// <summary>
        /// Data Type Interger, a seriries of numeric chars.
        /// </summary>
        Integer,
        /// <summary>
        /// Variable or Section Identifier, starts with an alphabetic char then can be followed by numbers or underscores.
        /// </summary>
        Identifier,
        /// <summary>
        /// Syntax Comma, seperates values.
        /// </summary>
        Comma,
        /// <summary>
        /// Syntax Colon.
        /// </summary>
        Colon,
        /// <summary>
        /// Syntax Semi Colon.
        /// </summary>
        SemiColon,
        /// <summary>
        /// Syntax Open Bracket ('(').
        /// </summary>
        OpenBracket,
        /// <summary>
        /// Syntax Close Bracket (')').
        /// </summary>
        CloseBracket,
        /// <summary>
        /// Syntax Open Bracket ('{').
        /// </summary>
        OpenBrace,
        /// <summary>
        /// Syntax Close Bracket ('}').
        /// </summary>
        CloseBrace,
        /// <summary>
        /// Operator Assign ('='), assigns the rhs to the variable on the lhs.
        /// </summary>
        Assign,
        /// <summary>
        /// Operator Addition ('+'), add the lhs and rhs.
        /// </summary>
        Addition,
        /// <summary>
        /// Operator Subtraction ('-'), subtract the rhs from the lhs.
        /// </summary>
        Subtraction,
        /// <summary>
        /// Operator Multiply ('*'), multiply the lhs by the rhs.
        /// </summary>
        Multiply,
        /// <summary>
        /// Operator Divide ('/'), divide the lhs by the rhs.
        /// </summary>
        Divide,
        /// <summary>
        /// Operator Equal to ('=='), compare the lhs too the rhs.
        /// </summary>
        Equal,
        /// <summary>
        /// Operator Greater than ('&gt;'), compares the lhs too the rhs.
        /// </summary>
        GreaterThan,
        /// <summary>
        /// Operator Greater than or Equal to ('&gt;='), compares the lhs too the rhs.
        /// </summary>
        GreaterThanOrEqual,
        /// <summary>
        /// Operator Less than or Equal to ('&lt;'), compares the lhs too the rhs.
        /// </summary>
        LessThan,
        /// <summary>
        /// Operator Less than or Equal to  ('&lt;='), compares the lhs too the rhs.
        /// </summary>
        LessThanOrEqual,
        /// <summary>
        /// Function Absolute, returns the absolute value of the passed variable.
        /// </summary>
        Abs,
        /// <summary>
        /// Keyword And, performs the bitwise and operation between the lhs and rhs.
        /// </summary>
        And,
        /// <summary>
        /// Keyword Call, calls the function located on the rhs.
        /// </summary>
        Call,
        /// <summary>
        /// Keyword Case, declares the start of the a case statement.
        /// </summary>
        Case,
        /// <summary>
        /// Keyword Data, declares the start of a constant piece of data, must be the first thing on a program line.
        /// </summary>
        Data,
        /// <summary>
        /// Keyword Define, pre declares a function, must be the first thing on a program line.
        /// </summary>
        Def,
        /// <summary>
        /// Keyword Divide, divides the lhs by the rhs.
        /// </summary>
        Div,
        /// <summary>
        /// Keyword Else, if statement delimiter which starts an alternate action.
        /// </summary>
        Else,
        /// <summary>
        /// Keyword End, marks an end of the program or function delimiter if followed by sub.
        /// </summary>
        End,
        /// <summary>
        /// Keyword End Case, marks an end of a case statement, must be the first thing on a program line.
        /// </summary>
        EndCase,
        /// <summary>
        /// Keyword End If, marks an end of a multi line if clause.
        /// </summary>
        EndIf,
        /// <summary>
        /// Keyword End If, marks an end of a multi line if clause.
        /// </summary>
        EndWhile,
        /// <summary>
        /// Keyword End Process, denotes the end of a procedure.
        /// </summary>
        EndProc,
        /// <summary>
        /// Keyword Exclusive Or, performs the bitwise xor operation between the lhs and rhs.
        /// </summary>
        EOr,
        /// <summary>
        /// Keyword Error, forces an error, is followed by error number and string.
        /// </summary>
        Error,
        /// <summary>
        /// Keyword Evaluate, evaluates a passed string expression.
        /// </summary>
        Eval,
        /// <summary>
        /// Keyword False, represents the boolean value false.
        /// </summary>
        False,
        /// <summary>
        /// Keyword For, declares the start of a for ... next loop, it is always executed once.
        /// </summary>
        For,
        /// <summary>
        /// Keyowrd Get, returns the next charactor from the keyboard buffer, it waits for a charactor.
        /// </summary>
        Get,
        /// <summary>
        /// Keyword Goto Subroutine, jumps to a section of the program, this should be a line number or label, the program then returns to this line.
        /// </summary>
        GoSub,
        /// <summary>
        /// Keyword Goto, jumps to a section of the program, this should be a line number or label.
        /// </summary>
        Goto,
        /// <summary>
        /// Keyword If, declares the start of an if ... then ... else statement, it maybe single or multi line.
        /// </summary>
        If,
        /// <summary>
        /// Keyword Input, a statement to input values from the keyboard.
        /// </summary>
        Input,
        /// <summary>
        /// A function that returns the position of a substring within a string.
        /// </summary>
        InStr,
        /// <summary>
        /// Function Int, returns truncates a real number to that of a floored interger.
        /// </summary>
        Int,
        /// <summary>
        /// Function Length, returns the length of the argument string.
        /// </summary>
        Len,
        /// <summary>
        /// Keyword Let, declares the assignment of a string or numeric / real variable.
        /// </summary>
        Let,
        /// <summary>
        /// Keyword Local, declares the assigment of a variable for inside of a function only.
        /// </summary>
        Local,
        /// <summary>
        /// Function Modulus, returns the signed remainder after an integer division.
        /// </summary>
        Mod,
        /// <summary>
        /// Keyword Next, delimits a for ... next loop, also has an optional control variable.
        /// </summary>
        Next,
        /// <summary>
        /// Keyword / Function Not, returns or performs the bitwise not operation on the argument or the rhs.
        /// </summary>
        Not,
        /// <summary>
        /// Keyword Of, proceeds the name of a case statements variable.
        /// </summary>
        Of,
        /// <summary>
        /// Keyword Or, performs the bitwise or operation between the lhs and rhs.
        /// </summary>
        Or,
        /// <summary>
        /// Keyword Otherwise, the optional default case of a case statement. 
        /// </summary>
        Otherwise,
        /// <summary>
        /// Function Pi, returns the const real value of Pi.
        /// </summary>
        Pi,
        /// <summary>
        /// Keyword Print, prints all of the items following it.
        /// </summary>
        Print,
        /// <summary>
        /// Keyword Private, declares a variable for private use in a function, this value shall not be reset on each function call.
        /// </summary>
        Private,
        /// <summary>
        /// Keyword Read, assigns a value from the data statements to a variable.
        /// </summary>
        Read,
        /// <summary>
        /// Keyword Remark, marks the start of a comment.
        /// </summary>
        Rem,
        /// <summary>
        /// Keyword Repeat, declares the start of a repeat ... until loop.
        /// </summary>
        Repeat,
        /// <summary>
        /// Keyword Return, returns the program to that of the last gosub or call statement.
        /// </summary>
        Return,
        /// <summary>
        /// Function Random, returns a random real or interger number.
        /// </summary>
        Rnd,
        /// <summary>
        /// Function Sign, returns −1 for negative argument, 0 for zero argument and +1 for positive argument.
        /// </summary>
        Sgn,
        /// <summary>
        /// Function Squareroot, returns the square root of its arguments
        /// </summary>
        Sqr,
        /// <summary>
        /// Keyword Step, optional statement in a for ... next loop which specifies the increment ammount.
        /// </summary>
        Step,
        /// <summary>
        /// Function To String, returns a the base 10 string form of the numeric argument.
        /// </summary>
        Str$,
        /// <summary>
        /// Function String Concatenate, returns the passed string concatenated n times.
        /// </summary>
        Sring$,
        /// <summary>
        /// Function Sum, returns the sum of an array or all of the passed values.
        /// </summary>
        Sum,
        /// <summary>
        /// Statement Swap, swaps the values of two variables.
        /// </summary>
        Swap,
        /// <summary>
        /// Statement Then, optional part of the if ... then ... else statement.
        /// </summary>
        Then,
        /// <summary>
        /// Statement To, part of the for ... to ... step loop, when the control variable exceeds that of the to the loop is terminated.
        /// </summary>
        To,
        /// <summary>
        /// Function Top, returns the first free memory location after the program.
        /// </summary>
        Top,
        /// <summary>
        /// Keyword True, represents the boolean value true.
        /// </summary>
        True,
        /// <summary>
        /// Keyword Until, delimeter of the repeat ... until loop, the code shall be executed until the following condition is met.
        /// </summary>
        Until,
        /// <summary>
        /// Function Value, returns a number from the passed numeric charactor string.
        /// </summary>
        Val,
        /// <summary>
        /// Statement Wait, causes the program to wait for the given number of centiseconds.
        /// </summary>
        Wait,
        /// <summary>
        /// Keyword When, part of a case ... endcase statement, proceeds the value(s) against which the case value shall be tested.
        /// </summary>
        When,
        /// <summary>
        /// Keyword While, declares the start of an while ... endwhile loop.
        /// </summary>
        While,
    };
}
