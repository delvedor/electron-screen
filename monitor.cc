#include <node.h>

// compile only under win 32
#ifdef _WIN32
#include <Winuser.h>

namespace windows_monitor {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

int getScreens () {
  return GetSystemMetrics(SM_CMONITORS);
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "getScreens", getScreens);
}

NODE_MODULE(monitor, init)

}
#endif
