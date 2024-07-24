#pragma once

#include <nlohmann/json.hpp>
#include <vector>
#include "mib/base.h"

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

    class CmdStart : public Command
    {

    public:
        CmdStart();
        void update(json &args);
        bool run(json &args);

    private:
        std::string address_;
    };
}