#include "../MixedHeader.hlsli"


VSOuputDeferred GbufferVS(VS_INPUTDeferred input)
{

    
    VSOuputDeferred o = (VSOuputDeferred) 0;  
    o.pos = input.pos;
    o.normal = input.normal;
    o.uv = input.uv;
    o.bone_jointidx = input.bone_jointidx;
    o.bone_weightidx = input.bone_weightidx;


    return o;

}
