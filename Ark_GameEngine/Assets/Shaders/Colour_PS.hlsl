struct PS_Input {
	float4 pos : SV_POSITION;
};

float4 Colour_PS(PS_Input input) : SV_TARGET
{
	return float4(0.0f, 1.0f, 0.0f, 1.0f);
}