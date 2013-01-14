/**
*@file		my_structs.h
*@brief		This file contains implementations of  class
*			
*
*
*	Copyrights 2012 by IvanZahrodsky.
*/
#ifndef _MY_STRUCTS_H_
#define _MY_STRUCTS_H_


namespace Zahrodsky
{
	/**
	* @class	my_structs
	* @brief	abstract class 
	*
	* Copyrights 2012 by IvanZahrodsky.
	* 
	*/
	template <class T>
	class my_structs
	{
	public:
		struct Node
		{
			T val;
			Node *next;
			Node ( T v = 0, Node *nxt = nullptr ) : val (v), next(nxt)  { /*NULL*/ }
		};
		virtual bool pop ( void ) = 0;
		virtual bool push ( T val ) = 0;
		virtual bool empty ( void ) = 0;
		virtual void clear ( void ) = 0;
		virtual ~my_structs ( ) {};
	};

	/**
	* @class	my_stack
	* @brief	implements the logical structure - stack 
	*
	* Copyrights 2012 by IvanZahrodsky.
	* 
	*/
	template <class T>
	class my_stack : public my_structs<T>
	{
	
	public:
		my_stack () : elem ( nullptr ) { /*NULL*/ }
		~my_stack (void)
		{
			clear();
		}
		/**
		 * @brief   This function delete all elements of stack
		 * @param	[void]            
		 * @return	void
		 * @exception			N/A
		*/
		void clear ( void )
		{
			Node *dptr;
			while(elem != nullptr)
			{
				dptr = elem;
				elem = elem->next;
				delete dptr;
				dptr = nullptr;
			}
		}
		/**
		 * @brief   This function adding element to stack
		 * @param	[class T]   elements         
		 * @return	bool
		 * @exception			N/A
		*/
		bool push ( T v )
		{
			Node *temp;
			try
			{
				temp = new Node(v);
			}
			catch(...)
			{
				return false;
			}
			if (elem != nullptr)
			{
				temp->next = elem;
				elem = temp;
				return true;
			}
			elem = temp;
			return true;
		}
		/**
		 * @brief   This function return  top element of stack
		 * @param	[void]            
		 * @return	class T element
		 * @exception	const char *
		*/
		T top ( void )
		{
			if(elem != nullptr)
			{
				return elem->val;
			}
			else
			{
				throw "Stack is empty!";
			}
		}
		/**
		 * @brief   This function delete top  element of stack
		 * @param	[void]            
		 * @return	bool
		 * @exception	N/A
		*/
		bool pop ( void )
		{
			if(elem != nullptr)
			{
				Node *dptr;
				dptr = elem;
				elem = elem->next;
				delete dptr;
				return true;
			}
			return false;
		}
		/**
		 * @brief   This function check is stack empty ?
		 * @param	[void]            
		 * @return	bool
		 * @exception	N/A
		*/
		bool empty ( void )
		{
			return elem == false;
		}
		my_stack& operator = ( const my_stack& old )
		{
			if ( this == &old )
			{
				return *this;
			}
			clear();
			Node *temp1, *temp2, *temp3;
			temp1 = old.elem;
			temp3 = elem;
			while(temp1 != nullptr )
			{
				try
				{
					temp2 = new Node(temp1->val);
				}
				catch(...)
				{
					clear();
					return *this;
				}
				if ( temp3 != nullptr )
				{
					temp3->next = temp2;
					temp3 = temp2;
					temp1 = temp1->next;
					continue;
				}
				elem = temp3 = temp2;
				temp1 = temp1->next;
			}
			return *this;
		}

	private:
		Node *elem;
	};

	/**
	* @class	my_queue
	* @brief	implements the logical structure - queue 
	*
	* Copyrights 2012 by IvanZahrodsky.
	* 
	*/
	template <class T>
	class my_queue : public my_structs<T>
	{
	private:
		Node *head;
		Node *last;

	public:
		my_queue () : last ( nullptr ) , head ( nullptr ) { /*NULL*/ }
		/**
		 * @brief   This function adding element to queue
		 * @param	[class T]   elements         
		 * @return	bool
		 * @exception			N/A
		*/
		bool push ( T v )
		{
			Node *temp;
			try
			{
				temp = new Node(v);
			}
			catch(...)
			{
				return false;
			}
			if (last!= nullptr)
			{
				last->next = temp;
				last = temp;
				return true;
			}
			head = last = temp;
			return true;
		}
		/**
		 * @brief   This function return  front element of queue
		 * @param	[void]            
		 * @return	class T element
		 * @exception	const char *
		*/
		T front ( void )
		{
			if(head == nullptr)
			{
				throw "Queue is empty!";
			}
			return head->val;
		}
		/**
		 * @brief   This function delete front  element of stack
		 * @param	[void]            
		 * @return	bool
		 * @exception	N/A
		*/
		bool pop ( void )
		{
			if(head != nullptr)
			{
				Node *dptr;
				dptr = head;
				head = head->next;
				delete dptr;
				return true;
			}
			return false;
		}
		/**
		 * @brief   This function check is queue empty ?
		 * @param	[void]            
		 * @return	bool
		 * @exception	N/A
		*/
		bool empty ( void )
		{
			return head == false;
		}
		/**
		 * @brief   This function delete all elements of queue
		 * @param	[void]            
		 * @return	void
		 * @exception			N/A
		*/
		void clear ( void )
		{
			Node *dptr;
			while ( head != nullptr )
			{
				dptr = head;
				head = head->next;
				delete dptr;
				dptr = nullptr;
			}
			last = nullptr;
		}
		~my_queue ( )
		{
			clear();
		}
		my_queue& operator = ( const my_queue& old )
		{
			if ( this == &old )
			{
				return *this;
			}
			clear();
			Node *temp1,*temp2;
			temp1 = old.head;
			while(temp1 != nullptr )
			{
				try
				{
					temp2 = new Node(temp1->val);
				}
				catch(...)
				{
					clear();
					return *this;
				}
				if ( last != nullptr )
				{
					last->next = temp2;
					last = temp2;
					temp1 = temp1->next;
					continue;
				}
				head = last = temp2;
				temp1 = temp1->next;
			}
			return *this;
		}

	};

}



#endif  //_MY_STRUCTS_H_