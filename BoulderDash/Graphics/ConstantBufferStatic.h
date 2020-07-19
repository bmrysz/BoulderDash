#pragma once

#include "Utility.h"
#include <wrl.h>

using namespace Microsoft::WRL;
using namespace utility;

template<class T>
class ConstantBufferStatic {
public:
	void set(const T& CBObject);
	ID3D11Buffer** getBufferAddress();
	ID3D11Buffer* getBuffer();
	void update(T CBObject, ID3D11DeviceContext* context);
	void update(ID3D11DeviceContext* context);
	bool create(const Direct3D11& d3d11);
private:
	T CBObject;
	ComPtr<ID3D11Buffer> CBuffer;
};

template<class T>
bool ConstantBufferStatic<T>::create(const Direct3D11& d3d11) {
	HRESULT hr = S_OK;
	hr = d3d11.createConstantBuffer(CBuffer.GetAddressOf(), sizeof(T));

	if (FAILED(hr)) {
		return false;
	}

	return true;
}

template<class T>
void ConstantBufferStatic<T>::set(const T& CBObject) {
	this->CBObject = CBObject;
}

template<class T>
ID3D11Buffer** ConstantBufferStatic<T>::getBufferAddress() {
	return CBuffer.GetAddressOf();
}

template<class T>
ID3D11Buffer* ConstantBufferStatic<T>::getBuffer() {
	return CBuffer.Get();
}

template<class T>
void ConstantBufferStatic<T>::update(ID3D11DeviceContext* context) {
	context->UpdateSubresource(CBuffer.Get(), 0, 0, &CBObject, 0, 0);
}

template<class T>
void ConstantBufferStatic<T>::update(T CBObject, ID3D11DeviceContext* context) {
	set(CBObject);
	update(context);
}