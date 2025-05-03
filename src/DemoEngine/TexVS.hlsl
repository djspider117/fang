struct VSOut
{
    float2 uv : TexCoord;
    float4 pos : SV_Position;
};

cbuffer CBuf : register(b0)
{
    matrix transform;
};

VSOut main(float3 vpos : Position, float2 uv : TexCoord)
{
    VSOut rv;
    rv.uv = uv;
    rv.pos = mul(float4(vpos, 1), transform);
    return rv;
}