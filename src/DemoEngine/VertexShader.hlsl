struct VSOut
{
    float3 color : VertexColor;
    float4 pos : SV_Position;
};

cbuffer CBuf
{
    matrix transform;
};

VSOut main(float3 vpos : Position, float3 col : VertexColor)
{
    VSOut rv;
    rv.pos = mul(float4(vpos, 1), transform);
    rv.color = col;
    
    return rv;
}