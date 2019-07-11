#include <MeshRenderer.h>
#include <WorldContext.h>
#include <RenderContext.h>
#include <ISceneObject.h>
#include <MeshFilter.h>
#include <IMesh.h>
#include <vector>

namespace Catherine
{
	void MeshRenderer::OnAddComponent(ISceneObject * owner)
	{

	}

	void MeshRenderer::OnRemoveComponent(ISceneObject * owner)
	{

	}

	void MeshRenderer::Update(float deltaTime)
	{
		// do some render update logic
	}

	ComponentKind MeshRenderer::GetComponentKind() const
	{
		return ComponentKind::MeshRenderer;
	}

	void MeshRenderer::Render(WorldContext * context)
	{
		ClearRenderContext();

		ISceneObject * tmp_owner = GetOwner();
		if (tmp_owner)
		{
			MeshFilter * tmp_meshFilter = (MeshFilter *)tmp_owner->GetComponent(ComponentKind::MeshFilter);
			if (tmp_meshFilter != nullptr)
			{
				const std::vector<IMaterial *> & tmp_materials = tmp_meshFilter->GetMaterials();
				const std::vector<IMesh *> & tmp_meshes = tmp_meshFilter->GetMeshes();

				for (size_t i = 0; i < tmp_meshes.size(); i++)
				{
					RenderContext * tmp_renderContext = new RenderContext();
					tmp_renderContext->SetMaterial(tmp_materials[i]);
					tmp_renderContext->SetVertexArray(tmp_meshes[i]->GetVertexArray());
					context->AddRenderContext(tmp_renderContext);
				}
			}
		}
	}

	void MeshRenderer::ClearRenderContext()
	{
		for (size_t i = 0; i < m_RenderContexts.size(); i++)
			delete m_RenderContexts[i];
		m_RenderContexts.clear();
	}
}