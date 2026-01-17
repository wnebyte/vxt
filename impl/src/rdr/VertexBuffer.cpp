#include <cstring>

#include "rdr/VertexBuffer.hpp"

using namespace vxt;
using namespace rdr;

VertexBuffer::VertexBuffer(uint8_t *data, std::size_t size)
	: m_buffers{
		{ufw::buffer::WBUF, (size/3), &(data[0])},
		{ufw::buffer::WBUF, (size/3), &(data[(size/3)*1])},
		{ufw::buffer::WBUF, (size/3), &(data[(size/3)*2])}
	}
{
	UFW_ASSERT((size % VBUF_NBR_OF_BUFFERS == 0) && ("size is not divisible by 3"));
}

void VertexBuffer::clear(void)
{
	for (uint i = 0; i < VBUF_NBR_OF_BUFFERS; ++i) {
		m_buffers[i].rewind();
	}
}

bool VertexBuffer::empty(void) const
{
	return (m_buffers[0].size() == 0);
}

std::size_t VertexBuffer::size(ssize_t index) const
{
	std::size_t size = 0;

	UFW_ASSERT(((index == NO_INDEX) || ((0 <= index) && (index < VBUF_NBR_OF_BUFFERS))) && ("index is out of range"));

	if (index != NO_INDEX) {
		size = m_buffers[index].size();
	} else {
		for (uint i = 0; i < VBUF_NBR_OF_BUFFERS; ++i) {
			size += m_buffers[i].size();
		}
	}

	return (size / (sizeof(uint32_t) * VBUF_NBR_OF_VERTICES_IN_QUAD));
}

std::size_t VertexBuffer::capacity(void) const
{
	return (m_buffers[0].capacity() * VBUF_NBR_OF_BUFFERS);
}

ssize_t VertexBuffer::remaining(ssize_t index) const
{
	ssize_t rem = 0;

	UFW_ASSERT(((index == NO_INDEX) || ((0 <= index) && (index < VBUF_NBR_OF_BUFFERS))) && ("index is out of range"));

	if (index != NO_INDEX) {
		rem = m_buffers[index].remaining();
	} else {
		for (uint i = 0; i < VBUF_NBR_OF_BUFFERS; ++i) {
			rem += m_buffers[i].remaining();
		}
	}

	return (rem / VBUF_NBR_OF_VERTICES_IN_QUAD);
}

std::size_t VertexBuffer::getNumVertices(void) const
{
	return (size() / VBUF_STRIDE);
}

std::size_t VertexBuffer::getNumQuads(void) const
{
	return (getNumVertices() / VBUF_NBR_OF_VERTICES_IN_QUAD);
}
