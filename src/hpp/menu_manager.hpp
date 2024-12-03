#ifndef MENUMANAGER_HPP
#define MENUMANAGER_HPP



#include <stdint.h>
#include <string>
#include <unordered_map>
#include <set>
#include <iostream>



namespace MENUMANAGER
{
	/* To work with dishes from the menu: */
	/*------------------------------------------------------------------------------------------------------------------------*/
	class MenuItem
	{
	public:
		MenuItem (const std::string &_name, const std::string &_description, const uint16_t &_price, uint16_t _id)
			: item {_name, _description, _price, _id}
		{
		}

		/* Getters section: */
		std::string   getName()        const noexcept { return item.name;        }
		std::string   getDescription() const noexcept { return item.description; }
		std::uint16_t getPrice()       const noexcept { return item.price;       }
		std::uint16_t getID()          const noexcept { return item.id;          }

		/* Setters section: */
		void setName(const std::string& input_name)               { this->item.name = input_name;               }
		void setDescription(const std::string& input_description) { this->item.description = input_description; }
		void setPrice(const std::uint16_t &input_price)           { this->item.price = input_price;             }
		void setID(const std::uint16_t &input_id)                 { this->item.id = input_id;                   }
	private:
		struct Item
		{
		public:
			/* The current name of the dish: */
			std::string name {};

			/* Short description of the dish: */
			std::string description {};

			/* The current price of the dish: */ 
			std::uint16_t price {};

			/* ID of the current dish: */
			std::uint16_t id {};
		};

		Item item {};
	};
	/*------------------------------------------------------------------------------------------------------------------------*/



	/* A class for menu management: */
	/*------------------------------------------------------------------------------------------------------------------------*/
	class Menu
	{
	public:
		Menu(std::string _name_menu) : name_menu(_name_menu) { }
		Menu() { name_menu = "+=+Default+=+"; }

		void insertItem(const std::string& category, const MenuItem& item) noexcept;

		void displayMenu() const noexcept;

		/* */
		const std::string getNameMenu() const noexcept;

		/* */
		void setNameMenu(const std::string &_name_menu);

	private:
		/* The dishes should be sorted by category - where the ID goes in ascending order: */
		struct MenuItemComparator
		{
		public:
			bool operator() (const MenuItem &lhs, const MenuItem &rhs) const noexcept { return lhs.getID() < rhs.getID(); }
		};

		/* std::string = Category | set <MenuItem> = Dishes */
		std::unordered_map <std::string, std::set <MenuItem, MenuItemComparator> > menu_map {};

		/* Current menu name: */
		std::string name_menu {};
	};
	/*------------------------------------------------------------------------------------------------------------------------*/
};
namespace MMNG = MENUMANAGER;



#endif /* !MENUMANAGER_HPP! */