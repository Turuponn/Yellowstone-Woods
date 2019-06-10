#pragma once

#include <DirectXMath.h>


//ローカル変換行列 これを使ってワールド変換行列を作成します
struct DR_MAT {
	DirectX::XMMATRIX dr_world_trans;
	DirectX::XMMATRIX dr_world_inv;
	DirectX::XMMATRIX dr_world;
	DirectX::XMFLOAT4 dr_diffuse_color; //拡散反射
	DirectX::XMFLOAT4 dr_ambient_color; //アンビエント
	DirectX::XMFLOAT4 dr_specular_color; //スペキュラ成分
};

//TODO: test gltf bone
#define JOINTMATMAX 256
struct JOINTBONE {
	DirectX::XMMATRIX jointMatrix[JOINTMATMAX];
};



struct Vector3 {
	float x;
	float y;
	float z;
	

	Vector3() { x = 0.0f; y = 0.0f; z = 0.0f;}
	Vector3(float newx, float newy, float newz) : x(newx), y(newy), z(newz) {}

	///正規化し結果を保持します
	void Normalize() {
		Vector3 newvec;
		float t;
		t = sqrtf((this->x*this->x) + (this->y*this->y) + (this->z*this->z));//大きさ
		newvec.x = this->x / t;
		newvec.y = this->y / t;
		newvec.z = this->z / t;
		*this = newvec;
	}
	/// 正規化し結果を返します
	Vector3 Normalized() {
		Vector3 newvec;
		float t;
		t = sqrtf((this->x*this->x) + (this->y*this->y) + (this->z*this->z));//大きさ
		newvec.x = this->x / t;
		newvec.y = this->y / t;
		newvec.z = this->z / t;
		return newvec;
	}
	float Forward() {
		return z;
	}


	Vector3 operator*(Vector3 right) {
		Vector3 newvector3;
		newvector3.x = this->x * right.x;
		newvector3.y = this->y * right.y;
		newvector3.z = this->z * right.z;
		return newvector3;
	}
	Vector3 operator+(Vector3 right) {
		Vector3 newvector3;
		newvector3.x = this->x + right.x;
		newvector3.y = this->y + right.y;
		newvector3.z = this->z + right.z;
		return newvector3;
	}
	Vector3 operator-(Vector3 right) {
		Vector3 newvector3;
		newvector3.x = this->x - right.x;
		newvector3.y = this->y - right.y;
		newvector3.z = this->z - right.z;
		return newvector3;
	}
	Vector3 operator/(Vector3 right) {
		Vector3 newvector3;
		newvector3.x = this->x / right.x;
		newvector3.y = this->y / right.y;
		newvector3.z = this->z / right.z;
		return newvector3;
	}
	Vector3 operator*(float right) {
		Vector3 newvector3;
		newvector3.x = this->x * right;
		newvector3.y = this->y * right;
		newvector3.z = this->z * right;
		return newvector3;
	}
	Vector3 operator+(float right) {
		Vector3 newvector3;
		newvector3.x = this->x + right;
		newvector3.y = this->y + right;
		newvector3.z = this->z + right;
		return newvector3;
	}
	Vector3 operator-(float right) {
		Vector3 newvector3;
		newvector3.x = this->x - right;
		newvector3.y = this->y - right;
		newvector3.z = this->z - right;
		return newvector3;
	}
	Vector3 operator/(float right) {
		Vector3 newvector3;
		newvector3.x = this->x / right;
		newvector3.y = this->y / right;
		newvector3.z = this->z / right;
		return newvector3;
	}
};


struct Vector4 {
	float x;
	float y;
	float z;
	float w;

	Vector4() { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; }
	Vector4(float newx, float newy, float newz,float neww) : x(newx), y(newy), z(newz),w(neww) {}

	///正規化し結果を保持します
	void Normalize() {
		Vector4 newvec;
		float t;
		t = sqrtf((this->x*this->x) + (this->y*this->y) + (this->z*this->z)+ (this->w*this->w));//大きさ
		newvec.x = this->x / t;
		newvec.y = this->y / t;
		newvec.z = this->z / t;
		newvec.w = this->w / t;
		*this = newvec;
	}
	/// 正規化し結果を返します
	Vector4 Normalized() {
		Vector4 newvec;
		float t;
		t = sqrtf((this->x*this->x) + (this->y*this->y) + (this->z*this->z)+ (this->w*this->w));//大きさ
		newvec.x = this->x / t;
		newvec.y = this->y / t;
		newvec.z = this->z / t;
		newvec.w = this->w / t;
		return newvec;
	}
	float Forward() {
		return z;
	}


