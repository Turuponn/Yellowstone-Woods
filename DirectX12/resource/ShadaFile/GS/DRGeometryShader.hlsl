


#include "../MixedHeader.hlsli"




[maxvertexcount(6)]
void GSMain(triangle VSOuputDeferred input[3], inout TriangleStream<PS_INPUTDeferred> gsstream)
{
    


   
    matrix WVP = mul(mul(dr_world_trans, camera_view_trans), camera_proje_trans);
   

    int i = 0;
    float posmove = 1.0f;
    // もとの頂点を出力
    for (i = 0; i < 3; i++)
    {
        

       

        float wx = input[i].bone_weightidx.x;
        float wy = input[i].bone_weightidx.y;
        float wz = input[i].bone_weightidx.z;
        float ww = input[i].bone_weightidx.w;
        matrix blend =
        (wx * jointMatrix[int(input[i].bone_jointidx.x)]) +
        (wy * jointMatrix[int(input[i].bone_jointidx.y)]) +
        (wz * jointMatrix[int(input[i].bone_jointidx.z)]) +
        (ww * jointMatrix[int(input[i].bone_jointidx.w)]);







       




        PS_INPUTDeferred Out = (PS_INPUTDeferred) 0;

        
        float4 Pos = float4(input[i].pos.xyz, 1);
        Pos.x *= -1;
        float4 norm = float4(input[i].normal.xyz,1);
        norm.x *= -1;
        
        //trans
        Out.svpos = mul(mul(blend, Pos), WVP);
        Out.pos = mul(mul(blend, Pos), dr_world_trans);
        Out.normal = mul(mul(blend,norm), dr_world_trans);
        Out.uv = input[i].uv;
        Out.color = float4(input[i].bone_weightidx.x, input[i].bone_weightidx.y, input[i].bone_weightidx.z, input[i].bone_weightidx.w);
        //キューブマップ
        Out.posbackup = Out.pos; //頂点から中心の方向ベクトル用
        

        //z/w 深度値格納
        float4 worldPosition = mul(dr_world, Pos);
        float4 gpostion = mul(mul(camera_proje, camera_view), worldPosition);
        Out.Depth = gpostion;
        //SSAO用ワールド行列座標
        Out.wpos = mul(mul(dr_world, blend), Pos);
        
        gsstream.Append(Out);
    }
    gsstream.RestartStrip();
  
 


}