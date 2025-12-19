#ifndef VXT_SHADER_HPP
#define VXT_SHADER_HPP

#include "Types.hpp"

#define SHADER_U_PROJECTION "uProjection"
#define SHADER_U_VIEW "uView"
#define SHADER_U_TEXTURES "uTextures"
#define SHADER_U_ACCUM "uAccum"
#define SHADER_U_REVEAL "uReveal"
#define SHADER_U_SCREEN "uScreen"
#define SHADER_U_ZINDEX "uZIndex"
#define SHADER_U_IS_WORLD_SPACE "uIsWorldSpace"
#define SHADER_U_INVERSE_PROJECTION "uInverseProjection"
#define SHADER_U_INVERSE_VIEW "uInverseView"

namespace vxt {
namespace rdr
{
class Shader {
public:
	Shader(const std::string &path);
	~Shader() noexcept = default;

public:
	void compile(void);
	void attach(void);
	void detach(void);
	uint32_t getId(void) const;
	std::string getPath(void) const;
	void uploadInt(const std::string& varName, int32_t i);
    void uploadFloat(const std::string& varName, float f);
	void uploadBool(const std::string &varName, bool b);
    void uploadIntArray(const std::string& varName, const int32_t *array, std::size_t size);
    void uploadFloatArray(const std::string& varName, const float *array, std::size_t size);
    void uploadVec2(const std::string& varName, const glm::vec2& vec);
    void uploadVec3(const std::string& varName, const glm::vec3& vec);
    void uploadVec4(const std::string& varName, const glm::vec4& vec);
    void uploadMat3(const std::string& varName, const glm::mat3& mat);
    void uploadMat4(const std::string& varName, const glm::mat4& mat);
    void uploadTexture(const std::string& varName, int32_t slot);

private:
	void checkCompileStatus(uint32_t shaderId, const std::string &shaderType) const;
	void checkLinkStatus(uint32_t shaderId) const;

private:
	uint32_t    m_id;
	std::string m_path;
	std::string m_vertexSource;
	std::string m_fragmentSource;
	bool        m_detached;
};
} // namespace rdr
} // namespace vxt

#endif // VXT_SHADER_HPP
