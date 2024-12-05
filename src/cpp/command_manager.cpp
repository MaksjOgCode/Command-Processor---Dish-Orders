#include "../hpp/command_manager.hpp"



/* COMMAND "menu": */
/*------------------------------------------------------------------------------------------------------------------------*/
void CMG::Command_Menu::execute(const std::vector<std::string>& args)
{
	auto result_checking_arguments = this->checkingArguments(args);
	if ( result_checking_arguments != std::nullopt)
	{
		std::cout << *result_checking_arguments << "\n";
		return;
	}

	if ( args[0] == "show" )
	{
		std::cout << "\n";
		this->toolbox_instance.getMenuInstance().displayMenu();
		std::cout << "\n";
	}
	else if ( args[0] == "help" )
	{
		this->getDescriptionCommand();
	}

	return;
}
/*------------------------------------------------------------------------------------------------------------------------*/
std::optional<std::string> COMMANDMANAGER::Command_Menu::checkingArguments(const std::vector<std::string>& args)
{
	if ( args.size() > 1 )
		return "There are too many arguments for the [menu] command:";

	if ( (args[0] != "show") && (args[0] != "help") )
		return "These attributes of the [menu] command are not supported:";

	return std::nullopt;	
}
/*------------------------------------------------------------------------------------------------------------------------*/
void COMMANDMANAGER::Command_Menu::getDescriptionCommand()
{
	std::cout << "Description of the [menu] command:\n" <<
		"\tAttribytes:\n\t\t- [show]\n\t\t- [help]\n\n";
}
/*------------------------------------------------------------------------------------------------------------------------*/



/* COMMAND "order": */
/*------------------------------------------------------------------------------------------------------------------------*/
void CMG::Command_Order::execute(const std::vector<std::string>& args)
{
	std::cout << "Command_Order\n";
}
/*------------------------------------------------------------------------------------------------------------------------*/
std::optional<std::string> COMMANDMANAGER::Command_Order::checkingArguments(const std::vector<std::string>& args)
{
	return std::nullopt;
}
/*------------------------------------------------------------------------------------------------------------------------*/
void COMMANDMANAGER::Command_Order::getDescriptionCommand()
{

}
/*------------------------------------------------------------------------------------------------------------------------*/



/* COMMAND "exit": */
/*------------------------------------------------------------------------------------------------------------------------*/
void COMMANDMANAGER::Command_Exit::execute(const std::vector<std::string>& args)
{
	std::exit(0);
}
/*------------------------------------------------------------------------------------------------------------------------*/
std::optional<std::string> COMMANDMANAGER::Command_Exit::checkingArguments(const std::vector<std::string>& args)
{
	return std::nullopt;
}
/*------------------------------------------------------------------------------------------------------------------------*/
void COMMANDMANAGER::Command_Exit::getDescriptionCommand()
{

}
/*------------------------------------------------------------------------------------------------------------------------*/



/* COMMAND "help": */
/*------------------------------------------------------------------------------------------------------------------------*/
void COMMANDMANAGER::Command_Help::execute(const std::vector<std::string>& args)
{
	std::cout << "Available commands:\n[menu] att - [show], - [help]\n[help]\n\n";
}
/*------------------------------------------------------------------------------------------------------------------------*/
std::optional<std::string> COMMANDMANAGER::Command_Help::checkingArguments(const std::vector<std::string>& args)
{
	return std::nullopt;
}
/*------------------------------------------------------------------------------------------------------------------------*/
void COMMANDMANAGER::Command_Help::getDescriptionCommand()
{

}
/*------------------------------------------------------------------------------------------------------------------------*/



/* struct Data Toolbox: */
/*------------------------------------------------------------------------------------------------------------------------*/
void COMMANDMANAGER::Data_Toolbox::setMenuInstance(const MMNG::Menu& input_menu_instance)
{
	current_menu_instance = input_menu_instance;
}
/*------------------------------------------------------------------------------------------------------------------------*/
const MMNG::Menu& COMMANDMANAGER::Data_Toolbox::getMenuInstance()
{
	return current_menu_instance;
}
/*------------------------------------------------------------------------------------------------------------------------*/
/* Static field: */
MMNG::Menu COMMANDMANAGER::Data_Toolbox::current_menu_instance;
/*------------------------------------------------------------------------------------------------------------------------*/



