#include "mib/base.h"

void mib::ApplicationBase::add(Command &cmd)
{
    app_.add_subparser(cmd.parser());
    cmds_.push_back(cmd);
}

int mib::ApplicationBase::run(int argc, char *argv[])
{
    auto initialized = false;
    auto executed = false;
    try
    {
        init_global();
        app_.parse_args(argc, argv);
        update_global();
        for (Command &cmd : cmds_)
        {
            if (app_.is_subcommand_used(cmd.name()))
            {
                cmd.update(args_);
                initialized = true;
                cmd.run(args_);
                executed = true;
                break;
            }
        }
        if (!executed)
        {
            std::cerr << "command is missing" << std::endl;
            std::cerr << app_.help().str();
            return EXIT_FAILURE;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        if (!initialized)
        {
            std::cerr << app_.help().str();
        }
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}