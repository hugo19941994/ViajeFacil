/*
   pel_vector.hpp
   -----------------------------------
   PEL - UEM - 2014/2015 Academic Year
   -----------------------------------
   v4.0 - May 19, 2015
*/

#ifndef PEL_vector_HPP_INCLUDED
#define PEL_vector_HPP_INCLUDED

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include "./cereal/cereal.hpp"
#include "./cereal/access.hpp"
#include "./cereal/types/memory.hpp"
#include "./cereal/details/helpers.hpp"
#include "./cereal/details/util.hpp"
#include "./cereal/types/utility.hpp"
#include "./cereal/archives/binary.hpp"

namespace pel {

template<typename T> // T must be a type
class vector {
   T* v_,     // start of allocation
    * space_, // end of sequence, start of expansion
    * last_;  // end of allocated memory space

   void rangeCheck(std::size_t i)
   {
      if (i >= size())
         throw std::out_of_range{"Out of range index"};
   }
public:
   /////////////////////////////////////////////////////////////////////////////
   // construction/copy/destruction:

   vector() // create empty vector
      : v_{new T[0]}, space_{v_}, last_{v_} { }

   vector(std::size_t size, T const& val)
      : v_{new T[size]}, space_{v_ + size}, last_{space_}
   {
      try {
         for (std::size_t i = 0; i < size; ++i)
            v_[i] = val;
      }
      catch (...) {
         delete[] v_;
         throw;
      }
   }

   vector(std::initializer_list<T> const& list)
      : v_{new T[list.size()]}, space_{v_ + list.size()}, last_{space_}
   {
      try {
         auto p = v_;
         for (auto q = list.begin(); q != list.end(); ++p, ++q)
            *p = *q;
      }
      catch (...) {
         delete[] v_;
         throw;
      }
   }

   vector(vector<T> const& vec) // copy constructor
      : v_{new T[vec.size()]}, space_{v_ + vec.size()}, last_{space_}
   {
      try {
         for (std::size_t i = 0; i < vec.size(); ++i)
            v_[i] = vec[i];
      }
      catch (...) {
         delete[] v_;
         throw;
      }
   }

   vector<T>& operator=(vector<T> const& vec) // copy assignment operator
   {
      // copy-and-swap idiom (strong exception safety guarantee):
      vector<T> tmp{vec};
      std::swap(v_,tmp.v_);
      std::swap(space_,tmp.space_);
      std::swap(last_,tmp.last_);
      return *this;
   } // local tmp vector is destroyed at this point

   ~vector() { delete[] v_; } // destructor

   /////////////////////////////////////////////////////////////////////////////
   // modifiers:

   void push_back(T const& val) // strong exception safety guarantee
   {
      if (space_ == last_) { // capacity exhaustion
         auto const sz = size(), // original size
                    cp = (sz)? static_cast<std::size_t>(1.5*sz) : 2; // new capacity
         T* newBlock = new T[cp];
         try {
            for (std::size_t i = 0; i < sz; ++i)
               newBlock[i] = v_[i];
         }
         catch (...) {
            delete[] newBlock;
            throw;
         }
         delete[] v_;
         v_ = newBlock;
         space_ = v_ + sz;
         last_ = v_ + cp;
      }
      *space_ = val;
      ++space_;
   }

   void popBack() // calling popBack() on an empty container is undefined
   {
      --space_;
      *space_ = T{};
   }

   // iterator position must be valid and dereferenceable
   T* erase(T* position) // basic exception safety guarantee
   {
      for (T* p = position + 1; p != space_; ++p)
         *(p - 1) = *p;
      popBack();
      return position;
   }

   T* insert(T* position, T const& val)
   {
      if (space_ != last_ && position == space_) {
         *space_ = val;
         ++space_;
      }
      else if (space_ != last_) { // basic guarantee; more efficient
         *space_ = *(space_ - 1);
         ++space_;
         // copy the elements in [position,space_-2) to range ending at space_-1
         // The elements are copied in reverse order (the last element is copied
         // first), but their relative order is preserved
         auto it1 = space_ - 1,
              it2 = space_ - 2;
         while (position != it2)
            *(--it1) = *(--it2);
         *position = val;
      }
      else { // strong safety guarantee trivially satisfied
         std::size_t const n = position - v_;
         // increase the alloc
         auto const sz = size(),
                    cp = (sz)? static_cast<std::size_t>(1.5*size()) : 2;
         T* newBlock = new T[cp];
         try {
            for (std::size_t i = 0; i < n; ++i)
               newBlock[i] = v_[i];
            newBlock[n] = val;
            for (std::size_t i = n; i < sz; ++i)
               newBlock[i + 1] = v_[i];
         }
         catch (...) {
            delete[] newBlock;
            throw;
         }
         delete[] v_;
         v_ = newBlock;
         space_ = v_+ sz + 1;
         last_ = v_ + cp;
         position = v_ + n;
      }
      return position;
   }

   void resize(std::size_t n) {
       int const toDestroy = size() - n; // note: conversion to int
           if (toDestroy > 0) {
               for (int i = 0; i < toDestroy; ++i)
                   popBack();
       }
           else if (toDestroy < 0) {
               for (int i = toDestroy; i < 0; ++i)
                   push_back(T{});
       }
   }

   /////////////////////////////////////////////////////////////////////////////
   // capacity:

   std::size_t size()     const { return space_ - v_; }
   std::size_t capacity() const { return last_ - v_; }
   bool        empty()    const { return v_ == space_; }

   /////////////////////////////////////////////////////////////////////////////
   // access:

   T const& operator[](std::size_t i) const { return v_[i]; }
   T&       operator[](std::size_t i)       { return v_[i]; }

   T const& at(std::size_t i) const { rangeCheck(i); return v_[i]; }
   T&       at(std::size_t i)       { rangeCheck(i); return v_[i]; }

   T const& front() const { return *v_; }
   T&       front()       { return *v_; }

   T const& back() const { return *(space_ - 1); }
   T&       back()       { return *(space_ - 1); }

   /////////////////////////////////////////////////////////////////////////////
   // iterators:

   T const* begin() const { return v_; }
   T*       begin()       { return v_; }

   T const* end() const { return space_; }
   T*       end()       { return space_; }

    /////////////////////////////////////////////////////////////////////////////
    // serialization:
    template<class Archive>
      void save(Archive & archive) const
      {
          archive( cereal::make_size_tag(size()) );

          for(std::size_t i = 0; i < size(); i++) {
            archive( v_[i] );
          }
      }

      template<class Archive>
      void load(Archive & ar)
      {
          cereal::size_type sz;
          ar( cereal::make_size_tag( sz ) );

          resize(sz);

          for(std::size_t i = 0; i < sz; i++) {
            ar( v_[i] );
          }
      }

};

} // pel NAMESPACE

#endif // PEL_vector_HPP_INCLUDED
