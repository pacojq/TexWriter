#pragma once

#include "Core/Core.h"
#include "Core/Shader.h"

#include "ShaderUniforms/ShaderUniformBinding.h"

namespace TexWriter {

	class EditorLayer;


	class ShaderUniformsWindow
	{
	public:
		ShaderUniformsWindow(EditorLayer* editor);
		~ShaderUniformsWindow() = default;

		void BindUniforms(const Ref<Shader>& shader) const;

		void OnImGuiRender(bool* show);
		
		template<class T>
		inline void AddBinding(const std::string name) { m_Bindings.push_back(CreateRef<T>(name)); }


	public:
		void DrawBinding(ShaderUniformTextureBinding* binding);
		void DrawBinding(ShaderUniformVectorBinding* binding);
		void DrawBinding(ShaderUniformColorBinding* binding);

	private:
		void DrawBindingName(ShaderUniformBinding* binding);


	private:
		EditorLayer* m_Editor;

		std::vector<Ref<ShaderUniformBinding>> m_Bindings;
	};

}