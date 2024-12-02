#include "../hpp/menu_manager.hpp"



/*------------------------------------------------------------------------------------------------------------------------*/
void MENUMANAGER::Menu::insertItem(const std::string& category, const MenuItem& item) noexcept
{
	menu_map[category].insert(item);
}
/*------------------------------------------------------------------------------------------------------------------------*/
void MENUMANAGER::Menu::displayMenu() const noexcept
{
	std::cout << "[MENU]: " << this->name_menu << "\n";
	for (const auto &category_and_dishes : menu_map)
	{
		std::cout << "\n\n\nCategory: " << category_and_dishes.first << "\n";
		std::cout << "==================================================\n";
		for (const auto& dishes : category_and_dishes.second)
		{
			std::cout << "--------------------------------------------------\n";
			std::cout << "Name dish: "   << dishes.getName()        << "\n";
			std::cout << "Description: " << dishes.getDescription() << "\n";
			std::cout << "Price: "       << dishes.getPrice()       << "\n";
			std::cout << "ID: "          << dishes.getID()          << "\n";
			std::cout << "--------------------------------------------------\n";
		}
	}
	std::cout << "==================================================\n";

	return;
}
/*------------------------------------------------------------------------------------------------------------------------*/