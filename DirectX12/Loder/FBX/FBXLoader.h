
#include <fbxsdk.h>
#include <DirectXMath.h>
#include <vector>
#include <memory>
#include "Geometori.h"
#include <map>
#include <Windows.h>


class D3D12DeviceManager;
class VertexBufferManager;
class IndexBufferManager;
class ComandManager;
class TextureManager;
class FenceManager;
class RootSignatureManager;

typedef unsigned int UINT;


struct VERTEX {
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 uv;
	float bwheight[4];
	float bjointidx[4];
};
struct FBX_MATERIAL
{
	std::string matname;
	DirectX::XMFLOAT4 ambient;
	DirectX::XMFLOAT4 diffuse;
	DirectX::XMFLOAT4 specular;
	std::string textureName;
	int fecenum;
};
struct BONE
{
	DirectX::XMMATRIX bindPose;
};
struct POLY_TABLE
{
	int PolyIndex[20];//�|���S���ԍ� 
	int Index123[20];//3�̒��_�̂����A���Ԗڂ�
	int NumRef;//�����Ă���|���S����

};
struct IndexBufferInfo {
	std::shared_ptr<IndexBufferManager> idxbuff;
	int* idxAddress;
};
struct VertexBufferInfo {
	std::shared_ptr<VertexBufferManager> vertexmanager;
	VERTEX* vertexAddress;
};
struct AnimationFrameInfo {
	std::vector<fbxsdk::FbxTime> frameList;
	int startFrame;//�J�n�t���[���ʒu
	int endFrame;
	std::string search_animname;//�T���p�A�j���[�V������
};

class FBXLoader {
private://�֗��֐�
	DirectX::XMMATRIX ToXm(const FbxAMatrix& pSrc);//FBXMat->DXMAT
	DirectX::XMMATRIX ExtractOffset(const DirectX::XMMATRIX& mWorld);
	DirectX::XMMATRIX ExtractScaling(const DirectX::XMMATRIX& mWorld);
	DirectX::XMMATRIX ExtractRotation(const DirectX::XMMATRIX&  mWorld);
	FbxMatrix ToFBXXm(DirectX::XMMATRIX& pSrc);
	FbxAMatrix GetGeometryTransformation(FbxNode* inNode);//GetTRSmat
private:
	//WIC���g���ăe�N�X�`�������[�h����
	void LoadTexture(
		const std::string& filepath,
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<FenceManager>& fence,
		std::shared_ptr<RootSignatureManager>& rootsignature,
		std::vector<std::shared_ptr<TextureManager>>& texms
	);
	//Animation�f�[�^�𒊏o����
	void LoadSkinAnim(FbxNode* meshNode, FbxScene* scene);
	void LoadVertexData(std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<FenceManager>& fence,
		std::shared_ptr<RootSignatureManager>& rootsignature,
		bool animationF
	);
	void MaterialData(
		FbxMesh*& meshdata,
		std::shared_ptr<D3D12DeviceManager>& device,
		std::vector<VERTEX>& vertexdata,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<FenceManager>& fence,
		std::shared_ptr<RootSignatureManager>& rootsignature
	);
	//�p�X���瑊�΃p�X���쐬����
	const std::string TexturePath(const std::string& filepath);
	//���_�����擾: uv������mesh�ɑΉ�
	void VertexDataImport(FbxMesh*& meshdata, std::vector<VERTEX>& vertexdata, bool animationF);
	void CreateIndexBuffer(
		FbxMesh*& meshdata,
		std::shared_ptr<D3D12DeviceManager>& device,
		int matIdx,
		std::vector<VERTEX>& vertexdata,
		std::vector<FBX_MATERIAL>& material,
		std::vector<IndexBufferInfo>& idxbuff
	);
	void CreateVertexBuffer(
		size_t meshsize,
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<FenceManager>& fence,
		std::shared_ptr<ComandManager>& comand
	);
private:
	//mesh���O�p�`������
	void TriangulateRecursive(FbxNode* _pNode,FbxScene* scene);
	void InitializeSdkObjects();
protected:
	FBXLoader();
	virtual ~FBXLoader();

	/// <summary>
	/// 3D���f�������[�h����
	/// </summary>
	/// <param name="filepath"></param>
	/// <param name="device"></param>
	/// <param name="comand"></param>
	/// <param name="fence"></param>
	/// <param name="rootsignature"></param>
	/// <param name="animationF">Animation���邩�ǂ��� true: ����@false:�@���Ȃ�</param>
	void Load(
		const std::string& filepath,
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<FenceManager>& fence,
		std::shared_ptr<RootSignatureManager>& rootsignature,
		bool animationF
	);
	/// <summary>
	/// ���_���\�[�X��Ԃ�
	/// </summary>
	/// <returns></returns>
	std::vector<VertexBufferInfo>&  GetVertexResoce();
	/// <summary>
	/// ���_�C���f�b�N�X��Ԃ�
	/// </summary>
	/// <returns></returns>
	std::vector<std::vector<IndexBufferInfo>>& GetVertexIndexData();
	/// <summary>
	/// �}�e���A���e�[�u����Ԃ�
	/// </summary>
	/// <returns></returns>
	std::vector<std::vector<FBX_MATERIAL>>& GetMaterialTable();
	/// <summary>
	/// �e�N�X�`���e�[�u����Ԃ�
	/// </summary>
	/// <returns></returns>
	std::map<std::string, std::vector<std::shared_ptr<TextureManager>>>& GetTextureData();
	/// <summary>
	/// ���A���^�C��Animation���[�v
	/// </summary>
	void Animation(const std::string& animname, const int frame);
	/// <summary>
	/// Animation�pJoint�s���Ԃ�
	/// </summary>
	/// <returns></returns>
	std::vector<BONE>& GetPaletteBone();
	/// <summary>
	/// AnimationEndPos��Ԃ�
	/// </summary>
	/// <param name="animname">�Đ�������Animation�̖��O</param>
	/// <returns></returns>
	int GetAnimationFrameEnd(const std::string& animname);
private:
	FbxManager*		_fbxManager;
	FbxScene*		_fbxScene;
	FbxImporter*    _fbxImporter;
	std::map<std::string,std::vector<std::shared_ptr<TextureManager>>> _textures;//�}�e���A���ɕR�Â�����Ă���Texture
	std::string _fbxfilepath;
	std::vector<VertexBufferInfo>				_vertexbuffers;
	std::vector<std::vector<VERTEX>>			_vertexData_mesh;	//���̑Ή��p��2����
	std::vector<std::vector<IndexBufferInfo>>	_indexbuffers;
	std::vector<std::vector<FBX_MATERIAL>>		_material;
	std::vector<BONE>							_boneArray;//jointidx�ŗ��p�����s��̔z��
	bool _meshuvF;
	//Animaton
	fbxsdk::FbxTime start;
	fbxsdk::FbxTime stop;
	fbxsdk::FbxTime FrameTime;
	fbxsdk::FbxTime timeCount;
	std::map<std::string, AnimationFrameInfo> _frameList;

private:
	bool _traiangleCoolF;//���f�����O�p�`���b�V���ō\������Ă��邩  true:����Ă��� false:����Ă��Ȃ�
};
