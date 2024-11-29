#include "../hpp/main_software.hpp"



int main (void)
{
	MMNG::MenuItem dish1("Bruschetta", "Tomato and basil bruschetta", 120, 2);
	MMNG::MenuItem dish2("Garlic Bread", "Garlic bread with cheese", 90, 1);
	MMNG::MenuItem dish3("Pasta Carbonara", "Pasta with bacon and cream sauce", 250, 4);
	MMNG::MenuItem dish4	("Steak", "Grilled steak with vegetables", 340, 3);

	MMNG::Menu menu("Base Menu");
	menu.insertItem("Appetizers",   dish1);
	menu.insertItem("Appetizers",   dish2);
	menu.insertItem("Main Courses", dish3);
	menu.insertItem("Main Courses", dish4);

	return 0;
}