/* class Command Processor: */
/*------------------------------------------------------------------------------------------------------------------------*/
void COMMANDMANAGER::Command_Processor::startCommandProcessor()
{
	/* Initializing the command handler: */
	Command_Executor executor_instance {};

	/* Read input string: */
	std::string input_string {};

	/* The string that is being read from the console will be divided into separate words and placed in this vector: */
	std::vector <std::string> command_and_attribytes {};

	/* Temporary element - separated words from the read string will be placed here. Next, the words will be placed in the vector [command_and_attribytes]: */
	std::string temp_element {};
	while (true)
	{
		std::cout << "\033[32m" << "User: " << "\033[0m" << "\033[35m" << "[current user]: " << "\033[0m" << "\n$ ";
		std::getline(std::cin, input_string);

		/* Splitting the input data into separate words: */
		std::istringstream stream(input_string);
		while (stream >> temp_element)
			command_and_attribytes.push_back(temp_element);

		/* The result of executing the [readingStreamForExecution] method will return std::nullopt - provided that the input data is correct - and the required command exists: */
		auto result = executor_instance.readingStreamForExecution(command_and_attribytes);
		if ( result != std::nullopt )
			std::cout << *result << "\n";

		/* Clearing a vector to process a new command: */
		command_and_attribytes.clear();
	}
}
/*------------------------------------------------------------------------------------------------------------------------*/
COMMANDMANAGER::Command_Processor& COMMANDMANAGER::Command_Processor::getInstance()
{ /* Singleton: */
	static Command_Processor instance {};
	return instance;
}
/*------------------------------------------------------------------------------------------------------------------------*/



/* class Command Executor: */
/*------------------------------------------------------------------------------------------------------------------------*/
std::optional <std::string> COMMANDMANAGER::Command_Executor::readingStreamForExecution(const std::vector <std::string> &command_and_attribytes)
{
	/* The user input must contain the correct available command from [command_table]: */
	if ( command_and_attribytes.empty() )
		return "Empty command\n";

	/* Commands without additional attributes are not supported (except for [exit]): */
	if ( command_and_attribytes.size() < 2 && 
		command_and_attribytes[0] != "exit" &&
		command_and_attribytes[0] != "help")
	{
		return "Commands without attributes are not supported";
	}


	auto iterator = this->getInstanceCommandTable().find( command_and_attribytes[0] );
	if ( iterator != this->getInstanceCommandTable().end() )
	{
		std::vector <std::string> attribytes( command_and_attribytes.begin() + 1, command_and_attribytes.end() );
		iterator->second(attribytes);
	}
	else { return "Unknown command: [This command is not supported]"; }

	return std::nullopt;
}
/*------------------------------------------------------------------------------------------------------------------------*/
COMMANDMANAGER::Command_Executor::Command_Executor()
{
	this->command_table["menu"]  = std::bind(&Command_Menu::execute,  this->getCommandMenuObject(),  std::placeholders::_1);
	this->command_table["order"] = std::bind(&Command_Order::execute, this->getCommandOrderObject(), std::placeholders::_1);
	this->command_table["exit"]  = std::bind(&Command_Exit::execute,  this->getCommandExitObject(),  std::placeholders::_1);
	this->command_table["help"]  = std::bind(&Command_Help::execute,  this->getCommandHelpObject(),  std::placeholders::_1);
}
/*------------------------------------------------------------------------------------------------------------------------*/
std::unordered_map<std::string, CMG::FunctionExecute>& COMMANDMANAGER::Command_Executor::getInstanceCommandTable()
{
	return this->command_table;
}
/*------------------------------------------------------------------------------------------------------------------------*/
CMG::Command_Menu& CMG::Command_Executor::getCommandMenuObject()
{
	return this->command_menu_instance;
}
/*------------------------------------------------------------------------------------------------------------------------*/
CMG::Command_Order& COMMANDMANAGER::Command_Executor::getCommandOrderObject()
{
	return this->command_order_instance;
}
/*------------------------------------------------------------------------------------------------------------------------*/
CMG::Command_Exit& COMMANDMANAGER::Command_Executor::getCommandExitObject()
{
	return this->command_exit_instance;
}
/*------------------------------------------------------------------------------------------------------------------------*/
CMG::Command_Help& COMMANDMANAGER::Command_Executor::getCommandHelpObject()
{
	return this->command_help_instance;
}
/*------------------------------------------------------------------------------------------------------------------------*/