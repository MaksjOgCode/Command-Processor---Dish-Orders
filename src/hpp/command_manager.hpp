#ifndef COMMANDMANAGER_HPP
#define COMMANDMANAGER_HPP



#include <string>
#include <iostream>



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
};
namespace CMG = COMMANDMANAGER;



#endif /* !COMMANDMANAGER_HPP! */