
/**
*@file		App.cpp
*@brief		This file contains implementations of function according to task 6
*			
*
*
*	Copyrights 2012 by IvanZahrodsky.
*/
#include "stdafx.h"



void Run ( void )
{
	UC *buf = nullptr;
	UC buf_i;
	UC ch;
	my_queue<Lex> lexem;
	printf ( "\nSelect the action:\n1 - Enter expression\n9 - Help\nESC - exit\n" ); 
	while( ( ch = _getch () ) != 27 ) 
	{
		switch (ch)
		{
		case '1':
			system ( "cls" );
			lexem.clear();
			printf ( "\nEnter expression :\n\n" );
			if(!ScanExp ( buf, buf_i))
			{
				printf ("\n!Error!\n");
			}
			else if ( buf_i !=0 )
			{
				try
				{
					if(LexAnalyze(buf,lexem,buf_i))
					{
						ToPostfix(lexem);
						double res = Calculate(lexem);
						//double res = CalculateASM(lexem);
						CheckDouble ( res );
						printf ( "\n\nResult  =   %.16G\n\n" , res);
						delete[] buf;
						buf = nullptr;
					}
				}
				catch(const char * e)
				{
					printf("\n%s\n",e);
				}
			}
			printf ( "\n\nSelect the action:\n1 - Enter expression\n9 - Help\nESC - exit\n\n" ); 
			break;
		case '9':
			system ( "cls" );
			PrintHelp();
			printf ( "\nSelect the action:\n1 - Enter expression\n9 - Help\nESC - exit\n" ); 
			break;
		}
	}
	printf ( "\nThank you for using application! Goodbye!!\n\n" );

}

void CheckDouble ( double temp)
{
	if ( ( abs(temp) > DBL_MAX ||  abs(temp) < DBL_MIN ) && temp != 0 )
	{
		throw "\nOverflow error !\n";
	}
}
bool ScanExp ( UC *& buf , UC&  buf_i)
{
	if ( buf != nullptr )
	{
		delete[] buf;
	}
	try
	{
		buf = new UC [256];
	}
	catch (...)
	{
		printf ( "\nError in allocate memory!\n" );
		return false;
	}
	memset(buf,0,256);
	buf_i = 0;
	UC ch;
	my_stack <UC> brk;
	while( ( ch = _getch () ) != 13 )
	{
		if ( buf_i == 255 )
		{
			printf ( "\n\nBuffer is full!\n" );
			break;
		}
		if ( isdigit (ch) && ( ( buf_i > 0 && buf [ buf_i-1 ] != ')' ) || buf_i == 0 ) )
		{

			printf ( "%c",ch );
			buf [buf_i] = ch;
			buf_i++;
			continue;
		}
		if ( strchr ( "+-/*%^.)",ch )>0 && buf_i > 0 && ( isdigit ( buf [ buf_i-1 ] ) || buf [ buf_i-1 ] == ')' ) )
		{
			if(ch == ')' && brk.empty () )
			{
				continue;
			}
			printf ("%c",ch);
			buf [buf_i ] = ch;
			buf_i ++;
			if ( ch == ')')
			{
				brk.pop();
			}
			continue;
		}
		if ( ch == '-' && ( ( buf_i > 1  && strchr ( "+-/*%.^(", buf [ buf_i - 2 ] ) <= 0 ) ||
							  buf_i < 1 || buf [ buf_i -1 ] == '(' ) )
		{
			printf ( "%c",ch );
			buf [buf_i] = ch;
			buf_i++;
			continue;
		}
		if ( ch== '(' && ( ( buf_i > 0 && strchr ( "+-/*%^(", buf [ buf_i-1 ] )  >0) || buf_i == 0 ) )
		{
		
			printf ( "%c",ch );
			buf [buf_i] = ch;
			buf_i++;
			brk.push ( ch );
			continue;
		}
		if ( ch == 8 )
		{
			if (buf_i > 0)
			{
				if( buf [buf_i] == '(' )
				{
					brk.pop ();
				}
				buf_i--;
			}
			printf ( "\b \b" );
		}
	
	}
	if ( !brk.empty () )
	{
		printf ( "\nToo many closing brackets!\n" );
		return false;
	}
	if ( strchr ( "+-/*%^", buf [ buf_i - 1 ] ) > 0 )
	{
		printf ( "\nExpression should end whith number or ')' \n" );
		return false;
	}
	return true;
}

