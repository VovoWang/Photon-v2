#include "FileIO/SDL/CommandEntry.h"

#include <iostream>

namespace ph
{

CommandEntry::CommandEntry() : 
	m_typeInfo(SdlTypeInfo::makeInvalid()), m_loader(), m_executors()
{

}

CommandEntry& CommandEntry::setTypeInfo(const SdlTypeInfo& typeInfo)
{
	m_typeInfo = typeInfo;

	return *this;
}

CommandEntry& CommandEntry::setLoader(const SdlLoader& loader)
{
	m_loader = loader;

	return *this;
}

CommandEntry& CommandEntry::addExecutor(const SdlExecutor& executor)
{
	m_executors.push_back(executor);

	return *this;
}

SdlTypeInfo CommandEntry::typeInfo() const
{
	return m_typeInfo;
}

SdlLoader CommandEntry::getLoader() const
{
	return m_loader;
}

SdlExecutor CommandEntry::getExecutor(const std::string& name) const
{
	for(const auto& executor : m_executors)
	{
		if(executor.getName() == name)
		{
			return executor;
		}
	}

	return SdlExecutor();
}

}// end namespace ph