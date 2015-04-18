Typical Function Comment
/**
	@author 
	@brief 
	@details
	@param
	@return
	@retval
	@bug
	@warning
	@note
	@todo
*/

File description
/**
	@file <put filename here with out the <> signs>
	@author
	@brief
	@details
	@warning
	@note
	@todo
	@ingroup
	@addtogroup
	@brief
	@{
*/

end of file
/**
	@}
*/


Structure Example
/** @struct CoordStruct
 * 	@brief a coordinate pair
 *	@details A XY coordinate pair
 */
struct CoordStruct
{
  /** The x coordinate */
  float x;
  /** The y coordinate */
  float y;
};
	

Mandatory Sections:
	@author
	@brief
	@details
	@return (if not void)
	@param (if parameters exist)

Defined Sections:
	@attention {attention text}
	@author {author} defines the author of the text. We typically use the following format (without the square brackets)"[name] <[email]> [phone number]"
	@brief {brief description} A brief description of the item
    @bug {bug description} A description of any bugs.
	@date {date} the last modified date of the item.
	@deprecated {description} marks that the item is depricated
    @details {detailed description} a detailed description that describes the function fully
	@example <file name> description of function, in a seprate file on how ot use the code specified.
	@note {text} a note, on the item. The section will be indented
    @overload [(function declaration)] specified an overload function
	@param <prameter-name> {parameter description} This defines the parameters to a function.
    @return {description} the descitpion of the return value of a block of code
    @retval <return value> {description} indicates what the value of the returned block means.
	@test {paragraph describing test case} starts a paragraph where a test case can be described
    @todo {pragraph describing what is to be done} put items on list into todo list

Formatting commands:
	@a <word>	displays the word in italics. To put multiple words in bold use <em>multiple words</em>
	@b <word> displays the word in bold font. To put multiple words in bold use <b>multiple words</b>
	@code ['{'<word>'}'] Starts a block of code. Ex "@code {.c} printf("hello world"); @endcode"
	@endcode ends a block of code
	@li {item description} List item with bullet points
	@par [(paragraph title)] Creates a paragraph with the given heading. The heading will be the line on which @par is defined.
	@page the comment block conatins a piece of documenation that is not directly related to one specfic item. This generates a new HTML page
	@section <section-name> (section title) creates a section 
    @see {refrences} for refrences to classes, functions, methods, variables, files, or URLs
    @struct <name> [<header-file>] [<header-name>] Indicates that a comment block contains documentation for a struct with name <name>.
    @subsection <section-name> (section title) creates a section in a section
    @subsubsection <section-name> (section title) creates a section in a sub-section
    @tableofcontents Creates a table of contents. Only works in page documentation, and not other documentation
	@warning {warning message} starts a paragraph where a warning mesage can be entered
	@$ used to write a $
    @@ used to write an @
    @\ used to write a \
    @& used to write an &
    @< used to write a <
    @> used to write a >
    @# used to write a #
    @% used to write a %
    @" used to write a "
    @. used to write a . at the start of a new line
    @:: used to write ::
	@f$ marks the start of an intext formula
    @f[ marks the start of a long formula, centered on a seprate line
    @f] marks teh end of a long formula
	
Specify what code is being documented:
	@def <macro name> indicates that the comment block contans documentation for a #define macro
	@enum indicates that the comment block contains information on an enumeration
	@file [<name>] Indicates that a comment block contains documentation for a source or header file with name <name>
	@typedef (typedef declaration) Indicates that a comment block contains documentation for a typedef
    @var (variable declaration)Indicates that a comment block contains documentation for a variable or enum value (global only)


HTML page control
	@anchor <word> places an invisible anchor, which you can refer to with the \ref command
	@f$ marks the start of an intext formula
    @f[ marks the start of a long formula, centered on a seprate line
    @f] marks teh end of a long formula
	@mainpage Placed in a comment block to customize the index page
	@page the comment block conatins a piece of documenation that is not directly related to one specfic item. This generates a new HTML page
	@paragraph <paragraph name> [(paragraph title)] works like the par command, but only can be used in page documenation.

	
