#ifndef GECKO_ENGINE_H
#define GECKO_ENGINE_H

#include <native_window/external_window.h>

class GeckoEngine {
public:
    GeckoEngine();
    ~GeckoEngine();
    
    bool Initialize(OH_NativeWindow* nativeWindow);
    void LoadUrl(const std::string& url);
    void GoBack();
    void GoForward();
    void Reload();
    void StopLoading();
    
private:
    OH_NativeWindow* mNativeWindow;
    // Add Gecko-specific members
};

#endif // GECKO_ENGINE_H