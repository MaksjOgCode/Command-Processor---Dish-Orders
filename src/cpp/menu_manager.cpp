#include "../hpp/menu_manager.hpp"



/*------------------------------------------------------------------------------------------------------------------------*/
void MENUMANAGER::Menu::insertItem(const std::string& category, const MenuItem& item) noexcept
{
	menu_map[category].insert(item);
}
/*------------------------------------------------------------------------------------------------------------------------*/
void MENUMANAGER::Menu::displayMenu() const noexcept
{
	if ( menu_map.empty() )
	{
		std::cout << "Menu is empty\n";
		return;
	}

	std::cout << "\n\n-------------------------------------------------\n\tDisplay menu: #" << this->name_menu << "\n-------------------------------------------------\n\n";
	for (const auto &category_and_dishes : menu_map)
	{
		std::cout << "-------------------------------------------------\n";
		std::cout << "  Category: " << category_and_dishes.first << "\n\n";
		for (const auto& dishes : category_and_dishes.second)
		{
			std::cout << "[!]";
			std::cout << " Name dish: "   << dishes.getName()        << "\n";
			std::cout << "    Description: " << dishes.getDescription() << "\n";
			std::cout << "    Price: "       << dishes.getPrice()       << "\n";
			std::cout << "    ID: "          << dishes.getID()          << "\n\n";
		}
		std::cout << "-------------------------------------------------\n\n";
	}
	std::cout << "-------------------------------------------------\n\n\n";

	return;
}
/*------------------------------------------------------------------------------------------------------------------------*/
const std::string MENUMANAGER::Menu::getNameMenu() const noexcept
{
	return this->name_menu;
}
/*------------------------------------------------------------------------------------------------------------------------*/
void MENUMANAGER::Menu::setNameMenu(const std::string& _name_menu)
{
	this->name_menu = _name_menu;
}
/*------------------------------------------------------------------------------------------------------------------------*/