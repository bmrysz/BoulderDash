#include "Graphics.h"

void Graphics::initialize(unsigned int width, unsigned int height, bool fullscreen) {
	screenWidth = width;
	screenHeight = height;

	d3d11.init(width, height, fullscreen);
	createShaders();
	createSamplers();
	setOrthogonalCamera(width, height);
	setConstantBuffers();
	setResources();
}

void Graphics::createShaders() {
	std::string path = "Shaders/";
	std::string debug_str;

#ifdef _DEBUG
	debug_str = "debug_";
#endif

	path += debug_str;

	d3d11.createCSOVSAndInputLayout(path + "QuadVS.cso", VS.GetAddressOf(), d3d11.createInputElement("POSITION 3 SIZE 2"), IL.GetAddressOf());
	d3d11.createCSOShader(path + "QuadGS.cso", GS.GetAddressOf());
	d3d11.createCSOShader(path + "QuadPS.cso", PS.GetAddressOf());
}

void Graphics::setOrthogonalCamera(unsigned int width, unsigned int height) {
	VP = camera.orthoLH(static_cast<float>(width), static_cast<float>(height), 0.01f, 1.0f);
}

void Graphics::setConstantBuffers() {
	cbOnce.create(d3d11);

	CBOnce CBonce;
	CBonce.VP = VP;
	CBonce.screenWidth = screenWidth;
	CBonce.screenHeight = screenHeight;
	CBonce.inverseScreenSize = 1.0f / bmath::Vec2(static_cast<float>(screenWidth), static_cast<float>(screenHeight));

	cbOnce.update(CBonce, d3d11.getContext());
}

void Graphics::setResources() {
	numberCellsY = 30;
	cellSize = screenHeight / numberCellsY;
	numberCellsX = screenWidth / cellSize;

	hardwall.create(d3d11, bmath::Vec2(0.0f, 0.0f), cellSize, cellSize);
	grass.create(d3d11, bmath::Vec2(0.0f, 0.0f), cellSize, cellSize);


}

void Graphics::createSamplers() {
	HRESULT hr;

	// create and fill sampler state with wrap texturing

	D3D11_SAMPLER_DESC sampDesc;

	ZeroMemory(&sampDesc, sizeof(sampDesc));

	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// create point sampler
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	hr = d3d11.getDevice()->CreateSamplerState(&sampDesc, samplerPoint.GetAddressOf());

	// create linear sampler
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	hr = d3d11.getDevice()->CreateSamplerState(&sampDesc, samplerLinear.GetAddressOf());

	// create blend state
	d3d11.createStateBlendAddAlpha(blendAlphaAdd.GetAddressOf(), 0);

	// disable depth

	D3D11_DEPTH_STENCIL_DESC depthDesc;

	ZeroMemory(&depthDesc, sizeof(depthDesc));

	depthDesc.DepthEnable = false;

	hr = d3d11.getDevice()->CreateDepthStencilState(&depthDesc, depthDisable.GetAddressOf());
}

void Graphics::render(const Level& level) {
	d3d11.clearScreen(0, 128, 255, d3d11.getContext());

	d3d11.getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	d3d11.getContext()->IASetInputLayout(IL.Get());

	d3d11.getContext()->VSSetShader(VS.Get(), nullptr, 0);
	
	d3d11.getContext()->GSSetShader(GS.Get(), nullptr, 0);
	d3d11.getContext()->GSSetConstantBuffers(0, 1, cbOnce.getBufferAddress());

	ID3D11SamplerState* samplers[] = { samplerPoint.Get() };
	d3d11.getContext()->PSSetShader(PS.Get(), nullptr, 0);
	d3d11.getContext()->PSSetSamplers(0, 1, samplers);

	for (unsigned int col = 0; col < level.blocks.size(); ++col) {
		for (unsigned int row = 0; row < level.blocks.at(col).size(); ++row) {

			BLOCK_TYPE block = level.blocks.at(col).at(row);
			switch (block) {
			case BLOCK_TYPE::HERO:
				drawHero(level.HEROpositionX, level.HEROpositionY);
				break;
			case BLOCK_TYPE::EXIT:
				drawExit(level.EXITpositionX, level.EXITpositionY);
				break;
			case BLOCK_TYPE::EMPTY:
				drawEmpty();
				break;
			case BLOCK_TYPE::DIRT:
				drawDirt(col, row);
				break;
			case BLOCK_TYPE::WALL:
				drawWall(col, row);
				break;
			};
		}
	}

	//hardwall.setPosition(0, 0);

	d3d11.getSwapChain()->Present(0, 0);
}

void Graphics::drawEmpty() {

}

void Graphics::drawHero(unsigned int col, unsigned int row) {

}

void Graphics::drawExit(unsigned int col, unsigned int row) {

}

void Graphics::drawDirt(unsigned int col, unsigned int row) {

}

void Graphics::drawWall(unsigned int col, unsigned int row) {

}