Modules
	We have the following modules. Telemetry, Motor, and Common
		/**
		*  @ingroup
		*  @addtogroup
		*  @brief
		*  @{
		*/

	(code and other comment blocks here)
	at the end of the file put

		/**
		* @}
		*/
		
		
Useful Commands
    @a <word> : displays the word in italics
    @addindex (text) adds text to the latex index
    @addtogroup  <name> [(title)] works like defgroup, but does not produce warning if used more than once.
    @anchor <word> places an invisible anchor, which you can refer to with the \ref command
    @attention {attention text}
    @author {author} defines the author of the text. We typically use the following format (without the square brackets)"[name] <[email]> [phone number]"
    @b <word> displays the word in bold font. To put multiple words in bold use <b>multiple words</b>
    @brief {brief description} A brief description of the item
    @bug {bug description} A description of any bugs.
    @c <word> use this to refer to a code. Code is made in typewriter font. Use <tt> for multiple words </tt>
    @code ['{'<word>'}'] Starts a block of code. Ex "@code {.c} printf("hello world"); @endcode"
    @date {date} the last modified date of the item.
    @def <macro name> indicates that the comment block contans documentation for a #define macro
    @deprecated {description} marks that the item is depricated
    @details {detailed description} a detailed description that describes the function fully
    @e <word> displays the word in italics use <em>for multiple words</em>
    @endcode ends a block of code
    @enum indicates that the comment block contains information on an enumeration
    @example <file name> description of function, in a seprate file on how to use the code specified.
    @f$ marks the start of an intext formula
    @f[ marks the start of a long formula, centered on a seprate line
    @f] marks teh end of a long formula
    @file [<name>] Indicates that a comment block contains documentation for a source or header file with name <name>
    @image <format> <file> ["caption"] [<sizeindication>=<size>] inserts an image into the documentation.
    @ingroup (<groupname> [<groupname> <groupname>])
	@li {item description} List item with bullet points
    @mainpage Placed in a comment block to customize the index page
    @n new line
    @note {text} a note, on the item. The section will be indented
    @overload [(function declaration)] specified an overload function
    @page the comment block conatins a piece of documenation that is not directly related to one specfic item. This generates a new HTML page
    @par [(paragraph title)] Creates a paragraph with the given heading. The heading will be the line on which @par is defined.
    @paragraph <paragraph name> [(paragraph title)] works like the par command, but only can be used in page documenation.
    @param <prameter-name> {parameter description} This defines the parameters to a function.
    @post {description of postcondition} This can be used to describe the postcondition of an item
    @pre {description of precondition} this can be used to describe the precondition of an item
    @private Indicates that the member documented is private, and should only be accessed by other members in the same file.
    @ref <name> ["(text)"] creates a refrence to a named section
    @return {description} the descitpion of the return value of a block of code
    @retval <return value> {description} indicates what the value of the returned block means.
    @section <section-name> (section title) creates a section 
    @see {refrences} for refrences to classes, functions, methods, variables, files, or URLs
    @struct <name> [<header-file>] [<header-name>] Indicates that a comment block contains documentation for a struct with name <name>.
    @subsection <section-name> (section title) creates a section in a section
    @subsubsection <section-name> (section title) creates a section in a sub-section
    @tableofcontents Creates a table of contents. Only works in page documentation, and not other documentation
    @test {paragraph describing test case} starts a paragraph where a test case can be described
    @todo {pragraph describing what is to be done} put items on list into todo list
    @typedef (typedef declaration) Indicates that a comment block contains documentation for a typedef
    @var (variable declaration)Indicates that a comment block contains documentation for a variable or enum value (global only)
    @warning {warning message} starts a paragraph where a warning mesage can be entered
    @$ used to write a $
    @@ used to write an @
    @\ used to write a \
    @& used to write an &
    @< used to write a <
    @> used to write a >
    @# used to write a #
    @% used to write a %
    @" used to write a "
    @. used to write a . at the start of a new line
    @:: used to write ::

