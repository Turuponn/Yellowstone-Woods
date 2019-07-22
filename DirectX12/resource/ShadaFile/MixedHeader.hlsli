
//通常テクスチャ　TODO:　テスト用
Texture2D<float4> tex:register(t0);
SamplerState smp:register(s0);
//Depth : TODO 未使用
Texture2D<float> g_texDepth : register(t1);
SamplerState g_samLinear : register(s1);
//dr model tex
Texture2D<float4> tex_dr : register(t2);
SamplerState texsmp_dr : register(s2);
//CubeMap : uv展開のみ用
TextureCube gCubeMap : register(t3);
SamplerState gsamPointWrap : register(s3);
//Gbuffer1 : buffer
Texture2D<float4> dr_color_tex : register(t4);
Texture2D<float4> dr_normal_tex : register(t5);
Texture2D<float4> dr_pos_tex : register(t6);
SamplerState dr_color_smp : register(s4);
SamplerState dr_normal_smp : register(s5);
SamplerState dr_pos_smp : register(s6);
//Gbuffer2 : lighting
Texture2D<float4> dl_color_tex : register(t7);
SamplerState dl_color_smp : register(s7);
//Gbuffer3 : PostProsess
Texture2D<float4> pp_color_tex : register(t8);
SamplerState pp_color_smp : register(s8);
//Canvas : UI
Texture2D<float4> canvas_tex : register(t9);
SamplerState canvas_smp : register(s9);


//ライト:　ディレクショナル,ポイント
cbuffer light_mat : register(b0) {
	matrix light_world;
	matrix lighe_scalemat;
	matrix lightview;
    matrix lightproje;
	matrix g_mWLPT; //ワールド・”ライトビュー”・プロジェクション・UV行列の合成
	matrix g_mWLP;
    float4 lightdir; //ディレクショナルライト情報（ライトの方向）
    float3 lightpos;
    float lightIntensity; //ディレクショナルライト情報（ライトの明るさ）
}
//カメラ定数
cbuffer camera_mat:register(b1) {
    matrix camera_viewproje;
    matrix camera_view;
    matrix camera_proje;
    matrix camera_viewproje_inv; //逆行列
    matrix camera_view_inv;
    matrix camera_proje_inv;
    matrix camera_viewproje_trans; //転置行列
    matrix camera_proje_trans;
    matrix camera_view_trans;
    float3 camera_postion;
    float3 camera_target;//注視点
    float3 camera_upvec;
}
//Layer用
cbuffer Layer_mat : register(b2)
{
    matrix Layer_world;
    matrix Layer_scale;
    matrix Layer_rotate;
    matrix Layer_translate;
}
//ディファード用共通
cbuffer dr_mat : register(b3)
{
    matrix dr_world_trans;
    matrix dr_world_inv;
    matrix dr_world;
    float4 dr_diffuse_color; //拡散反射
    float4 dr_ambient_color; //アンビエント
    float4 dr_specular_color; //スペキュラ成分
}
//bone
cbuffer testbone : register(b4)
{
    matrix jointMatrix[256];
}
//Canvas
cbuffer Canvas_mat : register(b5)
{
    matrix canvas_world;
    float4 canvas_color;
}


//ポストエフェクト
struct OutputPostEffect
{
    float4 svpos : SV_POSITION;
    float4 pos : POSITION;
    float4 normal : NORMAL;
    float2 uv : TEXCOORD;
};

//ディファードシェーディング
struct VSOuputDeferred
{
    float4 svpos : POSITION;
    float4 pos : POSITION2;
    float4 normal : NORMAL;
    float2 uv : TEXCOORD;
    float4 bone_weightidx : WEIGHTIDX;
    float4 bone_jointidx : JOINTIDX;
    float4 Depth : DEPTH;
    float4 posbackup : POSTION2; //頂点をピクセル単位にしたくない場合用
    float4 color : COLOR;
};
struct VS_INPUTDeferred{
    float4 pos : POSITION;
    float4 normal : NORMAL;
    float2 uv : TEXCOORD;
    float4 bone_weightidx : WEIGHTIDX;
    float4 bone_jointidx : JOINTIDX;
};
struct PS_INPUTDeferred{
    float4 svpos : SV_POSITION;
    float4 pos : POSITION;
    float4 normal : NORMAL;
    float2 uv : TEXCOORD;
    float4 Depth : DEPTH;//深度値
    float4 posbackup : POSTION2; //頂点をピクセル単位にしたくない場合用
    float4 wpos : POSTION3; //ワールド座標
    float4 color : COLOR;
};
//UI
struct VS_Output_UI{
    float4 svpos : SV_POSITION;
    float4 pos : POSITION;
    float4 normal : NORMAL;
    float2 uv : TEXCOORD;
};
struct PS_Input_UI
{
    float4 svpos : SV_POSITION;
    float4 pos : POSITION;
    float4 normal : NORMAL;
    float2 uv : TEXCOORD;
};


//接空間行列の逆行列を算出
float4x4 InvTangentMatrix(
   float3 tangent,
   float3 binormal,
   float3 normal)
{
    float4x4 mat =
    {
        float4(tangent, 0.0f),
        float4(binormal, 0.0f),
        float4(normal, 0.0f),
        { 0, 0, 0, 1 }
    };
    return transpose(mat); // 転置
}

