#include "../MixedHeader.hlsli"

VSOuputDeferred DSVS(VS_INPUTDeferred input)
{

    VSOuputDeferred output = (VSOuputDeferred) 0;

    
    
    matrix compositemat = Layer_translate * Layer_scale; //�����s��
    matrix newworld = mul(mul(Layer_scale, Layer_world), Layer_translate);
    
    
    //��ɑO��
    output.svpos = mul(newworld, input.pos);
    output.pos = mul(newworld, input.pos);
    output.normal = mul(mul(Layer_rotate, Layer_world), input.normal);
    output.uv = input.uv;
   
    

    return output;
}