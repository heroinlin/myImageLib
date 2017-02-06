#ifndef MY_ERROR_H
#define  MY_ERROR_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
//#include <stdlib.h>

	/**
	* error - print error information.
	*
	* Parameters:
	* @s ------ the string of error information.
	* Return:
	* none
	*/
	void error(const char *s);

	/**
	* malloc_error - print malloc error information.
	*
	* Return:
	* none
	*/
	void malloc_error();

	/**
	* file_error - print open file error information.
	*
	* Parameters:
	* @s ------ the name of open file .
	* Return:
	* none
	*/
	void file_error(char *s);

	/**
	* function_error - print function error information.
	*
	* Parameters:
	* @s ------ the name of open file .
	* Return:
	* none
	*/
	void function_error(char *s);

#ifdef __cplusplus
}
#endif
#endif
