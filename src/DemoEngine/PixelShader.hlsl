float4 main(float3 color : VertexColor) : SV_Target
{
    return float4(color, 1);
}
//float4 main() : SV_Target
//{
//    return float4(1, 0, 1, 1);
//}