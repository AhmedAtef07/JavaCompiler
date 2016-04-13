# JavaCompiler
Syntax Directed Translation Scheme to convert Java code to Java bytecode, performing necessary lexical, syntax and static semantic analysis (such as type checking and Expressions Evaluation).

Generated
bytecode must follow the standard bytecode instructions defined in
Java Virtual Machine Specification

[http://java.sun.com/docs/books/jvms/second_edition/html/VMSpecTOC.doc.html](http://java.sun.com/docs/books/jvms/second_edition/html/VMSpecTOC.doc.html)

[http://en.wikipedia.org/wiki/Java_bytecode](http://en.wikipedia.org/wiki/Java_bytecode)

Different phases are not necessarily sequential and may be
interleaved for better performance.

####### Phase1: [In Progress]
Lexical Analyzer Generator

**Objective**

This phase of the assignment aims to practice techniques for building
automatic lexical analyzer generator tools.

####### 
Description

Your
task in this phase of the assignment is to design and implement a
lexical analyzer generator tool.

The lexical analyzer generator is required to automatically construct
a lexical analyzer from a regular expression description of a set of
tokens. The tool is required to construct a nondeterministic finite
automata (NFA) for the given regular expressions, combine these NFAs
together with a new starting state, convert the resulting NFA to a
DFA, minimize it and emit the transition table for the reduced DFA
together with a lexical analyzer program that simulates the resulting
DFA machine.

The generated lexical analyzer has to read its input one character at
a time, until it finds the longest prefix of the input, which matches
one of the given regular expressions. It should create a symbol table
and insert each identifier in the table. If more than one regular
expression matches some longest prefix of the input, the lexical
analyzer should break the tie in favor of the regular expression
listed first in the regular specifications. If a match exists, the
lexical analyzer should produce the token class and the attribute
value. If none of the regular expressions matches any

input prefix, an error recovery routine is to be called to print an
error message and to continue looking for tokens.

The
lexical analyzer generator is required to be tested using the given
lexical rules of tokens
of a small subset of Java. Use the given simple program to test the
generated lexical
analyzer.

Keep in mind that the generated lexical analyzer will integrate with
a generated parser which you should implement in phase 2 of the
assignment such that the lexical analyzer is to be called by the
parser to find the next token.

**Lexical
Rules**

- The
	tokens of the given language are: identifiers, numbers,keywords, operators
	and punctuationsymbols. 
- The
	token id matches a letter followed by zero or more letters ordigits. 
- The
	token num matches an unsigned integer or a floating- point number.
	The number consists of one or more decimal digits, an optional
	decimal point followed by one or more digits and an optional
	exponent consisting of an E followed by one or moredigits. 
- Keywordsarereserved.Thegivenkeywordsare:int,float,boolean,if,else,while. 

•
Operators are: +, -, *, /, =, &lt;=, &lt;, &gt;, &gt;=, !=, ==

- Punctuation
	symbols are parentheses, curly brackets, commas andsemicolons. 
- Blanks
	between tokens areoptional. 

**Lexical
Rules Input File Format**

- Lexical
	rules input file is a textfile. 
- Regular
	definitions are lines in the form LHS =RHS 
- Regular
	expressions are lines in the form LHS:RHS 
- Keywords
	are enclosed by { } in separatelines. 
- Punctuations
	are enclosed by [ ] in separatelines 
- \L
	represents Lambdasymbol. 
- The
	following symbols are used in regular definitions and regular
	expressionswith
	the meaning discussed in class: - | + * () 
- Any
	reserved symbol needed to be used within the language, is preceded
	byan
	escape backslashcharacter. 

####### 

Input file example for the above
lexical rules:

letter
= a-z | A-Z digit = 0 - 9

id:
letter (letter|digit)* digits = digit+

{Boolean
int float}

num:
digit+ | digit+ . digits ( \L | E digits) relop: \=\= | !\= | &gt; |
&gt;\= | &lt; | &lt;\= assign:
\=

{
if else while } [;, \( \) { }]

addop:
\+ | \- mulop: \* | /

**Lexical
Analyzer Output File Format**

Your program should output the transition table of the generated
lexical analyzer in a format of your choice as well as recognized
token classes one per line (like the following format).

Output file example for the following test program:

int

id

,

id

,

id

,

id

;

while

(

id

relop

num

)

... to be continued
