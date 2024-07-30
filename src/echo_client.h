#pragma once

#include "echo.grpc.pb.h"
#include <memory>
#include <string>
namespace mib
{
    using echo::Greeter;
    using grpc::ChannelInterface;

    class EchoClient
    {
    public:
        EchoClient(std::shared_ptr<ChannelInterface> channel) : stub_(Greeter::NewStub(channel)) {}

        std::string SayHello(std::string &name);
        std::vector<std::string> SayHelloStreamReply(std::string &name);

    private:
        std::unique_ptr<Greeter::Stub> stub_;
    };
}
