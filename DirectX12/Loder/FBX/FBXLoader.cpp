#include "FBXLoader.h"
#include <d3d12.h>
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include "DirectXManagers\Texture\TextureManager.h"
#include "DirectXManagers\vertex\VertexBufferManager.h"
#include "DirectXManagers\index\IndexBufferManager.h"
#include "DirectXManagers\comand\ComandManager.h"
#include "DirectXManagers\Fence\FenceManager.h"
#include "DirectXManagers\rootsignature\RootSignatureManager.h"
#include <tchar.h>
#include "constance.h"

using namespace std;
using namespace DirectX;
using namespace fbxsdk;

#define NOT_ANIMATION 1




FBXLoader::FBXLoader() {
	_fbxManager = nullptr;
	_fbxScene = nullptr;
	_fbxImporter = nullptr;
	_traiangleCoolF = false;
	_meshuvF = true;
	start = 0;
	stop = 0;
	FrameTime =0;
	timeCount = 0;
}
FBXLoader::~FBXLoader() {
	if (_fbxImporter)
	{
		_fbxImporter->Destroy();
		_fbxImporter = nullptr;
	}

	if (_fbxScene)
	{
		_fbxScene->Destroy();
		_fbxScene = nullptr;
	}

	if (_fbxManager)
	{
		_fbxManager->Destroy();
		_fbxManager = nullptr;
	}
}


XMMATRIX FBXLoader::ToXm(const FbxAMatrix& pSrc)
{
	return XMMatrixSet(
		static_cast<FLOAT>(pSrc.Get(0, 0)), static_cast<FLOAT>(pSrc.Get(0, 1)), static_cast<FLOAT>(pSrc.Get(0, 2)), static_cast<FLOAT>(pSrc.Get(0, 3)),
		static_cast<FLOAT>(pSrc.Get(1, 0)), static_cast<FLOAT>(pSrc.Get(1, 1)), static_cast<FLOAT>(pSrc.Get(1, 2)), static_cast<FLOAT>(pSrc.Get(1, 3)),
		static_cast<FLOAT>(pSrc.Get(2, 0)), static_cast<FLOAT>(pSrc.Get(2, 1)), static_cast<FLOAT>(pSrc.Get(2, 2)), static_cast<FLOAT>(pSrc.Get(2, 3)),
		static_cast<FLOAT>(pSrc.Get(3, 0)), static_cast<FLOAT>(pSrc.Get(3, 1)), static_cast<FLOAT>(pSrc.Get(3, 2)), static_cast<FLOAT>(pSrc.Get(3, 3)));
}
XMMATRIX FBXLoader::ExtractOffset(const XMMATRIX& mWorld) {
	return XMMatrixTranslation(mWorld.r[3].m128_f32[0], mWorld.r[3].m128_f32[1], mWorld.r[3].m128_f32[2]);
}
XMMATRIX FBXLoader::ExtractScaling(const XMMATRIX& mWorld) {
	return XMMatrixScaling(
		XMVector3Length(XMVECTOR{ mWorld.r[0].m128_f32[0],mWorld.r[0].m128_f32[1],mWorld.r[0].m128_f32[2] }).m128_f32[0],
		XMVector3Length(XMVECTOR{ mWorld.r[1].m128_f32[0],mWorld.r[1].m128_f32[1],mWorld.r[1].m128_f32[2] }).m128_f32[0],
		XMVector3Length(XMVECTOR{ mWorld.r[2].m128_f32[0],mWorld.r[2].m128_f32[1],mWorld.r[2].m128_f32[2] }).m128_f32[0]
	);
}
// ワールド行列から回転成分のみを抽出する
XMMATRIX FBXLoader::ExtractRotation(const XMMATRIX&  mWorld) {
	XMMATRIX mOffset = ExtractOffset(mWorld);
	XMMATRIX mScaling = ExtractScaling(mWorld);
	XMVECTOR det;
	// 左からScaling、右からOffsetの逆行列をそれぞれかける。
	return XMMatrixInverse(&det, mScaling) * mWorld * XMMatrixInverse(&det, mOffset);
}
FbxMatrix FBXLoader::ToFBXXm(DirectX::XMMATRIX& pSrc)
{	
	const double m00 = pSrc.r[0].m128_f32[0];
	const double m01 = pSrc.r[0].m128_f32[1];
	const double m02 = pSrc.r[0].m128_f32[2];
	const double m03 = pSrc.r[0].m128_f32[3];
	const double m10 = pSrc.r[1].m128_f32[0];
	const double m11 = pSrc.r[1].m128_f32[1];
	const double m12 = pSrc.r[1].m128_f32[2];
	const double m13 = pSrc.r[1].m128_f32[3];
	const double m20 = pSrc.r[2].m128_f32[0];
	const double m21 = pSrc.r[2].m128_f32[1];
	const double m22 = pSrc.r[2].m128_f32[2];
	const double m23 = pSrc.r[2].m128_f32[3];
	const double m30 = pSrc.r[3].m128_f32[0];
	const double m31 = pSrc.r[3].m128_f32[1];
	const double m32 = pSrc.r[3].m128_f32[2];
	const double m33 = pSrc.r[3].m128_f32[3];
		
	auto Amat = FbxMatrix(
	m00,
	m10,
	m20,
	m30,
	m01,
	m11,
	m21,
	m31,
	m02,
	m12,
	m22,
	m32,
	m03,
	m13,
	m23,
	m33
	);
	return Amat;
}
FbxAMatrix FBXLoader::GetGeometryTransformation(FbxNode* inNode)
{
	if (!(inNode)) { throw (1); }
	const FbxVector4 lT = inNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	const FbxVector4 lR = inNode->GetGeometricRotation(FbxNode::eSourcePivot);
	const FbxVector4 lS = inNode->GetGeometricScaling(FbxNode::eSourcePivot);
	return FbxAMatrix(lT, lR, lS);
}

