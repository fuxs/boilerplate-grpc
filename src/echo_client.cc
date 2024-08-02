
#include "echo_client.h"
#include <fmt/core.h>
#include <grpcpp/grpcpp.h>
#include <thread>

using echo::HelloReply;
using echo::HelloRequest;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
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

std::vector<std::string> mib::EchoClient::SayHelloStreamReply(std::string &name)
{
    ClientContext context;
    HelloReply reply;
    HelloRequest request;
    request.set_name(name);
    auto result = std::vector<std::string>();
    std::unique_ptr<ClientReader<HelloReply>>
        reader(stub_->SayHelloStreamReply(&context, request));
    while (reader->Read(&reply))
        result.push_back(reply.message());

    auto status = reader->Finish();
    if (status.ok())
        return result;

    std::string msg = fmt::format("call of SayHelloStreamReply failed ({}): {}",
                                  static_cast<int>(status.error_code()),
                                  status.error_message());
    throw std::runtime_error(msg);
}

void mib::EchoClient::SayHelloBidiStream()
{
    ClientContext context;
    HelloRequest request;
    std::shared_ptr<ClientReaderWriter<HelloRequest, HelloReply>>
        stream(stub_->SayHelloBidiStream(&context));

    std::thread reader([stream]()
                       {
        HelloReply reply;
        while (stream->Read(&reply))
                std::cout << reply.message() << std::endl; });

    std::string line;
    while (std::getline(std::cin, line))
    {
        request.set_name(line);
        if (!stream->Write(request))
            break;
    }
    stream->WritesDone();
    reader.join();
    auto status = stream->Finish();
    if (status.ok())
        return;
    
    std::string msg = fmt::format("call of SayHelloBidiStream failed ({}): {}",
                                  static_cast<int>(status.error_code()),
                                  status.error_message());
    throw std::runtime_error(msg);
}