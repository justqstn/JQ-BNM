#pragma once

#include <cstdint>

namespace IL2CPP
{
    namespace Offsets
    {
        static int64_t toCharArray = -1;
        static int64_t methodOffset = -1;
        static uint64_t offsetOfMethod(uint64_t start_ptr, uint64_t equal_ptr)
        {
            if (IL2CPP::Offsets::methodOffset == -1)
            {
                int depth = 512;
                for (int i = 0; i < depth; i++)
                {
                    if (*(void **)(start_ptr + i) == *(void **)(equal_ptr))
                    {
                        IL2CPP::Offsets::methodOffset = i;
                        return i;
                    }
                }

                return 0;
            }
            else
                return IL2CPP::Offsets::methodOffset;
        }

        static uint64_t offsetOfCharArray(void *start_ptr, int16_t value)
        {
            if (IL2CPP::Offsets::toCharArray == -1)
            {
                int depth = 512;
                for (int i = 0; i < depth; i++)
                {
                    if ((uint16_t)(*((char *)((void *)((uint64_t)start_ptr + i)))) == value)
                    {
                        IL2CPP::Offsets::toCharArray = i;
                        return i;
                    }
                }
                return 0;
            }
            else
                return IL2CPP::Offsets::toCharArray;
        }
    }
}