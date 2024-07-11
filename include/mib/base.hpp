#pragma once

#include <argparse/argparse.hpp>
#include <nlohmann/json.hpp>
#include <vector>

namespace mib
{
    using json = nlohmann::json;
    using ArgumentParser = argparse::ArgumentParser;

    class Command
    {
    public:
        Command(const char *name) : parser_{name}, name_{name} {}
        virtual void update(json &args) = 0;
        virtual bool run(json &args) = 0;
        inline ArgumentParser &parser()
        {
            return parser_;
        }
        inline std::string &name()
        {
            return name_;
        }

    private:
        ArgumentParser parser_;
        std::string name_;
    };

    class ApplicationBase
    {
    public:
        ApplicationBase(const char *name, const char *version) : app_(name, version) {}
        /* Runs one of the subcommands.
         * @returns *true* if one of the commands could be execute, otherwise _false_
         */
        int run(int argc, char *argv[]);
        void add(Command &cmd);
        inline std::string help()
        {
            return app_.help().str();
        }
        inline bool subcommand(const char *cmd)
        {
            return app_.is_subcommand_used(cmd);
        }

    protected:
        virtual void init_global() = 0;
        virtual void update_global() = 0;
        inline ArgumentParser &app()
        {
            return app_;
        }
        inline json &args()
        {
            return args_;
        }

    private:
        ArgumentParser app_;
        std::vector<std::reference_wrapper<Command>> cmds_;
        json args_;
    };
}