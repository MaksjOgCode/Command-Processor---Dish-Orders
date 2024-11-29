#ifndef COMMANDMANAGER_HPP
#define COMMANDMANAGER_HPP



#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>



namespace COMMANDMANAGER
{
	/* Pattern Command: */
	class Command_Manager
	{
	public:
		~Command_Manager() = default;
		virtual void execute() = 0;
	};

	/* [> menu show] */
	class Command_Menu : public Command_Manager
	{
	public:
		void execute() override;
	private:
		inline void display();
		//Menu current_menu {};
	};

	/* [> order new] */
	class Command_Order : public Command_Manager
	{
	public:
		void execute() override;
	};

	class Command_Processor
	{
	private:
		/* std::string = The main token |  std::unordered_set <std::string> = Additional parameters */
		const std::unordered_map <std::string, std::unordered_set <std::string> > command_table
		{
			{ "menu",  {"show"} },
			{ "order", {"new", "add", "show"} }
		};
	};
};
namespace CMG = COMMANDMANAGER;



#endif /* !COMMANDMANAGER_HPP! */