void FBXLoader::TriangulateRecursive(FbxNode* _pNode, FbxScene* scene)
{
	FbxNodeAttribute* pNodeAttribute = _pNode->GetNodeAttribute();
	if (pNodeAttribute)
	{
		FbxNodeAttribute::EType type = pNodeAttribute->GetAttributeType();
		if (type == FbxNodeAttribute::eMesh ||
			type == FbxNodeAttribute::eNurbs ||
			type == FbxNodeAttribute::eNurbsSurface ||
			type == FbxNodeAttribute::ePatch)
		{
			FbxGeometryConverter lConverter(_pNode->GetFbxManager());
			if (_traiangleCoolF == false) {
				//printf("FBX: モデルが三角形化メッシュになっていないのでロードが遅くなります。\n");
				_traiangleCoolF = true;
			}
			lConverter.Triangulate(scene, true);
		}
	}
	const int lChildCount = _pNode->GetChildCount();
	for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
	{
		TriangulateRecursive(_pNode->GetChild(lChildIndex), scene);
	}
}

void FBXLoader::InitializeSdkObjects(){
	_fbxManager = FbxManager::Create();
	if (!_fbxManager)
	{
		throw(1);
	}
	FbxIOSettings* pIOS = FbxIOSettings::Create(_fbxManager, IOSROOT);
	_fbxManager->SetIOSettings(pIOS);
	FbxString lPath = FbxGetApplicationDirectory();
	_fbxManager->LoadPluginsDirectory(lPath.Buffer());
	_fbxScene = FbxScene::Create(_fbxManager, "Scene");
	if (!_fbxScene)
	{
		throw(1);
	}
}
void FBXLoader::Load(
	const std::string& filepath,
	std::shared_ptr<D3D12DeviceManager>& device,
	std::shared_ptr<ComandManager>& comand,
	std::shared_ptr<FenceManager>& fence,
	std::shared_ptr<RootSignatureManager>& rootsignature,
	bool animationF
){	
	_fbxfilepath = filepath;
	printf("\n");
	int sFileFormat = -1;
	InitializeSdkObjects();
	_fbxImporter = FbxImporter::Create(_fbxManager, "Importer");
	if (!_fbxImporter)
	{
		throw(1);
	}
	if (!_fbxManager->GetIOPluginRegistry()->DetectReaderFileFormat(filepath.c_str(), sFileFormat))
	{
		sFileFormat = _fbxManager->GetIOPluginRegistry()->FindReaderIDByDescription("FBX binary (*.fbx)");
	}
	if (!_fbxImporter->Initialize(filepath.c_str(), sFileFormat))
	{
		throw(1);
	}
	if (!_fbxImporter->Import(_fbxScene))
	{
		throw(1);
	}
	FbxAxisSystem OurAxisSystem = FbxAxisSystem::DirectX;
	FbxAxisSystem SceneAxisSystem = _fbxScene->GetGlobalSettings().GetAxisSystem();
	if (SceneAxisSystem != OurAxisSystem)
	{
		FbxAxisSystem::DirectX.ConvertScene(_fbxScene);
	}
	FbxSystemUnit SceneSystemUnit = _fbxScene->GetGlobalSettings().GetSystemUnit();
	if (SceneSystemUnit.GetScaleFactor() != 1.0f)
	{
		FbxSystemUnit::cm.ConvertScene(_fbxScene);
	}
	TriangulateRecursive(_fbxScene->GetRootNode(), _fbxScene);//三角形化させる必要があるのでmeshを三角形化します。
	LoadVertexData(device,comand,fence,rootsignature, animationF);
	if (_meshuvF != true) {
		printf("\n");
		printf("Warning!: %s  not attach  uv。UV展開を行ってください", filepath.c_str());
	}
}

