#pragma once
#include <cstdint>
#include <bitset>

using Entity = uint32_t; //Just a number.
using Signature = std::bitset<128>; //A 128 bit long entity signature. If you plan on registering more than 128 different types of components then you are gonna have to increase this.
using ComponentId = uint32_t; //Just a number.
using SystemId = uint32_t; //Just a number.