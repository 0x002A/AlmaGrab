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

#ifndef NOTIFIABLE_H
#define NOTIFIABLE_H

#include <string>

//namespace
namespace AlmaGrab {

// Forward declaration
class Application;

/**
 *  Interface class implemented by notification targets.
 *
 *  This class act's as an interface for all recipients of notifications.
 */
class Notifiable {
public:
  /**
   * Class constructor which recieves a pointer to the application class instance.
   * @see AlmaGrab::Application
   * @param pApp the pointer to the application class instance.
   */
  explicit Notifiable(const Application* pApp)
  : m_pApp(pApp) {};

  /**
   * Pure virtual notification method to be implemented by deriving classes.
   * @param msg the message to be sent to the notification target.
   */
  virtual void notify(std::string msg) const = 0;
protected:
  const Application* m_pApp; /*!< a pointer to the application class instance */
};

// End of namespace
}

#endif /* NOTIFIABLE_H */
