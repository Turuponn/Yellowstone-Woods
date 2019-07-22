#include "ImguiManager.h"
#include "DirectXManagers\Device\D3D12DeviceManager.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include "d3dx12.h"
#include <Windows.h>
#include "Graphics\Graphics.h"
#include "imgui.h"
#include "imguiManager\imgui\imgui_impl_win32.h"
#include "imguiManager\imgui\imgui_impl_dx12.h"
#include "DirectXManagers\Texture\TextureManager.h"
#include "DirectXManagers\comand\ComandManager.h"
#include "WindowInit.h"


ImguiManager::ImguiManager() {
	_heapeIncrementSize = 0;
	_lightintensitynum = nullptr;
	_lightdirpos = nullptr;
}
ImguiManager::~ImguiManager() {
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}


bool ImguiManager::Initialize(std::shared_ptr<D3D12DeviceManager>& device,std::shared_ptr<Graphics>& graphics,HWND& windowhwnd) {

	//imgui　バインディング
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;


	ImGui_ImplWin32_Init(windowhwnd);
	
	std::shared_ptr<TextureManager> guitex(new TextureManager());
	_guitex = guitex;
	_guitex->SRVCreateHeap(device);
	if (ImGui_ImplDX12_Init(
		device->GetDevice().Get(),
		1,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		_guitex->GetSrvHeap()->GetCPUDescriptorHandleForHeapStart(),
		_guitex->GetSrvHeap()->GetGPUDescriptorHandleForHeapStart()) != true) {
		throw(1);
	}






	//スタイル
	ImGui::StyleColorsDark();


	return true;
}
bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);//test
void ImguiManager::DrawimGui(std::shared_ptr<ComandManager>& comand) {
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//TODO:　このあたりはすべて使用者側に限定したい

	//big demo window
	if (show_demo_window) {
		ImGui::ShowDemoWindow(&show_demo_window);
	}


	
	static int counter = 0;

	ImGui::Begin("CreateDebugWindow");                         
	ImGui::Text("デバッグウィンドウテキスト日本語てすと！");
	//ウィンドウのレイアウト
	ImGui::Checkbox("Demo Window", &show_demo_window);     
	ImGui::Checkbox("Another Window", &show_another_window);
	
	ShowGuiLightIntensity();
	ShowGuiLightDirectionalLightDir();
	ShowCubeMapMeshScale();


	ImGui::ColorEdit3("clear color", (float*)&clear_color);

	if (ImGui::Button("Button")) {//押されたら
		counter++;
	}
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}


	_guitex->DrawSrv(comand);

	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), comand->GetGraphicsCommandList().Get());

}
///=====================================================
/// ShowGui
///=====================================================
void ImguiManager::ShowGuiLightIntensity() {
	//ライト強弱の項目
	if (_lightintensitynum != nullptr) {
		ImGui::SliderFloat("Light intensity", _lightintensitynum, 0.0f, 10.0f);
	}
}
void ImguiManager::ShowGuiLightDirectionalLightDir() {
	//平行光源の座標の項目
	if (_lightdirpos != nullptr) {
		ImGui::Text("Directional Light");
		ImGui::SliderFloat("x", &_lightdirpos->x, -1.0f, 1.0f);
		ImGui::SliderFloat("y", &_lightdirpos->y, -1.0f, 1.0f);
		ImGui::SliderFloat("z", &_lightdirpos->z, -1.0f, 1.0f);
	}
}
void ImguiManager::ResetimGuiCheck() {
	if (WindowInit::USE().GetimGuiResetF()) {
		WindowInit::USE().SetimGuiResetF(false);
		ImGui_ImplDX12_InvalidateDeviceObjects();
	}
}
void ImguiManager::ShowCubeMapMeshScale() {
	if (_cubemapscale != nullptr) {
		ImGui::Text("CubeMapScale");
		ImGui::SliderFloat("scale_x", &_cubemapscale->x, 0.0f, 10000.0f);
		ImGui::SliderFloat("scale_y", &_cubemapscale->y, 0.0f, 10000.0f);
		ImGui::SliderFloat("scale_z", &_cubemapscale->z, 0.0f, 10000.0f);
	}
}
void ImguiManager::ShowAddMeshScale(Vector3* newscale,std::string& text, std::string& label_x, std::string& label_y, std::string& label_z,float maxsize) {
		ImGui::Text(text.c_str());
		ImGui::SliderFloat(label_x.c_str(), &newscale->x, -maxsize, maxsize);
		ImGui::SliderFloat(label_y.c_str(), &newscale->y, -maxsize, maxsize);
		ImGui::SliderFloat(label_z.c_str(), &newscale->z, -maxsize, maxsize);
}





//ユーザー側バージョン
void ImguiManager::PreGui(std::shared_ptr<ComandManager>& comand) {
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//必要な処理
	//big demo window
	if (show_demo_window) {
		ImGui::ShowDemoWindow(&show_demo_window);
	}
	ImGui::Begin("CreateDebugWindow");
	//ウィンドウのレイアウト
	ImGui::Checkbox("Demo Window", &show_demo_window);
	ImGui::Checkbox("Another Window", &show_another_window);
	//FPS
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	

}
void ImguiManager::PostGui(std::shared_ptr<ComandManager>& comand) {
	ImGui::End();

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}


	_guitex->DrawSrv(comand);

	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), comand->GetGraphicsCommandList().Get());
}

void ImguiManager::ShowAddMeshVector3(Vector3& newparam, std::string& text, std::string& label_x, std::string& label_y, std::string& label_z, float maxsize,float minsize) {
		ImGui::Text(text.c_str());
		ImGui::SliderFloat(label_x.c_str(), &newparam.x, minsize, maxsize);
		ImGui::SliderFloat(label_y.c_str(), &newparam.y, minsize, maxsize);
		ImGui::SliderFloat(label_z.c_str(), &newparam.z, minsize, maxsize);
}
void ImguiManager::ShowAddMeshVector4(Vector4& newparam, std::string& text, std::string& label_x, std::string& label_y, std::string& label_z, std::string& label_w, float maxsize, float minsize) {
	ImGui::Text(text.c_str());
	ImGui::SliderFloat(label_x.c_str(), &newparam.x, minsize, maxsize);
	ImGui::SliderFloat(label_y.c_str(), &newparam.y, minsize, maxsize);
	ImGui::SliderFloat(label_z.c_str(), &newparam.z, minsize, maxsize);
	ImGui::SliderFloat(label_w.c_str(), &newparam.w, minsize, maxsize);
}
void ImguiManager::ShowAddMeshFloat(float& newparam, std::string& text, std::string& label, float maxsize, float minsize) {
	ImGui::Text(text.c_str());
	ImGui::SliderFloat(label.c_str(), &newparam, minsize, maxsize);
}
void ImguiManager::ShowAddMeshInt(int& newparam, std::string& text, std::string& label, int maxsize, int minsize) {
	ImGui::Text(text.c_str());
	ImGui::SliderInt(label.c_str(),&newparam, maxsize, minsize);
}
///==========================================
/// Acsess
///==========================================
void ImguiManager::AdditemLightIntensity(float& lightintensitynum){
	_lightintensitynum = &lightintensitynum;
}

void ImguiManager::AdditemDirLightPos(Vector3& dirpos) {
	_lightdirpos = &dirpos;
}
void ImguiManager::CubeMapMeshScale(Vector3& newscale) {
	_cubemapscale = &newscale;
}