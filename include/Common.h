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

/*! \mainpage AlmaGrab Documentation
 *
 * \section intro_sec Introduction
 *
 * This tool can be used to automatically parse the campus management system AlmaWeb and notify the user in case of changes.
 * It is designed to be easy extensible by implementing the desired interfaces (AlmaGrab::Notifiable, AlmaGrab::Watchable).
 *
 * \section install_sec Commandline Parameters
 *
 * Parameter     | Description
 * ------------- | -------------
 * tgtoken       | Token of the telegram bot used to send the messages 
 * tgchatid      | ChatID of the private messaging thread between the desired user and the telegram bot
 *
 */

#ifndef COMMON_H
#define COMMON_H

namespace AlmaGrab {

constexpr char RESOURCE_CURL[] = "curl";

constexpr char PARAM_TGTOKEN[] = "tgtoken";
constexpr char PARAM_TGCHATID[] = "tgchatid";

// End of namespace
}

#endif /* COMMON_H */
