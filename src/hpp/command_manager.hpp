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
	private:
		MMNG::Menu current_menu_instance;
	};
	/*------------------------------------------------------------------------------------------------------------------------*/



	/* Pattern Command: */
	/*------------------------------------------------------------------------------------------------------------------------*/
	class Command_Manager
	{
	public:
		~Command_Manager() = default;
		virtual void execute(const std::vector <std::string> &) = 0;
	};
	/*------------------------------------------------------------------------------------------------------------------------*/



	/* [> menu] */
	/*------------------------------------------------------------------------------------------------------------------------*/
	class Command_Menu : public Command_Manager
	{
	public:
		void execute(const std::vector <std::string> &args) override;
	};
	/*------------------------------------------------------------------------------------------------------------------------*/



	/* [> order] */
	/*------------------------------------------------------------------------------------------------------------------------*/
	class Command_Order : public Command_Manager
	{
	public:
		void execute(const std::vector <std::string> &args) override;
	};
	/*------------------------------------------------------------------------------------------------------------------------*/



	/* [> exit] */
	/*------------------------------------------------------------------------------------------------------------------------*/
	class Command_Exit : public Command_Manager
	{
	public:
		void execute(const std::vector <std::string> &args) override;
	};
	/*------------------------------------------------------------------------------------------------------------------------*/



	/* [> help] */
	/*------------------------------------------------------------------------------------------------------------------------*/
	class Command_Help : public Command_Manager
	{
	public:
		void execute(const std::vector <std::string> &args) override;
	};
	/*------------------------------------------------------------------------------------------------------------------------*/



	/* Process Management command tables: */
	/*------------------------------------------------------------------------------------------------------------------------*/
	class Command_Executor
	{
	public:
		/*  */
		Command_Executor();

		/*  */
		Command_Menu&  getCommandMenuObject();
		Command_Order& getCommandOrderObject();
		Command_Exit&  getCommandExitObject();
		Command_Help&  getCommandHelpObject();

		/*  */
		std::optional <std::string> readingStreamForExecution(const std::vector <std::string> &command_and_attribytes);

		/*  */
		std::unordered_map <std::string, FunctionExecute>& getInstanceCommandTable();
	private:
		/*  */
		std::unordered_map <std::string, FunctionExecute> command_table;

		/* */
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