void FBXLoader::LoadVertexData(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence, std::shared_ptr<RootSignatureManager>& rootsignature, bool animationF) {
	std::vector<VERTEX> vertices;
	//ルートノードからmeshを検索
	for (int i = 0; i < _fbxScene->GetRootNode()->GetChildCount(); i++) {
		if (_fbxScene->GetRootNode()->GetChild(i)->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh) {


			
			std::vector<VERTEX> v;
			auto mesh = _fbxScene->GetRootNode()->GetChild(i)->GetMesh();
			VertexDataImport(mesh, v, animationF);
			
			vertices.resize(mesh->GetControlPointsCount());
			for (int i = 0; i < mesh->GetControlPointsCount(); i++) {
				vertices[i].pos.x = (FLOAT)mesh->GetControlPointAt(i)[0];
				vertices[i].pos.y = (FLOAT)mesh->GetControlPointAt(i)[1];
				vertices[i].pos.z = (FLOAT)mesh->GetControlPointAt(i)[2];
			}

			if (v.size() <= 0) {
				return;
			}
			MaterialData(mesh, device, v, comand, fence, rootsignature);
			_vertexData_mesh.push_back(v);// 剛体は無視する
			
			//Animation 用Dataの抽出
			LoadSkinAnim(_fbxScene->GetRootNode()->GetChild(i), _fbxScene);		
		}
	}
	CreateVertexBuffer(_vertexData_mesh[0].size(), device, fence, comand);
}
void FBXLoader::LoadTexture(const std::string& filepath, std::shared_ptr<D3D12DeviceManager>& device,std::shared_ptr<ComandManager>& comand,std::shared_ptr<FenceManager>& fence,std::shared_ptr<RootSignatureManager>& rootsignature, std::vector<std::shared_ptr<TextureManager>>& texms) {
	std::shared_ptr<TextureManager> texmanager(new TextureManager());
	texmanager->WICLoadTexture(device,comand, filepath);
	texms.push_back(texmanager);
}
const std::string FBXLoader::TexturePath(const std::string& filepath) {
	std::string workpath = filepath;
	auto lastpath = filepath.substr(0, filepath.find_last_of('\\') + 1);
	workpath.erase(0, lastpath.size());
	auto lastpathfbx = _fbxfilepath.substr(0, _fbxfilepath.find_last_of('/') + 1);//指定文字までの文字列を返す
	if (lastpathfbx.size() < 1) {
		printf("fbx指定ファイルパスが無効\n");
		throw(1);
	}
	workpath = lastpathfbx + workpath;
	printf("LoadTexture: %s\n", workpath.c_str());
	return workpath;
}

