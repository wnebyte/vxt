#ifndef VXT_SHAPES_HPP
#define VXT_SHAPES_HPP

#include <cstring>

#include "Types.hpp"

namespace vxt {
namespace rdr
{
struct Vertex2 {
	glm::vec2 pos;
	int32_t   zIndex;
	glm::vec3 color;
	glm::vec2 uv;
	int32_t   texId;
	bool      blend;
};

struct GL_Vertex2 {
	glm::vec2 pos;
	glm::vec3 color;
	glm::vec2 uv;
	int32_t   texId;
};

struct Vertex3 {
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 uv;
	int32_t   texId;
};

typedef struct Vertex3 GL_Vertex3;

struct Line2 {
	glm::vec2 start;
	glm::vec2 end;
	int32_t   zIndex;
	glm::vec3 color;
	uint32_t  width;
};

struct GL_Line2 {
	glm::vec2 pos;
	glm::vec3 color;
};

struct Line3 {
	glm::vec3 start;
	glm::vec3 end;
	glm::vec3 color;
	uint32_t  width;
};

struct GL_Line3 {
	glm::vec3 pos;
	glm::vec3 color;
};

struct Box2 {
	glm::vec2 pos; // center pos
	int32_t   zIndex;
	glm::vec2 size;
	float     rotation;
	glm::vec3 color;
	uint32_t  width; // outline width
};

struct Box3 {
	glm::vec3 pos; // center pos
	glm::vec3 size;
	float     rotation;
	glm::vec3 color;
	uint32_t  width; // outline width
};

struct Quad2 {
	glm::vec2 pos; // lower left corner
	int32_t   zIndex;
	glm::vec2 size;
	float     scale;
	glm::vec3 color;
	int32_t   texId;
	bool      blend;
};

struct Cube3;

struct Spr {
	glm::vec2 pos;
	glm::vec4 color;
	glm::vec2 uv;
	int32_t   texId;
	int32_t   entityId;
};

struct CrossHair {
	glm::vec2 pos;
	glm::vec2 size;
	glm::vec3 color;
};

class ShapeBuilder {
public:
	ShapeBuilder()
		: m_vertex2()
		, m_vertex3()
		, m_line2()
		, m_line3()
		, m_box2()
		, m_box3()
		, m_quad2()
	{
	}

	~ShapeBuilder() noexcept = default;

public:
	ShapeBuilder& setPos(const glm::vec2 &pos)
	{
		m_vertex2.pos = pos;
		m_box2.pos = pos;
		m_box2.pos = pos;
		m_crossHair.pos = pos;
		return *this;
	}

	ShapeBuilder& setPos(const glm::vec3 &pos)
	{
		m_vertex3.pos = pos;
		m_box3.pos = pos;
		return *this;
	}

	ShapeBuilder& setStart(const glm::vec2 &start)
	{
		m_line2.start = start;
		return *this;
	}

	ShapeBuilder& setStart(const glm::vec3 &start)
	{
		m_line3.start = start;
		return *this;
	}

	ShapeBuilder& setEnd(const glm::vec2 &end)
	{
		m_line2.end = end;
		return *this;
	}

	ShapeBuilder& setEnd(const glm::vec3 &end)
	{
		m_line3.end = end;
		return *this;
	}

	ShapeBuilder& setZIndex(int32_t zIndex)
	{
		m_vertex2.zIndex = zIndex;
		m_box2.zIndex = zIndex;
		m_quad2.zIndex = zIndex;
		return *this;
	}

	ShapeBuilder& setColor(const glm::vec3 &color)
	{
		m_vertex2.color = color;
		m_vertex3.color = color;
		m_line2.color = color;
		m_line3.color = color;
		m_box2.color = color;
		m_box3.color = color;
		m_quad2.color = color;
		m_crossHair.color = color;
		return *this;
	}

	ShapeBuilder& setUv(const glm::vec2 &uv)
	{
		m_vertex2.uv = uv;
		m_vertex3.uv = uv;
		return *this;
	}

	ShapeBuilder& setTexId(int32_t texId)
	{
		m_vertex2.texId = texId;
		m_vertex3.texId = texId;
		m_quad2.texId = texId;
		return *this;
	}

	ShapeBuilder& setBlend(bool blend)
	{
		m_vertex2.blend = blend;
		m_quad2.blend = blend;
		return *this;
	}

	ShapeBuilder& setWidth(uint32_t width)
	{
		m_line2.width = width;
		m_line3.width = width;
		m_box2.width = width;
		m_box3.width = width;
		return *this;
	}

	ShapeBuilder& setRotation(float rotation)
	{
		m_box2.rotation = rotation;
		m_box3.rotation = rotation;
		return *this;
	}

	ShapeBuilder& setSize(const glm::vec2 &size)
	{
		m_box2.size = size;
		m_quad2.size = size;
		m_crossHair.size = size;
		return *this;
	}

	ShapeBuilder& setSize(const glm::vec3 &size)
	{
		m_box3.size = size;
		return *this;
	}

	ShapeBuilder& setScale(float scale)
	{
		m_quad2.scale = scale;
		return *this;
	}

	template<typename T>
	T build(void)
	{
		// empty
	}

private:
	void clear(void)
	{
		std::memset(this, 0, sizeof(*this));
	}

private:
	Vertex2   m_vertex2;
	Vertex3   m_vertex3;
	Line2     m_line2;
	Line3     m_line3;
	Box2      m_box2;
	Box3      m_box3;
	Quad2     m_quad2;
	CrossHair m_crossHair;
};

template<>
inline Vertex2 ShapeBuilder::build<Vertex2>(void)
{
	Vertex2 shape = m_vertex2;
	clear();
	return shape;
}

template<>
inline Vertex3 ShapeBuilder::build<Vertex3>(void)
{
	Vertex3 shape = m_vertex3;
	clear();
	return shape;
}

template<>
inline Line2 ShapeBuilder::build<Line2>(void)
{
	Line2 shape = m_line2;
	clear();
	return shape;
}

template<>
inline Line3 ShapeBuilder::build<Line3>(void)
{
	Line3 shape = m_line3;
	clear();
	return shape;
}

template<>
inline Box2 ShapeBuilder::build<Box2>(void)
{
	Box2 shape = m_box2;
	clear();
	return shape;
}

template<>
inline Box3 ShapeBuilder::build<Box3>(void)
{
	Box3 shape = m_box3;
	clear();
	return shape;
}

template<>
inline Quad2 ShapeBuilder::build<Quad2>(void)
{
	Quad2 shape = m_quad2;
	clear();
	return shape;
}

template<>
inline CrossHair ShapeBuilder::build<CrossHair>(void)
{
	CrossHair shape = m_crossHair;
	clear();
	return shape;
}

} // namespace rdr
} // namespace vxt

#endif // VXT_SHAPES_HPP
