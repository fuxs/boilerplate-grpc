#pragma once

#include <nlohmann/json.hpp>
#include <vector>
#include "mib/base.h"
#include <grpcpp/grpcpp.h>
#include <memory>

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

    class CmdSend : public Command
    {

    public:
        CmdSend();
        void update(json &args);
        bool run(json &args);

    private:
        std::shared_ptr<grpc::Channel> channel_;
        std::string address_;
        std::string message_;
        bool multi_;
        bool interact_;
    };
}
