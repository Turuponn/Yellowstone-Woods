
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
	int PolyIndex[20];//ポリゴン番号 
	int Index123[20];//3つの頂点のうち、何番目か
	int NumRef;//属しているポリゴン数

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
	int startFrame;//開始フレーム位置
	int endFrame;
	std::string search_animname;//探索用アニメーション名
};

class FBXLoader {
private://便利関数
	DirectX::XMMATRIX ToXm(const FbxAMatrix& pSrc);//FBXMat->DXMAT
	DirectX::XMMATRIX ExtractOffset(const DirectX::XMMATRIX& mWorld);
	DirectX::XMMATRIX ExtractScaling(const DirectX::XMMATRIX& mWorld);
	DirectX::XMMATRIX ExtractRotation(const DirectX::XMMATRIX&  mWorld);
	FbxMatrix ToFBXXm(DirectX::XMMATRIX& pSrc);
	FbxAMatrix GetGeometryTransformation(FbxNode* inNode);//GetTRSmat
private:
	//WICを使ってテクスチャをロードする
	void LoadTexture(
		const std::string& filepath,
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<FenceManager>& fence,
		std::shared_ptr<RootSignatureManager>& rootsignature,
		std::vector<std::shared_ptr<TextureManager>>& texms
	);
	//Animationデータを抽出する
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
	//パスから相対パスを作成する
	const std::string TexturePath(const std::string& filepath);
	//頂点情報を取得: uvが多いmeshに対応
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
	//meshを三角形化する
	void TriangulateRecursive(FbxNode* _pNode,FbxScene* scene);
	void InitializeSdkObjects();
protected:
	FBXLoader();
	virtual ~FBXLoader();

	/// <summary>
	/// 3Dモデルをロードする
	/// </summary>
	/// <param name="filepath"></param>
	/// <param name="device"></param>
	/// <param name="comand"></param>
	/// <param name="fence"></param>
	/// <param name="rootsignature"></param>
	/// <param name="animationF">Animationするかどうか true: する　false:　しない</param>
	void Load(
		const std::string& filepath,
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<FenceManager>& fence,
		std::shared_ptr<RootSignatureManager>& rootsignature,
		bool animationF
	);
	/// <summary>
	/// 頂点リソースを返す
	/// </summary>
	/// <returns></returns>
	std::vector<VertexBufferInfo>&  GetVertexResoce();
	/// <summary>
	/// 頂点インデックスを返す
	/// </summary>
	/// <returns></returns>
	std::vector<std::vector<IndexBufferInfo>>& GetVertexIndexData();
	/// <summary>
	/// マテリアルテーブルを返す
	/// </summary>
	/// <returns></returns>
	std::vector<std::vector<FBX_MATERIAL>>& GetMaterialTable();
	/// <summary>
	/// テクスチャテーブルを返す
	/// </summary>
	/// <returns></returns>
	std::map<std::string, std::vector<std::shared_ptr<TextureManager>>>& GetTextureData();
	/// <summary>
	/// リアルタイムAnimationループ
	/// </summary>
	void Animation(const std::string& animname, const int frame);
	/// <summary>
	/// Animation用Joint行列を返す
	/// </summary>
	/// <returns></returns>
	std::vector<BONE>& GetPaletteBone();
	/// <summary>
	/// AnimationEndPosを返す
	/// </summary>
	/// <param name="animname">再生したいAnimationの名前</param>
	/// <returns></returns>
	int GetAnimationFrameEnd(const std::string& animname);
private:
	FbxManager*		_fbxManager;
	FbxScene*		_fbxScene;
	FbxImporter*    _fbxImporter;
	std::map<std::string,std::vector<std::shared_ptr<TextureManager>>> _textures;//マテリアルに紐づけされているTexture
	std::string _fbxfilepath;
	std::vector<VertexBufferInfo>				_vertexbuffers;
	std::vector<std::vector<VERTEX>>			_vertexData_mesh;	//剛体対応用に2次元
	std::vector<std::vector<IndexBufferInfo>>	_indexbuffers;
	std::vector<std::vector<FBX_MATERIAL>>		_material;
	std::vector<BONE>							_boneArray;//jointidxで利用される行列の配列
	bool _meshuvF;
	//Animaton
	fbxsdk::FbxTime start;
	fbxsdk::FbxTime stop;
	fbxsdk::FbxTime FrameTime;
	fbxsdk::FbxTime timeCount;
	std::map<std::string, AnimationFrameInfo> _frameList;

private:
	bool _traiangleCoolF;//モデルが三角形メッシュで構成されているか  true:されている false:されていない
};
