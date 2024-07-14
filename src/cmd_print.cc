#include "cmd.h"
#include <fmt/core.h>
#include <string>

mib::CmdPrint::CmdPrint() : Command("print")
{
    auto &p = parser();
    p.add_description("Print a message to the standard output");
    p.add_argument("messages")
        .help("Pass a message to be printed.")
        .remaining();
}

void mib::CmdPrint::update(json &args)
{
    messages_ = parser().get<std::vector<std::string>>("messages");
}

bool mib::CmdPrint::run(json &args)
{
    if (args["verbose"].get<bool>())
    {
        fmt::println("Printing: ");
    }
    for (auto &message : messages_)
        std::cout << message << std::endl;
    return true;
}