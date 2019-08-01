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

#ifndef APPLICATION_H
#define APPLICATION_H

#include <map>
#include <string>

//namespace
namespace AlmaGrab {

/**
 *  Class containing application related methods.
 *
 *  This class contains methods useful for solving application level tasks like parsing arguments.
 */
class Application {
public:
  /**
   * Class constructor which directly tries to parse the application arguments. Throws an exception in case of illegal
   * parameter format.
   * @see parseArguments(int argc, char* argv[])
   * @param argc the number of arguments supplied.
   * @param argv the argument values.
   */
  Application(int argc, char* argv[]);
  /**
   * Returns the parameter value if the parameter exists. Throws an exception otherwise.
   * @param name the name of the parameter.
   * @return the parameter value.
   */
  std::string requireParam(std::string name);
  /**
   * Copies the parameter value to the received std::string reference if the parameter exists.
   * @param name the name of the parameter.
   * @param refValue the std::string reference receiving the copy of the parameter value.
   */
  void getParam(std::string name, std::string& refValue);

  /**
   * Checks wether the parameter exists or not.
   * @param name the name of the parameter.
   * @return bool representing wether the parameter exists or not.
   */
  inline bool hasParam(std::string name) { return !(m_args.find(name) == m_args.end()); };
protected:
  /**
   * Parses the supplied arguments by using a regular expression. Skips the first argument which mostly contains the
   * executable name.
   * @param argc the number of arguments supplied.
   * @param argv the argument values.
   * @return a map containing the argument values assigned to their keys.
   */
  std::map<std::string, std::string> parseArguments(int argc, char* argv[]);

  std::map<std::string, std::string> m_args; /*!< a map containing the argument values assigned to their keys */
};

// End of namespace
}

#endif /* APPLICATION_H */