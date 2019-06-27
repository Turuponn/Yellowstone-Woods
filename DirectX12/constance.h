#pragma once


#include <dxgidebug.h>//解放忘れレポート用
#include <tchar.h>
#include <d3d12.h>
#include <DirectXMath.h>



#define SAFE_DELETE(ptr){ if(ptr) { delete(ptr); (ptr)=nullptr; } }//安全にdelete
#define SAFE_RELEASE(ptr){ if(ptr) { (ptr)->Release(); (ptr)=nullptr; } } //安全なRelease
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=nullptr; } }//安全な配列用delete



//エラーを無視する
#ifdef _MSC_VER
#define DISABLE_C4996   __pragma(warning(push)) __pragma(warning(disable:4996))
#define ENABLE_C4996    __pragma(warning(pop))
#else
#define DISABLE_C4996
#define ENABLE_C4996
#endif



#define DX_PI 3.14
#define DX_DIV2 DX_PI/2




enum ROOT_PARAM_TYPE {
	ROOT_PARAM_TEXTURE,//Test
	ROOT_PARAM_TEXTURE_DEPTH,
	ROOT_PARAM_TEXTURE_DR,
	ROOT_PARAM_TEXTURE_CUBEMAP_SAMPLER_PWRAP,
	ROOT_PARAM_TEXTURE_DR_COLOR,
	ROOT_PARAM_TEXTURE_DR_NORMAL,
	ROOT_PARAM_TEXTURE_DR_POS,
	ROOT_PARAM_TEXTURE_DL_COLOR,
	ROOT_PARAM_TEXTURE_PP_COLOR,
	ROOT_PARAM_TEXTURE_CANVAS_COLOR,
	ROOT_PARAM_TEXTURE_UAV_TEST,//TODO: UAV送り側

	ROOT_PARAM_CONSTANT_LIGHT,//ライト:ディレクショナルライト,ポイントライト
	ROOT_PARAM_CONSTANT_CAMERA,
	ROOT_PARAM_CONSTANT_LAYER,
	ROOT_PARAM_CONSTANT_DR,
	ROOT_PARAM_CONSTANT_TESTBONE,
	ROOT_PARAM_CONSTANT_CANVAS,
	ROOT_PARAM_UAV_TEST,//TODO: Test用UAV
	ROOT_PARAM_MAX,
};


//テクスチャ用
enum TEXTURE_REGISTER {
	TEX_TEXTURE,
	TEX_DEPTH,
	TEX_DR,
	TEX_CUBEMAP,
	TEX_DR_COLOR,
	TEX_DR_NORMALMAP,
	TEX_DR_POSMAP,
	TEX_DL_COLOR,
	TEX_PP_COLOR,
	TEX_CANVAS_COLOR,
	TEX_UAV_TEST,
	TEX_MAX
};

//WindowSize 16:9
const unsigned int SCREEN_SIZE_X = 1280;//WIDTH
const unsigned int SCREEN_SIZE_Y = 720;//HEIGHT





