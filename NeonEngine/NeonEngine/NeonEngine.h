#pragma once

/* Utils */
#include "utils/debug/logger.hpp"
#include "utils/fileUtils/fileUtils.h"

/* Core */
#include "core/platforms/opengl/opengl.h"
#include "core/ecs/ecs.h"

/* Graphics */
#include "graphics/cameras/camera.h"
#include "graphics/entities/vertex.h"
#include "graphics/entities/transform.h"
#include "graphics/entities/renderable3d.h"
#include "graphics/entities/renderableCollection.h"
#include "graphics/layers/layer.h"
// light includes, not used yet

/* Shaders */
#include "shaders/material.h"

/* App */
#include "app/eventManager.h"
#include "app/eventTypes.h"
#include "app/application.h"
#include "app/input/input.h"

/* Main - entry point */
#include "main.h"
