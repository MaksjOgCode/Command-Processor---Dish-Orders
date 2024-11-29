#ifndef CPMENUFORMAT_HPP
#define CPMENUFORMAT_HPP



#include <fstream>
#include <string>
#include <expected>
#include <filesystem>
#include <iostream>



/* CPMENU = Command Processor Menu! */
namespace CPMENUFILE
{
	/* Creates a specific file format for the application: */
	std::expected <void, std::string> createCPMENU(const std::string& name_file);

	class Reader
	{
	public:
		Reader  (std::string &_input_path_to_file);
		~Reader ();

		/* Only with parametre = const std::string &input_path_to_file: */
		Reader () = delete;
		Reader (const Reader&) = delete;
		Reader &operator= (const Reader&) = delete;

		/* Open a file [.cpmenu] of a specific format for reading data: */
		const std::expected <void, std::string> openCPMENU();

		/* Close the reading stream of the .cpmenu file: */
		const std::expected <void, std::string> closeCPMENU();

		const std::expected <void, std::string> readCPMENU();
	private:
		/* Current [Menu] file: */
		std::ifstream input_cpmenu_file {};

		/* Path to the .cpmenu file: */
		std::string   input_path_to_file {};

		/* When calling the object constructor, a flag will be set in the current field: */
		std::expected <bool, std::string> file_status = false;

		/* The [openCPMENU()] function sets true, and the [closeCPMENU()] function sets false: */
		std::expected <bool, std::string> file_is_open = false;
	};
};
namespace CPMENU = CPMENUFILE;



#endif /* !CPMENUFORMAT_HPP! */