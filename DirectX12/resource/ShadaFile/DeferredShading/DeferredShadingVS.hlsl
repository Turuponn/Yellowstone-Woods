#include "../MixedHeader.hlsli"

VSOuputDeferred DSVS(VS_INPUTDeferred input)
{

    VSOuputDeferred o = (VSOuputDeferred) 0;

    
    o.pos = input.pos;
    o.normal = input.normal;
    o.uv = input.uv;
   
    

    return o;
}