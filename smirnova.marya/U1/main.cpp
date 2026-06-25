#include <fstream>
#include <iostream>
#include <string>

#include "input_handler.hpp"
#include "parse_line.hpp"
#include "person.hpp"
#include "vector.hpp"

int main(int argc, char* argv[])
{
  if (argc > 3)
  {
    std::cerr << "Invalid arguments." << std::endl;
    return 0;
  }

  std::string inputFileName;
  std::string outputFileName;
  bool hasOut = false;

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];

    if (arg.rfind("in:", 0) == 0)
    {
      inputFileName = arg.substr(3);
    }
    else if (arg.rfind("out:", 0) == 0)
    {
      if (hasOut)
      {
        std::cerr << "Invalid arguments." << std::endl;
        return 0;
      }

      outputFileName = arg.substr(4);
      hasOut = true;
    }
    else
    {
      std::cerr << "Invalid arguments." << std::endl;
      return 0;
    }
  }

  smirnova::InputHandler inputHandler(inputFileName);
  smirnova::Vector< smirnova::Person > persons;
  size_t validEntries = 0;
  size_t ignoredEntries = 0;

  smirnova::processInput(inputHandler.getInputStream(),
      persons, validEntries, ignoredEntries);

  if (validEntries == 0 && ignoredEntries == 0)
  {
    if (!hasOut)
    {
      std::cout << '\n';
    }
    return 0;
  }

  if (hasOut)
  {
    std::ofstream output(outputFileName.c_str());

    if (!output)
    {
      std::cerr << "Failed to open output file." << std::endl;
      return 2;
    }

    output << "in file " << outputFileName << '\n';
    smirnova::printPersons(persons, output);
  }
  else
  {
    smirnova::printPersons(persons, std::cout);
    std::cerr << validEntries << " " << ignoredEntries << std::endl;
  }

  return 0;
}
