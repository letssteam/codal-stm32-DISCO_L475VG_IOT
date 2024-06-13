#pragma once

#include <stdint.h>
#include <string.h>

template <typename T>
class Buffer {
  private:
    T* buffer;
    volatile size_t writeLocation;
    volatile size_t readLocation;
    size_t size;

  public:
    /** Create a Buffer and allocate memory for it
     *  @param size The size of the buffer
     */
    Buffer(size_t size = 0x100);

    /** Get the size of the ring buffer
     * @return the size of the ring buffer
     */
    size_t getSize();
    size_t getNbAvailable();

    /** Destry a Buffer and release it's allocated memory
     */
    ~Buffer();

    /** Add a data element into the buffer
     *  @param data Something to add to the buffer
     */
    void put(T data);

    /** Remove a data element from the buffer
     *  @return Pull the oldest element from the buffer
     */
    T get(void);

    /** Get the address to the head of the buffer
     *  @return The address of element 0 in the buffer
     */
    T* head(void);

    /** Reset the buffer to 0. Useful if using head() to parse packeted data
     */
    void clear(void);

    /** Determine if anything is readable in the buffer
     *  @return true if something can be read, false otherwise
     */
    bool available(void);

    /** Overloaded operator for writing to the buffer
     *  @param data Something to put in the buffer
     *  @return
     */
    Buffer& operator=(T data)
    {
        put(data);
        return *this;
    }

    /** Overloaded operator for reading from the buffer
     *  @return Pull the oldest element from the buffer
     */
    operator int(void) { return get(); }
};

template <typename T>
void Buffer<T>::put(T data)
{
    buffer[writeLocation] = data;

    ++writeLocation;
    writeLocation %= (this->size - 1);

    return;
}

template <typename T>
T Buffer<T>::get(void)
{
    T data_pos = buffer[readLocation];

    ++readLocation;
    readLocation %= (this->size - 1);

    return data_pos;
}

template <typename T>
T* Buffer<T>::head(void)
{
    T* data_pos = &buffer[0];

    return data_pos;
}

template <typename T>
bool Buffer<T>::available(void)
{
    return (writeLocation != readLocation);
}

template <typename T>
Buffer<T>::Buffer(size_t size)
{
    this->buffer = new T[size];
    this->size   = size;
    clear();
}

template <typename T>
Buffer<T>::~Buffer()
{
    delete[] this->buffer;
}

template <typename T>
size_t Buffer<T>::getSize()
{
    return this->size;
}

template <typename T>
size_t Buffer<T>::getNbAvailable()
{
    if (writeLocation >= readLocation) {
        return (writeLocation - readLocation);
    }
    else {
        return (size - readLocation + writeLocation);
    }
}

template <typename T>
void Buffer<T>::clear(void)
{
    writeLocation = 0;
    readLocation  = 0;

    memset(buffer, 0, size);
}