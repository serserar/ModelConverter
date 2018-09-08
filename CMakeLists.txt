cmake_minimum_required(VERSION 2.8.12)
project(modelconverter)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
add_definitions("-std=c++17")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
# search for pkg-config
include (FindPkgConfig)
if (NOT PKG_CONFIG_FOUND)
    message (FATAL_ERROR "pkg-config not found")
endif ()

# check for libpng
pkg_check_modules (LIBPNG libpng16 REQUIRED)
if (NOT LIBPNG_FOUND)
    message(FATAL_ERROR "You don't seem to have libpng16 development libraries installed")
else ()
    include_directories (${LIBPNG_INCLUDE_DIRS})
    link_directories (${LIBPNG_LIBRARY_DIRS})
    link_libraries (${LIBPNG_LIBRARIES})
endif ()
#CEGUI option
option(CEGUI
  "Use cegui" OFF)
  
option(BUNDLED_CEGUI
  "Use bundled CEGUI" OFF)

# cegui
if(BUNDLED_CEGUI)

  # freetype, if not found, we build ours
  find_package(Freetype)
  
  if(NOT FREETYPE_FOUND)
    add_subdirectory(libs/freetype)
    set(BUNDLED_FREETYPE ON CACHE BOOL "Select BUNDLED_FREETYPE for cegui" FORCE)
  endif()
  
  add_subdirectory(libs/cegui)
endif()  
  
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
if(SDLMIXER_FOUND)
	# take a lucky guess
	if(${SDLMIXER_INCLUDE_DIR} MATCHES "NOTFOUND")
		set(SDLMIXER_INCLUDE_DIR ${SDL_INCLUDE_DIR})
	endif(${SDLMIXER_INCLUDE_DIR} MATCHES "NOTFOUND")

	MESSAGE(STATUS
		"SDL Mixer has been found:")
	MESSAGE(STATUS
		"\tCFLAGS : ${SDLMIXER_INCLUDE_DIR}")
	MESSAGE(STATUS
		"\tLDFLAGS: ${SDLMIXER_LIBRARY}")
else(SDLMIXER_FOUND)

	MESSAGE(FATAL_ERROR
		"SDL Mixer is required")
endif(SDLMIXER_FOUND)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()
find_package(GLUT REQUIRED)




set(BASE_SRC src/base/Joint.cpp src/base/Skeleton.cpp src/base/SkinnedMesh.cpp  src/base/Mesh.cpp src/base/Triangle.cpp src/base/AnimationFrame.cpp src/base/Animation.cpp src/base/AnimationManager.cpp src/base/Model.cpp src/base/MDLImporter.cpp src/base/BBox.cpp src/base/Octree.cpp src/base/Camera.cpp src/base/Ray.cpp src/base/AutoRig.cpp src/base/VoxelizerTool.cpp
src/base/CollisionManager.cpp src/base/MeshUtils.cpp src/base/Cube.cpp src/base/RectangularPrism.cpp )

set(MDL_SRC src/mdl/MDLReader.cpp src/mdl/MDLReader.cpp src/mdl/MDLModel.cpp src/mdl/MDLMesh.cpp src/mdl/MDLJoint.cpp src/mdl/MDLFrame.cpp src/mdl/MDLBodyParts.cpp src/mdl/MDLAnimation.cpp src/mdl/MDLSkeleton.cpp src/mdl/MDLSubModel.cpp src/mdl/MDLTexture.cpp)

set(MD5_SRC src/md5/md5model.cpp src/md5/md5animation.cpp src/md5/md5animbaseframe.cpp src/md5/md5animbound.cpp src/md5/md5animframe.cpp src/md5/md5animjoint.cpp src/md5/md5animjointlocation.cpp src/md5/md5command.cpp src/md5/md5joint.cpp src/md5/md5mesh.cpp src/md5/md5model.cpp src/md5/md5reader.cpp src/md5/md5triangle.cpp src/md5/md5vertex.cpp src/md5/md5weight.cpp src/md5/md5writer.cpp src/md5/MD5Converter.cpp src/md5/MD5Exporter.cpp src/md5/Options.cpp)