void FBXLoader::LoadSkinAnim(FbxNode* node, FbxScene* scene) {


	FbxSkin* skinDeformer = nullptr;
	skinDeformer = (FbxSkin *)node->GetMesh()->GetDeformer(0, FbxDeformer::eSkin);
	if (skinDeformer == nullptr) {
		printf("FBX:  Not Animation \n");
		return;
	}
	if (node->GetMesh() == nullptr) {
		return;
	}
	//アニメーション名のリスト取得
	FbxArray<FbxString*> animArray;
	node->GetScene()->FillAnimStackNameArray(animArray);
	for (int i = 0; i < animArray.GetCount(); i++) {
		std::string animname = animArray[i]->Buffer();
		std::string workanimname = animname;
		printf("Animation :%s\n", animname.c_str());
		auto s = animname.substr(0, animname.find_last_of('|') + 1);//アニメーション名を簡単にします
		workanimname.erase(0, s.size());

		FbxTakeInfo *takeInfo = scene->GetTakeInfo(animname.c_str());
		start = takeInfo->mLocalTimeSpan.GetStart();//ついでにAnimation用Timeを抽出
		stop = takeInfo->mLocalTimeSpan.GetStop();
		FrameTime.SetTime(0, 0, 0, 1, 0, scene->GetGlobalSettings().GetTimeMode());//timeはframeに設定
		timeCount = start;
		//フレーム数取得
		int startFrame = (int)(start.Get() / FrameTime.Get());
		int endFrame = (int)(stop.Get() / FrameTime.Get());
		//フレームリストの作成
		std::vector<fbxsdk::FbxTime> frameList;
		frameList.resize(endFrame);
		for (int j = 0; j < endFrame; j++) {
			timeCount += FrameTime;
			frameList[j] = timeCount;
		}
		AnimationFrameInfo ainfo = {};
		ainfo.frameList = frameList;
		ainfo.startFrame = startFrame;
		ainfo.endFrame = endFrame;
		ainfo.search_animname = s;
		_frameList.insert(std::make_pair(workanimname, ainfo));

	}
	//wheightとjointindexの取得
	auto mesh = node->GetMesh();
	auto pcount = mesh->GetControlPointsCount();
	auto bonenum = skinDeformer->GetClusterCount();
	std::vector<FbxCluster*> ppCluster;
	for (int i = 0; i < bonenum; i++)
	{
		ppCluster.push_back(skinDeformer->GetCluster(i));
	}

	//UV数の多いモデル(頂点カラーを使用している場合)では普通の頂点数とUV数で作成した場合、うまく表示できませんでした。
	//おかしいため、頂点カラーを含めないモデルローダーの開発を行っています。
	//参考: ・23 FBX SkinMesh D3d11  DirectX10/11プログラミング (ネイティブDirectX10/11の入門から応用まで)
	std::vector<POLY_TABLE> PolyTable;//1頂点->3頂点へ
	PolyTable.resize(pcount);

	for (int i = 0; i < pcount; i++)
	{
		for (int k = 0; k < mesh->GetPolygonCount(); k++)
		{
			for (int m = 0; m < 3; m++)
			{
				if (mesh->GetPolygonVertex(k, m) == i)
				{
					PolyTable[i].PolyIndex[PolyTable[i].NumRef] = k;
					PolyTable[i].Index123[PolyTable[i].NumRef] = m;
					PolyTable[i].NumRef++;
				}
			}
		}
	}
	//全体の頂点情報に情報を格納する
	int skinCount = mesh->GetDeformerCount(FbxDeformer::eSkin);//メッシュにボーンが割り当てられているか
	for (int i = 0; i < skinCount; ++i) {
		FbxSkin* skin = (FbxSkin*)mesh->GetDeformer(i, FbxDeformer::eSkin);
		int PolyIndex = 0;
		int UVIndex = 0;
		for (int j = 0; j < skin->GetClusterCount(); j++)
		{
			int iNumIndex = ppCluster[j]->GetControlPointIndicesCount();
			int* piIndex = ppCluster[j]->GetControlPointIndices();
			double* pdWeight = ppCluster[j]->GetControlPointWeights();
			for (int k = 0; k < iNumIndex; k++)
			{
				for (int p = 0; p < PolyTable[piIndex[k]].NumRef; p++)
				{
					PolyIndex = PolyTable[piIndex[k]].PolyIndex[p];
					UVIndex = mesh->GetTextureUVIndex(PolyIndex, PolyTable[piIndex[k]].Index123[p], FbxLayerElement::eTextureDiffuse);

					for (int m = 0; m < 4; m++)
					{
						if (pdWeight[k] > _vertexData_mesh[0][UVIndex].bwheight[m])
						{
							_vertexData_mesh[0][UVIndex].bjointidx[m] = j;
							_vertexData_mesh[0][UVIndex].bwheight[m] = static_cast<float>(pdWeight[k]);
							break;
						}
					}
				}
			}
		}
	}

	

	//アニメーション参考: TKING45MEMO
	//行列を初期化します。：　AnimationStackは0番目をデフォルトにします。
	int timeCount = 0;
	FbxAMatrix globalFramepos = node->EvaluateGlobalTransform(timeCount);
	FbxAMatrix nodeTRSmat = GetGeometryTransformation(node);//TRS行列の作成
	FbxSkin* skinD = (FbxSkin*)mesh->GetDeformer(0, FbxDeformer::eSkin);
	int clusterCount = skinD->GetClusterCount();
	_boneArray.resize(clusterCount);
	//ボーンごとに行列作成
	for (int cidx = 0; cidx < clusterCount; cidx++) {
		_boneArray[cidx].bindPose = DirectX::XMMatrixIdentity();
		// クラスタ(ボーン)の取り出し
		FbxCluster* c = skinD->GetCluster(cidx);
		FbxAMatrix clusterTRS;
		FbxAMatrix localpos;
		c->GetTransformMatrix(clusterTRS);
		clusterTRS *= nodeTRSmat;
		c->GetTransformLinkMatrix(localpos);//クラスターのローカル座標
		auto framepos = c->GetLink()->EvaluateGlobalTransform(timeCount);
		auto cRInitPos = localpos.Inverse() * clusterTRS;//
		auto newpos = globalFramepos.Inverse() * framepos;
		auto bindpose = newpos * cRInitPos;//inverseで原点に戻し、フレーム時姿勢行列をかけていきます
		_boneArray[cidx].bindPose = ToXm(bindpose);
	}
}


