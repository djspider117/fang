struct VSOut
{
    float3 color : VertexColor;
    float4 pos : SV_Position;
};

cbuffer CBuf : register(b0)
{
    matrix transform;
};

VSOut main(float3 vpos : Position, float3 col : VertexColor)
{
    VSOut rv;
    rv.color = col;
    //rv.pos = float4(vpos, 1);
    rv.pos = mul(float4(vpos, 1), transform);
    return rv;
    //return mul(float4(vpos, 1), transform);
    //return float4(vpos, 1);
}