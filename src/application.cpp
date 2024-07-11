#include "application.hpp"

void mib::Application::init_global()
{
    app().add_argument("--verbose").help("Use verbose output").default_value(false).implicit_value(true);
}

void mib::Application::update_global()
{
    args()["verbose"] = app().get<bool>("--verbose");
}