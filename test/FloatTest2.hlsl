
// HLSL Translator: Floating-point Test 2 (to test expression conversion)
// 08/02/2017

float4 VS(float x : TEXCOORD0) : SV_Position
{
    float  a = 1 + 1;
    float  b = 2 + x;
    float  c = 3.0 + x;
    float  d = x + 4;
    float  e = 5;
    float  f = -6 + x;
    float3 g = 3 + 1.5;
    float3 h = 1 + g + 2;
    float3 i = h*2.0;
    float3 j = h*2;
    float3 k = h+2.0;
    float3 l = h+2;
    return 1;
}
