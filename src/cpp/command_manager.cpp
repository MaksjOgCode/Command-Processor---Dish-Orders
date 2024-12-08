#include "../hpp/command_manager.hpp"



/* struct Data Toolbox: */
/*------------------------------------------------------------------------------------------------------------------------*/
void CMG::Data_Toolbox::setMenuInstance(const MMNG::Menu& input_menu_instance)
{
	current_menu_instance = input_menu_instance;
}
/*------------------------------------------------------------------------------------------------------------------------*/
const MMNG::Menu& CMG::Data_Toolbox::getMenuInstance()
{
	return current_menu_instance;
}
/*------------------------------------------------------------------------------------------------------------------------*/
const OMNG::Order& CMG::Data_Toolbox::getOrderInstance()
{
	return current_order_instance;
}
/*------------------------------------------------------------------------------------------------------------------------*/
/* Static fields: [Data Toolbox]: */
MMNG::Menu CMG::Data_Toolbox::current_menu_instance;
/*------------------------------------------------------------------------------------------------------------------------*/
OMNG::Order CMG::Data_Toolbox::current_order_instance;
/*------------------------------------------------------------------------------------------------------------------------*/



/* COMMAND "menu": */
/*------------------------------------------------------------------------------------------------------------------------*/
void CMG::Command_Menu::execute(const std::vector<std::string>& args)
{
	auto result_checking_arguments = this->checkingArguments(args);
	if ( result_checking_arguments.has_value() )
	{
		switch ( result_checking_arguments.value() )
		{
		case 0b0'0'1'1: /* flags 0'0'1'0 - [1] - The current argument is [show]? */
			this->toolbox_instance.getMenuInstance().displayMenu();
			break;

		case 0b0'1'0'1: /* flags 0'1'0'0 - [1] - The current argument is [help]? */
			this->getDescriptionCommand();
			break;

		default: /* If something went wrong: [What?] */
			std::cout << "[?] The command cannot be executed:\n\n";
			break;
		}

		return;
	}
	else
	{
		/* Output of the exception description: */
		std::cout << result_checking_arguments.error() << "\n\n";
		return;
	}
}
/*------------------------------------------------------------------------------------------------------------------------*/
std::expected <std::uint8_t, std::string> CMG::Command_Menu::checkingArguments(const std::vector<std::string>& args)
{
	/*
	* flags 0'0'0'1 - [1] - Checking the number of arguments;
	* flags 0'0'1'0 - [1] - The current argument is [show]?
	* flags 0'1'0'0 - [1] - The current argument is [help]?
	*/
	uint8_t flags = 0b0'1'1'1;

	/* The line will remain empty if all arguments are correct: */
	std::string error_description {};

	if ( args.size() != 1 )
	{ /* At the moment, only single arguments are supported: */
	  /* flags = 0b0000; */ /* Resetting all flags - arguments are not valid: */
		error_description = "[] Incorrect number of arguments - call \"help\" to clarify the supported attributes:\n";
		return std::unexpected(error_description);
	}

	if ( args[0] == "show" )
	{ /* The current argument is [show]? */
		flags &= 0b0'0'1'1;
		return flags;
	}
	else if ( args[0] == "help" )
	{ /* The current argument is [help]? */
		flags &= 0b0'1'0'1;
		return flags;
	}
	else
	{ /* Unknown argument: */
		/* flags = 0b0001; */
		error_description = "[] This argument is not supported - call \"help\" to clarify the supported attributes:\n";
		return std::unexpected(error_description);
	}
}
/*------------------------------------------------------------------------------------------------------------------------*/
void CMG::Command_Menu::getDescriptionCommand()
{
	std::cout << "\nDescription of the [menu] command: Managing the menu class:\n" <<
		"  Available command arguments:\n" <<
		"\t[1] \"show\"  Displays the current menu in the console: dishes, categories, descriptions, prices and ID's:\n" <<
		"\t[2] \"help\"  Displays a brief description of the current command and its arguments:\n\n";
}
/*------------------------------------------------------------------------------------------------------------------------*/



