#include "Geometori.h"
#include <stdio.h>
#include <Windows.h>
using namespace DirectX;

Geometori::Geometori() {

}
Geometori::~Geometori() {

}

void Geometori::lookAt(DirectX::XMVECTOR& eyevec,DirectX::XMVECTOR& targetvec,DirectX::XMVECTOR& upvec, DirectX::XMMATRIX& newmatrix) {
	//視点が原点になるように平行移動
	auto r_eyevec = -eyevec;
	DirectX::XMMATRIX r_eyevecmat = {};
	r_eyevecmat = DirectX::XMMatrixIdentity();
	r_eyevecmat *= XMMatrixTranslationFromVector(r_eyevec);
	//基底ベクトルの作成　
	DirectX::XMVECTOR basevec_x = {};//x' = (u × z') / |u × z'|
	DirectX::XMVECTOR basevec_y = {};// y' = z' × x' 
	DirectX::XMVECTOR basevec_z = {};//z' = (e - t) / |e - t|

	basevec_z = DirectX::XMVector3Normalize((DirectX::XMVector3Normalize(r_eyevec) - targetvec));
	basevec_x = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(upvec, basevec_z));
	basevec_y = DirectX::XMVector3Cross(basevec_z, basevec_x);
	DirectX::XMMATRIX fieldtransmat = {};//視野変換行列
	fieldtransmat = DirectX::XMMatrixIdentity();
	fieldtransmat *= XMMatrixTranslationFromVector(basevec_x);//最後のベクトル要素(w)は0になっているか？
	fieldtransmat *= XMMatrixTranslationFromVector(basevec_y);
	fieldtransmat *= XMMatrixTranslationFromVector(basevec_z);

	//視野変換行列 を求める
	auto lockatmat = fieldtransmat*r_eyevecmat;
	newmatrix = lockatmat;

}
void Geometori::CalcTangentAndBinormal(
	DirectX::XMFLOAT3* p0, DirectX::XMFLOAT2* uv0,
	DirectX::XMFLOAT3* p1, DirectX::XMFLOAT2* uv1,
	DirectX::XMFLOAT3* p2, DirectX::XMFLOAT2* uv2,
	Vector3* outTangent, Vector3* outBinormal
) {
	// 5次元→3次元頂点に
	DirectX::XMFLOAT3 CP0[3] = {
		DirectX::XMFLOAT3(p0->x, uv0->x, uv0->y),
		DirectX::XMFLOAT3(p0->y, uv0->x, uv0->y),
		DirectX::XMFLOAT3(p0->z, uv0->x, uv0->y),
	};
	DirectX::XMFLOAT3 CP1[3] = {
		DirectX::XMFLOAT3(p1->x, uv1->x, uv1->y),
		DirectX::XMFLOAT3(p1->y, uv1->x, uv1->y),
		DirectX::XMFLOAT3(p1->z, uv1->x, uv1->y),
	};
	DirectX::XMFLOAT3 CP2[3] = {
		DirectX::XMFLOAT3(p2->x, uv2->x, uv2->y),
		DirectX::XMFLOAT3(p2->y, uv2->x, uv2->y),
		DirectX::XMFLOAT3(p2->z, uv2->x, uv2->y),
	};

	// 平面パラメータからUV軸座標算出
	float U[3], V[3];
	for (int i = 0; i < 3; ++i) {
		DirectX::XMFLOAT3 V1 = { CP1[i].x - CP0[i].x,CP1[i].y - CP0[i].y,CP1[i].z - CP0[i].z };//三角形の辺ベクトルを取る
		DirectX::XMFLOAT3 V2 = { CP2[i].x - CP1[i].x,CP2[i].y - CP1[i].y,CP2[i].z - CP1[i].z };
		auto cross = Cross(Vector3(V1.x, V1.y, V1.z), Vector3(V2.x, V2.y, V2.z));//右ねじの法則から法線を取る
		DirectX::XMFLOAT3 ABC = { cross.x,cross.y,cross.z };//
		if (ABC.x == 0.0f) {
			//UV同士が重なっていた場合エラー扱いに
			return;
		}
		U[i] = -ABC.y / ABC.x;// -(b/x)  
		V[i] = -ABC.z / ABC.x;// -(c/x)
	}
	outTangent->x = U[0];
	outTangent->y = U[1];
	outTangent->z = U[2];

	outBinormal->x = V[0];
	outBinormal->y = V[1];
	outBinormal->z = V[2];
	//memcpy(outTangent, U, sizeof(float) * 3);
	//memcpy(outBinormal, V, sizeof(float) * 3);

	// 正規化します
	outTangent->Normalize();
	outBinormal->Normalize();
	
}


void CalcTangentAndBinormal2(
	DirectX::XMFLOAT3* p0, DirectX::XMFLOAT2* uv0,
	DirectX::XMFLOAT3* p1, DirectX::XMFLOAT2* uv1,
	DirectX::XMFLOAT3* p2, DirectX::XMFLOAT2* uv2,
	Vector3* outTangent, Vector3* outBinormal
) {
	//(-p1.x*(uv1.x - uv0.x))/ p0.x;//tan x
	//(-p2.x*(uv1.y - uv0.y)) / p0.x;//bin x

	//(-p1.y*(uv1.x - uv0.x)) / p0.x;//tan y
	//(-p2.y*(uv1.y - uv0.y)) / p0.x;//bin y

	//(-p1.z*(uv1.x - uv0.x)) / p0.x;//tan z
	//(-p2.z*(uv1.y - uv0.y)) / p0.x;//bin z

}