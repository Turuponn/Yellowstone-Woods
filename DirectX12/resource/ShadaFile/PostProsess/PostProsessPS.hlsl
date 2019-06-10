#include "../MixedHeader.hlsli"
#include "../FXAA.hlsl"


struct DF_PS_OUTPUT
{
    float4 DF_Color : SV_Target0;
};

DF_PS_OUTPUT PPPS(PS_INPUTDeferred input) : SV_Target
{
    DF_PS_OUTPUT o = (DF_PS_OUTPUT) 0;
    float3 color = tex.Sample(smp, input.uv); //rtÇÃêF
   

    o.DF_Color = float4(color, 1.0f);


    return o;
}