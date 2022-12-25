#pragma once

#include "Core/Core.h"
#include "Core/RenderPass.h"

#include <map>

namespace TexWriter {	

	class EditorLayer;

	class TWriterProject
	{
	public:
		TWriterProject(const std::string& name, const std::string& path);

		const std::string& GetName() const { return m_Name; }
		const std::string& GetPath() const { return m_Path; }

	public:
		void CompileShader(const EditorLayer* editor);

		inline const Ref<RenderPass> GetRenderPass() const { return m_RenderPass; }
		
	private:
		std::string m_Name;
		std::string m_Path;

		Ref<RenderPass> m_RenderPass;
	};
}
