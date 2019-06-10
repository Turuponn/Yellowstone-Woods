#pragma once



#include <memory>
#include <vector>
#include <wrl.h>

struct ID3D12DescriptorHeap;
class D3D12DeviceManager;
struct ID3D12Resource;
class TextureManager;
class DepthManager;
class PipelineStateManager;
class RootSignatureManager;
class PixcelShadaManager;
class VertexShadaManager;
enum DXGI_FORMAT;
class ComandManager;
class RenderTargetManager;
class FenceManager;
class GSManager;
class Layer;
class Camera;

class PostProsessManager {
private:
	/// RT�̍쐬
	void CreateRT(std::shared_ptr<D3D12DeviceManager>& device);
	/// texture�̗p��
	void CreateSRV(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand);
	/// �p�C�v���C���̍쐬
	void CreatePipeline(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignature);
	void CreateGbuffer(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<RootSignatureManager>& rootsignature);
	/// �V�F�[�_�̍쐬
	void CreateVS();
	void CreatePS();
	void CreateGS();
	void Draw(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence);

public:
	PostProsessManager();
	virtual ~PostProsessManager();

	void Initialize(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<ComandManager>& comand, std::shared_ptr<RootSignatureManager>& rootsignature);


	/// <summary>
	/// �x�������_�����O
	/// </summary>
	void PreRender(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<RenderTargetManager>& rtvmanager,
		std::shared_ptr<DepthManager>& depth,
		std::shared_ptr< Camera>& camera,
		std::shared_ptr< FenceManager>& fence
	);
	void PostRender(std::shared_ptr<ComandManager>& comand, std::shared_ptr<FenceManager>& fence);
	/// <summary>
	/// �ʏ�`��p�p�C�v���C���֕ύX
	/// </summary>
	/// <param name="comand"></param>
	void SetDrawPipeline(std::shared_ptr<ComandManager>& comand);

private:
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> _rtvbuffer;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _rtvheap;
	std::vector<std::shared_ptr<TextureManager>> _texMs;
	std::vector<DXGI_FORMAT> _rtvformats;//�����_�[�^�[�Q�b�g�̃t�H�[�}�b�g


	std::shared_ptr<Layer> _layer;
	std::shared_ptr<PipelineStateManager> _mrtPipeline;//MRT�p�p�C�v���C��
	std::shared_ptr<VertexShadaManager> _vs;
	std::shared_ptr<PixcelShadaManager> _ps;
	std::shared_ptr<GSManager> _gs;

};