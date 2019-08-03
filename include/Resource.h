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

#ifndef RESOURCE_H
#define RESOURCE_H

#include <functional>

//namespace
namespace AlmaGrab {

/**
 *  Class functioning as a resource wrapper.
 *
 *  This class holds a pointer to a resource as well as it's deallocation function. It can be used to build a stack of
 *  deallocation functions to be called at the end of some scope.
 */
class Resource {
public:
  /**
   * Class constructor which creates a new instance.
   * @param ptr the resource handle.
   * @param deallocator the deallocation function.
   */
  template<typename T>
  Resource(T* ptr, std::function<void(const Resource*)> deallocator)
  : m_ptr(ptr)
  , m_typeid(const_cast<std::type_info&>(typeid(ptr)))
  , m_deallocator(deallocator) {};
  /**
   * Class move constructor.
   * @param other the instance to be moved.
   */
  Resource(Resource&& other)
  : m_ptr(other.m_ptr)
  , m_typeid(other.m_typeid)
  , m_deallocator(std::move(other.m_deallocator))
  {
    other.m_ptr = nullptr;
  };
  /**
   * Copy constructor.
   * Explicitly deleted.
   */
  Resource(const Resource&) = delete;
  /**
   * Copy assignment operator.
   * Explicitly deleted.
   */
  Resource& operator=(const Resource&) = delete;
  /**
   * Move assignment operator.
   * Explicitly deleted.
   */
  Resource& operator=(Resource&&) = delete;
  /**
   * Converts the internal handle back to the original type. Throws an exception if requested type doesn't match the
   * original one.
   * @return the casted resource pointer.
   */
  template<typename T>
  inline operator T() const
  {
    if(typeid(T) != m_typeid) {
      throw std::runtime_error("Invalid typecast");
    }

    return (T)m_ptr;
  }
  /**
   * Calls the supplied deallocation function.
   */
  inline void callDeallocator() const { m_deallocator(this); };
protected:
  void* m_ptr; /*!< the resource handle */
  std::type_info& m_typeid; /*!< the original type information */
  std::function<void(const Resource*)> m_deallocator; /*!< the deallocation function */
};

// End of namespace
}

#endif /* RESOURCE_H */
