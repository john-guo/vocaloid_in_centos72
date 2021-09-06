// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: protos/server.proto

#include "protos/server.pb.h"
#include "protos/server.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace MyVocaloid {

static const char* Vocaloid_method_names[] = {
  "/MyVocaloid.Vocaloid/Sing",
};

std::unique_ptr< Vocaloid::Stub> Vocaloid::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Vocaloid::Stub> stub(new Vocaloid::Stub(channel));
  return stub;
}

Vocaloid::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Sing_(Vocaloid_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Vocaloid::Stub::Sing(::grpc::ClientContext* context, const ::MyVocaloid::SingRequest& request, ::MyVocaloid::SingReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Sing_, context, request, response);
}

void Vocaloid::Stub::experimental_async::Sing(::grpc::ClientContext* context, const ::MyVocaloid::SingRequest* request, ::MyVocaloid::SingReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Sing_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::MyVocaloid::SingReply>* Vocaloid::Stub::AsyncSingRaw(::grpc::ClientContext* context, const ::MyVocaloid::SingRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::MyVocaloid::SingReply>::Create(channel_.get(), cq, rpcmethod_Sing_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::MyVocaloid::SingReply>* Vocaloid::Stub::PrepareAsyncSingRaw(::grpc::ClientContext* context, const ::MyVocaloid::SingRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::MyVocaloid::SingReply>::Create(channel_.get(), cq, rpcmethod_Sing_, context, request, false);
}

Vocaloid::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Vocaloid_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Vocaloid::Service, ::MyVocaloid::SingRequest, ::MyVocaloid::SingReply>(
          std::mem_fn(&Vocaloid::Service::Sing), this)));
}

Vocaloid::Service::~Service() {
}

::grpc::Status Vocaloid::Service::Sing(::grpc::ServerContext* context, const ::MyVocaloid::SingRequest* request, ::MyVocaloid::SingReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace MyVocaloid

