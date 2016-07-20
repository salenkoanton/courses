#include "dllmanager.h"
#include "main_ui.h"
using namespace sf;
void error_massage(void)
{

}

int main(void)
{
    RenderWindow window(VideoMode(WINDOW_WIGHT, WINDOW_HIGHT), "Labyrinth");
    window.setFramerateLimit(30);
    Main_UI ui = Main_UI();
    while (true)
    {
        enum run_return_statemant status = ui.load_dll(window);
        if (status == EXIT)
            return 0;
        if (status == FAIL)
            return 1;
        if (status == FAIL_IN_LOAD_LIB)
        {
            error_massage();
            continue;
        }
        status = ui.run(window);
        if (status == EXIT)
            return 0;
        if (status == RELOAD_LIB)
            continue;
        if (status == FAIL)
            return 1;
        if (status == FAIL_IN_LOAD_MAP)
            return 2;
    }
    return 0;
}
