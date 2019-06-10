#include "../MixedHeader.hlsli"
#include "../FXAA.hlsl"




float4 FPS(OutputPostEffect input) : SV_Target
{
    float4 color = 1;

    //テクスチャのサイズ
    float invW = 0.0f;
    float invH = 0.0f;
    float w = 0;
    float h = 0;
    dr_color_tex.GetDimensions(w, h);//テクスチャのサイズを取得します
    invW = 1.0f / w; //0~1
    invH = 1.0f / h;

    //FXAA: Nvidia
    float4 fxaacolor = 1;
    float2 size;
    size.x = invW;
    size.y = invH;
    FxaaTex InputFXAATex = { pp_color_smp, pp_color_tex };
    color = float4(FxaaPixelShader(
     input.uv,
     FxaaFloat4(0, 0, size.x, size.y),
     InputFXAATex,
     InputFXAATex,
     InputFXAATex,
     size,
     FxaaFloat4(0.0f, 0.0f, 0.0f, 0.0f),
     FxaaFloat4(0.0f, 0.0f, 0.0f, 0.0f),
     FxaaFloat4(0.0f, 0.0f, 0.0f, 0.0f),
    0.75f,
    0.166f,
     0.0833f,
     8.0f,
     0.125f,
     0.05f,
    FxaaFloat4(0.0f, 0.0f, 0.0f, 0.0f)
    ).rgb, color.a);
    return color;
}
