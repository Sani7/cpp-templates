/*
  A simple ring buffer implementation as C++ template.

  Copyright (c) 2011 Hannes Flicka
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

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <algorithm>
#include <memory.h>

template <typename T> class ringbuffer
{
  public:
    /**
     * create a ringbuffer with space for up to size elements.
     */
    explicit ringbuffer(size_t size) : size(size), write_pos(0)
    {
        buffer = new T[size];
        memset(buffer, 0, sizeof(T) * size);
    }

    /**
     * copy constructor
     */
    ringbuffer(const ringbuffer<T> &rb)
    {
        this(rb.size);
        write_pos = rb.write_pos;
        memcpy(buffer, rb.buffer, sizeof(T) * size);
    }

    /**
     * destructor
     */
    ~ringbuffer()
    {
        delete[] buffer;
    }

    size_t write(const T *data, size_t n)
    {
        n = std::min(n, size);

        if (n == 0)
        {
            return n;
        }

        if (write_pos + n >= size)
        {
            size_t first_chunk = size - write_pos;
            memcpy(buffer + write_pos, data, sizeof(T) * first_chunk);
            memcpy(buffer, data + first_chunk, sizeof(T) * (n - first_chunk));

            write_pos = (write_pos + n) % size;
        }
        else
        {
            memcpy(buffer + write_pos, data, sizeof(T) * n);
            write_pos += n;
        }

        return n;
    }

    size_t read(T *dest, size_t n)
    {
        size_t read_pos = (write_pos + size - n) % size;
        n = std::min(n, size);

        if (n == 0)
        {
            return n;
        }

        if (read_pos + n >= size)
        {
            size_t first_chunk = size - read_pos;
            memcpy(dest, buffer + read_pos, sizeof(T) * first_chunk);
            memcpy(dest + first_chunk, buffer, sizeof(T) * (n - first_chunk));
        }
        else
        {
            memcpy(dest, buffer + read_pos, sizeof(T) * n);
        }

        return n;
    }

    void clear(void)
    {
        memset(buffer, 0, sizeof(T) * size);
    }

  private:
    T *buffer;
    size_t size;
    size_t write_pos;
};

#endif // RINGBUFFER_H
