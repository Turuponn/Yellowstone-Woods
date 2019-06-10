
#include "../MixedHeader.hlsli"


OutputPostEffect PEVS(float4 pos : POSITION, float4 normal : NORMAL, float2 uv : TEXCOORD)
{
    OutputPostEffect output = (OutputPostEffect) 0;

    
    
    matrix compositemat = Layer_translate * Layer_scale; //合成行列
    matrix newworld = mul(mul(Layer_scale, Layer_world), Layer_translate);
    
    
    //常に前へ
    output.svpos = mul(newworld, pos);
    output.pos = mul(newworld, pos);
    output.normal = mul(mul(Layer_rotate, Layer_world), normal);
    output.uv = uv;

  
    return output;
}