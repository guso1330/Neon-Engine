#include "forwardRenderer.h"

namespace neon {
	// ForwardRenderer::ForwardRenderer() {
	// 	m_ambientLight = new AmbientLight();
	// }
	// ForwardRenderer::~ForwardRenderer() {
	// 	delete m_ambientLight;
	// }

	// void ForwardRenderer::Submit(Renderable3d* renderable) {
	// 	m_renderables.push_back(renderable);
	// }

	// void ForwardRenderer::Submit(GameObject* gameobject) {
	// 	m_renderables.push_back(gameobject->GetModel());
	// }

	// void ForwardRenderer::SetUpDraw() {
	// 	GL_Call(glEnable(GL_BLEND));
	// 	GL_Call(glBlendFunc(GL_ONE, GL_ONE));
	// 	GL_Call(glDepthMask(false));
	// 	GL_Call(glDepthFunc(GL_EQUAL));
	// }

	// void ForwardRenderer::UnSetDraw() {
	// 	GL_Call(glDepthFunc(GL_LESS));
	// 	GL_Call(glDepthMask(true));
	// 	GL_Call(glDisable(GL_BLEND));
	// }
	
	// void ForwardRenderer::Flush() {
	// 	// SetUpDraw();
	// 	for(std::vector<Renderable3d*>::iterator it=m_renderables.begin(); it != m_renderables.end(); ++it) {
	// 		m_ambientLight->Bind((*it), m_mainCamera);
	// 		GL_Call(glDrawElements(GL_TRIANGLES, (*it)->GetIbo()->GetCount(), GL_UNSIGNED_INT, NULL));
	// 		m_ambientLight->Unbind();
	// 	}
	// 	// UnSetDraw();
	// }
}