#ifndef VXT_SPRITE_BATCH_RENDERER_HPP
#define VXT_SPRITE_BATCH_RENDERER_HPP

#include "Types.hpp"
#include "Camerafwd.hpp"
#include "rdr/Shapes.hpp"
#include "rdr/Renderer.hpp"
#include "rdr/Shaderfwd.hpp"
#include "utl/CapacitySet.hpp"
#include "cmp/SpriteRender.hpp"

namespace vxt {
namespace rdr 
{
class SpriteBatchRenderer : public Renderer {
public:
	static const uint32_t maxBatchSize = 1000;

public:
	SpriteBatchRenderer();
	~SpriteBatchRenderer() noexcept = default;

public:
	void init(void);
	bool add(cmp::SpriteRender *spr);
	void render(const Camera &camera) override;
	void destroy(void) override;
	int32_t zIndex(void) const override;
	std::size_t size(void) const;

private:
	void setRenderData(cmp::SpriteRender *spr, std::size_t idx);
	void remove(std::size_t idx);
	bool atCapacity(cmp::SpriteRender *spr);
	bool atTexCapacity(int32_t texId);

private:
	uint32_t m_vaoId;
	uint32_t m_vboId;
	std::size_t m_size;
	Spr m_data[maxBatchSize];
	std::size_t m_numOfSprites;
	cmp::SpriteRender *m_sprites[maxBatchSize];
	utl::CapacitySet<int32_t> m_textures;
	Shader *m_shader;
	int32_t m_zIndex;
};
} // namespace rdr
} // namespace vxt

#endif // VXT_SPRITE_BATCH_RENDERER_HPP
