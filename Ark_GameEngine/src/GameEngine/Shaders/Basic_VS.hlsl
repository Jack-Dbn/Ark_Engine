struct VS_Input{
	float2 pos : POSITION;
};

struct PS_Input {
	float4 pos : SV_POSITION;
};

PS_Input Basic_VS(VS_Input input) {
	PS_Input VS_Result;

	VS_Result.pos = float4(input.pos, 0.5f, 1.0f);

	return VS_Result;
}