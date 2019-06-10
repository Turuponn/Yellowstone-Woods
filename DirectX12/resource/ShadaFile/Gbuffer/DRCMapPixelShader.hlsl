#include "../MixedHeader.hlsli"


struct DF_CMAP_PS_OUTPUT
{
    float4 DF_Color : SV_Target0;
    float4 DF_Normal : SV_Target1;
    float4 DF_Position : SV_Target2;
};


DF_CMAP_PS_OUTPUT DRCMapPS(PS_INPUTDeferred input) : SV_TARGET
{
    DF_CMAP_PS_OUTPUT o = (DF_CMAP_PS_OUTPUT)0;
    
    
    float4 texcolor = gCubeMap.Sample(gsamPointWrap, input.posbackup.xyz);
   

    float d = input.Depth.z / input.Depth.w; //深度値
    o.DF_Color = float4(texcolor.rgb,1);
    o.DF_Normal = float4(normalize(input.normal.xyz) * 0.5 + 0.5, -1);//キューブマップは深度値計算を行わない(-1)
    o.DF_Position = normalize(input.wpos) * 0.5 + 0.5; //0~1  SSAO用Pos
   
    return o;
}