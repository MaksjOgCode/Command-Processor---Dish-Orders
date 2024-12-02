#ifndef CPMENUFORMAT_HPP
#define CPMENUFORMAT_HPP



#include <fstream>
#include <string>
#include <expected>
#include <filesystem>
#include <iostream>
#include <limits>



#include "menu_manager.hpp"



/* CPMENU = Command Processor Menu! */
namespace CPMENUFILE
{
	/* Creates a specific file format for the application: */
	/* You can call the function that creates the .cpmenu file - using the correct path: */
	std::expected <void, std::string> createCPMENU(const std::string& name_file);

	class Reader
	{
	public:
		Reader  (const std::string &name_cpmenu_file);
		~Reader ();

		/* Only with parametre = const std::string &input_path_to_file: */
		Reader () = delete;
		Reader (const Reader&) = delete;
		Reader &operator= (const Reader&) = delete;

		/* Open a file [.cpmenu] of a specific format for reading data: */
		const std::expected <void, std::string> openCPMENU();

		/* Close the reading stream of the .cpmenu file: */
		const std::expected <void, std::string> closeCPMENU();

		const std::expected <void, std::string> readCPMENU(MMNG::Menu &menu_object);
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

	class AlgorithmsReader
	{
	public:
		AlgorithmsReader  () {};
		~AlgorithmsReader () {};

		/*  Only without parametres: Only default constuctor: */
		AlgorithmsReader (const Reader&) = delete;
		AlgorithmsReader &operator= (const Reader&) = delete;

		/* The function safely translates std::string to uint16_t: */
		/* If a correct translation is not possible, then std::nullopt will be returned: */
		std::optional <std::uint16_t> stringToUInt16(const std::string& input_str) const;

		/* A special function for taking values from a specific syntax in a .cpmenu file (numbers must be enclosed in [*], string literals in [""]): */
		/* If the syntax in the file is incorrect, then std::nullopt will be returned: */
		std::optional <std::string> extractValue(const std::string &input_line, const std::string &key_token, const size_t &start_key_token_pos, const char &delimiter);
		
		/* A function for correctly reading the attributes of the [new object] syntax in the .cpmenu file: */
		/* Incorrect syntax when reading the file - returns std::nullopt: */
		std::optional <std::string>  entityAnalyzerCPMENU(const std::string &input_line, std::unordered_map<std::string, std::string>& current_tokens, bool& new_object_opened);
	private:
	};
};
namespace CPMENU = CPMENUFILE;



#endif /* !CPMENUFORMAT_HPP! */