void FBXLoader::MaterialData(FbxMesh*& meshdata, std::shared_ptr<D3D12DeviceManager>& device, std::vector<VERTEX>& vertexdata, std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence, std::shared_ptr<RootSignatureManager>& rootsignature) {

	FbxNode* pNode = meshdata->GetNode();
	std::vector<FBX_MATERIAL> material;
	std::vector<IndexBufferInfo> indexbuffers;
	int facenum = meshdata->GetPolygonCount();
	int materialnum = pNode->GetMaterialCount();
	if (materialnum <= 0) {
		printf("not mesh Attach material\n");
		return;
	}
	material.resize(materialnum);
	indexbuffers.resize(materialnum);
	for (int i = 0; i < materialnum; i++)
	{
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);
		FbxSurfacePhong* pPhong = (FbxSurfacePhong*)pMaterial;
		material[i].matname = pMaterial->GetName();
		material[i].ambient.x = static_cast<float>(pPhong->Ambient.Get()[0]);
		material[i].ambient.y = static_cast<float>(pPhong->Ambient.Get()[1]);
		material[i].ambient.z = static_cast<float>(pPhong->Ambient.Get()[2]);
		material[i].diffuse.x = static_cast<float>(pPhong->Diffuse.Get()[0]);
		material[i].diffuse.y = static_cast<float>(pPhong->Diffuse.Get()[1]);
		material[i].diffuse.z = static_cast<float>(pPhong->Diffuse.Get()[2]);
		material[i].specular.x = static_cast<float>(pPhong->Specular.Get()[0]);
		material[i].specular.y = static_cast<float>(pPhong->Specular.Get()[1]);
		material[i].specular.z = static_cast<float>(pPhong->Specular.Get()[2]);
		auto lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
		std::vector<std::shared_ptr<TextureManager>> texs;
		std::string rerativpath = "nottexture";
		int layeredTextureCount = lProperty.GetSrcObjectCount();
		if (layeredTextureCount > 1) {
			for (int k = 0; layeredTextureCount > k; k++) {
				FbxFileTexture* texture = lProperty.GetSrcObject<FbxFileTexture>(k);
				if (texture) {
					std::string texfilepath = texture->GetRelativeFileName();
					rerativpath = TexturePath(texfilepath);
					LoadTexture(rerativpath, device, comand, fence, rootsignature, texs);
					texs.push_back(nullptr);
					material[i].textureName = rerativpath;
				}
			}
			continue;
		}
		int fileTextureCount = lProperty.GetSrcObjectCount<FbxFileTexture>();
		if (fileTextureCount > 0) {
			for (int j = 0; fileTextureCount > j; j++) {
				FbxFileTexture* texture = lProperty.GetSrcObject<FbxFileTexture>(j);
				if (texture) {
					std::string texfilepath = texture->GetRelativeFileName();
					rerativpath = TexturePath(texfilepath);
					LoadTexture(rerativpath, device, comand, fence, rootsignature, texs);
					material[i].textureName = rerativpath;
				}
			}
		}
		_textures.insert(std::make_pair(rerativpath, texs));

		CreateIndexBuffer(meshdata, device, i, vertexdata, material, indexbuffers);
	}
	_material.push_back(material);
	_indexbuffers.push_back(indexbuffers);
}

