#include "gecko_napi.h"
#include "gecko_engine.h"
#include <hilog/log.h>
#include <napi/native_api.h>

#undef LOG_DOMAIN
#define LOG_DOMAIN 0x3200
#define LOG_TAG "GeckoNAPI"

static GeckoEngine* sEngine = nullptr;

static napi_value InitializeEngine(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    
    // Get native window handle from XComponent
    OH_NativeWindow* nativeWindow = nullptr;
    napi_get_value_external(env, args[0], reinterpret_cast<void**>(&nativeWindow));
    
    if (!nativeWindow) {
        OH_LOG_ERROR(LOG_APP, "Failed to get native window");
        return nullptr;
    }
    
    // Initialize Gecko engine
    sEngine = new GeckoEngine();
    bool success = sEngine->Initialize(nativeWindow);
    
    napi_value result;
    napi_get_boolean(env, success, &result);
    return result;
}

static napi_value LoadUrl(napi_env env, napi_callback_info info) {
    if (!sEngine) {
        OH_LOG_ERROR(LOG_APP, "Gecko engine not initialized");
        return nullptr;
    }
    
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    
    // Get URL string from ArkTS
    size_t urlLength;
    napi_get_value_string_utf8(env, args[0], nullptr, 0, &urlLength);
    
    std::string url(urlLength + 1, '\0');
    napi_get_value_string_utf8(env, args[0], &url[0], urlLength + 1, &urlLength);
    
    // Call Gecko engine
    sEngine->LoadUrl(url);
    OH_LOG_INFO(LOG_APP, "Loading URL: %{public}s", url.c_str());
    
    return nullptr;
}

// Add similar implementations for GoBack, GoForward, Reload, StopLoading

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
        { "initialize", nullptr, InitializeEngine, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "loadUrl", nullptr, LoadUrl, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "goBack", nullptr, GoBack, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "goForward", nullptr, GoForward, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "reload", nullptr, Reload, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "stopLoading", nullptr, StopLoading, nullptr, nullptr, nullptr, napi_default, nullptr }
    };
    
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    OH_LOG_INFO(LOG_APP, "Gecko NAPI module initialized");
    return exports;
}
EXTERN_C_END

static napi_module gecko_module = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "gecko",
    .nm_priv = nullptr,
    .reserved = {0},
};

extern "C" __attribute__((constructor)) void RegisterGeckoModule() {
    napi_module_register(&gecko_module);
}