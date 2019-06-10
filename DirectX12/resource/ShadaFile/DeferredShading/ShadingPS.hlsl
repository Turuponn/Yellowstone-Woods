#include "../MixedHeader.hlsli"
#include "../FXAA.hlsl"


float random(float2 uv, int Seed)
{
    return frac(sin(dot(uv.xy, float2(12.9898, 78.233)) + Seed) * 43758.5453);
}

//�[�x�l����������
float LinearizeDepth(float depth, float near, float far)
{
    return (2.0 * near) / (far + near - depth * (far - near));
}

float4 SPS(OutputPostEffect input) : SV_Target
{

   
    
    float4 color = 1;
    
    float4 vWorldNormal =dr_normal_tex.Sample(dr_normal_smp, input.uv) * 2.0 - 1.0; //0~1->-1~1 
    
    
    // z/w Depth -> viewDepth
    //float4 p_vd = mul(camera_proje_inv, p);
    //float depth_v = (p_vd.xyz / p_vd.w).z;
    // z/w Depth ���烏�[���h���W���v�Z����
    //float depth_zw = dr_pos_tex.Sample(dr_pos_smp, input.uv).w;
    //float4 p = float4(input.uv * 2.0f - 1.0f, depth_zw, 1.0f);
    //float4 p_zwd = mul(camera_viewproje_inv,p);
    //float3 worldpos = p_zwd.xyz / p_zwd.w;
    
    float4 worldpos = dr_pos_tex.Sample(dr_pos_smp, input.uv);
    worldpos = worldpos * 2.0 - 1.0;
    worldpos = float4(worldpos.xyz / worldpos.w, 1);


    //SSAO TODO:�@�ۗ� 
    float4 ssaocolor = 1;
    

    return ssaocolor;
 
    
}