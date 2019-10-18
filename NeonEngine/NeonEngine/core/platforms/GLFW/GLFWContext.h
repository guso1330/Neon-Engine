#pragma once

#include <GLFW/glfw3.h>

namespace Neon {
	class GLFWContext {
		public:
			GLFWContext(GLFWContext const&) = delete;
			void operator=(GLFWContext const&) = delete;

			static GLFWContext& GetInstance() {
				static GLFWContext instance;
				return instance;
			}

			/* Implementation functions */
			void CreateContext();

		private:
			GLFWContext() {}
	};
}
