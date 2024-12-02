#include "../hpp/main_software.hpp"
#include <stack>



class Command_Processor
{
public:
	void displayLogica(const std::stack <std::string> &input_commands) const noexcept
	{
	
	}
private:
	/* std::string = The main token |  std::unordered_set <std::string> = Additional parameters */
	const std::unordered_map <std::string, std::unordered_set <std::string> > command_table
	{
		{ "menu",  {"show"} },
		{ "order", {"new", "add", "show"} }
	};
};



std::stack <std::string> getCommands(const std::string &input_string)
{
	std::istringstream input_stream(input_string);

	std::stack<std::string> words_stack;

	std::string current_word;
	while (input_stream >> current_word)
		words_stack.push(current_word);

	while ( !words_stack.empty() )
	{
		std::cout << words_stack.top() << "\n";
		words_stack.pop();
	}

	return words_stack;
}



int main (void)
{
	std::cout << "Welcome:\n";
	//std::string input_string {};
 //  while (true)
 //  {
 //     std::cin >> input_string;
	//	getCommands(input_string);
 //  }

	MMNG::Menu menu("Base Menu");

	CPMENU::createCPMENU("Template Menu");
	CPMENU::Reader reader_obj("Template Menu.cpmenu");
	reader_obj.openCPMENU();
	reader_obj.readCPMENU(menu);

	menu.displayMenu();

	return 0;
}