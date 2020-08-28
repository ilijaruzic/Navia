#ifndef _NAVIA_ENTRYPOINT_HPP_
#define _NAVIA_ENTRYPOINT_HPP_

extern Navia::Application* Navia::create();

#ifdef NAVIA_PLATFORM_WINDOWS
int main(int argc, char* argv[]) {
    Navia::Logger::init();

    NAVIA_PROFILE_BEGIN_SESSION("Startup", "NaviaProfile-Startup.json");
    auto application = Navia::create();
    NAVIA_PROFILE_END_SESSION();

    NAVIA_PROFILE_BEGIN_SESSION("Runtime", "NaviaProfile-Runtime.json");
    application->run();
    NAVIA_PROFILE_END_SESSION();

    NAVIA_PROFILE_BEGIN_SESSION("Runtime", "NaviaProfile-Shutdown.json");
    delete application;
    NAVIA_PROFILE_END_SESSION();
}
#endif

#endif