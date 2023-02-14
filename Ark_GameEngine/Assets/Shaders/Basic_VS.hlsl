cbuffer simpleConstantBuffer : register (b0)
{
	matrix model;
	matrix view;
	matrix projection;
};

struct VS_Input{
	float3 pos : POSITION;
	float3 color : COLOR;
};

struct PS_Input {
	float4 pos : SV_POSITION;
	float3 color : COLOR;
};

PS_Input Basic_VS(VS_Input input) {
	PS_Input VS_Result;

	float4 newPos = float4(input.pos, 1.0f);
	
	newPos = mul(newPos, model);
	newPos = mul(newPos, view);
	newPos = mul(newPos, projection);

	VS_Result.pos = newPos;
	VS_Result.color = input.color;

	return VS_Result;
}