
//�ʏ�e�N�X�`���@TODO:�@�e�X�g�p
Texture2D<float4> tex:register(t0);
SamplerState smp:register(s0);
//Depth : TODO ���g�p
Texture2D<float> g_texDepth : register(t1);
SamplerState g_samLinear : register(s1);
//dr model tex
Texture2D<float4> tex_dr : register(t2);
SamplerState texsmp_dr : register(s2);
//CubeMap : uv�W�J�̂ݗp
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


//���C�g:�@�f�B���N�V���i��,�|�C���g
cbuffer light_mat : register(b0) {
	matrix light_world;
	matrix lighe_scalemat;
	matrix lightview;
    matrix lightproje;
	matrix g_mWLPT; //���[���h�E�h���C�g�r���[�h�E�v���W�F�N�V�����EUV�s��̍���
	matrix g_mWLP;
    float4 lightdir; //�f�B���N�V���i�����C�g���i���C�g�̕����j
    float3 lightpos;
    float lightIntensity; //�f�B���N�V���i�����C�g���i���C�g�̖��邳�j
}
//�J�����萔
cbuffer camera_mat:register(b1) {
    matrix camera_viewproje;
    matrix camera_view;
    matrix camera_proje;
    matrix camera_viewproje_inv; //�t�s��
    matrix camera_view_inv;
    matrix camera_proje_inv;
    matrix camera_viewproje_trans; //�]�u�s��
    matrix camera_proje_trans;
    matrix camera_view_trans;
    float3 camera_postion;
    float3 camera_target;//�����_
    float3 camera_upvec;
}
//Layer�p
cbuffer Layer_mat : register(b2)
{
    matrix Layer_world;
    matrix Layer_scale;
    matrix Layer_rotate;
    matrix Layer_translate;
}
//�f�B�t�@�[�h�p����
cbuffer dr_mat : register(b3)
{
    matrix dr_world_trans;
    matrix dr_world_inv;
    matrix dr_world;
    float4 dr_diffuse_color; //�g�U����
    float4 dr_ambient_color; //�A���r�G���g
    float4 dr_specular_color; //�X�y�L��������
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


//�|�X�g�G�t�F�N�g
struct OutputPostEffect
{
    float4 svpos : SV_POSITION;
    float4 pos : POSITION;
    float4 normal : NORMAL;
    float2 uv : TEXCOORD;
};

//�f�B�t�@�[�h�V�F�[�f�B���O
struct VSOuputDeferred
{
    float4 svpos : POSITION;
    float4 pos : POSITION2;
    float4 normal : NORMAL;
    float2 uv : TEXCOORD;
    float4 bone_weightidx : WEIGHTIDX;
    float4 bone_jointidx : JOINTIDX;
    float4 Depth : DEPTH;
    float4 posbackup : POSTION2; //���_���s�N�Z���P�ʂɂ������Ȃ��ꍇ�p
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
    float4 Depth : DEPTH;//�[�x�l
    float4 posbackup : POSTION2; //���_���s�N�Z���P�ʂɂ������Ȃ��ꍇ�p
    float4 wpos : POSTION3; //���[���h���W
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


//�ڋ�ԍs��̋t�s����Z�o
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
    return transpose(mat); // �]�u
}

