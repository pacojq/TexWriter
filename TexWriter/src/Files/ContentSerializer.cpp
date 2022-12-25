#include "twpch.h"
#include "ContentSerializer.h"

#include <fstream>
#include <filesystem>

namespace TexWriter {

    
	
	Ref<TWriterProject> ContentSerializer::Deserialize(const std::string& filename)
	{
        pugi::xml_document doc = ReadDoc(filename);
        pugi::xml_node root = doc.child("localization");

        pugi::xml_node meta = root.child("meta");
        std::string name = meta.child("name").child_value();

        TW_LOG_TRACE("Loading localization: '{}'", name);

        Ref<TWriterProject> content = CreateRef<TWriterProject>(name, filename);

        // TODO: Big ass to-do here
		/*
        // =================================== LANGUAGE FILES =================================== //

		struct LanguageFile
        {
            LanguageIso Iso;
            std::string Path;
        };
		
        // Language files that we are going to parse once the project is loaded
        std::vector<LanguageFile> filesVector;
        std::filesystem::path path(filename);
		
        pugi::xml_node languageFiles = meta.child("languageFiles");
        for (pugi::xml_node languageFile = languageFiles.child("languageFile"); languageFile; languageFile = languageFile.next_sibling("languageFile"))
        {
            LanguageIso iso = Language::FromString(languageFile.attribute("iso").value());
            std::string langFilename = languageFile.child_value();

            std::filesystem::path langPath = path.parent_path().append(langFilename);
        	
            LanguageFile lang = { iso , langPath.string() };
            filesVector.push_back(lang);
        }


        // ===================================== STRING IDS ===================================== //

        pugi::xml_node strings = root.child("stringIds");

        for (pugi::xml_node group = strings.child("stringGroup"); group; group = group.next_sibling("stringGroup"))
        {
            std::string groupName = group.attribute("name").value();
            std::string groupDescription = group.attribute("description").value();

            uint32_t groupId = content->GetStringBank()->AddGroup(groupName, groupDescription);
        	
            for (pugi::xml_node stringId = group.child("stringId"); stringId; stringId = stringId.next_sibling("stringId"))
            {
                std::string id = stringId.attribute("id").value();
                std::string description = stringId.attribute("description").value();

                content->GetStringBank()->AddString(id, description, groupId);
            }
        }

		
        // ===================================== LANGUAGES ===================================== //
        
		for (LanguageFile langFile : filesVector)
		{
            RosettaProjectLanguageBinding binding;

			bool result = DeserializeLanguage(langFile.Path, binding);
			if (!result)
			{
                TW_LOG_WARN("Could not load language file: [{0}] {1}", langFile.Iso, langFile.Path);
                continue;
			}
			
            content->AddExistingLanguage(langFile.Iso, binding);
		}
        */

        return content;
	}


    


    


	
	

	void ContentSerializer::Serialize(const Ref<TWriterProject>& content, const std::string& filename)
	{
        pugi::xml_document doc;
        pugi::xml_node root = CreateDoc(doc);


        pugi::xml_node meta = root.append_child("meta");
        pugi::xml_node gameName = meta.append_child("name");
        gameName.append_child(pugi::node_pcdata).set_value(content->GetName().c_str());


        // TODO: Big ass to-do here
        /*
        // =================================== LANGUAGE FILES =================================== //

        pugi::xml_node languageFiles = meta.append_child("languageFiles");

        for (auto pair : content->GetBindings())
        {
            pugi::xml_node langNode = languageFiles.append_child("languageFile");

            langNode.append_attribute("iso").set_value(Language::ToString(pair.first).c_str());
            langNode.append_child(pugi::node_pcdata).set_value(pair.second.Filename.c_str());
        }


        // ===================================== STRING IDS ===================================== //

        pugi::xml_node stringIds = root.append_child("stringIds");

        for (auto group : content->GetStringBank()->GetGroups())
        {
            pugi::xml_node groupNode = stringIds.append_child("stringGroup");
            groupNode.append_attribute("name").set_value(group.Name.c_str());
            groupNode.append_attribute("description").set_value(group.Description.c_str());


            for (auto stringId : content->GetStringBank()->GetStringsInGroup(group.Id))
            {
                pugi::xml_node stringNode = groupNode.append_child("stringId");

                stringNode.append_attribute("id").set_value(stringId.Id.c_str());
                if (stringId.Description.length() > 0)
                {
                    stringNode.append_attribute("description").set_value(stringId.Description.c_str());
                }
            }
        }
        */
        
		
		
        // ===================================== SAVE FILE ===================================== //
		
        bool success = doc.save_file(filename.c_str());
        if (!success)
        {
            TW_LOG_ERROR("Could not save localization in path '{}'", filename);
        }
        else TW_LOG_INFO("Localization saved in path '{}'", filename);

	}









	


