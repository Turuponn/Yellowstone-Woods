
#include "../MixedHeader.hlsli"



VSOuputDeferred DRCMapVS(VS_INPUTDeferred input)
{

    VSOuputDeferred output = (VSOuputDeferred) 0;
  
  
    output.pos = input.pos;
    output.normal = input.normal;
    output.uv = input.uv;
    output.bone_jointidx = input.bone_jointidx;
    output.bone_weightidx = input.bone_weightidx;

    return output;

}