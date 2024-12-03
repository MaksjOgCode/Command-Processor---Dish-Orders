#include "command_manager.hpp"



/* COMMAND "menu": */
/*------------------------------------------------------------------------------------------------------------------------*/
void CMG::Command_Menu::execute(const std::vector<std::string>& args)
{
	std::cout << "Command_Menu\n";

	return;
}
/*------------------------------------------------------------------------------------------------------------------------*/



/* COMMAND "order": */
/*------------------------------------------------------------------------------------------------------------------------*/
void CMG::Command_Order::execute(const std::vector<std::string>& args)
{
	std::cout << "Command_Order\n";
}
/*------------------------------------------------------------------------------------------------------------------------*/



/* COMMAND "exit": */
/*------------------------------------------------------------------------------------------------------------------------*/
void COMMANDMANAGER::Command_Exit::execute(const std::vector<std::string>& args)
{

}
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
		std::cout << "User: [current user]: ";
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
{
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
		return "Empty command";

	/* Commands without additional attributes are not supported (except for [exit]): */
	if ( command_and_attribytes.size() < 2 && command_and_attribytes[0] != "exit")
		return "Commands without attributes are not supported";


	auto iterator = this->getInstanceCommandTable().find( command_and_attribytes[0] );
	if ( iterator != this->getInstanceCommandTable().end() )
	{
		std::vector <std::string> attribytes( command_and_attribytes.begin() + 1, command_and_attribytes.end() );
		iterator->second(attribytes);
	}
	else { return "Unknown command: [This command is not supported]"; }
}
/*------------------------------------------------------------------------------------------------------------------------*/
COMMANDMANAGER::Command_Executor::Command_Executor()
{
	this->command_table["menu"]  = std::bind(&Command_Menu::execute,  this->getCommandMenuObject(),  std::placeholders::_1);
	this->command_table["order"] = std::bind(&Command_Order::execute, this->getCommandOrderObject(), std::placeholders::_1);
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
std::unordered_map<std::string, CMG::FunctionExecute>& COMMANDMANAGER::Command_Executor::getInstanceCommandTable()
{
	return this->command_table;
}
/*------------------------------------------------------------------------------------------------------------------------*/