#ifndef GECKO_NAPI_H
#define GECKO_NAPI_H

#include <napi/native_api.h>

// NAPI module initialization
napi_value Init(napi_env env, napi_value exports);

// NAPI method declarations
napi_value InitializeEngine(napi_env env, napi_callback_info info);
napi_value LoadUrl(napi_env env, napi_callback_info info);
napi_value GoBack(napi_env env, napi_callback_info info);
napi_value GoForward(napi_env env, napi_callback_info info);
napi_value Reload(napi_env env, napi_callback_info info);
napi_value StopLoading(napi_env env, napi_callback_info info);

#endif // GECKO_NAPI_H