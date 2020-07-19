#include "FontIO.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState samPoint : register(s0);

float4 main(PS_INPUT input) : SV_Target {
	return input.Color * tex.Sample(samPoint, input.Tex);
}