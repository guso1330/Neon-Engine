#pragma once

namespace Neon {
	class IGraphicContext {
		public:
			virtual ~IGraphicContext() = default;

			virtual void CreateContext() = 0;
	};
}
