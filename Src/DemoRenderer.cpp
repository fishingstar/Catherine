#include <DemoRenderer.h>
#include <DemoMesh.h>
#include <VertexLayout.h>
#include <OpenGLProgram.h>
#include <OpenGLTexture.h>
#include <Material.h>
#include <Camera.h>
#include <Light.h>
#include <global.h>
#include <string>

namespace Catherine
{
	extern IDevice * g_Device;

	bool DemoRenderer::Initialize()
	{
		m_Camera = new Camera();
		m_Camera->SetPosition(glm::vec3(1.0f, 1.0f, 1.0f));
		m_Camera->SetRotation(glm::vec3(45.0f, -45.0f, 0.0f));
		m_Camera->SetProjectionMode(ProjectionMode::Persperctive);
		m_Camera->SetClearColor(glm::vec3(0.2f, 0.3f, 0.4f));

		CreateLights();

		IMesh * tmp_mesh = new DemoMesh();
		tmp_mesh->LoadFromFile(nullptr);

		unsigned int tmp_vertexSize = 0;
		const void * tmp_vertex = tmp_mesh->GetVertexBuffer(tmp_vertexSize);
		unsigned int tmp_indexSize = 0;
		const void * tmp_index = tmp_mesh->GetIndexBuffer(tmp_indexSize);
		const VertexLayout * tmp_layout = tmp_mesh->GetVertexLayout();

		unsigned int VBO;
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, tmp_vertexSize, tmp_vertex, GL_STATIC_DRAW);

		unsigned int tmp_count = tmp_layout->Count();
		for (unsigned int i = 0; i < tmp_count; ++i)
		{
			const VertexLayout::AttributeItem & tmp_item = tmp_layout->GetItem(i);
			glVertexAttribPointer(i, tmp_item.count, tmp_item.type, tmp_item.normalized, tmp_item.stride, (void *)tmp_item.offset);
			glEnableVertexAttribArray(i);
		}

		m_Material = new Material();
		m_Material->Initialize(nullptr);

		g_Device->SetFrontFace(FrontFaceMode::CounterClockwise);

		return true;
	}

	void DemoRenderer::Uninitialize()
	{

	}

	void DemoRenderer::PreRender()
	{

	}

	void DemoRenderer::Render()
	{
		const glm::vec3 & tmp_color = m_Camera->GetClearColor();
		g_Device->ClearColor(tmp_color.r, tmp_color.g, tmp_color.b, 1.0f);
		g_Device->Clear();

		const glm::vec3 & tmp_cameraPos = m_Camera->GetPosition();
		const glm::mat4x4 & tmp_view = m_Camera->GetViewMatrix();
		const glm::mat4x4 & tmp_projection = m_Camera->GetProjectionMatrix();
		m_Material->SetMat4x4("model", glm::mat4x4(1));
		m_Material->SetMat4x4("view", tmp_view);
		m_Material->SetMat4x4("projection", tmp_projection);
		m_Material->SetVec3("viewPos", tmp_cameraPos);
		m_Material->SetFloat("ambient", 0.2f);

		const glm::vec4 & tmp_lightColor = m_DirLight->GetLightColor();
		const glm::vec3 & tmp_lightDir = glm::vec3(0.3f, -0.3f, -0.6f);
		m_Material->SetVec3("dirLight.lightDir", tmp_lightDir);
		m_Material->SetVec4("dirLight.lightColor", tmp_lightColor);

		for (auto i = 0; i < 4; i++)
		{
			const glm::vec4 & tmp_pointColor = m_PointLight[i]->GetLightColor();
			const glm::vec3 & tmp_pointPos = m_PointLight[i]->GetPosition();
			float tmp_constant = m_PointLight[i]->GetAttenuationConstant();
			float tmp_linear = m_PointLight[i]->GetAttenuationLinear();
			float tmp_quadratic = m_PointLight[i]->GetAttenuationQuadratic();

			std::string tmp_key;
			std::string tmp_index = "pointLight[" + std::to_string(i) + "]";
			tmp_key = tmp_index + ".lightPos";
			m_Material->SetVec3(tmp_key.c_str(), tmp_pointPos);
			tmp_key = tmp_index + ".lightColor";
			m_Material->SetVec4(tmp_key.c_str(), tmp_pointColor);
			tmp_key = tmp_index + ".constant";
			m_Material->SetFloat(tmp_key.c_str(), tmp_constant);
			tmp_key = tmp_index + ".linear";
			m_Material->SetFloat(tmp_key.c_str(), tmp_linear);
			tmp_key = tmp_index + ".quadratic";
			m_Material->SetFloat(tmp_key.c_str(), tmp_quadratic);
		}

		const glm::vec4 tmp_spotColor = m_SpotLight->GetLightColor();
		const glm::vec3 tmp_spotPos = m_SpotLight->GetPosition();
		const glm::vec3 tmp_spotDir = glm::vec3(0.0f, 0.0f, -1.0f);
		float tmp_constant = m_SpotLight->GetAttenuationConstant();
		float tmp_linear = m_SpotLight->GetAttenuationLinear();
		float tmp_quadratic = m_SpotLight->GetAttenuationQuadratic();
		m_Material->SetVec3("spotLight.lightPos", tmp_spotPos);
		m_Material->SetVec4("spotLight.lightColor", tmp_spotColor);
		m_Material->SetVec3("spotLight.lightDir", tmp_spotDir);
		m_Material->SetFloat("spotLight.innerCutoff", glm::cos(glm::radians(45.0)));
		m_Material->SetFloat("spotLight.outerCutoff", glm::cos(glm::radians(60.0)));
		m_Material->SetFloat("spotLight.constant", tmp_constant);
		m_Material->SetFloat("spotLight.linear", tmp_linear);
		m_Material->SetFloat("spotLight.quadratic", tmp_quadratic);

		m_Material->Use();

		glBindVertexArray(m_VAO);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void DemoRenderer::PostRender()
	{

	}

	void DemoRenderer::CreateLights()
	{
		m_DirLight = new Light();
		m_DirLight->SetLightType(LightType::Directional);
		m_DirLight->SetLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		glm::vec3 tmp_pos[4] = {
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(1.0f, 1.0f, 1.0f)
		};

		glm::vec4 tmp_color[4] = {
			glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
			glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
			glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
		};

		for (auto i = 0; i < 4; i++)
		{
			m_PointLight[i] = new Light();
			m_PointLight[i]->SetLightType(LightType::Point);
			m_PointLight[i]->SetLightColor(tmp_color[i]);
			m_PointLight[i]->SetPosition(tmp_pos[i]);
		}

		m_SpotLight = new Light();
		m_SpotLight->SetLightType(LightType::Spot);
		m_SpotLight->SetLightColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
		m_SpotLight->SetPosition(glm::vec3(0.0f, 0.0f, 0.7f));
		m_SpotLight->SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	}
}