void FBXLoader::CreateVertexBuffer(size_t meshsize, std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<FenceManager>& fence, std::shared_ptr<ComandManager>& comand) {	
	std::shared_ptr<VertexBufferManager> v(new VertexBufferManager());
			VERTEX* vAddress = nullptr;
			v->CreateVertexBuffer(device, (int)(sizeof(VERTEX) * meshsize), sizeof(VERTEX));
			v->ResoceMap(&vAddress);
			DISABLE_C4996
				std::copy(
					_vertexData_mesh[0].begin(),
					_vertexData_mesh[0].end(),
					vAddress
				);
			ENABLE_C4996
				v->ResoceUnmap();

			VertexBufferInfo vinfo;
			vinfo.vertexmanager = v;
			vinfo.vertexAddress = vAddress;
			_vertexbuffers.push_back(vinfo);		
}
void FBXLoader::VertexDataImport(FbxMesh*& meshdata, std::vector<VERTEX>& vertexdata, bool animationF) {
	auto pcount = meshdata->GetControlPointsCount();
	auto uvnum = meshdata->GetTextureUVCount();
	pcount < uvnum ? vertexdata.resize(uvnum) : vertexdata.resize(pcount);//522 < 1387
	FbxVector4 Normal = {};
	for (int i = 0; i < meshdata->GetPolygonCount(); i++)
	{
		int iIndex0 = 0;
		int iIndex1 = 0;
		int iIndex2 = 0;
		int iStartIndex = meshdata->GetPolygonVertexIndex(i);
		int* piIndex = meshdata->GetPolygonVertices();
		iIndex0 = piIndex[iStartIndex];
		iIndex1 = piIndex[iStartIndex + 1];
		iIndex2 = piIndex[iStartIndex + 2];
		if (pcount < uvnum)
		{
			iIndex0 = meshdata->GetTextureUVIndex(i, 0, FbxLayerElement::eTextureDiffuse);
			iIndex1 = meshdata->GetTextureUVIndex(i, 1, FbxLayerElement::eTextureDiffuse);
			iIndex2 = meshdata->GetTextureUVIndex(i, 2, FbxLayerElement::eTextureDiffuse);
		}
		
		//頂点
		int index = meshdata->GetPolygonVertex(i, 0);
		vertexdata[iIndex0].pos.x = -static_cast<float>(meshdata->GetControlPointAt(index)[0]);//FBXは右手座標系なのでxあるいはｚを反転
		vertexdata[iIndex0].pos.y = static_cast<float>(meshdata->GetControlPointAt(index)[1]);
		vertexdata[iIndex0].pos.z = static_cast<float>(meshdata->GetControlPointAt(index)[2]);
		if (animationF == false) {//アニメーションを使用しない場合スキンアニメーションしない
			vertexdata[iIndex0].bwheight[0] = NOT_ANIMATION;
			vertexdata[iIndex0].bwheight[1] = NOT_ANIMATION;
			vertexdata[iIndex0].bwheight[2] = NOT_ANIMATION;
			vertexdata[iIndex0].bwheight[3] = NOT_ANIMATION;
		}
		else {
			vertexdata[iIndex0].bwheight[0] = 0;
			vertexdata[iIndex0].bwheight[1] = 0;
			vertexdata[iIndex0].bwheight[2] = 0;
			vertexdata[iIndex0].bwheight[3] = 0;
		}
		

		index = meshdata->GetPolygonVertex(i, 1);
		vertexdata[iIndex1].pos.x = -static_cast<float>(meshdata->GetControlPointAt(index)[0]);
		vertexdata[iIndex1].pos.y = static_cast<float>(meshdata->GetControlPointAt(index)[1]);
		vertexdata[iIndex1].pos.z = static_cast<float>(meshdata->GetControlPointAt(index)[2]);
		if (animationF == false) {
			vertexdata[iIndex1].bwheight[0] = NOT_ANIMATION;
			vertexdata[iIndex1].bwheight[1] = NOT_ANIMATION;
			vertexdata[iIndex1].bwheight[2] = NOT_ANIMATION;
			vertexdata[iIndex1].bwheight[3] = NOT_ANIMATION;
		}
		else {
			vertexdata[iIndex1].bwheight[0] = 0;
			vertexdata[iIndex1].bwheight[1] = 0;
			vertexdata[iIndex1].bwheight[2] = 0;
			vertexdata[iIndex1].bwheight[3] = 0;
		}

		index = meshdata->GetPolygonVertex(i, 2);
		vertexdata[iIndex2].pos.x = -static_cast<float>(meshdata->GetControlPointAt(index)[0]);
		vertexdata[iIndex2].pos.y = static_cast<float>(meshdata->GetControlPointAt(index)[1]);
		vertexdata[iIndex2].pos.z = static_cast<float>(meshdata->GetControlPointAt(index)[2]);
		if (animationF == false) {
			vertexdata[iIndex2].bwheight[0] = NOT_ANIMATION;
			vertexdata[iIndex2].bwheight[1] = NOT_ANIMATION;
			vertexdata[iIndex2].bwheight[2] = NOT_ANIMATION;
			vertexdata[iIndex2].bwheight[3] = NOT_ANIMATION;
		}
		else {
			vertexdata[iIndex2].bwheight[0] = 0;
			vertexdata[iIndex2].bwheight[1] = 0;
			vertexdata[iIndex2].bwheight[2] = 0;
			vertexdata[iIndex2].bwheight[3] = 0;
		}
		//法線		
		meshdata->GetPolygonVertexNormal(i, 0, Normal);
		vertexdata[iIndex0].normal.x = -static_cast<float>(Normal[0]);//FBXは右手座標系なのでxあるいはｚを反転
		vertexdata[iIndex0].normal.y = static_cast<float>(Normal[1]);
		vertexdata[iIndex0].normal.z = static_cast<float>(Normal[2]);


		meshdata->GetPolygonVertexNormal(i, 1, Normal);
		vertexdata[iIndex1].normal.x = -static_cast<float>(Normal[0]);
		vertexdata[iIndex1].normal.y = static_cast<float>(Normal[1]);
		vertexdata[iIndex1].normal.z = static_cast<float>(Normal[2]);

		meshdata->GetPolygonVertexNormal(i, 2, Normal);
		vertexdata[iIndex2].normal.x = -static_cast<float>(Normal[0]);
		vertexdata[iIndex2].normal.y = static_cast<float>(Normal[1]);
		vertexdata[iIndex2].normal.z = static_cast<float>(Normal[2]);
		//テクスチャー座標
		int UVindex = meshdata->GetTextureUVIndex(i, 0, FbxLayerElement::eTextureDiffuse);
		FbxLayerElementUV* pUV = 0;
		FbxLayerElementUV* uv = meshdata->GetLayer(0)->GetUVs();
		if (uvnum && uv->GetMappingMode() == FbxLayerElement::eByPolygonVertex)
		{
			UVindex = meshdata->GetTextureUVIndex(i, 0, FbxLayerElement::eTextureDiffuse);
			pUV = meshdata->GetLayer(0)->GetUVs();
			vertexdata[iIndex0].uv.x = static_cast<float>(pUV->GetDirectArray().GetAt(UVindex)[0]);
			vertexdata[iIndex0].uv.y = static_cast<float>(1.0f - pUV->GetDirectArray().GetAt(UVindex)[1]);
			UVindex = meshdata->GetTextureUVIndex(i, 1, FbxLayerElement::eTextureDiffuse);
			vertexdata[iIndex1].uv.x = static_cast<float>(pUV->GetDirectArray().GetAt(UVindex)[0]);
			vertexdata[iIndex1].uv.y = static_cast<float>(1.0f - pUV->GetDirectArray().GetAt(UVindex)[1]);
			UVindex = meshdata->GetTextureUVIndex(i, 2, FbxLayerElement::eTextureDiffuse);
			vertexdata[iIndex2].uv.x = static_cast<float>(pUV->GetDirectArray().GetAt(UVindex)[0]);
			vertexdata[iIndex2].uv.y = static_cast<float>(1.0f - pUV->GetDirectArray().GetAt(UVindex)[1]);
		}
	}


}