    pugi::xml_node ContentSerializer::CreateDoc(pugi::xml_document& doc)
    {
        pugi::xml_parse_result res = doc.load_string("<!-- Rosetta  -  v0.0.1 - Meteorbyte Studios -->", pugi::parse_default | pugi::parse_comments | pugi::encoding_utf8);

        // add a custom declaration node
        pugi::xml_node decl = doc.prepend_child(pugi::node_declaration);
        decl.append_attribute("version") = "1.0";
        decl.append_attribute("encoding") = "utf-8";

        if (!res && res.status != pugi::status_no_document_element)
        {
            TW_LOG_ERROR("Parsing status: {}", res.status);
            TW_LOG_ERROR("Parsing error: {}", res.description());
            TW_ASSERT(false, "Something went wrong!");
        }

        pugi::xml_node root = doc.append_child("localization");
        return root;
    }

    pugi::xml_document ContentSerializer::ReadDoc(const std::string& filename)
    {
        pugi::xml_document doc;
        std::ifstream stream(filename);
        pugi::xml_parse_result result = doc.load(stream);

        TW_LOG_TRACE("Localization read file result: {}", result.description());

        if (result.status != pugi::xml_parse_status::status_ok)
        {
            if (result.status == pugi::xml_parse_status::status_file_not_found)
            {
                TW_ASSERT(false, "Could not load localization. File not found.");
            }
            else
            {
                TW_ASSERT(false, "Could not load localization.");
            }
        }
        return doc;
    }




	/*
    Ref<TForgeGraph> ContentSerializer::DeserializeImpl(pugi::xml_document& doc, const std::string& filename)
	{
        pugi::xml_node root = doc.child("localization");

        pugi::xml_node meta = root.child("meta");
        std::string name = meta.child("name").child_value();

        TW_LOG_TRACE("Loading localization: '{}'", name);

        Ref<TForgeGraph> content = CreateRef<TForgeGraph>(name, filename);


        // = = = = = = = = = = = = = = = = = = = = STRINGS = = = = = = = = = = = = = = = = = = = = = //

        pugi::xml_node strings = root.child("stringIds");

        for (pugi::xml_node stringId = strings.child("stringId"); stringId; stringId = stringId.next_sibling("stringId"))
        {
            std::string id = stringId.attribute("id").value();
            std::string description = stringId.attribute("description").value();

            content->GetStringBank()->AddString(id, description);
        }


        // = = = = = = = = = = = = = = = = = = =  LANGUAGES  = = = = = = = = = = = = = = = = = = = = //

        pugi::xml_node languages = root.child("languages");
        for (pugi::xml_node language = languages.child("language"); language; language = language.next_sibling("language"))
        {
            LanguageIso iso = Language::FromString(language.attribute("iso").value());
            content->AddLanguage(iso);

            auto lang = content->GetLanguage(iso);
        	

            // Iterate through XML strings

            pugi::xml_node string = language.child("string");
            for (pugi::xml_node string = language.child("string"); string; string = string.next_sibling("string"))
            {
                // TODO handle error if the stringId has not been declared

                auto id = string.attribute("stringId").value();
                if (lang->CreateString(id))
                {
                    auto& str = lang->GetString(id);
                    str.Content = string.child_value();
                }
            }
        }


        return content;
	}



	void ContentSerializer::SerializeImpl(const Ref<TForgeGraph>& content, pugi::xml_node& root)
    {
		// = = = = = = = = = = = = = = = = = = = = = META = = = = = = = = = = = = = = = = = = = = = //
		
        pugi::xml_node meta = root.append_child("meta");
		
        pugi::xml_node gameName = meta.append_child("name");
        gameName.append_child(pugi::node_pcdata).set_value(content->GetName().c_str());

        
        // = = = = = = = = = = = = = = = = = = = = STRINGS = = = = = = = = = = = = = = = = = = = = = //

        pugi::xml_node stringIds = root.append_child("stringIds");

        for (auto stringId : content->GetStringBank()->GetStrings())
        {
            pugi::xml_node stringNode = stringIds.append_child("stringId");

            stringNode.append_attribute("id").set_value(stringId.Id.c_str());

            if (stringId.Description.length() > 0)
            {
                stringNode.append_attribute("description").set_value(stringId.Description.c_str());
            }
        }


        // = = = = = = = = = = = = = = = = = = =  LANGUAGES  = = = = = = = = = = = = = = = = = = = = //

        pugi::xml_node languages = root.append_child("languages");
		
        for (auto language : content->GetLanguages())
        {
            pugi::xml_node langNode = languages.append_child("language");
            langNode.append_attribute("iso").set_value(Language::ToString(language->GetIso()).c_str());

            for (auto stringId : content->GetStringBank()->GetStrings())
            {
                if (language->StringExists(stringId.Id))
                {
                    auto str = language->GetString(stringId.Id);

                    pugi::xml_node stringNode = langNode.append_child("string");
                    stringNode.append_attribute("stringId").set_value(stringId.Id.c_str());
                    stringNode.append_child(pugi::node_pcdata).set_value(str.Content.c_str());
                }
            }
        }
    }
	 */



	
}
