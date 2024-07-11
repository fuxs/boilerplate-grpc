#pragma once

#include <nlohmann/json.hpp>
#include <vector>
#include "mib/base.hpp"

namespace mib
{
    class CmdPrint : public Command
    {

    public:
        CmdPrint();
        void update(json &args);
        bool run(json &args);

    private:
        std::vector<std::string> messages_;
    };
}