#include "twpch.h"
#include "ShaderUniformBinding.h"

#include "Editor/Windows/ShaderUniformsWindow.h"


namespace TexWriter {

	ShaderUniformBinding::ShaderUniformBinding(const std::string name, UniformType type) 
		: m_Name(name), m_Type(type),
		  m_TempName(name), m_IsEditingName(false)
	{
	}


	uint16_t ShaderUniformTextureBinding::s_SlotCount = 0;

	void ShaderUniformTextureBinding::Bind(const Ref<Shader>& shader) const
	{
		if (m_Texture.get())
		{
			m_Texture->Bind(s_SlotCount);
		}
		s_SlotCount++;
	}
	void ShaderUniformTextureBinding::Accept(ShaderUniformsWindow* uniformsWindow)
	{
		uniformsWindow->DrawBinding(this);
	}


	void ShaderUniformVectorBinding::Bind(const Ref<Shader>& shader) const
	{
		shader->SetFloat4(m_Name, m_Value);
	}
	void ShaderUniformVectorBinding::Accept(ShaderUniformsWindow* uniformsWindow)
	{
		uniformsWindow->DrawBinding(this);
	}


	void ShaderUniformColorBinding::Bind(const Ref<Shader>& shader) const
	{
		shader->SetFloat4(m_Name, m_Value);
	}
	void ShaderUniformColorBinding::Accept(ShaderUniformsWindow* uniformsWindow)
	{
		uniformsWindow->DrawBinding(this);
	}

}