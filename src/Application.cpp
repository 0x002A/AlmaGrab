/***********************************************************************************************************************
                                _______           _______  _______  _______  _______
                               (  __   )|\     /|(  __   )(  __   )/ ___   )(  ___  )
                               | (  )  |( \   / )| (  )  || (  )  |\/   )  || (   ) |
                               | | /   | \ (_) / | | /   || | /   |    /   )| (___) |
                               | (/ /) |  ) _ (  | (/ /) || (/ /) |  _/   / |  ___  |
                               |   / | | / ( ) \ |   / | ||   / | | /   _/  | (   ) |
                               |  (__) |( /   \ )|  (__) ||  (__) |(   (__/\| )   ( |
                               (_______)|/     \|(_______)(_______)\_______/|/     \|

   MIT License

   Copyright (c) 2019 Kevin Klein

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
   documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
   rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
   Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
   WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
   COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
   OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 **********************************************************************************************************************/

#include "Application.h"

#include <regex>

AlmaGrab::Application::Application(int argc, char* argv[])
{
  if(argc > 1) {
    m_args = parseArguments(argc, argv);
  }
}

AlmaGrab::Application::~Application()
{
  // The map containing all managed resources act's like a LIFO stack
  // we have to iterate using reverse order an call all associated deallocator functions
  for(auto it = m_resIdx.rbegin(); it != m_resIdx.rend(); ++it) {
    m_resources.at(*it).callDeallocator();
  }
}

std::unordered_map<std::string, std::string>
AlmaGrab::Application::parseArguments(int argc, char* argv[])
{
  std::unordered_map<std::string, std::string> argsMap;

  // The value of argc will never be below zero, but we need to shut up the compiler because it's an int
  for(size_t i = 0; i < (size_t)argc; ++i) {
    // The first arg is the name of the executable -> drop it
    if(i == 0) {
      continue;
    }

    std::regex rgx("-([A-Za-z0-9]*)=([A-Za-z0-9:\\-,.]*)");
    std::smatch matches;
    std::string arg(argv[i]);

    if(std::regex_search(arg, matches, rgx)) {
      argsMap.insert(std::make_pair(matches[1].str(), matches[2].str()));
    } else {
      throw std::runtime_error("Illegal parameter format");
    }
  }

  return argsMap;
}

std::string
AlmaGrab::Application::requireParam(std::string name) const
{
  if(hasParam(name)) {
    return m_args.at(name);
  } else {
    throw std::runtime_error("Missing required parameter: " + name);
  }
}

void
AlmaGrab::Application::getParam(std::string name, std::string& refValue) const
{
  if(hasParam(name)) {
    refValue = m_args.at(name);
  }
}
