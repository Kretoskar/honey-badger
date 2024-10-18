#include "HoneyBadgerCore/Core/Public/HBString.h"

char HoneyBadger::HBString::hashTable[HoneyBadger::HBString::hashTableSize][hashTableMaxStringLenght] = { {'\0'} };
HoneyBadger::HBString HoneyBadger::HBString::None = HoneyBadger::HBString();