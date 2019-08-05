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

#ifndef CURLRESPONSEHELPER_H
#define CURLRESPONSEHELPER_H

#include <cstdlib>

//namespace
namespace AlmaGrab {

/**
 *  Class containing the implementation of the AlmaWeb observation target.
 *
 *  This class enables extracting relevant information by parsing the AlmaWeb web application.
 */
class CURLResponseHelper {
public:
  /**
   * Class constructor. Creates a well initialized instance of CURLResponseHelper.
   */
  CURLResponseHelper()
  : m_pData(nullptr)
  , m_size(0) {};
  /**
   * Class destructor. Free's the memory allocated to store the CURL response.
   */
  inline ~CURLResponseHelper() { std::free(m_pData); };
  /**
   * Getter returning the pointer to the internal piece of memory.
   * Attention: Get's invalid after CURLResponseHelper goes out of scope.
   * @return the pointer to the memory location containing the CURL response.
   */
  inline char* getData() { return m_pData; };
  /**
   * Getter returning the size of the allocated piece of memory.
   * @return the size of the allocated piece of memory.
   */
  inline size_t getSize() { return m_size; };
  /**
   * Internal non-static CURL callback used to store the response in memory.
   * @param buffer the pointer pointing to the data delivered by curl.
   * @param sz the size of a single element in bytes.
   * @param n the number of elements delivered by curl.
   * @return the number of bytes actually taken care of.
   */
  size_t internalCallback(void* buffer, size_t sz, size_t n);
  /**
   * Static callback function for curl.
   * The last parameter will be used to pass a pointer to an instance of CURLResponseHelper. This can be done using the
   * option CURLOPT_WRITEDATA. This way a non-static callback can be used.
   * @param buffer the pointer pointing to the data delivered by curl.
   * @param sz the size of a single element in bytes.
   * @param n the number of elements delivered by curl.
   * @param f the pointer to the instance of CURLResponseHelper used to call the internal non-static callback.
   * @return the number of bytes actually taken care of.
   */
  inline static size_t callback(void* buffer, size_t sz, size_t n, void* f)
  {
    // Call non-static member function.
    return static_cast<CURLResponseHelper*>(f)->internalCallback(buffer, sz, n);
  };
protected:
  char* m_pData; /*!< a pointer to the memory location used to store the CURL response */
  size_t m_size; /*!< the size of the memory allocated */
};

// End of namespace
}

#endif /* CURLRESPONSEHELPER_H */