set(IMAGE_SRC src/image/Imagefactory.cpp src/image/Image.cpp src/image/BMPLoader.cpp src/image/PNGLoader.cpp src/image/TGALoader.cpp src/image/PPMReader.cpp)
set(ENTITY_SRC src/entity/EntityShape.cpp src/entity/EntityStatus.cpp src/entity/Entity.cpp src/entity/DynamicEntity.cpp src/entity/EntityAction.cpp src/entity/EntityManager.cpp)
set(UTIL_SRC src/util/tokenizer.cpp src/util/ImageUtils.cpp src/util/PoissonDiskAlg.cpp src/util/Fsm.cpp src/util/PoissonDiskAlg3D.cpp src/util/TimeUtils.cpp src/util/xml/XMLParserUtil.cpp)
set(EVENT_SRC src/event/Event.cpp src/event/EventManager.cpp)
set(GAME_SRC src/game/GameApp.cpp )
set(INPUT_SRC src/input/InputManager.cpp src/input/InputAction.cpp src/input/JumpAction.cpp)
set(VIEWER_SRC  src/viewer/GLRender.cpp src/viewer/Md5Model.cpp src/viewer/Shader.cpp src/viewer/Texture.cpp src/viewer/ImageX.cpp src/viewer/Font.cpp src/viewer/GlErrors.cpp  src/viewer/ArbProgram.cpp)
set(RESOURCES_SRC src/resources/ResourceManager.cpp src/resources/ResourceFile.cpp src/resources/parser/ResourcesFileParser.cpp src/resources/parser/ResourceDef.cpp)
set(SAMPLESDESCRIPTOR_SRC src/samplesdescriptor/SamplesConfig.cpp src/samplesdescriptor/SamplesConfigParser.cpp)
set(TEST_MATH_SRC src/test/TestMath.cpp)
set(TEST_RENDER_SRC src/test/TestBBox.cpp)
set(TEST_TRIANGLE_SRC src/test/TestTriangle.cpp src/base/Triangle.cpp src/base/Ray.cpp  src/base/CollisionManager.cpp src/base/MeshUtils.cpp src/base/BBox.cpp src/base/Mesh.cpp src/base/Joint.cpp src/base/Skeleton.cpp src/base/Cube.cpp src/base/RectangularPrism.cpp)
set(TEST_MESHUTILS_SRC src/test/TestMeshUtils.cpp ${BASE_SRC} ${MDL_SRC} ${IMAGE_SRC} ${UTIL_SRC})

#### create symlinks for unix so game can be run from build
if(UNIX)
  if(BUNDLED_CEGUI)
    add_custom_target(
      "CEGUI_lib_symlinks" ALL
      COMMAND ln -sf "${CMAKE_BINARY_DIR}/libs/cegui/CEGUI.git/lib" "${CMAKE_BINARY_DIR}/lib"
      )
  endif()
endif()
MESSAGE(STATUS
		"\tCONAN LIBS : ${CONAN_LIBS}")
add_executable(modelconverter src/main.cpp ${BASE_SRC} ${MD5_SRC} ${MDL_SRC} ${IMAGE_SRC} ${ENTITY_SRC} ${UTIL_SRC} ${EVENT_SRC} ${INPUT_SRC} ${VIEWER_SRC})
target_link_libraries(modelconverter ${LIBPNG_LINK_FLAGS}  ${SDL_LIBRARY} ${SDLMIXER_LIBRARY} ${OPENGL_gl_LIBRARY} ${SDL2TTF_LIBRARY} GLU glut jpeg ${CONAN_LIBS})
add_executable(testMath ${TEST_MATH_SRC})
add_executable(testBBox src/base/BBox.cpp ${TEST_RENDER_SRC})
add_executable(testTriangle  ${TEST_TRIANGLE_SRC})
add_executable(testMeshUtils  ${TEST_MESHUTILS_SRC})
target_link_libraries(testMeshUtils -lstdc++fs ${CONAN_LIBS})
add_executable(modelSampler src/modelSampler.cpp src/ModelSamplerApp.cpp ${BASE_SRC} ${MD5_SRC} ${MDL_SRC} ${IMAGE_SRC} ${ENTITY_SRC} ${UTIL_SRC} ${EVENT_SRC} ${INPUT_SRC} ${RESOURCES_SRC} ${SAMPLESDESCRIPTOR_SRC})
target_link_libraries(modelSampler ${CONAN_LIBS} -lstdc++fs)
enable_testing()
add_test(NAME testMVector COMMAND testMVector)
add_test(NAME testBBox COMMAND testBBox)
install(TARGETS modelconverter RUNTIME DESTINATION bin)
