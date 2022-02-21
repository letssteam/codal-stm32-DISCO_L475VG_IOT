#include "Buffer.h"

// make the linker aware of some possible specialisation
template class Buffer<uint8_t>;
template class Buffer<int8_t>;
template class Buffer<uint16_t>;
template class Buffer<int16_t>;
template class Buffer<uint32_t>;
template class Buffer<int32_t>;
template class Buffer<uint64_t>;
template class Buffer<int64_t>;
template class Buffer<char>;
template class Buffer<wchar_t>;