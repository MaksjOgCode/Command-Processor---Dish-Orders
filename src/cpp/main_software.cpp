#include "../hpp/main_software.hpp"



int main (void)
{
	MMNG::Menu menu("Template Menu");

	CPMENU::createCPMENU("Template Menu");
	CPMENU::Reader reader_obj("Template Menu.cpmenu");
	reader_obj.openCPMENU();
	reader_obj.readCPMENU(menu);

	CMG::Command_Processor& command_processor_instance = CMG::Command_Processor::getInstance();
	CMG::Data_Toolbox data_toolbox_instance;
	data_toolbox_instance.setMenuInstance(menu);
	command_processor_instance.startCommandProcessor();

	return 0;
}