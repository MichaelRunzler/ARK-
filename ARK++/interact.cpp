#include "stdafx.h"
#include "interact.h"

char waitForKeypress(long maxDelayMS) 
{
    // Clear any existing keycodes that may be in the buffer to prevent false triggering.
    while (_kbhit()) _getwch();

    // Define thread object and executable lambda for timer, as well as local flag for completion state
    bool isFinished = false;
    thread tExec;
    auto timer = [&isFinished](long delay) 
    {
        // Return from thread call without setting flags if delay is <= 0
        if (delay <= 0) return;

        // Get current time and multiply delay to nanoseconds instead of milliseconds
        __int64 time = chrono::steady_clock::now().time_since_epoch().count();
        __int64 delay_nano = (__int64)delay * 1000000;

        // Wait for time expiry or forcible completion.
        while ((chrono::steady_clock::now().time_since_epoch().count() - time < delay_nano) && !isFinished)
            this_thread::sleep_for(chrono::milliseconds(10));

        // Set completion flag even if termination was forced by it, since it will be true anyway
        isFinished = true;
    };

    // Start timer thread
    tExec = thread(timer, maxDelayMS);

    char retV = -1;

    // Wait for the timer to finish and set completion flag, or a key to be pressed, whichever comes first
    while (!isFinished) {
        if (_kbhit()) {
            // Get key code and break. Ignore codes less than 1, since they are reserved for function
            // keys (like the arrow keys and the F keys), and we don't want to read those.
            retV = _getwch();

            if(retV > 0) break;
            // Clear the other keycode in the buffer if the previous key hit produced two codes.
            else _getwch();
        }
        this_thread::sleep_for(chrono::milliseconds(10)); 
    }

    // Force finished flag, join and destroy thread.
    isFinished = true;
    tExec.join();
    tExec.~thread();

    return retV;
}

char waitForKeypress() {
    return waitForKeypress(-1);
}

