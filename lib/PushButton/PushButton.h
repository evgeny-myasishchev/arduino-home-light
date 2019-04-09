#ifndef PushButton_h
#define PushButton_h

struct pushButtonConfig
{
    // Min number of ms a signal should be seen
    // to consider button pressed or switched
    int minSignalDurationMs;

    
};

class PushButton
{
private:
    /* data */
public:
    PushButton(pushButtonConfig cfg);

    // Return state of a button (either LOW or HIGH)
    int getState();

    void processCurrentLevel(int level);
};

#endif