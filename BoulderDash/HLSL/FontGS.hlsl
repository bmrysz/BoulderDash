#include "FontIO.hlsli"
#include "CBOnce.hlsli"

[maxvertexcount(4)]
void main(point VS_INPUT input[1], inout TriangleStream<PS_INPUT> outputStream) {

	float4 w = float4(input[0].Size.x, 0.0f, 0.0f, 0.0f);
	float4 h = float4(0.0f, input[0].Size.y, 0.0f, 0.0f);
	float2 tex = input[0].Tex;
	float4 pos = input[0].Pos;
	float2 scale = input[0].Scale;

	float4 Pos[4] = (float4[4])0.0f;
	float2 Tex[4] = (float2[4])0.0f;

	// first vertex
	Pos[0] = pos;
	Tex[0] = tex * scale;

	// second vertex
	Pos[1] = pos + w;
	Tex[1] = (tex + w.xy) * scale;

	// third vertex
	Pos[2] = pos - h;
	Tex[2] = (tex + h.xy) * scale;

	// fourth vertex
	Pos[3] = pos + w - h;
	Tex[3] = (tex + w.xy + h.xy) * scale;

	PS_INPUT output;
	output.Color = input[0].Color;

	for (int i = 0; i < 4; i++) {
		output.Pos = mul(Pos[i], WVP);
		output.Tex = Tex[i];

		outputStream.Append(output);
	}
}