bool LexAnalyze ( UC* buf, my_queue<Lex>& lexem, UC buf_i)
{
	UC i = 0;
	Lex temp;
	UC *ptr;
	if ( buf == nullptr )
	{
		printf ( "\nBuffer is empty!\n" );
		return false;
	}
	if ( buf_i > 255 )
	{
		printf ( "\nOferflow buffer!\n" );
		return false;
	}
	while ( i < buf_i )
	{
		if(buf[i] == '-' )
		{
			if( (buf_i - i) > 1 )
			{
				if ( isdigit ( buf [i+1] ) && i == 0 )
				{ 
					temp.val = strtod ( ( const char* ) buf+i , (char **) &ptr );
					i += ( int ) ( ptr - buf - i );
					CheckDouble ( temp.val );
					temp.type = number_;
					lexem.push ( temp );
					continue;
				}
			}
			if ( i > 1 )
			{
				if( strchr ( "+-/*%.^(",buf [ i-1 ] ) > 0 && isdigit ( buf [i+1] ))
				{
					temp.val = strtod ( ( const char* ) buf + i, ( char **) &ptr );
					i += (int) ( ptr - buf - i);
					CheckDouble ( temp.val);
					temp.type = number_;
					lexem.push(temp);
					continue;
				}
			}
		}
		if ( isdigit ( buf [i] ) )
		{
			temp.val  = strtod ( ( const char* ) buf + i, (char **) &ptr );
			i += (int) ( ptr - buf - i );
			CheckDouble ( temp.val);
			temp.type = number_ ;
			lexem.push ( temp );
			continue;
		}
		if ( strchr ( "+-/*%^()", buf [i] ) > 0 )
		{
			switch ( buf [i] )
			{
			case '+':
				temp.type = add_ ;
				lexem.push (temp);
				break;
			case '*':
				temp.type = mul_;
				lexem.push (temp);
				break;
			case '/':
				temp.type = div_;
				lexem.push (temp);
				break;
			case '%':
				temp.type = mod_;
				lexem.push ( temp );
				break;
			case '^':
				temp.type = pow_;
				lexem.push ( temp );
				break;
			case '-':
				if ( buf[i+1] == '(' &&  !isdigit(buf[i-1]) && buf[i-1] != ')' )
				{
					temp.type = negate_;
					lexem.push (temp);
				}
				else
				{
					temp.type = sub_;
					lexem.push (temp);
				}
				break;
			case '(':
				temp.type = LeftBraket_;
				lexem.push (temp);
				break;
			case ')':
				temp.type = RightBraket_;
				lexem.push (temp);
				break;
			default:
				printf ( "\n\nError! Uncknown symbols is entered!!\n");
				return false;
			}
			i++;
		}
	}
	return true;
}

bool Priority ( LexType t, my_stack<Lex> & tr)
{
	bool r = false;
	if (!tr.empty()) {
		r = ((t == div_ || t == mul_ || t == mod_ || t == negate_ || t == pow_ ) && (tr.top().type == add_) || 
			 (t == div_ || t == mul_ || t == mod_ || t == negate_ || t == pow_ ) && (tr.top().type == sub_)) ;
	}
	return r;
}

bool IsOperation(LexType t)
{
	return ((t == add_) || (t == sub_) || (t == div_) || (t == mul_) ||
			(t == mod_) || (t == negate_) || (t == pow_));
}

void ToPostfix ( my_queue<Lex>& lexem )
{
	my_stack<Lex> temp;
	my_queue<Lex> postf;

	while ( !lexem.empty () )
	{
		if ( lexem.front ().type == number_ )
		{
			temp.push ( lexem.front() );
		}
		else if( IsOperation ( lexem.front ().type ) )
		{
			if ( temp.empty () ) 
			{
				temp.push ( lexem.front () );
			}
			else if ( Priority ( lexem.front ().type, temp ) ) 
			{
				temp.push ( lexem.front() );
			}
			else 
			{
				if (temp.top().type != LeftBraket_) 
				{
					do {
						postf.push ( temp.top() );
						temp.pop();
					}
					while ( ( !Priority ( lexem.front().type, temp ) ) && ( !temp.empty() ) &&
						( temp.top().type != LeftBraket_ ) );
				}
				temp.push ( lexem.front() );
			}
		}
		else if ( lexem.front().type == LeftBraket_ ) 
		{
			temp.push (lexem.front() );
		}
		else if ( lexem.front().type == RightBraket_ ) 
		{
			while ( temp.top().type != LeftBraket_ ) 
			{
				postf.push (temp.top() );
				temp.pop();
			}
			temp.pop();
			if ( !temp.empty() )
			{
				if ( temp.top().type == negate_ )
				{
					postf.push ( temp.top() );
					temp.pop();
				}
			}
		}
		lexem.pop();
	}

	while ( !temp.empty() ) 
	{
		postf.push ( temp.top() );
		temp.pop();
	}
	lexem = postf;
}