/* COMMAND "order": */
/*------------------------------------------------------------------------------------------------------------------------*/
void CMG::Command_Order::execute(const std::vector<std::string>& args)
{
	auto result_checking_arguments = this->checkingArguments(args);
	if ( result_checking_arguments.has_value() )
	{
		auto order = this->toolbox_instance.getOrderInstance();
		switch ( result_checking_arguments.value() )
		{
		case 0b0'0'0'0'0'1'1'1: /* [new] order? */
			order.createOrder(std::stoi( args[1] ));
			break;

		case 0b0'0'0'0'1'0'1'1: /* [show] order? */
			order.getItem( std::stoi(args[0]) ).displayOrder();
			break;

		case 0b0'0'1'1'0'0'0'1: /* [add] order by ID: */
			order.getItem( std::stoi( args[0] ) ).addMeal( std::stoi(args[2]), std::stoi(args[3]) ); 
			break;

		case 0b0'1'0'0'0'0'0'1: /* order [help]: */
			this->getDescriptionCommand();
			break;

		default: /* If something went wrong: [What?] */
			std::cout << "[?] The command cannot be executed:\n\n";
			break;
		}

		return;
	}
	else
	{
		/* Output of the exception description: */
		std::cout << result_checking_arguments.error() << "\n\n";
		return;
	}
}
/*------------------------------------------------------------------------------------------------------------------------*/
std::expected <std::uint8_t, std::string> CMG::Command_Order::checkingArguments(const std::vector<std::string>& args)
{
	/*
	* flags 0'0'0'0'0'0'0'[1] - [1] - Checking the number of arguments;
	* flags 0'0'0'0'0'0'[1]'0 - [1] - Arguments have 2 element?
	* flags 0'0'0'0'0'[1]'0'0 - [1] - Argument is [new]?
	* flags 0'0'0'0'[1]'0'0'0 - [1] - Argument is [show]?
	* flags 0'0'0'[1]'0'0'0'0 - [1] - Arguments have 4 element?
	* flags 0'0'[1]'0'0'0'0'0 - [1] - Argument is [add]?
	* flags 0'[1]'0'0'0'0'0'0 - [1] - Argument is [help]?
	*/
	uint8_t flags = 0b0'0'0'0'0'0'0'1;

	/* The line will remain empty if all arguments are correct: */
	std::string error_description {};

	/* Argument is [help]? */
	if (args.size() == 1)
	{
		if ( args[0] == "help" )
		{
			flags |= 0b0'1'0'0'0'0'0'1;
			return flags;
		}
	}

	/* Checking the number of arguments: */
	if (args.size() != 2 && args.size() != 4)
	{
		error_description = "[] Incorrect number of arguments - call \"help\" to clarify the supported attributes:\n";
		return std::unexpected(error_description);
	}

	/* handler for [new] and [show]: */
	if (args.size() == 2)
	{
		/* Arguments have 2 element: */
		flags |= 0b0'0'0'0'0'0'1'0;

		if (args[0] == "new")
		{
			/* Argument is [new]: */
			flags |= 0b0'0'0'0'0'1'0'0;

			/* Is the input number correct: */
			if ( this->isNumber(args[1]).has_value() ) { return flags; }
			else { return  std::unexpected("[1] " + this->isNumber(args[1]).error() + "\n[2] [] The second argument must be the [order-id]:\n"); }
		}
		else if ( this->isNumber(args[0]).has_value() )
		{
			/* Argument is [show]: */
			if ( args[1] == "show" ) { flags |= 0b0'0'0'0'1'0'0'0; return flags; }
			else { return  std::unexpected("[] The second argument must be the [show]\n"); }
		}
		else { return  std::unexpected("[1] " + this->isNumber(args[0]).error() + "\n[2] [] The first argument must be the [order-id] OR [new]\n"); }
	}
	else if (args.size() == 4)
	{
		/* Arguments have 4 element: */
		flags |= 0b0'0'0'1'0'0'0'0;

		if ( this->isNumber(args[0]).has_value() )
		{
			if (args[1] == "add")
			{
				/* Argument is [add]: */
				flags |= 0b0'0'1'0'0'0'0'0;
				if ( this->isNumber(args[2]).has_value() )
				{
					if ( this->isNumber(args[3]).has_value() ) { return flags; }
					else { return std::unexpected("[1] " + this->isNumber(args[3]).error() + "\n[2] [] The fourth argument must be the quantity\n"); }
				}
				else { return std::unexpected("[1] " + this->isNumber(args[2]).error() + "\n[2] [] The third argument must be the [meal-id]\n"); }
			}
			else { return std::unexpected("[] The second argument must be the [add]\n"); }
		}
		else  { return std::unexpected("[1] " + this->isNumber(args[3]).error() + "\n[2] [] The first argument must be the order-id\n"); }
	}
}
/*------------------------------------------------------------------------------------------------------------------------*/
std::expected <bool, std::string> CMG::Command_Order::isNumber(const std::string &input) const
{
	try 
	{
		std::stoi(input);
		return true;
	} catch (const std::invalid_argument &)
	{
		return std::unexpected("[] Invalud attribute [must number] [" + input + "] is not valid");
	} catch (const std::out_of_range &)
	{
		return std::unexpected("[] Out of range: \"" + input + "\" is out of the range of representable values");
	}
}
/*------------------------------------------------------------------------------------------------------------------------*/
void CMG::Command_Order::getDescriptionCommand()
{
	std::cout << "\nDescription of the [order] command: Managing the [order] class (Creating an order, editing, displaying):\n" <<
		"  Available command arguments:\n" <<
		"\t[1] \"[new] -> [order-id]\"  Creating a new order with a unique identifier {EXAMPLE: \"order new 102\"}:\n" <<
		"\t[2] \"[order-id] -> add [meal-id] [quantity]\"  Adding dishes (according to ID) and adding their quantity to the menu: {EXAMPLE: order 102 add 5 2}:\n" <<
		"\t[3] \"[order-id] -> show\"  Show the order with the specified ID: {EXAMPLE: order 102 show}:\n" <<
		"\t[4] \"[help]\"  Shows the full description of the current command: {EXAMPLE: order help}\n\n";
}
/*------------------------------------------------------------------------------------------------------------------------*/



/* COMMAND "exit": */
/*------------------------------------------------------------------------------------------------------------------------*/
void CMG::Command_Exit::execute(const std::vector<std::string>& args)
{
	auto result_checking_arguments = this->checkingArguments(args);
	if ( result_checking_arguments.has_value() )
	{
		switch ( result_checking_arguments.value() )
		{
		case 0b0'1'0'1: /* flags 0'1'0'0 - [1] - Call [exit] without argumets; */
			std::exit(0);
			break;

		case 0b0'0'1'1: /* flags 0'1'0'0 - [1] - The current argument is [help]? */
			this->getDescriptionCommand();
			break;

		default: /* If something went wrong: [What?] */
			std::cout << "[?] The command cannot be executed:\n\n";
			break;
		}

		return;
	}
	else
	{
		/* Output of the exception description: */
		std::cout << result_checking_arguments.error() << "\n\n";
		return;
	}
}
/*------------------------------------------------------------------------------------------------------------------------*/
std::expected <std::uint8_t, std::string> CMG::Command_Exit::checkingArguments(const std::vector<std::string>& args)
{
	/*
	* flags 0'0'0'1 - [1] - Checking the number of arguments;
	* flags 0'0'1'0 - [1] - The current argument is [help]?
	* flags 0'1'0'0 - [1] - Call [exit] without argumets;
	*/
	uint8_t flags = 0b0'1'1'1;

	/* The line will remain empty if all arguments are correct: */
	std::string error_description {};

	if ( args.size() > 1 )
	{ /* At the moment, only single arguments are supported: */
	  /* flags = 0b0000; */ /* Resetting all flags - arguments are not valid: */
		error_description = "[] Incorrect number of arguments - call \"help\" to clarify the supported attributes:\n";
		return std::unexpected(error_description);
	}

	if ( args.size() == 0 )
	{	/* Call [exit] without argumets: */
		flags &= 0b0101;
		return flags;
	}

	if ( args[0] == "help" )
	{ /* The current argument is [help]? */
		flags &= 0b0011;
		return flags;
	}
	else
	{ /* Unknown argument: */
	  /* flags = 0b0001; */
		error_description = "[] This argument is not supported - call \"help\" to clarify the supported attributes:\n";
		return std::unexpected(error_description);
	}
}
/*------------------------------------------------------------------------------------------------------------------------*/
void CMG::Command_Exit::getDescriptionCommand()
{
	std::cout << "\nDescription of the [exit] command: The \"exit\" command terminates the program :\n" <<
		"  Available command arguments:\n" <<
		"\t[1] \"help\"  Displays a brief description of the current command and its arguments:\n\n";
}
/*------------------------------------------------------------------------------------------------------------------------*/



/* COMMAND "help": */
/*------------------------------------------------------------------------------------------------------------------------*/
void CMG::Command_Help::execute(const std::vector<std::string>& args)
{
	auto result_checking_arguments = this->checkingArguments(args);
	if (result_checking_arguments.has_value())
	{
		if (result_checking_arguments.value() == 0b1'1'1'1)
		{
			/* If flags = 0b'1'1'1'1, then the command is correct: */
			this->getDescriptionCommand();
		}
		else
		{
			/* If something went wrong: [What?] */
			std::cout << "[?] The command cannot be executed:\n\n";
		}

		return;
	}
	else
	{
		/* Output of the exception description: */
		std::cout << result_checking_arguments.error() << "\n\n";
	}
}
/*------------------------------------------------------------------------------------------------------------------------*/
std::expected <std::uint8_t, std::string> CMG::Command_Help::checkingArguments(const std::vector<std::string>& args)
{
	/* flags 1'1'1'1 - [1] - If flags = 0b'1'1'1'1, then the command is correct: */
	uint8_t flags = 0b1'1'1'1;

	if ( args.size() != 0 )
	{
		flags = 0b0000;
		return std::unexpected("[] The help command is not used attributes:");
	}
	
	return flags;
}
/*------------------------------------------------------------------------------------------------------------------------*/
void CMG::Command_Help::getDescriptionCommand()
{
	/* help: */
	std::cout << "\n[!] Description of the [help] command: The \"help\" command displays a list of commands and their attributes:\n";

	/* menu: */
	std::cout << "\n[!] Description of the [menu] command: Managing the menu class:\n" <<
		"  Available command arguments:\n" <<
		"\t[1] \"show\"  Displays the current menu in the console: dishes, categories, descriptions, prices and ID's:\n" <<
		"\t[2] \"help\"  Displays a brief description of the current command and its arguments:\n\n";

	/* order: */
	std::cout << "\n[!] Description of the [order] command: Managing the [order] class (Creating an order, editing, displaying):\n" <<
		"  Available command arguments:\n" <<
		"\t[1] \"[new] -> [order-id]\"  Creating a new order with a unique identifier {EXAMPLE: \"order new 102\"}:\n" <<
		"\t[2] \"[order-id] -> add [meal-id] [quantity]\"  Adding dishes (according to ID) and adding their quantity to the menu: {EXAMPLE: order 102 add 5 2}:\n" <<
		"\t[3] \"[order-id] -> show\"  Show the order with the specified ID: {EXAMPLE: order 102 show}:\n" <<
		"\t[4] \"[help]\"  Shows the full description of the current command: {EXAMPLE: order help}\n\n";

	/* exit: */
	std::cout << "\n[!] Description of the [exit] command: The \"exit\" command terminates the program :\n" <<
		"  Available command arguments:\n" <<
		"\t[1] \"help\"  Displays a brief description of the current command and its arguments:\n\n";
}
/*------------------------------------------------------------------------------------------------------------------------*/



/* class Command Processor: */
/*------------------------------------------------------------------------------------------------------------------------*/
void CMG::Command_Processor::startCommandProcessor()
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
CMG::Command_Processor& CMG::Command_Processor::getInstance()
{ /* Singleton: */
	static Command_Processor instance {};
	return instance;
}
/*------------------------------------------------------------------------------------------------------------------------*/



/* class Command Executor: */
/*------------------------------------------------------------------------------------------------------------------------*/
std::optional <std::string> CMG::Command_Executor::readingStreamForExecution(const std::vector <std::string> &command_and_attribytes)
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
CMG::Command_Executor::Command_Executor()
{
	this->command_table["menu"]  = std::bind(&Command_Menu::execute,  this->getCommandMenuObject(),  std::placeholders::_1);
	this->command_table["order"] = std::bind(&Command_Order::execute, this->getCommandOrderObject(), std::placeholders::_1);
	this->command_table["exit"]  = std::bind(&Command_Exit::execute,  this->getCommandExitObject(),  std::placeholders::_1);
	this->command_table["help"]  = std::bind(&Command_Help::execute,  this->getCommandHelpObject(),  std::placeholders::_1);
}
/*------------------------------------------------------------------------------------------------------------------------*/
std::unordered_map<std::string, CMG::FunctionExecute>& CMG::Command_Executor::getInstanceCommandTable()
{
	return this->command_table;
}
/*------------------------------------------------------------------------------------------------------------------------*/
CMG::Command_Menu& CMG::Command_Executor::getCommandMenuObject()
{
	return this->command_menu_instance;
}
/*------------------------------------------------------------------------------------------------------------------------*/
CMG::Command_Order& CMG::Command_Executor::getCommandOrderObject()
{
	return this->command_order_instance;
}
/*------------------------------------------------------------------------------------------------------------------------*/
CMG::Command_Exit& CMG::Command_Executor::getCommandExitObject()
{
	return this->command_exit_instance;
}
/*------------------------------------------------------------------------------------------------------------------------*/
CMG::Command_Help& CMG::Command_Executor::getCommandHelpObject()
{
	return this->command_help_instance;
}
/*------------------------------------------------------------------------------------------------------------------------*/