
#include <stdio.h>
#include <emscripten.h>
#include <emscripten/bind.h>

extern "C" {

EM_JS(void, qt_suspend, (), {
    let sleepFn = function(wakeUp) {
        Module.qtWakeUp = wakeUp;
    };
    return Asyncify.handleSleep(sleepFn);
});

EM_JS(void, qt_resume, (), {
    if (Module.qtWakeUp == undefined) {
        out("err: resume called when not suspended");
        return;
    }
    let wakeUp = Module.qtWakeUp;
    Module.qtWakeUp == undefined;
    setTimeout(wakeUp); // workaround for https://github.com/emscripten-core/emscripten/issues/10515
});

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("resume", &qt_resume);
}

int main()
{
    while (true) {
        printf("suspending - press resume button to wake \n");
        qt_suspend();
        printf("resumed \n");
    }
    return 0;
}

}
