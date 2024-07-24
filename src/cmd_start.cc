#include "cmd.h"
#include "service.h"
#include <fmt/core.h>
#include <string>

mib::CmdStart::CmdStart() : Command("start")
{
    auto &p = parser();
    p.add_description("Start a server replying with 'Hello {message}' ");
    p.add_argument("-a","--address")
        .help("The binding address of the server")
        .default_value("0.0.0.0:50051");
}

void mib::CmdStart::update(json &args)
{
    address_ = parser().get<std::string>("--address");
}

bool mib::CmdStart::run(json &args)
{
    if (args["verbose"].get<bool>())
    {
        fmt::println("Starting server at {} ", address_);
    }
    run_server(address_);
    return true;
}