#pragma once

#include "Core/Core.h"
#include "Project/TWriterProject.h"

#include <pugixml.hpp>

namespace TexWriter {

	class ContentSerializer
	{
	public:
		static Ref<TWriterProject> Deserialize(const std::string& filename);
		static void Serialize(const Ref<TWriterProject>& content, const std::string& filename);

	private:
		static pugi::xml_node CreateDoc(pugi::xml_document& doc);
		static pugi::xml_document ReadDoc(const std::string& filename);
		
		//static Ref<TForgeGraph> DeserializeImpl(pugi::xml_document& doc, const std::string& filename);
		//static void SerializeImpl(const Ref<TForgeGraph>& content, pugi::xml_node& root);
	};
	
}
