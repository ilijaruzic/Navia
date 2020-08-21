#ifndef _NAVIA_ENTRYPOINT_HPP_
#define _NAVIA_ENTRYPOINT_HPP_

extern Navia::Application* Navia::create();

#ifdef NAVIA_PLATFORM_WINDOWS
int main(int argc, char* argv[]) {
    Navia::Logger::init();
    NAVIA_CORE_INFO("Logger initialized successfully!");
    auto application = Navia::create();
    application->run();
    delete application;
}
#endif

#endif