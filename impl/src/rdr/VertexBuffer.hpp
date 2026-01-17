#ifndef VXT_VERTEX_BUFFER_HPP
#define VXT_VERTEX_BUFFER_HPP

#include "Types.hpp"

#define VBUF_DATA_SIZE 1
#define VBUF_STRIDE VBUF_DATA_SIZE
#define VBUF_VERTEX_CAPACITY 10000
#define VBUF_NBR_OF_BUFFERS 3
#define VBUF_NBR_OF_VERTICES_IN_QUAD 6

struct FaceData {
	uint16_t pos;
	uint16_t uv;
	uint8_t  faceId;
};

namespace vxt {
namespace rdr
{
class VertexBuffer {
public:
	VertexBuffer(uint8_t *data, std::size_t size);
	~VertexBuffer() noexcept = default;

public:
	/// @brief
	void clear(void);

	/// @brief
	/// @return
	bool empty(void) const;

	/// @brief Returns the size in faces/quads.
	/// @param index index of the subbuffer or -1 for total size
	/// @return size
	std::size_t size(ssize_t index = NO_INDEX) const;

	/// @brief
	/// @return
	std::size_t capacity(void) const;

	/// @brief
	/// @param index
	/// @return
	ssize_t remaining(ssize_t index = NO_INDEX) const;

	/// @brief
	/// @return
	std::size_t getNumVertices(void) const;

	/// @brief
	/// @return
	std::size_t getNumQuads(void) const;

	template<typename T>
	void put(std::size_t index, const T &t);

private:
	template<typename T>
	uint32_t pack(const T &t);

protected:
	ufw::buffer m_buffers[VBUF_NBR_OF_BUFFERS];
};

template<>
inline uint32_t VertexBuffer::pack<FaceData>(const FaceData &in)
{
	return (in.pos << 16) | (in.uv << 6) | (in.faceId << 3);
}

template<>
inline void VertexBuffer::put<FaceData>(std::size_t index, const FaceData &in)
{
	const uint32_t shared = pack(in);
	ufw::buffer *buffer = NULL;

	UFW_ASSERT(((0 <= index) && (index < VBUF_NBR_OF_BUFFERS)) && ("index is out of range"));
	buffer = &(m_buffers[index]);
	UFW_ASSERT((buffer->remaining() >= (sizeof(uint32_t) * VBUF_NBR_OF_VERTICES_IN_QUAD)) && ("not enough space"));

	*buffer << static_cast<uint32_t>( shared | 0 ); // TR
	*buffer << static_cast<uint32_t>( shared | 3 ); // TL
	*buffer << static_cast<uint32_t>( shared | 2 ); // BL
	*buffer << static_cast<uint32_t>( shared | 1 ); // BR
	*buffer << static_cast<uint32_t>( shared | 0 ); // TR
	*buffer << static_cast<uint32_t>( shared | 2 ); // BL
}

} // namespace rdr
} // namespace vxt

#endif // VXT_VERTEX_BUFFER_HPP
