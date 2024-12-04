#ifndef COMMANDMANAGER_HPP
#define COMMANDMANAGER_HPP



#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <optional>
#include <sstream>



#include "menu_manager.hpp"



namespace COMMANDMANAGER
{
	/* Function pointers for the command table: */
	typedef std::function <void (const std::vector <std::string>&)> FunctionExecute;



	/* A simple data container for command algorithms: */
	/*------------------------------------------------------------------------------------------------------------------------*/
	struct Data_Toolbox
	{
		/* Fields are filled in through the interface of static methods: */
		Data_Toolbox() = default;

		/* Getter and setter for the [MENU] field: */
		static void setMenuInstance(const MMNG::Menu &input_menu_instance);
		static const MMNG::Menu& getMenuInstance();
	private:
		/* Available for expansion - currently only interaction with [MENU] is supported: */
		static MMNG::Menu current_menu_instance;
	};
	/*------------------------------------------------------------------------------------------------------------------------*/



	/* Pattern Command: */
	/*------------------------------------------------------------------------------------------------------------------------*/
	class Command_Manager
	{
	public:
		~Command_Manager() = default;
		virtual void execute(const std::vector <std::string> &) = 0;
		
		virtual void getDescriptionCommand() = 0;
	};
	/*------------------------------------------------------------------------------------------------------------------------*/



	/* [> menu] */
	/*------------------------------------------------------------------------------------------------------------------------*/
	class Command_Menu : public Command_Manager
	{
	public:
		void execute(const std::vector <std::string> &args) override;

		void getDescriptionCommand() override;

		/* In the toolbox, let's turn to the method - which will return us a link to the [MENU]: */
		Data_Toolbox toolbox_instance;
	};
	/*------------------------------------------------------------------------------------------------------------------------*/



	/* [> order] */
	/*------------------------------------------------------------------------------------------------------------------------*/
	class Command_Order : public Command_Manager
	{
	public:
		void execute(const std::vector <std::string> &args) override;

		void getDescriptionCommand() override;
	};
	/*------------------------------------------------------------------------------------------------------------------------*/



	/* [> exit] */
	/*------------------------------------------------------------------------------------------------------------------------*/
	class Command_Exit : public Command_Manager
	{
	public:
		void execute(const std::vector <std::string> &args) override;

		void getDescriptionCommand() override;
	};
	/*------------------------------------------------------------------------------------------------------------------------*/



	/* [> help] */
	/*------------------------------------------------------------------------------------------------------------------------*/
	class Command_Help : public Command_Manager
	{
	public:
		void execute(const std::vector <std::string> &args) override;

		void getDescriptionCommand() override;
	};
	/*------------------------------------------------------------------------------------------------------------------------*/



	/* Process Management command tables: */
	/*------------------------------------------------------------------------------------------------------------------------*/
	class Command_Executor
	{
	public:
		/* Initializes the command table and binds the command name and the function pointer: */
		Command_Executor();

		/* Getters for accessing command objects: */
		Command_Menu&  getCommandMenuObject();
		Command_Order& getCommandOrderObject();
		Command_Exit&  getCommandExitObject();
		Command_Help&  getCommandHelpObject();

		/* The method is to search for a team from our command table: */
		std::optional <std::string> readingStreamForExecution(const std::vector <std::string> &command_and_attribytes);

		/* Getter for accessing our table: */
		std::unordered_map <std::string, FunctionExecute>& getInstanceCommandTable();
	private:
		/* Command table: the key is std::string (command name) */
		/* The value is functions (which are called with std parameters::vector <std::string> & args - which are additional attributes of the command): */
		std::unordered_map <std::string, FunctionExecute> command_table;

		/* These objects are needed inside the constructor of this class. When used together with std::bind - specific objects are needed: */
		Command_Menu  command_menu_instance;
		Command_Order command_order_instance;
		Command_Exit  command_exit_instance;
		Command_Help  command_help_instance;
	};
	/*------------------------------------------------------------------------------------------------------------------------*/



	/* Pattern Singleton: */
	/*------------------------------------------------------------------------------------------------------------------------*/
	class Command_Processor
	{
	public:
		/* To access or initialize an object: */
		static Command_Processor& getInstance();

		/* REPL - read-eval-print [LOOP]: */
		void startCommandProcessor();
	private:
		Command_Processor()  = default;
		~Command_Processor() = default;

		/* This is a singleton, which means it is forbidden to have more than one instance of the class: */
		Command_Processor(const Command_Processor &) = delete;
		Command_Processor& operator= (const Command_Processor &) = delete;
	};
	/*------------------------------------------------------------------------------------------------------------------------*/
};
namespace CMG = COMMANDMANAGER;



#endif /* !COMMANDMANAGER_HPP! */