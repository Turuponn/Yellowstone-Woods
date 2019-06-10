#include "../MixedHeader.hlsli"




[maxvertexcount(6)]
void PPGS(triangle VSOuputDeferred input[3], inout TriangleStream<PS_INPUTDeferred> gsstream)
{
    //WVP
    float4x4 cameraviewproje = mul(camera_proje, camera_view);
    matrix WVP = mul(cameraviewproje, dr_world);
    
    int i = 0;
    // ���Ƃ̒��_���o��
    for (i = 0; i < 3; i++)
    {
        PS_INPUTDeferred Out = (PS_INPUTDeferred) 0;
        Out.svpos = mul(WVP, input[i].pos); //���X�^���C�U�p
        Out.pos = mul(dr_world, input[i].pos);
        Out.normal = input[i].normal;
        Out.uv = input[i].uv;
        gsstream.Append(Out);
    }
    gsstream.RestartStrip();
  
}