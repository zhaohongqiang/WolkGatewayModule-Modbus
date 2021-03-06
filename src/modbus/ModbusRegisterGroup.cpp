/*
 * Copyright 2020 WolkAbout Technology s.r.o.
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

#include "ModbusRegisterGroup.h"

namespace wolkabout
{
ModbusRegisterGroup::ModbusRegisterGroup(const std::shared_ptr<ModbusRegisterMapping>& mapping)
: m_slaveAddress(-1)
, m_registerType(mapping->getRegisterType())
, m_dataType(mapping->getDataType())
, m_modbusRegisterMappings{mapping}
{
}

ModbusRegisterGroup::ModbusRegisterGroup(ModbusRegisterMapping::RegisterType registerType,
                                         ModbusRegisterMapping::DataType dataType)
: m_slaveAddress(-1), m_registerType(registerType), m_dataType(dataType), m_modbusRegisterMappings()
{
}

ModbusRegisterGroup::ModbusRegisterGroup(int slaveAddress, ModbusRegisterMapping::RegisterType registerType,
                                         ModbusRegisterMapping::DataType dataType)
: m_slaveAddress(slaveAddress), m_registerType(registerType), m_dataType(dataType), m_modbusRegisterMappings()
{
}

ModbusRegisterGroup::ModbusRegisterGroup(const ModbusRegisterGroup& group)
: m_slaveAddress(group.m_slaveAddress)
, m_registerType(group.m_registerType)
, m_dataType(group.m_dataType)
, m_modbusRegisterMappings()
{
    m_modbusRegisterMappings.clear();
    for (const auto& mapping : group.m_modbusRegisterMappings)
    {
        m_modbusRegisterMappings.push_back(mapping);
    }
}

int ModbusRegisterGroup::getSlaveAddress() const
{
    return m_slaveAddress;
}

ModbusRegisterMapping::RegisterType ModbusRegisterGroup::getRegisterType() const
{
    return m_registerType;
}

ModbusRegisterMapping::DataType ModbusRegisterGroup::getDataType() const
{
    return m_dataType;
}

int ModbusRegisterGroup::getStartingRegisterAddress() const
{
    const auto& front = m_modbusRegisterMappings.front();
    if (m_modbusRegisterMappings.empty() || front == nullptr)
    {
        // If there's no mappings
        return -1;
    }
    else if (front->getLabelsAndAddresses().empty())
    {
        // if it's only a single address
        return front->getAddress();
    }
    // if the addresses are in a labelMap, get the minimum
    int min = front->getLabelsAndAddresses().begin()->second;
    for (auto& label : front->getLabelsAndAddresses())
    {
        if (label.second < min)
        {
            min = label.second;
        }
    }
    return min;
}

int ModbusRegisterGroup::getMappingsCount() const
{
    return static_cast<int>(m_modbusRegisterMappings.size());
}

int ModbusRegisterGroup::getRegisterCount() const
{
    int count = 0;
    for (auto& mappings : m_modbusRegisterMappings)
    {
        count += mappings->getRegisterCount();
    }
    return count;
}

const std::vector<std::shared_ptr<ModbusRegisterMapping>>& ModbusRegisterGroup::getRegisters() const
{
    return m_modbusRegisterMappings;
}

void ModbusRegisterGroup::addRegister(const std::shared_ptr<ModbusRegisterMapping>& modbusRegisterMapping)
{
    m_modbusRegisterMappings.push_back(modbusRegisterMapping);
}

void ModbusRegisterGroup::setSlaveAddress(int slaveAddress)
{
    m_slaveAddress = slaveAddress;
}
}    // namespace wolkabout