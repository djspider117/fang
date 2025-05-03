Texture2D tex;
SamplerState ss;

float4 main(float2 uv : TexCoord) : SV_Target
{
    return tex.Sample(ss, uv);
}