	Vector4 operator*(Vector4 right) {
		Vector4 newvector;
		newvector.x = this->x * right.x;
		newvector.y = this->y * right.y;
		newvector.z = this->z * right.z;
		newvector.w = this->w * right.w;
		return newvector;
	}
	Vector4 operator+(Vector4 right) {
		Vector4 newvector;
		newvector.x = this->x + right.x;
		newvector.y = this->y + right.y;
		newvector.z = this->z + right.z;
		newvector.w = this->w + right.w;
		return newvector;
	}
	Vector4 operator-(Vector4 right) {
		Vector4 newvector;
		newvector.x = this->x - right.x;
		newvector.y = this->y - right.y;
		newvector.z = this->z - right.z;
		newvector.w = this->w - right.w;
		return newvector;
	}
	Vector4 operator/(Vector4 right) {
		Vector4 newvector;
		newvector.x = this->x / right.x;
		newvector.y = this->y / right.y;
		newvector.z = this->z / right.z;
		newvector.w = this->w / right.w;
		return newvector;
	}
	Vector4 operator*(float right) {
		Vector4 newvector;
		newvector.x = this->x * right;
		newvector.y = this->y * right;
		newvector.z = this->z * right;
		newvector.w = this->w * right;
		return newvector;
	}
	Vector4 operator+(float right) {
		Vector4 newvector;
		newvector.x = this->x + right;
		newvector.y = this->y + right;
		newvector.z = this->z + right;
		newvector.w = this->w + right;
		return newvector;
	}
	Vector4 operator-(float right) {
		Vector4 newvector;
		newvector.x = this->x - right;
		newvector.y = this->y - right;
		newvector.z = this->z - right;
		newvector.w = this->w - right;
		return newvector;
	}
	Vector4 operator/(float right) {
		Vector4 newvector;
		newvector.x = this->x / right;
		newvector.y = this->y / right;
		newvector.z = this->z / right;
		newvector.w = this->w / right;
		return newvector;
	}
};


class Geometori {
public:

	Geometori();
	virtual ~Geometori();



	/*
	tangent
	binormal
	Note:
	座標の高さに差を出さないと値がでない
	*/
	// 3頂点とUV値から指定座標でのU軸（Tangent）及びV軸（Binormal）を算出
	//
	// p0, p1, p2    : ローカル空間での頂点座標（ポリゴン描画順にすること）
	// uv0, uv1, uv2 : 各頂点のUV座標
	// outTangent    : U軸（Tangent）出力
	// outBinormal   : V軸（Binormal）出力
	void CalcTangentAndBinormal(
		DirectX::XMFLOAT3* p0, DirectX::XMFLOAT2* uv0,
		DirectX::XMFLOAT3* p1, DirectX::XMFLOAT2* uv1,
		DirectX::XMFLOAT3* p2, DirectX::XMFLOAT2* uv2,
		Vector3* outTangent, Vector3* outBinormal
	);


	/*void CalcTangentAndBinormal2(
		DirectX::XMFLOAT3* p0, DirectX::XMFLOAT2* uv0,
		DirectX::XMFLOAT3* p1, DirectX::XMFLOAT2* uv1,
		DirectX::XMFLOAT3* p2, DirectX::XMFLOAT2* uv2,
		Vector3* outTangent, Vector3* outBinormal
	);*/



	Vector3 Cross(Vector3& left, Vector3& right) {
		Vector3 cross = {};
		DirectX::XMVECTOR vec1 = { left.x,left.y,left.z, };
		DirectX::XMVECTOR vec2 = { right.x,right.y,right.z, };
		auto vec = DirectX::XMVector2Cross(vec1, vec2);
		DirectX::XMFLOAT3 crossanser = {};
		DirectX::XMStoreFloat3(&crossanser, vec);
		cross = { crossanser.x,crossanser.y,crossanser.z };
		return cross;
	}

	//視差変換行列
	//同次座標=XMVECTOR 
	void lookAt(DirectX::XMVECTOR& eyevec,DirectX::XMVECTOR& targetvec, DirectX::XMVECTOR& upvec, DirectX::XMMATRIX& newmatrix);
private:

};


