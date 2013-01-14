/**
*@file		App.h
*@brief		This file contains interface of function according to task 6
*			
*
*
*	Copyrights 2012 by IvanZahrodsky.
*/
#ifndef _APP_H_
#define _APP_H_

#include "stdafx.h"

using namespace Zahrodsky;

typedef unsigned char UC;


enum LexType
{
	add_, sub_, mul_, div_, negate_, pow_, mod_,
	number_, LeftBraket_, RightBraket_
};

struct Lex
{
	double val;
	LexType type;
};

/**
*@brief		This function implements interface
*@param		[void] 
*@return	void 
*/
void Run ( void );

/**
*@brief		This function scan expression from keyboard
*@param		[UC*&, UC&] 
*@return	bool 
*/
bool ScanExp ( UC*& , UC&);

/**
*@brief		This function executes lexiacal analyze of expression
*@param		[UC*, my_queue ,UC] 
*@return	bool 
*/
bool LexAnalyze ( UC*, my_queue<Lex>& , UC);

/**
*@brief		This function converts expression to postfix form
*@param		[ my_queue ] 
*@return	void
*/
void ToPostfix ( my_queue<Lex>& );

/**
*@brief		This function identifies priority of operation
*@param		[ LexType, my_stack ] 
*@return	bool
*/
bool Priority ( LexType , my_stack<Lex> & );
/**
*@brief		This function check whether the token is operation
*@param		[ LexType ] 
*@return	bool
*/
bool IsOperation ( LexType );
/**
*@brief		This function check overflow of number
*@param		[ double ] 
*@return	void
*/
void CheckDouble ( double );
/**
*@brief		This function print help
*@param		[ void ] 
*@return	void
*/
void PrintHelp ( void );
/**
*@brief		This function calculate expression
*@param		[ void ] 
*@return	double
*/
double Calculate( my_queue<Lex>& );
/**
*@brief		This function calculate expression whith  FPU
*@param		[ void ] 
*@return	double
*/
double CalculateASM ( my_queue<Lex>& );




#endif _APP_H_