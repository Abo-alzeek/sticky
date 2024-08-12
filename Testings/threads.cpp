#include <SFML/System.hpp>
#include <iostream>

void func()
{
    // this function is started when thread.launch() is called

    for (int i = 0; i < 100; ++i)
        std::cout << "I'm thread number one\n";
}

int main()
{
    // create a thread with func() as entry point
    sf::Thread thread(&func);

    // run it
    thread.launch();

    // the main thread continues to run...

    for (int i = 0; i < 100; ++i)
        std::cout << "I'm the main thread\n";

    return 0;
}
