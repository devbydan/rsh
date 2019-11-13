/*
 * Name -> Dan Murphy
 * Desc -> Abstract base component represents a singular [string-type]
 * 				 command as input by the user.
 *
 * 				 Holds a parse pointer to Input_Parser concrete instance.
 *
 * 				 Utilizes pure virtual execute() function that defines the
 * 				 interface for command execution by client.
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * File -> Base.hpp
 */

/* HEADER GUARD */
#ifndef __BASE_HPP__ /* Checks whether __BASE_HPP__ is declared in the scope */
#define __BASE_HPP__ /* If __BASE_HPP__ is not defined, wrap within the scope */

/* LIBARIES */
#include <string> /* Include the string library */

/* CLASS DECLARATION */
class Base
{
private:
	std::string command;

public:

	Base();   							/* DEFAULT constructor */
	Base(std::string str);  /* WORKING constructor */

	/* Chain effects may be disasterous,
	 * will let compiler handle destructor
	 * for now.
	 * Idea holds something along these lines:
	 *
	 * ~Base() { delete this->parser; }
	 *
	 */

	/* Permits valid traversal through the tree */
	Base *get_root()	{ return this; }

	/* Virtual Functions */
	virtual void set_string(std::string str);
	virtual std::string &get_command();
	virtual int execute() = 0; // Public interface


};/* End of Base class --- */


/* Setter function for the command string */
void Base::set_string(std::string str)
{
	this->command = str;
}

/* Returns reference to the command string */
std::string &Base::get_command()
{
	return this->command;
}

#endif /* !__BASE_HPP__ */
