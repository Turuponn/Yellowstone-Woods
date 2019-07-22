#include "../MixedHeader.hlsli"
#include "../FXAA.hlsl"

float4 PEPS(OutputPostEffect input) : SV_Target
{

    float4 color = float4((dr_color_tex.Sample(dr_color_smp, input.uv).rgb),1);
    
    
    //テクスチャーから情報を取り出す

    //テクスチャのサイズ
    float invW = 0.0f;
    float invH = 0.0f;
    float w = 0;
    float h = 0;
    dr_color_tex.GetDimensions(w, h);
    invW = 1.0f / w; //0~1
    invH = 1.0f / h;

    
  

    //ぼかし
    float4 ret = 0;
    float w2 = 0;
    float h2 = 0;
    dr_color_tex.GetDimensions(w2, h2);
    const float dx = 1 / w2;
    const float dy = 1 / h2;
    //テクセルを取得
    float2 Texel0 = input.uv + float2(-dx, 0.0f);
    float2 Texel1 = input.uv + float2(+dx, 0.0f);
    float2 Texel2 = input.uv + float2(0.0f, +dy);
    float2 Texel3 = input.uv + float2(0.0f, -dy);
    float2 Texel4 = input.uv + float2(-dx, -dy);
    float2 Texel5 = input.uv + float2(+dx, -dy);
    float2 Texel6 = input.uv + float2(-dx, +dy);
    float2 Texel7 = input.uv + float2(+dx, +dy);
    float4 t0 = dl_color_tex.Sample(dl_color_smp, Texel0);
    float4 t1 = dl_color_tex.Sample(dl_color_smp, Texel1);
    float4 t2 = dl_color_tex.Sample(dl_color_smp, Texel2);
    float4 t3 = dl_color_tex.Sample(dl_color_smp, Texel3);
    float4 t4 = dl_color_tex.Sample(dl_color_smp, Texel4);
    float4 t5 = dl_color_tex.Sample(dl_color_smp, Texel5);
    float4 t6 = dl_color_tex.Sample(dl_color_smp, Texel6);
    float4 t7 = dl_color_tex.Sample(dl_color_smp, Texel7);
    float4 tt0 = dl_color_tex.Sample(dl_color_smp, Texel0 + float2(-4 / w2, 0));
    float4 tt1 = dl_color_tex.Sample(dl_color_smp, Texel1 + float2(-4 / w2, 0));
    float4 tt2 = dl_color_tex.Sample(dl_color_smp, Texel2 + float2(-4 / w2, 0));
    float4 tt3 = dl_color_tex.Sample(dl_color_smp, Texel3 + float2(-4 / w2, 0));
    float4 tt4 = dl_color_tex.Sample(dl_color_smp, Texel4 + float2(-4 / w2, 0));
    float4 tt5 = dl_color_tex.Sample(dl_color_smp, Texel5 + float2(-4 / w2, 0));
    float4 tt6 = dl_color_tex.Sample(dl_color_smp, Texel6 + float2(-4 / w2, 0));
    float4 tt7 = dl_color_tex.Sample(dl_color_smp, Texel7 + float2(-4 / w2, 0));
    float4 Blur = t0 + t1 + t2 + t3 + t4 + t5 + t6 + t7 +
					tt0 + tt1 + tt2 + tt3 + tt4 + tt5 + tt6 + tt7;
    Blur /= 16; //平均化
   

    //輪郭線 :ラプラシアンフィルタ 
    float2 uv = input.uv;
    float4 d2 = g_texDepth.Sample(dr_pos_smp, uv + float2(invW * 0, invH * 1));
    float4 d4 = g_texDepth.Sample(dr_pos_smp, uv + float2(invW * -1, invH * 0));
    float4 d5 = g_texDepth.Sample(dr_pos_smp, uv + float2(invW * 0, invH * 0));
    float4 d6 = g_texDepth.Sample(dr_pos_smp, uv + float2(invW * 1, invH * 0));
    float4 d8 = g_texDepth.Sample(dr_pos_smp, uv + float2(invW * 0, invH * -1));
    float4 v = d2 + d4 + d6 + d8 + (d5 * -4.0);
    v = v > 0.001f ? 1.0 : 0.0;
    float v2 = (1 - v);
    if (v2 == 0)
    { //ラプラシアン値が0(輪郭線)ならば輪郭線を描画
        color *= float4(0, 0, 0, 1);
    }
    color = color*Blur;

       
 


    
    
    
    return color;
    //return float4(dl_color_tex.Sample(dl_color_smp, input.uv).rgb,1);
    //return dr_color_tex.Sample(dr_color_smp, input.uv);

}