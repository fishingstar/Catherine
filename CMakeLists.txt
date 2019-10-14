# minimum version
cmake_minimum_required (VERSION 2.8)

set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)

# project name
project (Catherine)

# #configure file
# configure_file (
# 	"${PROJECT_SOURCE_DIR}/config.h.in"
# 	"${PROJECT_BINARY_DIR}/config.h"
# 	)

# # defines
# option (USE_MYFUNCTION "Use provided function" ON)

# if (USE_MYFUNCTION)
# 	include_directories("${PROJECT_SOURCE_DIR}/function")
# 	add_subdirectory(function)
# 	set(EXTRA_LIBS ${EXTRA_LIBS} functionlib)
# endif (USE_MYFUNCTION)

# header file directories
include_directories(
	"${PROJECT_SOURCE_DIR}/Src/glad/include"
	"${PROJECT_SOURCE_DIR}/Src/thirdparty/assimp/include"
	"${PROJECT_SOURCE_DIR}/Src/thirdparty/glm"
	"${PROJECT_SOURCE_DIR}/Src/thirdparty/glfw/include"
	"${PROJECT_SOURCE_DIR}/Src/thirdparty/stb_image/include"
)

# lib file directories
link_directories(
	"${PROJECT_SOURCE_DIR}/Src/thirdparty/glfw/lib"
	"${PROJECT_SOURCE_DIR}/Src/thirdparty/assimp/lib"
)

#################Souce Files#################

# Client
SET(Src_Client
	"${PROJECT_SOURCE_DIR}/Src/Client.h"
	"${PROJECT_SOURCE_DIR}/Src/Client.cpp"
)
source_group(Client FILES ${Src_Client})

# Device\\Common
SET(Src_Device_Common
	"${PROJECT_SOURCE_DIR}/Src/AttributeLayout.h"
	"${PROJECT_SOURCE_DIR}/Src/DeviceCommon.h"
	"${PROJECT_SOURCE_DIR}/Src/DeviceConst.h"
	"${PROJECT_SOURCE_DIR}/Src/DeviceConst.cpp"
	"${PROJECT_SOURCE_DIR}/Src/DeviceFactory.h"
	"${PROJECT_SOURCE_DIR}/Src/DeviceFactory.cpp"
	"${PROJECT_SOURCE_DIR}/Src/IDevice.h"
	"${PROJECT_SOURCE_DIR}/Src/ITexture.h"
	"${PROJECT_SOURCE_DIR}/Src/IProgram.h"
	"${PROJECT_SOURCE_DIR}/Src/IIndexBuffer.h"
	"${PROJECT_SOURCE_DIR}/Src/IVertexBuffer.h"
	"${PROJECT_SOURCE_DIR}/Src/IVertexArray.h"
	"${PROJECT_SOURCE_DIR}/Src/IRenderTarget.h"
	"${PROJECT_SOURCE_DIR}/Src/ISampler.h"
	"${PROJECT_SOURCE_DIR}/Src/IStorageBuffer.h"
)
source_group(Device\\Common FILES ${Src_Device_Common})

# Device\\OpenGL
SET(Src_Device_OpenGL
	"${PROJECT_SOURCE_DIR}/Src/glad/src/glad.c"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLBuffer.h"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLBuffer.cpp"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLCommon.h"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLCommon.cpp"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLDevice.h"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLDevice.cpp"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLIndexBuffer.h"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLIndexBuffer.cpp"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLVertexBuffer.h"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLVertexBuffer.cpp"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLVertexArray.h"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLVertexArray.cpp"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLTexture.h"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLTexture.cpp"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLCubeTexture.h"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLCubeTexture.cpp"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLProgram.h"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLProgram.cpp"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLRenderTarget.h"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLRenderTarget.cpp"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLSampler.h"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLSampler.cpp"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLStorageBuffer.h"
	"${PROJECT_SOURCE_DIR}/Src/OpenGLStorageBuffer.cpp"
)
source_group(Device\\OpenGL FILES ${Src_Device_OpenGL})

# Global
SET(Src_Global
	"${PROJECT_SOURCE_DIR}/Src/global.cpp"
)
source_group(Global FILES ${Src_Global})

# Render\\Context
SET(Src_Render_Context
	"${PROJECT_SOURCE_DIR}/Src/CameraContext.h"
	"${PROJECT_SOURCE_DIR}/Src/CameraContext.cpp"
	"${PROJECT_SOURCE_DIR}/Src/LightContext.h"
	"${PROJECT_SOURCE_DIR}/Src/LightContext.cpp"
	"${PROJECT_SOURCE_DIR}/Src/RenderContext.h"
	"${PROJECT_SOURCE_DIR}/Src/RenderContext.cpp"
	"${PROJECT_SOURCE_DIR}/Src/WorldContext.h"
	"${PROJECT_SOURCE_DIR}/Src/WorldContext.cpp"
)
source_group(Render\\Context FILES ${Src_Render_Context})

