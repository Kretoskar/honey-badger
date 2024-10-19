#pragma once

#include <string>

namespace HoneyBadger
{
    class HBString
    {
    public:
        HBString()
            : _hash(hashTableSize + 1) {}

        HBString(const char* s)
            : _hash(Hash(s)) {}

        HBString(std::string s)
            : _hash(Hash(s.c_str())) {}

        uint32_t GetHash() const { return _hash; }

        static HBString None;

    private:
        uint32_t _hash;

    public:
        const char* Get() const
        {
            return hashTable[_hash];
        }

    private:
        // hash using prime numbers
        static constexpr uint32_t Hash(const char* s)
        {
            uint32_t h = 37;
            uint32_t size = 0;

            while (*s)
            {
                h = (h * 54059) ^ (s[0] * 76963);
                size++;
                s++;
            }

            h %= hashTableSize;

            s = s - size;

#ifdef HB_DEBUG
            if (hashTable[h][0] != '\0')
            {
                HB_LOG_WARNING("REHASHING SPOTTED")
            }

            if (hashTable[h][0] != '\0')
            {
                for (unsigned i = 0; i < hashTableMaxStringLenght; i++)
                {
                    const char existingChar = hashTable[h][i];
                    const char newChar = *(s + i);

                    if (existingChar == newChar == '\0')
                    {
                        break;
                    }

                    if (existingChar != newChar)
                    {
                        HB_LOG_ERROR("HASH CONFLICT")
                    }
                }
            }
#endif

            unsigned i = 0;

            while (*s)
            {
                hashTable[h][i] = *s;
                i++;
                s++;
            }

            return h;
        }

        static constexpr uint32_t hashTableSize = 65536;
        static constexpr uint32_t hashTableMaxStringLenght = 256;
        static char hashTable[hashTableSize][hashTableMaxStringLenght];

    public:
        bool operator==(HBString&& other) const
        {
            return other._hash == _hash;
        }

        bool operator==(const HBString& other) const
        {
            return (other._hash == _hash);
        }

        bool operator<(const HBString other) const
        {
            return _hash < other._hash;
        }

        struct HBStringHasher
        {
            std::size_t operator()(const HBString& k) const
            {
                return k.GetHash();
            }
        };
    };
}