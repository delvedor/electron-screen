#include <node.h>

// compile only under win 32
#ifdef _WIN32
#include <windows.h>

namespace windows_monitor {

using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Null;
using v8::Object;
using v8::String;
using v8::Value;

void getScreens (const FunctionCallbackInfo<Value>& args) {
  args.GetReturnValue().Set(GetSystemMetrics(SM_CMONITORS));
}

void callback (const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Function> cb = Local<Function>::Cast(args[0]);
  Local<Value> argv[1] = { String::NewFromUtf8(isolate, "hello world") };
  cb->Call(Null(isolate), 1, argv);
}

void getObject (const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Object> obj = Object::New(isolate);
  obj->Set(String::NewFromUtf8(isolate, "value"), args[0]->ToString());
  obj->Set(String::NewFromUtf8(isolate, "name"), args[1]->ToString());

  args.GetReturnValue().Set(obj);
}

BOOL MyInfoEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
  /* Local<Object> obj = Object::New(isolate);
  obj->Set(String::NewFromUtf8(isolate, "hMonitor"), hMonitor;
  obj->Set(String::NewFromUtf8(isolate, "hdcMonitor"), hdcMonitor;
  obj->Set(String::NewFromUtf8(isolate, "lprcMonitor"), lprcMonitor;
  */

  int* ptr = (int*)dwData;
  (*ptr)++;
}

void getInfo (const FunctionCallbackInfo<Value>& args) {
  int screens = 0;
  EnumDisplayMonitors(GetDC(), NULL, MyInfoEnumProc, &screens);

  Local<Object> obj = Object::New(isolate);
  obj->Set(String::NewFromUtf8(isolate, "screens"), screens);

  args.GetReturnValue().Set(obj);
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "getScreens", getScreens);
  NODE_SET_METHOD(exports, "getInfo", getInfo);
  NODE_SET_METHOD(exports, "getObject", getObject);
  NODE_SET_METHOD(exports, "callback", callback);
}

NODE_MODULE(monitor, init)

}
#endif
