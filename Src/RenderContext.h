#pragma once

#include "glm/glm.hpp"

namespace Catherine
{
	class IMaterial;
	class IVertexArray;

	class RenderContext
	{
	public:
		void SetMaterial(IMaterial * material) { m_Material = material; }
		IMaterial * GetMaterial() const { return m_Material; }

		void SetVertexArray(IVertexArray * va) { m_VertexArray = va; }
		IVertexArray * GetVertexArray() const { return m_VertexArray; }

		// position properties
		const glm::vec3 & GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3 & position) { m_Position = position; }

		// rotation properties
		const glm::vec3 & GetRotation() const { return m_Rotation; }
		void SetRotation(const glm::vec3 & rotation) { m_Rotation = rotation; }

		// scale properties
		const glm::vec3 & GetScale() const { return m_Scale; }
		void SetScale(const glm::vec3 & scale) { m_Scale = scale; }

		// cast shadow properties
		bool GetCastShadow() const { return m_CastShadow; }
		void SetCastShadow(bool value) { m_CastShadow = value; }

		// receive shadow properties
		bool GetReceiveShadow() const { return m_ReceiveShadow; }
		void SetReceiveShadow(bool value) { m_ReceiveShadow = value; }

		// model matrix properties
		const glm::mat4x4 & GetModelMatrix() const { return m_ModelMatrix; }

		// apply and calculate model matrix
		void Apply();

	private:
		IMaterial * m_Material = nullptr;
		IVertexArray * m_VertexArray = nullptr;

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);

		glm::mat4x4 m_ModelMatrix = glm::mat4x4(1.0f);

		bool m_CastShadow = true;
		bool m_ReceiveShadow = true;
	};
}