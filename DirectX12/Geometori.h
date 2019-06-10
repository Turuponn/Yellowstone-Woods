#pragma once

#include <DirectXMath.h>


//���[�J���ϊ��s�� ������g���ă��[���h�ϊ��s����쐬���܂�
struct DR_MAT {
	DirectX::XMMATRIX dr_world_trans;
	DirectX::XMMATRIX dr_world_inv;
	DirectX::XMMATRIX dr_world;
	DirectX::XMFLOAT4 dr_diffuse_color; //�g�U����
	DirectX::XMFLOAT4 dr_ambient_color; //�A���r�G���g
	DirectX::XMFLOAT4 dr_specular_color; //�X�y�L��������
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

	///���K�������ʂ�ێ����܂�
	void Normalize() {
		Vector3 newvec;
		float t;
		t = sqrtf((this->x*this->x) + (this->y*this->y) + (this->z*this->z));//�傫��
		newvec.x = this->x / t;
		newvec.y = this->y / t;
		newvec.z = this->z / t;
		*this = newvec;
	}
	/// ���K�������ʂ�Ԃ��܂�
	Vector3 Normalized() {
		Vector3 newvec;
		float t;
		t = sqrtf((this->x*this->x) + (this->y*this->y) + (this->z*this->z));//�傫��
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

	///���K�������ʂ�ێ����܂�
	void Normalize() {
		Vector4 newvec;
		float t;
		t = sqrtf((this->x*this->x) + (this->y*this->y) + (this->z*this->z)+ (this->w*this->w));//�傫��
		newvec.x = this->x / t;
		newvec.y = this->y / t;
		newvec.z = this->z / t;
		newvec.w = this->w / t;
		*this = newvec;
	}
	/// ���K�������ʂ�Ԃ��܂�
	Vector4 Normalized() {
		Vector4 newvec;
		float t;
		t = sqrtf((this->x*this->x) + (this->y*this->y) + (this->z*this->z)+ (this->w*this->w));//�傫��
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
	���W�̍����ɍ����o���Ȃ��ƒl���łȂ�
	*/
	// 3���_��UV�l����w����W�ł�U���iTangent�j�y��V���iBinormal�j���Z�o
	//
	// p0, p1, p2    : ���[�J����Ԃł̒��_���W�i�|���S���`�揇�ɂ��邱�Ɓj
	// uv0, uv1, uv2 : �e���_��UV���W
	// outTangent    : U���iTangent�j�o��
	// outBinormal   : V���iBinormal�j�o��
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

	//�����ϊ��s��
	//�������W=XMVECTOR 
	void lookAt(DirectX::XMVECTOR& eyevec,DirectX::XMVECTOR& targetvec, DirectX::XMVECTOR& upvec, DirectX::XMMATRIX& newmatrix);
private:

};


