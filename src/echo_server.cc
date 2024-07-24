#include "service.h"
#include "echo.grpc.pb.h"
#include <fmt/core.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>


using echo::Greeter;
using echo::HelloReply;
using echo::HelloRequest;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;

class EchoServerImpl final : public Greeter::Service
{
public:
    Status SayHello(ServerContext *context, const HelloRequest *request, HelloReply *response) override
    {
        auto name = request->name();
        auto message = fmt::format("Hello {}", name);
        response->set_message(message);
        return Status::OK;
    }

    Status SayHelloStreamReply(ServerContext *context, const HelloRequest *request, ServerWriter<HelloReply> *writer) override
    {
        return Status::OK;
    }

    Status SayHelloBidiStream(ServerContext *context, ServerReaderWriter<HelloReply, HelloRequest> *stream) override
    {
        return Status::OK;
    }
};

void run_server(const std::string& address) {
    EchoServerImpl service;

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    
    ServerBuilder sb;
    sb.AddListeningPort(address, grpc::InsecureServerCredentials());
    sb.RegisterService(&service);
    std::unique_ptr<Server> server(sb.BuildAndStart());
    server->Wait();
}