# Render\\Material
SET(Src_Render_Material
	"${PROJECT_SOURCE_DIR}/Src/IMaterial.h"
	"${PROJECT_SOURCE_DIR}/Src/Material.h"
	"${PROJECT_SOURCE_DIR}/Src/Material.cpp"
)
source_group(Render\\Material FILES ${Src_Render_Material})

# Render\\Common
SET(Src_Render_Common
	"${PROJECT_SOURCE_DIR}/Src/RenderCommon.h"
	"${PROJECT_SOURCE_DIR}/Src/RenderCommon.cpp"
)
source_group(Render\\Common FILES ${Src_Render_Common})

# Render\\Pipeline
SET(Src_Render_Pipeline
	"${PROJECT_SOURCE_DIR}/Src/IPipeline.h"
	"${PROJECT_SOURCE_DIR}/Src/ForwardPipeline.h"
	"${PROJECT_SOURCE_DIR}/Src/ForwardPipeline.cpp"
	"${PROJECT_SOURCE_DIR}/Src/DeferredPipeline.h"
	"${PROJECT_SOURCE_DIR}/Src/DeferredPipeline.cpp"
	"${PROJECT_SOURCE_DIR}/Src/TileBasedDeferredPipeline.h"
	"${PROJECT_SOURCE_DIR}/Src/TileBasedDeferredPipeline.cpp"
	"${PROJECT_SOURCE_DIR}/Src/ForwardPlusPipeline.h"
	"${PROJECT_SOURCE_DIR}/Src/ForwardPlusPipeline.cpp"
)
source_group(Render\\Pipeline FILES ${Src_Render_Pipeline})

# Render\\PostProcess
SET(Src_Render_PostProcess
	"${PROJECT_SOURCE_DIR}/Src/IPostProcess.h"
	"${PROJECT_SOURCE_DIR}/Src/Bloom.h"
	"${PROJECT_SOURCE_DIR}/Src/Bloom.cpp"
	"${PROJECT_SOURCE_DIR}/Src/Exposure.h"
	"${PROJECT_SOURCE_DIR}/Src/Exposure.cpp"
)
source_group(Render\\PostProcess FILES ${Src_Render_PostProcess})

# Render\\Renderer
SET(Src_Render_Renderer
	"${PROJECT_SOURCE_DIR}/Src/IRenderer.h"
	"${PROJECT_SOURCE_DIR}/Src/RendererFactory.h"
	"${PROJECT_SOURCE_DIR}/Src/RendererFactory.cpp"
	"${PROJECT_SOURCE_DIR}/Src/WorldRenderer.h"
	"${PROJECT_SOURCE_DIR}/Src/WorldRenderer.cpp"
)
source_group(Render\\Renderer FILES ${Src_Render_Renderer})

# Render\\Resource
SET(Src_Render_Resource
	"${PROJECT_SOURCE_DIR}/Src/MaterialManager.h"
	"${PROJECT_SOURCE_DIR}/Src/MaterialManager.cpp"
	"${PROJECT_SOURCE_DIR}/Src/ProgramManager.h"
	"${PROJECT_SOURCE_DIR}/Src/ProgramManager.cpp"
	"${PROJECT_SOURCE_DIR}/Src/TextureManager.h"
	"${PROJECT_SOURCE_DIR}/Src/TextureManager.cpp"
	"${PROJECT_SOURCE_DIR}/Src/RenderTargetManager.h"
	"${PROJECT_SOURCE_DIR}/Src/RenderTargetManager.cpp"
)
source_group(Render\\Resource FILES ${Src_Render_Resource})

# Render\\State
SET(Src_Render_State
	"${PROJECT_SOURCE_DIR}/Src/StateManager.h"
	"${PROJECT_SOURCE_DIR}/Src/StateManager.cpp"
)
source_group(Render\\State FILES ${Src_Render_State})

# Entry
SET(Src_Entry
	"${PROJECT_SOURCE_DIR}/Src/main.cpp"
)
source_group(Entry FILES ${Src_Entry})

# Utility\\File
SET(Src_Utility_File
	"${PROJECT_SOURCE_DIR}/Src/FileUtility.h"
	"${PROJECT_SOURCE_DIR}/Src/FileUtility.cpp"
)
source_group(Utility\\File FILES ${Src_Utility_File})

# Utility\\Log
SET(Src_Utility_Log
	"${PROJECT_SOURCE_DIR}/Src/log.h"
	"${PROJECT_SOURCE_DIR}/Src/log.cpp"
	"${PROJECT_SOURCE_DIR}/Src/LogUtility.h"
	"${PROJECT_SOURCE_DIR}/Src/LogUtility.cpp"
)
source_group(Utility\\Log FILES ${Src_Utility_Log})

