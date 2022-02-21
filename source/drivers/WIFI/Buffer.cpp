
/**
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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