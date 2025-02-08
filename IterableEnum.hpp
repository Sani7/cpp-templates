/*
  A way to iterate over enumerations as C++ template.

  Copyright (c) 2023 Sander Speetjens
  Licensed under the terms of the MIT license (given below).

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#pragma once

#define ITERABLE_ENUM_BEGIN(name)                                                                                      \
    enum class name : int                                                                                              \
    {
#define ITERABLE_ENUM_END                                                                                              \
    , end, begin = 0                                                                                                   \
    }

template <class T> class Iterable
{
  public:
    Iterable(T value = T::begin) : mValue(value)
    {
    }
    Iterable(const Iterable &other) : mValue(other.mValue)
    {
    }

    Iterable &operator++()
    {
        assert(mValue >= T::begin && mValue < T::end);
        mValue = static_cast<T>(static_cast<int>(mValue) + 1);
        return *this;
    }

    Iterable operator++(int)
    {
        Iterable prev = *this;
        mValue = static_cast<T>(static_cast<int>(mValue) + 1);
        return prev;
    }

    Iterable &operator--()
    {
        assert(mValue >= T::end && mValue < T::begin);
        mValue = static_cast<T>(static_cast<int>(mValue) - 1);
        return *this;
    }

    Iterable operator--(int)
    {
        Iterable prev = *this;
        mValue = static_cast<T>(static_cast<int>(mValue) - 1);
        return prev;
    }

    Iterable operator+(int i)
    {
        return static_cast<T>(static_cast<int>(mValue) + i);
    }

    Iterable operator+(T i)
    {
        return static_cast<T>(static_cast<int>(mValue) + static_cast<int>(i));
    }

    Iterable operator-(int i)
    {
        return static_cast<T>(static_cast<int>(mValue) - i);
    }

    Iterable operator-(T i)
    {
        return static_cast<T>(static_cast<int>(mValue) - static_cast<int>(i));
    }

    bool operator>(const T &other) const
    {
        return static_cast<int>(mValue) > static_cast<int>(other);
    }

    bool operator>=(const T &other) const
    {
        return static_cast<int>(mValue) >= static_cast<int>(other);
    }

    bool operator<(const T &other) const
    {
        return static_cast<int>(mValue) < static_cast<int>(other);
    }

    bool operator<=(const T &other) const
    {
        return static_cast<int>(mValue) <= static_cast<int>(other);
    }

    bool operator==(const T &other) const
    {
        return static_cast<int>(mValue) == static_cast<int>(other);
    }

    bool valid() const
    {
        return mValue != T::end;
    }

    operator T() const
    {
        return mValue;
    }
    operator T &()
    {
        return mValue;
    }
    T val() const
    {
        return mValue;
    }

  private:
    T mValue;
};