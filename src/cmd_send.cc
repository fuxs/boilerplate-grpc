#include "cmd.h"
#include <fmt/core.h>
#include <string>
#include "echo_client.h"

mib::CmdSend::CmdSend() : Command("send")
{
    auto &p = parser();
    p.add_description("Send a message");
    p.add_argument("-a","--address")
        .help("The address of the server")
        .default_value("localhost:50051");
    p.add_argument("message")
        .help("The message to be sent.");
}

void mib::CmdSend::update(json &args)
{
    address_ = parser().get<std::string>("--address");
    message_ = parser().get<std::string>("message");
    channel_ = grpc::CreateChannel(address_, grpc::InsecureChannelCredentials());
}

bool mib::CmdSend::run(json &args)
{
    EchoClient client(channel_);
    if (args["verbose"].get<bool>())
    {
        fmt::println("Sending message {} to server at {} ", message_, address_);
    }
    auto response = client.SayHello(message_);
    fmt::println(response);
    return true;
}
