#include "../hpp/cpmenu_format.hpp"



/*------------------------------------------------------------------------------------------------------------------------*/
static const std::string ultimate_path = "menu//";
/*------------------------------------------------------------------------------------------------------------------------*/
std::expected <void, std::string> CPMENU::createCPMENU(const std::string& name_file = "Menu")
{ /* Creates a specific file format for the application: */
  /* Checking for the existence of a file with the same name: */
	std::ifstream check_file( (ultimate_path) + (name_file + ".cpmenu") );
	if ( check_file.good() )
	{
		check_file.close();
		return std::unexpected( "[CODE CPMENU-02] File with the same name already exists" );
	}

	/* Creating a new file and enabling the exception flag for the file stream: */
	std::ofstream cpmenu_file( (ultimate_path) + (name_file + ".cpmenu") );
	cpmenu_file.exceptions( std::ofstream::failbit | std::ofstream::badbit );

	/* Checking the status of the created file: */
	try
	{
		if ( cpmenu_file.is_open() )
		{
			cpmenu_file << "// This section of the comment is generated automatically: To use this format, read the rules for formatting the \".cpmenu\" file format\n\n";

			cpmenu_file.close();
		}
		else
			return std::unexpected( "[CODE CPMENU-00] Failed to open the created file" );
	}
	catch (const std::ios_base::failure& current_ex)
	{
		return std::unexpected( "[CODE CPMENU-01] I/O error: " + std::string( current_ex.what() ) );
	}

	return {};
}
/*------------------------------------------------------------------------------------------------------------------------*/
CPMENU::Reader::Reader(std::string& _input_path_to_file) : input_path_to_file(_input_path_to_file)
{
	_input_path_to_file += (ultimate_path);

	if (
		_input_path_to_file.empty() ||
		_input_path_to_file.length() < 7 ||
		_input_path_to_file.substr( input_path_to_file.length() - 7 ) != ".cpmenu"
		)
		this->file_status = std::unexpected( "[CODE CPMENU-11] Supported only .cpmenu format: [OR] The file has no name: [OR] The file path is empty" );
	else
		this->file_status = true;
}
/*------------------------------------------------------------------------------------------------------------------------*/
CPMENU::Reader::~Reader()
{
	if ( input_cpmenu_file.is_open() )
		closeCPMENU();
}
/*------------------------------------------------------------------------------------------------------------------------*/
const std::expected<void, std::string> CPMENU::Reader::openCPMENU()
{ /* Open a file [.cpmenu] of a specific format for reading data: */
	if ( file_status.value() == false )
		return std::unexpected( "[CODE CPMENU-12] Error opening the [.cpmenu] file - try to recreate the object" );

	input_cpmenu_file.open(ultimate_path + input_path_to_file);
	if ( input_cpmenu_file.is_open() )
		this->file_is_open = true;

	return {};
}
/*------------------------------------------------------------------------------------------------------------------------*/
const std::expected<void, std::string> CPMENU::Reader::closeCPMENU()
{ /* Close the reading stream of the .cpmenu file: */
	if ( file_status.value() == false )
		return std::unexpected( "[CODE CPMENU-13] You cannot close a file that has not been opened" );

	input_cpmenu_file.close();
	this->file_is_open = false;

	return {};
}
/*------------------------------------------------------------------------------------------------------------------------*/
const std::expected<void, std::string> CPMENU::Reader::readCPMENU()
{
	if ( file_is_open.value() == false )
		return std::unexpected("[CODE CPMENU-14] You cannot read the file that has not been opened");

	int aroma {};

	std::string temp {};
	while ( std::getline(input_cpmenu_file, temp) )
	{
		/* The comments section is ignored: */
		if ( temp.find("//") == 0 )
			continue;

		/* Empty lines are not perceived: */
		if ( temp.empty() )
			continue;

		/* The key syntax is [new dish] - denotes the creation of a new object: */
		if ( temp.find("new dish") == 0 )
		{
			++aroma;
			continue;
		}

		std::cout << temp << "\n";
	}

	std::cout << aroma << "\n";

	return std::expected<void, std::string>();
}
/*------------------------------------------------------------------------------------------------------------------------*/