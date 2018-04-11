/*
 * Copyright 2018 WolkAbout Technology s.r.o.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MODBUSREGISTERMAPPING_H
#define MODBUSREGISTERMAPPING_H

#include <memory>
#include <string>
#include <vector>

namespace wolkabout
{
class ModbusRegisterMapping
{
public:
    enum class RegisterType
    {
        INPUT_REGISTER,
        HOLDING_REGISTER,

        INPUT_BIT,
        COIL
    };

    enum class DataType
    {
        INT16,
        UINT16,

        REAL32,

        BOOL
    };

    ModbusRegisterMapping(std::string name, std::string reference, int address, RegisterType registerType,
                          DataType dataType);

    const std::string& getName() const;
    const std::string& getReference() const;

    RegisterType getRegisterType() const;
    DataType getDataType() const;

    int getAddress() const;

private:
    std::string m_name;
    std::string m_reference;

    int m_address;

    RegisterType m_registerType;
    DataType m_dataType;
};

class ModbusRegisterMappingFactory
{
public:
    static std::unique_ptr<std::vector<wolkabout::ModbusRegisterMapping>> fromJson(
      const std::string& modbusRegisterMappingFile);

private:
    static ModbusRegisterMapping::RegisterType deserializeRegisterType(const std::string& registerType);
    static ModbusRegisterMapping::DataType deserializeDataType(const std::string& dataType);
};
}    // namespace wolkabout

#endif
