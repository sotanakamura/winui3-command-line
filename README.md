# Build C++ WinUI 3 Apps with Command Line Tools
This repository provides information about how to build C++ WinUI 3 apps with commnad line tools.

## Build a sample
You can build a sample app easily.

```
git clone https://github.com/sotanakamura/winui3-command-line.git
cd winui3-command-line
build
```

## Requirements
* Visual Studio
* Visual Studio Desktop development with C++ Workload
* Visual Studio Windows App SDK C++ Templates
* Windows App SDK Runtime
* NuGet CLI

## Install required tools with `winget`

1. Install Visual Studio and C++ components.

    ```
    winget install "Visual Studio Community 2022"  --override "--add Microsoft.VisualStudio.Workload.NativeDesktop  Microsoft.VisualStudio.ComponentGroup.WindowsAppSDK.Cpp" -s msstore
    ```

1. Install Windows App Runtime.

    ```
    winget install --id Microsoft.WindowsAppRuntime.1.2
    ```
    
1. Install NuGet CLI.

    ```
    winget install --id Microsoft.NuGet
    ```

## Build a WinUI 3 app

1. Open x64 Native Tools Command Prompt for VS 2022 and then create a project folder

    ```
    mkdir project
    cd project
    ```

1. Install nuget packages with nuget.exe to support C++/WinRT and Windows App SDK.

    ```
    nuget install Microsoft.Windows.CppWinRT -OutputDirectory packages
    nuget install Microsoft.WindowsAppSDK -OutputDirectory packages 
    ```

1. Generate C++ projection header files with cppwinrt.exe.

    ```
    packages\Microsoft.Windows.CppWinRT.2.0.230225.1\bin\cppwinrt.exe -optimize -input packages\Microsoft.WindowsAppSDK.1.2.230217.4\lib\uap10.0 -input packages\Microsoft.WindowsAppSDK.1.2.230217.4\lib\uap10.0.18362 -input sdk -output "Generated Files"
    ```

1. Copy DLL file for bootstrap.

    ```
    copy packages\Microsoft.WindowsAppSDK.1.2.230217.4\runtimes\win10-x64\native\Microsoft.WindowsAppRuntime.Bootstrap.dll .
    ```

1. Add following main.cpp file.

    ```cpp
    // main.cpp
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
    ```

1. Build the WinUI 3 app

    ```
    cl /I"packages\Microsoft.WindowsAppSDK.1.2.230217.4\include" /I"Generated Files" /EHsc /std:c++17 main.cpp /link /LIBPATH:"packages\Microsoft.WindowsAppSDK.1.2.230217.4\lib\win10-x64" Microsoft.WindowsAppRuntime.Bootstrap.lib Microsoft.WindowsAppRuntime.lib WindowsApp.lib /SUBSYSTEM:WINDOWS /MANIFEST:EMBED
    ```
    
    or
    
    ```
    g++ -std=c++20 -municode -I "packages\Microsoft.WindowsAppSDK.1.3.230331000\include" -I "Generated Files" main.cpp -L "packages\Microsoft.WindowsAppSDK.1.3.230331000\lib\win10-x64" -l Microsoft.WindowsAppRuntime.Bootstrap -l Microsoft.WindowsAppRuntime -l WindowsApp -l ole32 -l oleaut32
    ```

1. Execute the WinUI 3 app

    ```
    main
    ```

## Reference

* [WinUI 3 in C++ without XAML](https://github.com/sotanakamura/winui3-without-xaml)
* [WinUI 3 in C++ and XAML without MIDL](https://github.com/sotanakamura/winui3-without-midl)