void FBXLoader::CreateIndexBuffer(
	FbxMesh*& meshdata,
	std::shared_ptr<D3D12DeviceManager>& device,
	int matIdx, 
	std::vector<VERTEX>& vertexdata, 
	std::vector<FBX_MATERIAL>& material,
	std::vector<IndexBufferInfo>& idxbuff
) {
	std::shared_ptr<IndexBufferManager> indexbuffe(new IndexBufferManager());
	int* address = nullptr;
	indexbuffe->CreateIndexBuffer(device, sizeof(int) * meshdata->GetPolygonVertexCount(), sizeof(int));
	indexbuffe->CreateBufferViewR32(sizeof(int) * meshdata->GetPolygonVertexCount(), sizeof(int));
	indexbuffe->ResoceMap(&address);
	//マテリアルの数だけインデックスバッファーを作成
	auto pcount = meshdata->GetControlPointsCount();
	auto uvnum = meshdata->GetTextureUVCount();
	auto facenum = meshdata->GetPolygonCount();
	int iCount = 0;

	std::vector<int> pIndex;
	pIndex.resize(facenum * 3);//メッシュ内のポリゴン数でメモリ確保
	
	//そのマテリアルであるインデックス配列内の開始インデックスを調べる　さらにインデックスの個数も調べる		
	for (int k = 0; k < facenum; k++)
	{
		FbxLayerElementMaterial* mat = meshdata->GetLayer(0)->GetMaterials();//レイヤーが1枚だけを想定
		int matId = mat->GetIndexArray().GetAt(k);
		if (matId == matIdx)
		{
			if (pcount < uvnum)
			{
				pIndex[iCount] = meshdata->GetTextureUVIndex(k, 0, FbxLayerElement::eTextureDiffuse);
				pIndex[iCount + 1] = meshdata->GetTextureUVIndex(k, 1, FbxLayerElement::eTextureDiffuse);
				pIndex[iCount + 2] = meshdata->GetTextureUVIndex(k, 2, FbxLayerElement::eTextureDiffuse);
			}
			else
			{
				pIndex[iCount] = meshdata->GetPolygonVertex(k, 0);
				pIndex[iCount + 1] = meshdata->GetPolygonVertex(k, 1);
				pIndex[iCount + 2] = meshdata->GetPolygonVertex(k, 2);
			}
			iCount += 3;
		}
	}
	material[matIdx].fecenum = iCount;
	std::copy(
		pIndex.begin(),
		pIndex.end(),
		address
	);
	indexbuffe->ResoceUnmap();
	idxbuff[matIdx].idxbuff = indexbuffe;
	idxbuff[matIdx].idxAddress = address;
}

