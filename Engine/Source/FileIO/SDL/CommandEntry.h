#pragma once

#include "FileIO/SDL/SdlTypeInfo.h"
#include "FileIO/SDL/ISdlResource.h"
#include "FileIO/SDL/SdlLoader.h"
#include "FileIO/SDL/SdlExecutor.h"

#include <string>
#include <vector>

namespace ph
{

class InputPacket;

class CommandEntry final
{
public:
	CommandEntry();

	CommandEntry& setTypeInfo(const SdlTypeInfo& typeInfo);
	CommandEntry& setLoader(const SdlLoader& loader);
	CommandEntry& addExecutor(const SdlExecutor& executor);

	SdlTypeInfo typeInfo() const;
	SdlLoader   getLoader() const;
	SdlExecutor getExecutor(const std::string& name) const;

private:
	SdlTypeInfo              m_typeInfo;
	SdlLoader                m_loader;
	std::vector<SdlExecutor> m_executors;
};

}// end namespace ph