float4 main(float3 color : VertexColor) : SV_Target
{
    return float4(color, 1);
}