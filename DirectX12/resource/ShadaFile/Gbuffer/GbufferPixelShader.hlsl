#include "../MixedHeader.hlsli"

//ピクセルシェーダー出力 : MRT
struct DF_PS_OUTPUT
{
    float4 DF_Color : SV_Target0;
    float4 DF_Normal : SV_Target1;
    float4 DF_Position : SV_Target2;
};

DF_PS_OUTPUT GbufferPS(PS_INPUTDeferred input) : SV_TARGET
{
    DF_PS_OUTPUT o = (DF_PS_OUTPUT) 0;
    float3 color = tex_dr.Sample(texsmp_dr, input.uv);
   
    
    float3 das = 0;
    das = dr_specular_color > 0 ? dr_diffuse_color * dr_specular_color + dr_ambient_color : dr_diffuse_color;
    

    
    float d = input.Depth.z / input.Depth.w; //深度値
    o.DF_Color = float4(color,1); 
    o.DF_Normal = float4(normalize(input.normal.xyz) * 0.5 + 0.5, 1);
    //o.DF_Position = normalize(input.wpos) * 0.5 + 0.5; //0~1  SSAO用Pos
    o.DF_Position = float4(d,0,0,0);

    return o;
}