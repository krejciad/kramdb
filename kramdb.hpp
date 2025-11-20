/*---   kramdb.hpp - Library for simple in-RAM database system.   ---*/
/*---                   Created by: Adam Krejčí                   ---*/

/*---        Online:    https://github.com/krejciad/kramdb        ---*/
/*---        Documentation:                      README.md        ---*/
/*---        Licence:                          LICENCE.txt        ---*/
/*---        Licensed under CreativeCommons CC-BY-SA ©2025        ---*/


/*--- Defining library and dependencies. ---*/
#pragma once

#include <vector>
#include <string>
#include <sstream>

/*--- Variables types for identifying via NEW() function. ---*/
enum class TYPE {
	Boolean,
	Integer,
	String,
	Float
	// Here to expand ...
};

/*--- Object defining the form of one table cell. ---*/
class tableCellObj {
public:

	/*--- Entries for aviable variables types. ---*/
	std::vector<bool> cellBoolean;  // Vector for storing all instances of Boolean in current cell
	std::vector<int> cellInteger;  // Vector for storing all instances of Integer in current cell
	std::vector<std::string> cellString;  // Vector for storing all instances of String in current cell
	std::vector<float> cellFloat;  // Vector for storing all instances of Float in current cell
	// Here to expand ...

	/*--- Function for initializing new variable into current cell. ---*/
	void NEW(TYPE type) {  // Initialize a new instance of variable
		switch (type) {  // Select a data type from parameter
		case TYPE::Boolean:
			cellBoolean.push_back(false);  // Initialize a new instance of Boolean
			break;
		case TYPE::Integer:
			cellInteger.push_back(0);  // Initialize a new instance of Integer
			break;
		case TYPE::String:
			cellString.push_back("");  // Initialize a new instance of String
			break;
		case TYPE::Float:
			cellFloat.push_back(0.0f);  // Initialize a new instance of Float
			break;
		// Here to expand ...
		}
	}
};

/*--- Object defining the form of one table row. ---*/
class tableRowObj {
private:
	tableCellObj newCellObj;  // Initializing an object of tableCellObj class as template
public:
	std::vector<tableCellObj> CELL;  // Vector for storing all cells in current row
	void NEW() {  // Function for inicializing new cell in current row
		CELL.push_back(newCellObj);  // Saves instance of newCellObj object into vector
	}
};

/*--- Object defining the form of one table. ---*/
class tableObj {
private:
	tableRowObj newRowObj;  // Initializing an object of tableRowObj class as template
public:
	std::vector<tableRowObj> ROW;  // Vector for storing all rows in current table
	void NEW() {  // Function for inicializing new row in current table
		ROW.push_back(newRowObj);  // Saves instance of newRowObj object into vector
	}
};

/*--- Namespace for all default entries into system from user-side code. ---*/
namespace DB {

	/*--- Declaring, and duping instances of tables. ---*/
	std::vector<tableObj> TABLE;  // Vector for storing all tables globally
	tableObj newTableObj;  // Initializing an object of tableObj class as template
	void NEW() {  // Global function for inicializing new table
		TABLE.push_back(newTableObj);  // Saves instance of newTableObj object into vector
	}

	template <typename T>
	void REMOVE(std::vector<T>& onRemove, size_t toRemove) {
		if (toRemove < onRemove.size()) {
			onRemove.erase(onRemove.begin() + toRemove);
		}
	}

