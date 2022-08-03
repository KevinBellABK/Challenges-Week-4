#include <iostream>
#include <thread>
using namespace std;

bool ShouldEndThread = false;

int threadVal = 0;

bool didQuit = false, shouldDecrementLife = false;

struct Character
{
    float position = 0.0f;
    int score = 0;
    int lives = 1;

    void DisplayStats()
    {
        cout << "Lives: " << lives << endl;
    }
};

Character Player;

void UpdateCharacter1()
{
    while (!didQuit)
    {
        if (shouldDecrementLife)
        {
            if (Player.lives > 0)
            {
                this_thread::sleep_for(chrono::milliseconds(500));
                //this_thread::yield();
                Player.lives--;
            }
        }
    }
}

void UpdateCharacter2()
{
    while (!didQuit)
    {
        if (shouldDecrementLife)
        {
            if (Player.lives > 0)
            {
                this_thread::sleep_for(chrono::milliseconds(500));
                //this_thread::yield();
                Player.lives--;
            }
        }
    }
}

void ProcessInput()
{
    while (!didQuit)
    {
        cout << "'a' to take a life\n";
        cout << "'d' to display stats\n";
        cout << "'q to quit\n";
        char UserInput;
        cin >> UserInput;

        switch (UserInput)
        {
        case 'a':
            shouldDecrementLife = true;
            break;
        case 'd':
            Player.DisplayStats();
            break;
        case 'q':
            didQuit = true;
            break;
        default:
            break;
        }
        didQuit = (UserInput == 'q');
    }
}

void HelloWorldThread()
{
    while(!didQuit)
    {
        threadVal++;
        if (threadVal > 1000)
            threadVal = 0;
    }
}

int main()
{
    thread inputHandler(ProcessInput);
    thread characterUpdate1(UpdateCharacter1);
    thread characterUpdate2(UpdateCharacter2);

    inputHandler.join();
    characterUpdate1.join();
    characterUpdate2.join();
    return 0;
    /*
    cout << "Hello World!\n";
    thread Hello(HelloWorldThread);
    char userChar = ' ';

    while (!didQuit)
    {
        cout << "Enter any key to display counter or 'Q' to quit" << endl;
        cin >> userChar;
        if (userChar == 'Q' || userChar == 'q')
            didQuit = true;
        else
            cout << "Thread Value: " << threadVal << endl;
    }
    
    Hello.join();
    
    return 0;
    */
}