#pragma once

/* Core */
#include "Core/ecs/ecs.h"

/* Graphics */
#include "Graphics/Cameras/camera.h"
#include "Graphics/Entities/vertex.h"
#include "Graphics/Entities/transform.h"
#include "Graphics/Entities/renderable3d.h"
#include "Graphics/Entities/renderableCollection.h"
#include "Graphics/Layers/layer.h"
#include "Graphics/Renderers/Renderer.h"
// light includes, not used yet

/* Shaders */
#include "Graphics/Shaders/material.h"

/* App */
#include "App/eventManager.h"
#include "App/eventTypes.h"
#include "App/Application.h"
#include "App/Input/input.h"

/* Utils */
#include "Utils/Debug/logger.hpp"
#include "Utils/Debug/Utils.h"
#include "Utils/FileUtils/FileUtils.h"

/* Main - entry point */
#include "main.h"
