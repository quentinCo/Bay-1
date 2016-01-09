/*#include "ShadowMapFBO.hpp"

//Méthodes pour traiter le FBO de shadow map

bool ShadowMapFBO::Init(unsigned int WindowWidth, unsigned int WindowHeight)
{
    // Create the FBO
    glGenFramebuffers(1, &m_fbo);

    // Create the depth buffer
    glGenTextures(1, &m_depth);
    glBindTexture(GL_TEXTURE_2D, m_depth);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, WindowWidth, WindowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Create the cube map
    glGenTextures(1, &m_shadowMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_shadowMap);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for (uint i = 0 ; i < 6 ; i++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_R32F, WindowWidth, WindowHeight, 0, GL_RED, GL_FLOAT, NULL);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth, 0);

    // Disable writes to the color buffer
    glDrawBuffer(GL_NONE);

    // Disable reads from the color buffer
    glReadBuffer(GL_NONE);

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE) {
        printf("FB error, status: 0x%x\n", Status);
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return GLCheckError();
}

void ShadowMapFBO::BindForWriting(GLenum CubeFace)
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, CubeFace, m_shadowMap, 0);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
}

//Traitement des ombres

void ShadowMapPass()
{
    glCullFace(GL_FRONT);

    m_shadowMapEffect.Enable();

    PersProjInfo ProjInfo;
    ProjInfo.FOV = 90.0f;
    ProjInfo.Height = WINDOW_HEIGHT;
    ProjInfo.Width = WINDOW_WIDTH;
    ProjInfo.zNear = 1.0f;
    ProjInfo.zFar = 100.0f;

    Pipeline p;
    p.SetPerspectiveProj(m_persProjInfo);

    glClearColor(FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX);

    for (uint i = 0 ; i < NUM_OF_LAYERS ; i++) {
        m_shadowMapFBO.BindForWriting(gCameraDirections[i].CubemapFace);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        p.SetCamera(m_pointLight.Position, gCameraDirections[i].Target, gCameraDirections[i].Up);

        p.Orient(m_mesh1Orientation);
        m_shadowMapEffect.SetWorld(p.GetWorldTrans());
        m_shadowMapEffect.SetWVP(p.GetWVPTrans());
        m_mesh.Render();

        p.Orient(m_mesh2Orientation);
        m_shadowMapEffect.SetWorld(p.GetWorldTrans());
        m_shadowMapEffect.SetWVP(p.GetWVPTrans());
        m_mesh.Render();
    }
} 

void RenderPass()
{
    glCullFace(GL_BACK);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_lightingEffect.Enable();
    m_shadowMapFBO.BindForReading(SHADOW_TEXTURE_UNIT);
    m_lightingEffect.SetEyeWorldPos(m_pGameCamera->GetPos());

    Pipeline p;
    p.SetPerspectiveProj(m_persProjInfo);
    p.SetCamera(*m_pGameCamera);

    // Render the quads
    m_pGroundTex->Bind(COLOR_TEXTURE_UNIT);
    p.Orient(m_quad1Orientation);
    m_lightingEffect.SetWorldMatrix(p.GetWorldTrans());
    m_lightingEffect.SetWVP(p.GetWVPTrans());
    m_quad.Render();

    p.Orient(m_quad2Orientation);
    m_lightingEffect.SetWorldMatrix(p.GetWorldTrans());
    m_lightingEffect.SetWVP(p.GetWVPTrans());
    m_quad.Render();

    // Render the meshes
    p.Orient(m_mesh1Orientation);
    m_lightingEffect.SetWorldMatrix(p.GetWorldTrans());
    m_lightingEffect.SetWVP(p.GetWVPTrans());
    m_mesh.Render();

    p.Orient(m_mesh2Orientation);
    m_lightingEffect.SetWorldMatrix(p.GetWorldTrans());
    m_lightingEffect.SetWVP(p.GetWVPTrans());
    m_mesh.Render();
} */
