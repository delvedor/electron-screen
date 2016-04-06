#include <node.h>

// code for win32 only
#ifdef _WIN32
#include <windows.h>
#include <cstdint>
#include <vector>

namespace electron_screen {

using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Int32;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Array;

/**
 * Monitor info structure:
 * 	{
 *  	x: Number,
 *   	y: Number,
 *    width: Number,
 *    height: Number
 *  }
 */
struct screen_info {
  screen_info(uint32_t x, uint32_t y, uint32_t width, uint32_t height) : x(x), y(y), width(width), height(height) {}
  uint32_t x;
  uint32_t y;
  uint32_t width;
  uint32_t height;
};

/**
 * Gets information about hMonitor
 */
BOOL InfoMonitor (HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
  std::vector<screen_info>& infos = *((std::vector<screen_info>*)dwData);

  MONITORINFOEX mon_info{};
  mon_info.cbSize = sizeof(MONITORINFOEX);
  GetMonitorInfo(hMonitor, &mon_info);

  infos.emplace_back(mon_info.rcMonitor.left, mon_info.rcMonitor.top,
    mon_info.rcMonitor.right - mon_info.rcMonitor.left,
    mon_info.rcMonitor.bottom - mon_info.rcMonitor.top);

  return TRUE;
}

/**
 * Gets info about all connected monitors and return an array of objects.
 */
void getInfo (const FunctionCallbackInfo<Value>& args) {
  std::vector<screen_info> screens{};
  HDC hdc = GetDC(NULL);
  EnumDisplayMonitors(hdc, NULL, InfoMonitor, (LPARAM)&screens);

  Isolate* isolate = args.GetIsolate();
  Local<Array> array = Array::New(isolate, (int)screens.size());

  for (uint32_t i = 0; i < screens.size(); ++i) {
    Local<Object> bounds = Object::New(isolate);
    Local<Object> obj = Object::New(isolate);
    bounds->Set(String::NewFromUtf8(isolate, "x"), Int32::NewFromUnsigned(isolate, screens[i].x));
    bounds->Set(String::NewFromUtf8(isolate, "y"), Int32::NewFromUnsigned(isolate, screens[i].y));
    bounds->Set(String::NewFromUtf8(isolate, "width"), Int32::NewFromUnsigned(isolate, screens[i].width));
    bounds->Set(String::NewFromUtf8(isolate, "height"), Int32::NewFromUnsigned(isolate, screens[i].height));
    obj->Set(String::NewFromUtf8(isolate, "bounds"), bounds);
    array->Set(i, obj);
  }

  ReleaseDC(0, hdc);
  args.GetReturnValue().Set(array);
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "getInfo", getInfo);
}

NODE_MODULE(electronscreen, init)

}

#endif
