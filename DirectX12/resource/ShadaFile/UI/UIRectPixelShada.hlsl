#include "../MixedHeader.hlsli"


float4 UIRectPixelShada(PS_Input_UI input) : SV_Target
{
    float4 color = canvas_tex.Sample(canvas_smp,input.uv);
 
    if (color.a == 0)//
    {
        discard;
    }
    return color * canvas_color;
}
