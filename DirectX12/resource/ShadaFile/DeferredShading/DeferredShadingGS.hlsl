#include "../MixedHeader.hlsli"




[maxvertexcount(6)]
void DSGS(triangle VSOuputDeferred input[3], inout TriangleStream<PS_INPUTDeferred> gsstream)
{
    //WVP
    matrix cameraviewproje = mul(camera_proje, camera_view);
    matrix WVP = mul(cameraviewproje, dr_world);
    
    int i = 0;
    // もとの頂点を出力
    for (i = 0; i < 3; i++)
    {
        PS_INPUTDeferred Out = (PS_INPUTDeferred) 0;
        Out.svpos = mul(WVP, input[i].pos); //ラスタライザ用
        Out.pos = mul(dr_world, input[i].pos);
        Out.normal = input[i].normal;
        Out.uv = input[i].uv;
        gsstream.Append(Out);
    }
    gsstream.RestartStrip();
  
}