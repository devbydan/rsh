/*
 * Name -> Dan Murphy
 * Desc -> Concrete instance of abstract Base class stores a
 * 			   singular user command and also encapsulates command
 * 				 execution functionality.
 *
 * 				 Command->execute calls execvp after converting Base data member
 * 				 string to a char* array.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * File -> Command.hpp
 */

/* HEADER GUARD */
#ifndef __COMMAND_HPP__ /* Checks whether __COMMAND_HPP__ is declared in the scope */
#define __COMMAND_HPP__ /* If __COMMAND_HPP__ is not defined, wrap within the scope */

/* LIBRARIES */
#include <vector>
#include <string>

/* DEFINED HEADERS */
#include "Base.h"

/* Inherits from Base to instantiate concrete instance of Command class */
class Command : public Base
{
public:
	Command(); 													  /* DEFAULT constructor */
	Command(std::string str) : Base(str); /* WORKING constructor */
	void add_command(std::string str) { Base::set_string(str); }
	virtual int execute();                /* Public interface */

private:

	/* no private data necessary yet */

};/* End of Command class --- */

int Command::execute()
{
	int argc = 0;
	std::istringstream iss;               /* buffer stream space separator */
	std::vector<std::string> vect_tokens; /*holds tokens in string format */
	/* str_temp shuttles string tokens into vect_tokens
	 * for further tokinization prior argv[] for
	 * execution by execvp
	 */
	std::string str_temp = "";

	/* get this command string (Base: -command) */
	std::string command = this->get_command();

	/* stream the command */
	iss.str(command);

/*
 * FOR the length of the command, incrementing by one
 * ( we count the tokens of the command . . . )
 * 		 IF there exists white space or a null terminator (i.e. end)
 * 				=> Count the elements of the individual command
 *           & isolate by space
 *
 */

	for (size_t i = 0; i <= command.length(); i++)
	{
		if (command[i] == ' ' || command[i] == '\0') { argc++; }

	}/* End of FOR loop --- */

 /*
	* FOR the vector commands population
	* ( Use the buffer stream space separator into a temporary variable . . . )
	* 		IF exit or quit is found
	* 			 => Force exit the instance
	* 		ELSE
	* 			 => Push to the vector for conversion to argv & collect the parts
	*/

	for (int i = 0; i < argc; i++)
	{
		/* Push the buffer stream space into a temp variable */
		iss >> str_temp;

		/* Force exit */
		if (str_temp == "exit" || str_temp == "quit") { exit(0); }

		/* If not exited, collect the parts */
		vect_tokens.push_back(str_temp);

	}/* End of FOR loop --- */

 /*
  * Instantiate a char* argv array to prep for command execution
	*
	* FOR the number of elements in command populating the array of char*'s
	* 		( Cast a char* into a c string . . . )
  *
	* Set the last element to required NULL
	*
	*/

	char* argv[argc + 1]; /* Preps argv for execution of command */

	for (int i = 0; i < argc; i++)
	{ argv[i] = const_cast<char*>(vect_tokens[i].c_str()); }

	argv[argc] = NULL;


 /*
  * FORKING PROCESS OCCURS
	*
	* Note that fork() returns 3 different values:
	*  0 => child process executed properly
	*  1 => parent process executed properly
	* -1 => forking process failed, potential zombie
  *
  */

	int childStatus;
	int local = 0;
	pid_t child_pid = fork();
	/* ---------------------------------------------------------------------- */
	if (child_pid == 0)
	{
		/* If cannot execute, throws error */
		if (execvp(argv[0], argv) < 0) { perror(argv[0]); }

		/* Base case exit */
		exit(0);
	}
	/* ---------------------------------------------------------------------- */
	else if (child_pid < 0)
	{
		/* Process ID cannot be less than zero, throws error */
		perror("forking child process failed");

		/* Force exits the environment */
		exit(0);
	}
	/* ---------------------------------------------------------------------- */
	else if (child_pid > 0)
	{
		wait(&childStatus); /* Wait until child finishes */

		/* If waiting for child completion takes too long, throws an error */
		if (wait(&childStatus) != -1) { perror("wait error"); }

		if (WIFEXITED(childStatus))
		{
			if (WEXITSTATUS(childStatus) != 0)
				return -1; /* Failed execution, exit */
		  return 0;    /* Succeeded execution, exit */
		}
		else /* Incorrect child exit, error thrown & force exit */
		{
			perror("ABNORMAL CHILD . . . exit!");
			return -1;
		}
	}
	/* ---------------------------------------------------------------------- */

}/* End of execute --- */

#endif /* !__COMMAND_HPP__ */
