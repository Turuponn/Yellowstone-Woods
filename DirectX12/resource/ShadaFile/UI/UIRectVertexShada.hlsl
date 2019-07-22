#include "../MixedHeader.hlsli"


VS_Output_UI UIRectVertexShada(float4 pos : POSITION, float4 normal : NORMAL, float2 uv : TEXCOORD)
{
    VS_Output_UI output = (VS_Output_UI) 0;


    //matrix compositemat = canvas_translate * canvas_scale;
    //matrix newworld = mul(mul(canvas_scale, canvas_world), canvas_translate);
    
    //èÌÇ…ëOÇ÷
    output.svpos = mul(canvas_world, pos);
    output.pos = mul(canvas_world, pos);
    output.normal = mul(canvas_world, normal);
    output.uv = uv;
    return output;
}