void PrintHelp ( void )
{
	printf ( "\n\nYou can use the following operations:\n\n\
			  \n'+'  -- addition\
			  \n'-'  -- subtraction\
			  \n'*'  -- multiplication\
			  \n'/'  -- division\
			  \n'%%'  -- remainder of the division\
			  \n'^'  -- exponentiation\n\n" ) ;
}

double Calculate ( my_queue<Lex>& lexem )
{
	my_stack<double> st_res;
	double res;
	double temp1,temp2;
	while(!lexem.empty())
	{
		switch(lexem.front().type)
		{
			case add_:
				temp1 =st_res.top();
				st_res.pop();
				temp2 = st_res.top();
				st_res.pop();
				st_res.push(temp2+temp1);
				break;
			case sub_:
				temp1 = st_res.top();
				st_res.pop();
				temp2 =st_res.top();
				st_res.pop();
				st_res.push(temp2-temp1);
				break;
			case div_:
				temp1 = st_res.top();
				st_res.pop();
				temp2 = st_res.top();
				st_res.pop();
				if ( temp1 == 0 )
				{
					throw "\n\nEror! Division by zero!\n\n";
				}
				st_res.push(temp2/temp1);
				break;
			case mul_:
				temp1 = st_res.top();
				st_res.pop();
				temp2 = st_res.top();
				st_res.pop();
				st_res.push(temp2*temp1);
				break;
			case pow_:
				temp1 = st_res.top();
				st_res.pop();
				temp2 = st_res.top();
				st_res.pop();
				st_res.push(pow(temp2,temp1));
				break;
			case negate_:
				temp1 = st_res.top();
				st_res.pop();
				st_res.push(-temp1);
				break;
			case mod_:
				temp1 = st_res.top();
				st_res.pop();
				temp2 = st_res.top();
				st_res.pop();
				if ( temp1 == 0 )
				{
					throw "\n\nEror! Division by zero!\n\n";
				}
				st_res.push(temp2 - (temp2/temp1)*temp1);
				break;
			case number_:
				st_res.push(lexem.front().val);
				break;
		}
		lexem.pop();
	}
	res = st_res.top();
	return res;
}



double CalculateASM ( my_queue<Lex>& lexem )
{
	my_stack<double> st_res;
	double res;
	double temp;
	while(!lexem.empty())
	{
		switch(lexem.front().type)
		{
			case add_:
				_asm
				{
					fadd
				}
				break;
			case sub_:
				_asm
				{
					fsub
				}
				break;
			case div_:
				int temp2;
				_asm
				{
					ftst
					fstsw temp2
				}
				if ( temp2 & 0x00004000 )
				{
					throw "\n\nEror! Division by zero!\n\n";
				}
				_asm
				{
					fdiv
				}
				break;
			case mul_:
				_asm
				{
					fmul
				}
				break;
			case pow_:
				_asm
				{
					fxch
					fyl2x 
					fld st(0) 
					frndint   
					fxch st(1)
					fsub st(0),st(1) 
					f2xm1  
					fld1     
					faddp st(1),st 
					fscale
				}
				break;
			case negate_:
				_asm
				{
					fchs
				}
				break;
			case mod_:
				_asm
				{
					ftst
					fstsw temp2
				}
				if ( temp2 & 0x00004000 )
				{
					throw "\n\nEror! Division by zero!\n\n";
				}
				_asm
				{
					fxch
					fprem
				}
				break;
			case number_:
				temp = lexem.front().val;
				_asm
				{
					fld temp;
				}
				break;
		}
		lexem.pop();
	}
	_asm
	{
		fstp res
	}
	return res;
}

