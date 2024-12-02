#include "../hpp/cpmenu_format.hpp"



/*------------------------------------------------------------------------------------------------------------------------*/
static const std::string ultimate_path = "..//menu//";
/*------------------------------------------------------------------------------------------------------------------------*/



/* You can call the function that creates the .cpmenu file - using the correct path: */
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
			cpmenu_file << "// This section of the comment is generated automatically: To use this format, read the rules for formatting the \".cpmenu\" file format\n// My github: https://github.com/MaksjOgCode\n\n";

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



/* Reader class: */
/*------------------------------------------------------------------------------------------------------------------------*/
CPMENU::Reader::Reader(const std::string &name_cpmenu_file)
{
	this->input_path_to_file = ultimate_path + name_cpmenu_file;

	if ( input_path_to_file.empty() || input_path_to_file.length() < 7 || input_path_to_file.substr( input_path_to_file.length() - 7 ) != ".cpmenu" )
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
const std::expected<void, std::string> CPMENU::Reader::readCPMENU(MMNG::Menu &menu_object)
{
	/* Protection against undefined behavior: */
	if ( file_is_open.value() == false )
		return std::unexpected("[CODE CPMENU-14] You cannot read the file that has not been opened");

	std::unordered_map <std::string, std::string> current_tokens {}; 	/* This is a box with information. The information is read from a file and divided into parts. We need this box to fill the MMNG menu: */
	
	CPMENUFILE::AlgorithmsReader object {}; 	/* It contains the necessary transformations, the hpp file has a full description: */
	
	bool new_object_opened = false; 	/* Flag for determining that the reading stream of a new object is opened [new object {]: */
	
	std::string temp {}; /* A temporary string to save a string read from a file: */

	/* The process of reading a file: */
	while ( std::getline(input_cpmenu_file, temp) )
	{
		/* The comments section is ignored when reading the file : */
		if ( temp.find("//") == 0 ) { continue; }

		/* Empty lines are not perceived when reading the file: */
		if ( temp.empty() ) { continue; }

		/* The key syntax is [new object] - denotes the creation of a new object: */
		if ( temp.find("new object {") == 0 )
		{ /* Flag state changes - when true, we will search for the necessary keywords [for example, "category", "dish"]: */
			new_object_opened = true;
			continue;
		}

		/* If the object was opened and we meet the closing token of the object: */
		if ( (temp.find("}") == 0 && new_object_opened) )
		{
			/* If all fields are read, we cannot save such data to the menu object: */
			if (current_tokens.size() != 5)
				return std::unexpected("Syntax error in the .cpmenu file: not all fields have been read [Required fields: category, dish, description, price, id]");

			/* Resetting the object reading flag: */
			new_object_opened = false;

			/* Temporary object to add to the [menu_object] object: */
			/* Converting string to uint16_t is safe - the algorithm filters out unsafe options during conversion: */
			MMNG::MenuItem temp_item (
				current_tokens["dish"],
				current_tokens["description"],
				std::stoul(current_tokens["price"]),
				std::stoul(current_tokens["id"])
			); 

			/* Filling in the read and processed data: */
			menu_object.insertItem(current_tokens["category"], temp_item);

			/* Clearing the read data is necessary for a new iteration of reading a new object from the file: */
			current_tokens.clear();
			continue;
		}

		/* The value from the method will be returned as std::nullopt if the function worked correctly: */
		/* Otherwise, the text will be returned in the form of a std::string detailed exception: */
		auto result_entity_analyzer = object.entityAnalyzerCPMENU(temp, current_tokens, new_object_opened);
		if (result_entity_analyzer == std::nullopt)
			continue;
		else
			return std::unexpected(*result_entity_analyzer);
	}

	return {};
}
/*--------------------------------------------------------------------------------------------- ---------------------------*/



/* AlgorithmsReader class: */
/*------------------------------------------------------------------------------------------------------------------------*/
std::optional <std::uint16_t>  CPMENU::AlgorithmsReader::stringToUInt16(const std::string& input_str) const
{
	if (input_str < "0" || input_str > std::to_string(std::numeric_limits<uint16_t>::max()) )
		return std::nullopt;
	
	int value = std::stoul(input_str);

	/* The translation is safe - you can return the value */
	return static_cast<uint16_t>(value);
}
/*------------------------------------------------------------------------------------------------------------------------*/
std::optional<std::string> CPMENUFILE::AlgorithmsReader::extractValue(const std::string& input_line, const std::string& key_token, const size_t& start_key_token_pos, const char& delimiter)
{
	/* A search that searches for the desired syntactic character [" (for string literals) OR * (for numbers)]: */
	size_t start_delimiter = input_line.find(delimiter, start_key_token_pos);
	if (start_delimiter != std::string::npos)
	{
		/* Search for a closed [" (for string literals) OR * (for numbers)]: */
		size_t end_delimiter = input_line.find(delimiter, start_delimiter + 1);
		if (end_delimiter != std::string::npos)
		{
			/* If the conditions are met (there is * (for numbers) or " (for string literals) ), then we read the word inside this construction: */
			return input_line.substr(start_delimiter + 1, end_delimiter - start_delimiter - 1);
		}
	}

	/* If (* (for numbers) OR " (for string literals) ) not found after the current token, you must follow the strict syntax of the file: */
	return std::nullopt;
}
/*------------------------------------------------------------------------------------------------------------------------*/
std::optional <std::string> CPMENUFILE::AlgorithmsReader::entityAnalyzerCPMENU(const std::string& input_line, std::unordered_map<std::string, std::string>& current_tokens, bool& new_object_opened)
{
	/* If the flag indicates a new object, we read its fields from the .cpmenu file: */
	/* Magic number [5] - currently there are only 5 fields available for reading: [category name, dish name, short description of the dish, price, ID] */
	/* Checking whether the size of the token structure is equal to 5 is some kind of protection against repeating fields: */
	/* Because the file is changing from the outside: */
	if (new_object_opened && current_tokens.size() != 5)
	{
		/* Syntax search in the file ["category ="]: */
		if ( input_line.find("category = ") != std::string::npos )
		{
			/* An attempt to take a value from a syntactic construct (if std::nullopt is returned, then there are no syntactic errors in the file - the capture was successful): */
			auto category_value = extractValue(input_line, "category = ", 12, '"');
			if ( category_value != std::nullopt )
			{
				current_tokens["category"] = *category_value;
				return std::nullopt;
			} /* If quotes are not found after the current token, it is worth observing the strict syntax of the file: */
			else { return "Syntax error in the .cpmenu file - values must have a strictly opening quotation mark and a closing quotation mark"; }

		} /* Syntax search in the file ["dish ="]: */
		else if ( input_line.find("dish = ") != std::string::npos )
		{
			/* An attempt to take a value from a syntactic construct (if std::nullopt is returned, then there are no syntactic errors in the file - the capture was successful): */
			auto dish_value = extractValue(input_line, "dish = ", 8, '"');
			if ( dish_value != std::nullopt )
			{
				current_tokens["dish"] = *dish_value;
				return std::nullopt;
			} /* If quotes are not found after the current token, it is worth observing the strict syntax of the file: */
			else { return "Syntax error in the .cpmenu file - values must have a strictly opening quotation mark and a closing quotation mark"; }

		} /* Syntax search in the file ["description ="]: */
		else if ( input_line.find("description = ") != std::string::npos )
		{
			/* An attempt to take a value from a syntactic construct (if std::nullopt is returned, then there are no syntactic errors in the file - the capture was successful): */
			auto description_value = extractValue(input_line, "description = ", 15, '"');
			if ( description_value != std::nullopt )
			{
				current_tokens["description"] = *description_value;
				return std::nullopt;
			} /* If quotes are not found after the current token, it is worth observing the strict syntax of the file: */
			else { return "Syntax error in the .cpmenu file - values must have a strictly opening quotation mark and a closing quotation mark"; }

		} /* Syntax search in the file ["price ="]: */
		else if ( input_line.find("price = ") != std::string::npos )
		{
			/* An attempt to take a value from a syntactic construct (if std::nullopt is returned, then there are no syntactic errors in the file - the capture was successful): */
			auto price_value = extractValue(input_line, "price = ", 9, '*');
			if ( price_value != std::nullopt )
			{ 
				/* If std::nullopt is returned, then a safe translation from a string literal to uint16_t is possible: */
				if ( stringToUInt16(*price_value) != std::nullopt)
				{
					current_tokens["price"] = *price_value;
					return std::nullopt;
				} /* Correct translation from a string literal to uint16_t is not possible: */
				else { return "Overflow error in the .cpmenu file numeric values [price or id] - must be greater than 0 and less than 65536 "; }
			} /* [If] * are not found after the current token, it is worth following the strict syntax of the file: */
			else { return "Syntax error in the .cpmenu file - numeric values must be strictly enclosed in [*]"; }
		}
		else if ( input_line.find("id = ") != std::string::npos )
		{
			/* An attempt to take a value from a syntactic construct (if std::nullopt is returned, then there are no syntactic errors in the file - the capture was successful): */
			auto id_value = extractValue(input_line, "price = ", 6, '*');
			if ( id_value != std::nullopt )
			{
				/* If std::nullopt is returned, then a safe translation from a string literal to uint16_t is possible: */
				if ( stringToUInt16(*id_value) != std::nullopt)
				{
					current_tokens["id"] = *id_value;
					return std::nullopt;
				} /* Correct translation from a string literal to uint16_t is not possible: */
				else { return "Overflow error in the .cpmenu file numeric values [price or id] - must be greater than 0 and less than 65536 "; }
			} /* [If] * are not found after the current token, it is worth following the strict syntax of the file: */
			else { return "Syntax error in the .cpmenu file - numeric values must be strictly enclosed in [*]"; }
		}
	}

	/* The function has been completed successfully - the structure for filling [Menu] is ready: */
	return std::nullopt;
}
/*------------------------------------------------------------------------------------------------------------------------*/