# Utility\\Time
SET(Src_Utility_Time
	"${PROJECT_SOURCE_DIR}/Src/TimeUtility.h"
	"${PROJECT_SOURCE_DIR}/Src/TimeUtility.cpp"
)
source_group(Utility\\Time FILES ${Src_Utility_Time})

# Utility\\Xml
SET(Src_Utility_Xml
	"${PROJECT_SOURCE_DIR}/Src/tinyxml2.h"
	"${PROJECT_SOURCE_DIR}/Src/tinyxml2.cpp"
)
source_group(Utility\\Xml FILES ${Src_Utility_Xml})

# Utility\\Math3D
SET(Src_Utility_Math3D
	"${PROJECT_SOURCE_DIR}/Src/Math3DUtility.h"
	"${PROJECT_SOURCE_DIR}/Src/Math3DUtility.cpp"
)
source_group(Utility\\Math3D FILES ${Src_Utility_Math3D})

# World\\Component
SET(Src_World_Component
	"${PROJECT_SOURCE_DIR}/Src/ComponentCommon.h"
	"${PROJECT_SOURCE_DIR}/Src/IComponent.h"
	"${PROJECT_SOURCE_DIR}/Src/Transform.h"
	"${PROJECT_SOURCE_DIR}/Src/Transform.cpp"
	"${PROJECT_SOURCE_DIR}/Src/Camera.h"
	"${PROJECT_SOURCE_DIR}/Src/Camera.cpp"
	"${PROJECT_SOURCE_DIR}/Src/Light.h"
	"${PROJECT_SOURCE_DIR}/Src/Light.cpp"
	"${PROJECT_SOURCE_DIR}/Src/MeshFilter.h"
	"${PROJECT_SOURCE_DIR}/Src/MeshFilter.cpp"
	"${PROJECT_SOURCE_DIR}/Src/MeshRenderer.h"
	"${PROJECT_SOURCE_DIR}/Src/MeshRenderer.cpp"
)
source_group(World\\Component FILES ${Src_World_Component})

# World\\Level
SET(Src_World_Level
	"${PROJECT_SOURCE_DIR}/Src/ILevel.h"
	"${PROJECT_SOURCE_DIR}/Src/Level.h"
	"${PROJECT_SOURCE_DIR}/Src/Level.cpp"
)
source_group(World\\Level FILES ${Src_World_Level})

# World\\Manager
SET(Src_World_Manager
	"${PROJECT_SOURCE_DIR}/Src/CameraManager.h"
	"${PROJECT_SOURCE_DIR}/Src/CameraManager.cpp"
	"${PROJECT_SOURCE_DIR}/Src/LightManager.h"
	"${PROJECT_SOURCE_DIR}/Src/LightManager.cpp"
)
source_group(World\\Manager FILES ${Src_World_Manager})

# World\\Mesh
SET(Src_World_Mesh
	"${PROJECT_SOURCE_DIR}/Src/IMesh.h"
	"${PROJECT_SOURCE_DIR}/Src/Mesh.h"
	"${PROJECT_SOURCE_DIR}/Src/Mesh.cpp"
)
source_group(World\\Mesh FILES ${Src_World_Mesh})

# World\\SceneObject
SET(Src_World_SceneObject
	"${PROJECT_SOURCE_DIR}/Src/SceneObject.h"
	"${PROJECT_SOURCE_DIR}/Src/SceneObject.cpp"
)
source_group(World\\SceneObject FILES ${Src_World_SceneObject})

# World\\World
SET(Src_World_World
	"${PROJECT_SOURCE_DIR}/Src/IWorld.h"
	"${PROJECT_SOURCE_DIR}/Src/GameWorld.h"
	"${PROJECT_SOURCE_DIR}/Src/GameWorld.cpp"
	"${PROJECT_SOURCE_DIR}/Src/WorldFactory.h"
	"${PROJECT_SOURCE_DIR}/Src/WorldFactory.cpp"
)
source_group(World\\World FILES ${Src_World_World})

# Others
aux_source_directory(./Src Src_Others)

#################Souce Files#################


# executable file
add_executable(Catherine
	${Src_Client}
	${Src_Device_Common}
	${Src_Device_OpenGL}
	${Src_Global}
	${Src_Render_Context}
	${Src_Render_Material}
	${Src_Render_Common}
	${Src_Render_Pipeline}
	${Src_Render_PostProcess}
	${Src_Render_Renderer}
	${Src_Render_Resource}
	${Src_Render_State}
	${Src_Entry}
	${Src_Utility_File}
	${Src_Utility_Log}
	${Src_Utility_Time}
	${Src_Utility_Xml}
	${Src_Utility_Math3D}
	${Src_World_Component}
	${Src_World_Level}
	${Src_World_Manager}
	${Src_World_Mesh}
	${Src_World_SceneObject}
	${Src_World_World}
	${Src_Others}
)

# lib
target_link_libraries(Catherine glfw3.lib assimp.lib)
