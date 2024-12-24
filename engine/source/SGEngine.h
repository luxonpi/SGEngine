

#ifndef SGENGINE_SGENGINE_H
#define SGENGINE_SGENGINE_H

// Animation
#include "Animation/ArmatureAnimation.h"
#include "Animation/ArmatureAnimationController.h"

// Component
#include "Component/Component.h"
#include "Component/Entity.h"
#include "Component/EntityManager.h"
#include "Component/CameraControlComponent.h"


// Actions
#include "Actions/ActionComponent.h"
#include "Actions/ActionMoveTo.h"
#include "Actions/ActionRotateTo.h"
#include "Actions/ActionRepeatForever.h"
#include "Actions/ActionSequence.h"
#include "Actions/ActionParallel.h"
#include "Actions/ActionHelper.h"

// Parser
#include "Parser/IniParser.h"

// Objects
#include "Objects/Light.h"
#include "Objects/Quad2D.h"
#include "Objects/SScene.h"
#include "Objects/Node.h"
#include "Objects/Sprite.h"

// Physics
#include "Physics/PhysicComponent.h"
#include "Physics/PhysicWorld.h"

// Model
#include "Model/ModelLoader.h"
#include "Model/ModelInstanced.h"
#include "Model/Model.h"
#include "Model/ModelRigged.h"

// Particle
#include "Objects/ParticleSystem.h"
#include "Objects/Particle.h"

// Main
#include "Game/Director.h"
#include "ApplicationController.h"
#include "Game/Application.h"
#include "Game/UpdateDispenser.h"
#include "SMath.h"
#include "Benchmark.h"
#include "System/Resources.h"

// Primitives
#include "Math/Vec2.h"
#include "Math/Vec3.h"
#include "Math/Vec4.h"
#include "Math/Range.h"
#include "Math/Matrix.h"
#include "Math/PerlinNoise.h"

// Input
#include "IO/KeyboardDispenser.h"
#include "IO/TouchDispenser.h"

// Grapics
#include "Graphic/FrameBuffer.h"
#include "Graphic/Compositor.h"
#include "Graphic/Texture/TextureArray.h"
#include "Graphic/Texture/TextureCubeMap.h"
#include "Graphic/Shader/ShaderModule.h"
#include "Graphic/VertexBuffer.h"
#include "Graphic/VertexArrayObject.h"
#include "Graphic/Camera/CameraFilterFrustum.h"
#include "Graphic/Camera/CameraFilter.h"
#include "Graphic/Camera/SCamera.h"

// Effects
#include "Effects/Bloom.h"
#include "Effects/SSAO.h"
#include "Effects/ShadowMap.h"
#include "Effects/DeferredBuffer.h"
#include "Effects/Blur.h"
#include "Effects/DynamicCubeMap.h"
#include "Effects/ExposureMeasurer.h"

// Ui
#include "UI/View.h"
#include "UI/TableView.h"
#include "UI/Label.h"
#include "UI/UISwitch.h"
#include "UI/UISlider.h"

// Platform
#include "Devices/GPUInfo.h"

// Extern
#include "stb_image.h"

#endif