	/*--- Function for compact table print. ---*/
	std::string PRINT(tableObj& tableTemp) {

		/*--- Buffer for storing string to return. ---*/
		std::stringstream buffer;

		/*--- Identify the index of given table instance. ---*/
		size_t index;  // Identifier of given table
		auto target = std::find_if(DB::TABLE.begin(), DB::TABLE.end(), [&](const tableObj& t) { return &t == &tableTemp; });  // Gets locations of all tables in memory
		if (target != TABLE.end()) {  // Error handling - index out of range
			index = std::distance(DB::TABLE.begin(), target);  // Calculate relative index of given table
		} else { buffer << "TABLE[?]: ERR: index identification failed\n"; }  // Error - index out of range

		/*--- Formatting data into readable tree structure. ---*/
		for (size_t countRows = 0; countRows < tableTemp.ROW.size(); countRows++) {  // Lists all row objects stored in tableRow vector
			for (size_t countCells = 0; countCells < tableTemp.ROW[countRows].CELL.size(); countCells++) {  // Lists all cell objects stored in tableCell vector
				for (size_t countVarsBoolean = 0; countVarsBoolean < tableTemp.ROW[countRows].CELL[countCells].cellBoolean.size(); countVarsBoolean++) {  // Lists all instances of cellBoolean variable
					std::string cellBooleanReturn; if (tableTemp.ROW[countRows].CELL[countCells].cellBoolean[countVarsBoolean]) { cellBooleanReturn = "true"; }
					else { cellBooleanReturn = "false"; }  // Formatting bool output
					buffer << "DB::TABLE[" << index << "].ROW[" << countRows << "].CELL[" << countCells << "].cellBoolean[" << countVarsBoolean << "]="  // Output - variable value (prefix)
						<< cellBooleanReturn << "\n";  // Output - variable value
				}
				for (size_t countVarsInteger = 0; countVarsInteger < tableTemp.ROW[countRows].CELL[countCells].cellInteger.size(); countVarsInteger++) {  // Lists all instances of cellInteger variable
					buffer << "DB::TABLE[" << index << "].ROW[" << countRows << "].CELL[" << countCells << "].cellInteger[" << countVarsInteger << "]="  // Output - variable value (prefix)
						<< tableTemp.ROW[countRows].CELL[countCells].cellInteger[countVarsInteger] << "\n";  // Output - variable value
				}
				for (size_t countVarsString = 0; countVarsString < tableTemp.ROW[countRows].CELL[countCells].cellString.size(); countVarsString++) {  // Lists all instances of cellString variable
					buffer << "DB::TABLE[" << index << "].ROW[" << countRows << "].CELL[" << countCells << "].cellString[" << countVarsString << "]=\""  // Output - variable value (prefix)
						<< tableTemp.ROW[countRows].CELL[countCells].cellString[countVarsString] << "\"\n";  // Output - variable value
				}
				for (size_t countVarsFloat = 0; countVarsFloat < tableTemp.ROW[countRows].CELL[countCells].cellFloat.size(); countVarsFloat++) {  // Lists all instances of cellFloat variable
					buffer << "DB::TABLE[" << index << "].ROW[" << countRows << "].CELL[" << countCells << "].cellFloat[" << countVarsFloat << "]="  // Output - variable value (prefix)
						<< tableTemp.ROW[countRows].CELL[countCells].cellFloat[countVarsFloat] << "f\n";  // Output - variable value
				}
				// Here to expand ...
			}
		}

		/*--- Returns the formatted print as one string. ---*/
		return buffer.str();
	}

