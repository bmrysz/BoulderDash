struct PS_INPUT {
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
	float2 Tex : TEXCOORD;
};

struct VS_INPUT {
	float4 Pos : POSITION;
	float2 Size : SIZE;
	float4 Color : COLOR;
	float2 Tex : TEXCOORD;
	float2 Scale : SCALE;
};