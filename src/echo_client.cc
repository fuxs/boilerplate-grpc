
#include "echo_client.h"
#include <fmt/core.h>
#include <grpcpp/grpcpp.h>

using echo::HelloReply;
using echo::HelloRequest;
using grpc::ClientContext;
using grpc::Status;

std::string mib::EchoClient::SayHello(std::string &name)
{
    ClientContext context;
    HelloReply reply;
    HelloRequest request;
    request.set_name(name);
    
    auto status = stub_->SayHello(&context, request, &reply);
    if (status.ok())
    {
        return reply.message();
    }
    std::string msg = fmt::format("call of SayHello failed ({}): {}",
                                  static_cast<int>(status.error_code()),
                                  status.error_message());
    throw std::runtime_error(msg);
}
