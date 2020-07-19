#pragma once

#include <wrl.h>
#include "Utility.h"
#include "ConstantBufferStatic.h"
#include "ConstantBuffers.h"
#include "Quad.h"
#include "../Game/Level.h"

using namespace utility;
using namespace Microsoft::WRL;

class Graphics {
public:
	void initialize(unsigned int width, unsigned int height, bool fullscreen);
	void render(const Level& level);
private:
	void setOrthogonalCamera(unsigned int width, unsigned int height);
	void setConstantBuffers();
	void setResources();
	void createShaders();
	void createSamplers();

	bmath::Matrix VP;
	unsigned int screenWidth;
	unsigned int screenHeight;

	unsigned int numberCellsX;
	unsigned int numberCellsY;
	unsigned int cellSize;

	ComPtr<ID3D11InputLayout> IL;
	ComPtr<ID3D11VertexShader> VS;
	ComPtr<ID3D11GeometryShader> GS;
	ComPtr<ID3D11PixelShader> PS;

	// resources states

	ComPtr<ID3D11BlendState> blendAlphaAdd;
	ComPtr<ID3D11DepthStencilState> depthDisable;
	ComPtr<ID3D11SamplerState> samplerPoint;
	ComPtr<ID3D11SamplerState> samplerLinear;

	bmath::Camera camera;

	Direct3D11 d3d11;

	// set constant buffers

	ConstantBufferStatic<CBOnce> cbOnce;
	
	// quads

	Quad hardwall, grass;

	// draw blocks

	void drawHero(unsigned int col, unsigned int row);
	void drawExit(unsigned int col, unsigned int row);

	void drawEmpty();
	void drawDirt(unsigned int col, unsigned int row);
	void drawWall(unsigned int col, unsigned int row);

};