	/*--- Function for pretty-print of given table. ---*/
	std::string TREE(tableObj& tableTemp) {

		/*--- Buffer for storing string to return. ---*/
		std::stringstream buffer;

		/*--- Identify the index of given table instance. ---*/
		size_t index;  // Identifier of given table
		auto target = std::find_if(DB::TABLE.begin(), DB::TABLE.end(), [&](const tableObj& t) { return &t == &tableTemp; });  // Gets locations of all tables in memory
		if (target != TABLE.end()) {  // Error handling - index out of range
			index = std::distance(DB::TABLE.begin(), target);  // Calculate relative index of given table
			std::cout << "TABLE[" << index << "]:\n";  // Output - table description
		} else { std::cout << "TABLE[?]: ERR: index identification failed\n"; }  // Error - index out of range

		/*--- Formatting data into readable tree structure. ---*/
		for (size_t countRows = 0; countRows < tableTemp.ROW.size(); countRows++) {  // Lists all row objects stored in tableRow vector
			buffer << " | " << "TABLE[" << index << "].ROW[" << countRows << "]:" << "\n";  // Output - row description with prefix
			for (size_t countCells = 0; countCells < tableTemp.ROW[countRows].CELL.size(); countCells++) {  // Lists all cell objects stored in tableCell vector
				buffer << " |  | " << "TABLE[" << index << "].ROW[" << countRows << "].CELL[" << countCells << "]:" << "\n";  // Output - cell description with prefix
				for (size_t countVarsBoolean = 0; countVarsBoolean < tableTemp.ROW[countRows].CELL[countCells].cellBoolean.size(); countVarsBoolean++) {  // Lists all instances of cellBoolean variable
					std::string cellBooleanReturn; if (tableTemp.ROW[countRows].CELL[countCells].cellBoolean[countVarsBoolean]) { cellBooleanReturn = "true"; } else { cellBooleanReturn = "false"; }  // Formatting bool output
					buffer << " |  |  | " << "TABLE[" << index << "].ROW[" << countRows << "].CELL[" << countCells << "].cellBoolean[" << countVarsBoolean << "]: "  // Output - variable value (prefix)
						<< cellBooleanReturn << "\n";  // Output - variable value
				} if (tableTemp.ROW[countRows].CELL[countCells].cellBoolean.size() > 0) { buffer << " |  |  |\n"; }  // Structure formatting - end of var section
				for (size_t countVarsInteger = 0; countVarsInteger < tableTemp.ROW[countRows].CELL[countCells].cellInteger.size(); countVarsInteger++) {  // Lists all instances of cellInteger variable
					buffer << " |  |  | " << "TABLE[" << index << "].ROW[" << countRows << "].CELL[" << countCells << "].cellInteger[" << countVarsInteger << "]: "  // Output - variable value (prefix)
						<< tableTemp.ROW[countRows].CELL[countCells].cellInteger[countVarsInteger] << "\n";  // Output - variable value
				} if (tableTemp.ROW[countRows].CELL[countCells].cellInteger.size() > 0) { buffer << " |  |  |\n"; }  // Structure formatting - end of var section
				for (size_t countVarsString = 0; countVarsString < tableTemp.ROW[countRows].CELL[countCells].cellString.size(); countVarsString++) {  // Lists all instances of cellString variable
					buffer << " |  |  | " << "TABLE[" << index << "].ROW[" << countRows << "].CELL[" << countCells << "].cellString[" << countVarsString << "]: \""  // Output - variable value (prefix)
						<< tableTemp.ROW[countRows].CELL[countCells].cellString[countVarsString] << "\"\n";  // Output - variable value
				} if (tableTemp.ROW[countRows].CELL[countCells].cellString.size() > 0) { buffer << " |  |  |\n"; }  // Structure formatting - end of var section
				for (size_t countVarsFloat = 0; countVarsFloat < tableTemp.ROW[countRows].CELL[countCells].cellFloat.size(); countVarsFloat++) {  // Lists all instances of cellFloat variable
					buffer << " |  |  | " << "TABLE[" << index << "].ROW[" << countRows << "].CELL[" << countCells << "].cellFloat[" << countVarsFloat << "]: "  // Output - variable value (prefix)
						<< tableTemp.ROW[countRows].CELL[countCells].cellFloat[countVarsFloat] << "f\n";  // Output - variable value
				} if (tableTemp.ROW[countRows].CELL[countCells].cellFloat.size() > 0) { buffer << " |  |  |\n"; }  // Structure formatting - end of var section
				// Here to expand ...
				buffer << " |  |\n";  // Structure formatting - end of cell section
			} buffer << " |\n";  // Structure formatting - end of row section
		} buffer << "\n";  // Structure formatting - end of table

		/*--- Returns the formatted print as one string. ---*/
		return buffer.str();
	}

	/*--- Function for generating demo table. ---*/  // Usable for testing and debugging purposes
	void createDemoTable(tableObj& tableTemp) {
		tableTemp.NEW();
		tableTemp.NEW();
		tableTemp.ROW[0].NEW();
		tableTemp.ROW[0].NEW();
		tableTemp.ROW[1].NEW();
		tableTemp.ROW[1].NEW();
		tableTemp.ROW[1].NEW();
	}

	/*--- Function for choosing from multiple in-system easter eggs. ---*/  // Just because :3
	std::string easterEgg(int egg) {
		std::stringstream buffer;
		buffer << "EASTER_EGG: ";
		switch (egg) {
		case 1:
			buffer << "Erik je negr";
			break;
		default: break;
		} buffer << "\n";
		return buffer.str();
	}

}