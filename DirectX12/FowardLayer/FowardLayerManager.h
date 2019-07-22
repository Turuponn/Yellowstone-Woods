#pragma once

#include <string>
#include <vector>
#include <memory>

struct D3D12_INPUT_ELEMENT_DESC;
class Layer;
class D3D12DeviceManager;
class RootSignatureManager;
class ComandManager;
class Camera;
class FenceManager;

class FowardLayerManager {
public:
	FowardLayerManager();
	~FowardLayerManager();

	void CreateLayer(std::shared_ptr<D3D12DeviceManager>& device, std::shared_ptr<RootSignatureManager>& rootsignature);
	void Draw(
		std::shared_ptr<D3D12DeviceManager>& device,
		std::shared_ptr<ComandManager>& comand,
		std::shared_ptr<Camera>& camera,
		std::shared_ptr<FenceManager>& fence
	);
private:
	std::shared_ptr<Layer> _layer;
};