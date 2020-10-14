#include "proxy_wasm_intrinsics.h"
#define StringView std::string_view

class ExampleRootContext: public RootContext {
public:
  explicit ExampleRootContext(uint32_t id, StringView root_id): RootContext(id, root_id) {}

  bool onStart(size_t) override;
};

class ExampleContext: public Context {
public:
  explicit ExampleContext(uint32_t id, RootContext* root) : Context(id, root) {}

  FilterHeadersStatus onResponseHeaders(uint32_t, bool) override;

  FilterStatus onDownstreamData(size_t, bool) override;
};

// register factories for ExampleContext and ExampleRootContext
static RegisterContextFactory register_FilterContext(CONTEXT_FACTORY(ExampleContext),
                                                      ROOT_FACTORY(ExampleRootContext),
                                                      "my_root_id");

// invoked when the plugin initialised and is ready to process streams
bool ExampleRootContext::onStart(size_t n) {
  LOG_DEBUG("ready to process streams");

  return true;
}

// invoked when HTTP response header is decoded
FilterHeadersStatus ExampleContext::onResponseHeaders(uint32_t, bool) {
  addResponseHeader("resp-header-demo", "added by our filter");

  return FilterHeadersStatus::Continue;
}

// invoked when downstream TCP data chunk is received
FilterStatus ExampleContext::onDownstreamData(size_t, bool) {
  auto res = setBuffer(WasmBufferType::NetworkDownstreamData, 0, 0, "prepend payload to downstream data");

   if (res != WasmResult::Ok) {
     LOG_ERROR("Modifying downstream data failed: " + toString(res));
      return FilterStatus::StopIteration;
   }

   return FilterStatus::Continue;
}