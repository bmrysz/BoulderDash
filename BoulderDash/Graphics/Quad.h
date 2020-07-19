#pragma once

#include <wrl.h>
#include "Utility.h"

using namespace utility;
using namespace Microsoft::WRL;

class Quad {
private:
	unsigned int width;
	unsigned int height;
	bmath::Vec2 position;

	ComPtr<ID3D11Buffer> vertexBuffer;
	ComPtr<ID3D11ShaderResourceView> SRV;
	unsigned int stride;

	void createVertexBuffer(const Direct3D11& d3d11, const utility_quad_vertex& vertex);
public:
	Quad();
	void create(const Direct3D11& d3d11, const bmath::Vec2& position, const Image& image);
	void create(const Direct3D11& d3d11, const bmath::Vec2& position, unsigned int width, unsigned int height);
	unsigned int getStride() const;
	ID3D11Buffer* getVertexBuffer() const;
	ID3D11ShaderResourceView* getShaderResourceView() const;
};