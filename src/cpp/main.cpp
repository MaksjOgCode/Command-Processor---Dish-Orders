#include "../hpp/command_manager.hpp"
#include "../hpp/menu_manager.hpp"
#include "../hpp/cpmenu_format.hpp"



int main (void)
{
	MMNG::Menu menu("Template Menu");

	CPMENU::createCPMENU("Template Menu");
	CPMENU::Reader reader_obj("Template Menu.cpmenu");
	reader_obj.openCPMENU();
	reader_obj.readCPMENU(menu);

	CMG::Data_Toolbox data_toolbox_instance;
	data_toolbox_instance.setMenuInstance(menu);
	CMG::startCommandProcessor();

	return 0;
}