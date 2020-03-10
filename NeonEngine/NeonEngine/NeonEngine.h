#pragma once

/* Core */
#include "Core/Memory/LinearAllocator.h"
#include "Core/Memory/PoolAllocator.h"
#include "Core/Events/EventManager.h"
#include "Core/Events/EventTypes.h"

/* Graphics */
#include "Graphics/Cameras/Camera.h"
#include "Graphics/Entities/vertex.h"
#include "Graphics/Entities/transform.h"
#include "Graphics/Entities/renderable3d.h"
#include "Graphics/Entities/renderableCollection.h"
#include "Graphics/Layers/layer.h"
#include "Graphics/Renderers/Renderer.h"

/* Shaders */
#include "Graphics/Shaders/material.h"

/* App */
#include "App/Application.h"
#include "App/Input/Input.h"

/* Utils */
#include "Utils/Debug/logger.hpp"
#include "Utils/Debug/Utils.h"
#include "Utils/FileUtils/FileUtils.h"

/* Main - entry point */
#include "main.h"
