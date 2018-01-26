#include "graphics/waterframebuffers.h"
#include "glad/glad.h"

#include "ui/windowmanager.h"

namespace ren
{
    int WaterFramebuffers::reflection_width = 1280;
    int WaterFramebuffers::reflection_height = 720;

    int WaterFramebuffers::refraction_width = 1280;
    int WaterFramebuffers::refraction_height = 720;

    WaterFramebuffers::WaterFramebuffers()
    {
        initializeReflectionFramebuffer();
        initializeRefractionFramebuffer();
    }

    auto WaterFramebuffers::cleanUp() -> void
    {
        glDeleteFramebuffers(1, &m_reflectionFramebuffer);
        glDeleteTextures(1, &m_reflectionTexture);
        glDeleteRenderbuffers(1, &m_reflectionDepthBuffer);

        glDeleteFramebuffers(1, &m_refractionFramebuffer);
        glDeleteTextures(1, &m_refractionTexture);
        glDeleteTextures(1, &m_refractionDepthTexture);
    }

    auto WaterFramebuffers::bindReflectionFramebuffer() -> void
    {
        bindFramebuffer(m_reflectionFramebuffer, reflection_width, reflection_height);
    }

    auto WaterFramebuffers::bindRefractionFramebuffer() -> void
    {
        bindFramebuffer(m_refractionFramebuffer, refraction_width, refraction_height);
    }

    auto WaterFramebuffers::unbindCurrentFramebuffer() -> void
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, WindowManager::getWidth(), WindowManager::getHeight());
    }

    auto WaterFramebuffers::getReflectionTexture() const -> decltype(m_reflectionTexture)
    {
        return m_reflectionTexture;
    }

    auto WaterFramebuffers::getRefractionTexture() const -> decltype(m_refractionTexture)
    {
        return m_refractionTexture;
    }

    auto WaterFramebuffers::getRefractionDepthTexture() const -> decltype(m_refractionDepthTexture)
    {
        return m_refractionDepthTexture;
    }

    auto WaterFramebuffers::initializeReflectionFramebuffer() -> void
    {
        m_reflectionFramebuffer = createFramebuffer();
        m_reflectionTexture = createTextureAttachment(reflection_width, reflection_height);
        m_reflectionDepthBuffer = createDepthBufferAttachment(reflection_width, reflection_height);
        unbindCurrentFramebuffer();
    }

    auto WaterFramebuffers::initializeRefractionFramebuffer() -> void
    {
        m_refractionFramebuffer = createFramebuffer();
        m_refractionTexture = createTextureAttachment(refraction_width, refraction_height);
        m_refractionDepthTexture = createDepthTextureAttachment(refraction_width, refraction_height);
        unbindCurrentFramebuffer();
    }

    auto WaterFramebuffers::bindFramebuffer(GLuint frameBuffer, int width, int height) -> void
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glViewport(0, 0, width, height);
    }

    auto WaterFramebuffers::createFramebuffer() -> GLuint
    {
        GLuint frameBuffer;
        glGenFramebuffers(1, &frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glDrawBuffer(GL_COLOR_ATTACHMENT0);
        return frameBuffer;
    }

    auto WaterFramebuffers::createTextureAttachment(int width, int height) -> GLuint
    {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
        return texture;
    }

    auto WaterFramebuffers::createDepthTextureAttachment(int width, int height) -> GLuint
    {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
        return texture;
    }

    auto WaterFramebuffers::createDepthBufferAttachment(int width, int height) -> GLuint
    {
        GLuint depthBuffer;
        glGenRenderbuffers(1, &depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
        return depthBuffer;
    }
}