void FBXLoader::Animation(const std::string& animname, const int frame) {
	//名前をキーにしてアニメーションリストを呼び出します
	auto sname = _frameList[animname].search_animname+ animname;
	auto t = _frameList[animname].frameList[frame];
	//複数Animationに対応させるため 動的にAnimationstackを切り替えます
	FbxAnimStack* animstack = _fbxScene->FindMember<FbxAnimStack>(sname.c_str());
	if (animstack == nullptr) { throw(1); }
	_fbxScene->SetCurrentAnimationStack(animstack);
	//Joint合成行列を作成します
	for (int i = 0; i < _fbxScene->GetRootNode()->GetChildCount(); i++) {
		if (_fbxScene->GetRootNode()->GetChild(i)->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh) {
			auto node = _fbxScene->GetRootNode()->GetChild(i);
			FbxAMatrix globalFramepos = node->EvaluateGlobalTransform(t);
			FbxAMatrix nodeTRSmat = GetGeometryTransformation(node);

			FbxSkin *skinD = (FbxSkin *)node->GetMesh()->GetDeformer(0, FbxDeformer::eSkin);
			int clusterCount = skinD->GetClusterCount();
			for (int cidx = 0; cidx < clusterCount; cidx++) {//クラスターごとにそれぞれ回転行列を掛けます
				FbxCluster* c = skinD->GetCluster(cidx);
				FbxAMatrix clusterTRS;
				FbxAMatrix localpos;
				c->GetTransformMatrix(clusterTRS);
				clusterTRS *= nodeTRSmat;
				c->GetTransformLinkMatrix(localpos);//クラスターのローカル座標
				auto framepos = c->GetLink()->EvaluateGlobalTransform(t);
				auto cRInitPos = localpos.Inverse() * clusterTRS;//
				auto newpos = globalFramepos.Inverse() * framepos;
				auto bindpose = newpos * cRInitPos;//inverseで原点に戻し、フレーム時姿勢行列をかけていきます
				_boneArray[cidx].bindPose = ToXm(bindpose);
			}
		}
	}
}
std::vector<BONE>& FBXLoader::GetPaletteBone() {
	return _boneArray;
}
std::vector<VertexBufferInfo>&  FBXLoader::GetVertexResoce() {
	return _vertexbuffers;
}
std::vector<std::vector<IndexBufferInfo>>& FBXLoader::GetVertexIndexData() {
	return _indexbuffers;
}
std::vector<std::vector<FBX_MATERIAL>>& FBXLoader::GetMaterialTable() {
	return _material;
}
std::map<std::string, std::vector<std::shared_ptr<TextureManager>>>& FBXLoader::GetTextureData() {
	return _textures;
}
int FBXLoader::GetAnimationFrameEnd(const std::string& animname) {
	return _frameList[animname].endFrame-1;
}