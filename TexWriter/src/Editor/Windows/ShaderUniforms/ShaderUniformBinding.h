#pragma once

#include "Core/Core.h"

#include "Core/Shader.h"
#include "Core/Texture.h"

#include <glm/glm.hpp>

namespace TexWriter {

	class ShaderUniformsWindow;


	enum class UniformType
	{
		Int,
		Vector4,
		Texture
	};


	class ShaderUniformBinding
	{
	public:
		ShaderUniformBinding(const std::string name, UniformType type);

		inline const std::string GetName() const { return m_Name; }
		inline UniformType GetType() const { return m_Type; }

		virtual void Bind(const Ref<Shader>& shader) const = 0;
		virtual void Accept(ShaderUniformsWindow* uniformsWindow) = 0;

	protected:
		std::string m_Name;
		UniformType m_Type;
	};


	class ShaderUniformTextureBinding : public ShaderUniformBinding
	{
	public:
		inline ShaderUniformTextureBinding(const std::string name) : ShaderUniformBinding(name, UniformType::Texture) {}

		void Bind(const Ref<Shader>& shader) const override;
		void Accept(ShaderUniformsWindow* uniformsWindow) override;

		inline const Ref<Texture2D>& GetTexture() const { return m_Texture; }

		inline void SetTexture(std::string path)
		{
			Ref<Texture2D> tex = Texture2D::Create(path);
			if (tex.get())
			{
				//if (m_Texture != s_TexPink)
					m_Texture.reset();
				m_Texture = tex;
			}
		}

	public:
		static uint16_t s_SlotCount;

	private:
		Ref<Texture2D> m_Texture;
	};


	class ShaderUniformVectorBinding : public ShaderUniformBinding
	{
	public:
		inline ShaderUniformVectorBinding(const std::string name) 
			: ShaderUniformBinding(name, UniformType::Vector4), m_Value(0) {}

		void Bind(const Ref<Shader>& shader) const override;
		void Accept(ShaderUniformsWindow* uniformsWindow) override;

	private:
		glm::vec4 m_Value;
	};

}