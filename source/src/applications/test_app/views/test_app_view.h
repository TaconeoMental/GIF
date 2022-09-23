#ifndef TEST_APP_FRAME_H
#define TEST_APP_FRAME_H

enum TestAppView
{
    TestAppViewMain,
    TestAppViewSecond,
    TestAppViewNum
};

enum TestAppEvent
{
    TestAppMainEventOpenSecond,
    TestAppSecondEventOpenMain,
    TestAppSecondEventRedraw
};

#endif
