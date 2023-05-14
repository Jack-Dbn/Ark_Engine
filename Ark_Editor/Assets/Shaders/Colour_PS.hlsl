Texture2D simpleTexture : register(t0);
SamplerState simpleSampler : register(s0);

struct PS_Input {
	float4 pos : SV_POSITION;
	float3 norm : NORMAL;
	float2 tex : TEXCOORD0;
};

float4 Colour_PS(PS_Input input) : SV_TARGET
{
	float3 lightDir = normalize(float3(1, -1, 0));
	float4 texColour = simpleTexture.Sample(simpleSampler, input.tex);
	float lightMag = 0.1f * saturate(dot(input.norm, -lightDir)) + 0.2f;

	return texColour + lightMag;
}