#include <Windows.h>
#undef GetCurrentTime
#include <winrt/Microsoft.UI.Xaml.h>
#include <MddBootstrap.h>
#include <WindowsAppSDK-VersionInfo.h>

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace ::Microsoft::WindowsAppSDK;

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
	init_apartment(apartment_type::single_threaded);
	MddBootstrapInitialize2(
		Release::MajorMinor,
		Release::VersionTag,
		PACKAGE_VERSION{Runtime::Version::UInt64},
		MddBootstrapInitializeOptions_OnNoMatch_ShowUI);
	Application::Start([](auto&&) {
		Application();
		Window window;
		window.Activate();
	});
	MddBootstrapShutdown(); 
}