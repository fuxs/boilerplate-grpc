#pragma once

#include "mib/base.hpp"

namespace mib
{

    class Application : public ApplicationBase
    {
    public:
        Application() : ApplicationBase{"app", "0.1.0"} {};

    protected:
        void init_global();
        void update_global();
    };

}