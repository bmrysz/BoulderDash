#include "Quad.h"

Quad::Quad() {
	width = 0;
	height = 0;
	stride = sizeof(utility_quad_vertex);
}

void Quad::createVertexBuffer(const Direct3D11& d3d11, const utility_quad_vertex& vertex) {
	std::vector<utility_quad_vertex> vertices;
	vertices.push_back(vertex);

	d3d11.createVertexBuffer(vertexBuffer.GetAddressOf(), vertices);
}

void Quad::create(const Direct3D11& d3d11, const bmath::Vec2& position, const Image& image) {
	width = image.getWidth();
	height = image.getHeight();
	SRV = image.getView();

	utility_quad_vertex vertex = { bmath::Vec3(position, 1.0f), bmath::Vec2(width, height) };

	createVertexBuffer(d3d11, vertex);
}

void Quad::create(const Direct3D11& d3d11, const bmath::Vec2& position, unsigned int width, unsigned int height) {
	utility_quad_vertex vertex = { bmath::Vec3(position, 1.0f), bmath::Vec2(width, height) };

	this->width = width;
	this->height = height;
	this->position = position;

	createVertexBuffer(d3d11, vertex);
}

unsigned int Quad::getStride() const {
	return stride;
}

ID3D11Buffer* Quad::getVertexBuffer() const {
	return vertexBuffer.Get();
}

ID3D11ShaderResourceView* Quad::getShaderResourceView() const {
	return SRV.Get();
}