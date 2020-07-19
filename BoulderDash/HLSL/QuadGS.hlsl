#include "QuadIO.hlsli"
#include "ConstantBuffers.hlsli"

[maxvertexcount(4)]
void main(point VS_INPUT input[1], inout TriangleStream<PS_INPUT> outputStream) {

	float4 w = float4(input[0].Size.x, 0.0f, 0.0f, 0.0f);
	float4 h = float4(0.0f, input[0].Size.y, 0.0f, 0.0f);
	float4 pos = input[0].Pos;

	float4 Pos[4] = (float4[4])0.0f;
	float2 Tex[4] = (float2[4])0.0f;

	// first vertex
	Pos[0] = pos;
	Tex[0] = float2(0.0f, 0.0f);

	// second vertex
	Pos[1] = pos + w;
	Tex[1] = float2(1.0f, 0.0f);

	// third vertex
	Pos[2] = pos - h;
	Tex[2] = float2(0.0f, 1.0f);

	// fourth vertex
	Pos[3] = pos + w - h;
	Tex[3] = float2(1.0f, 1.0f);

	PS_INPUT output = (PS_INPUT)0.0f;

	for (int i = 0; i < 4; i++) {
		output.Pos = mul(Pos[i], VP);
		output.Tex = Tex[i];

		outputStream.Append(output);
	}
}