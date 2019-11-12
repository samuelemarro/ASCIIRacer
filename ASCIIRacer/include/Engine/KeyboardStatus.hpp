#pragma once

#include <vector>

#include "Key.hpp"

class KeyboardStatus
{
private:
    std::vector<Key> pressedKeys_;
    std::vector<Key> downKeys_;
    std::vector<Key> releasedKeys_;
    //Possibile ottimizzazione: pressedKeys_ e stillDownKeys_

public:
    bool isPressed(Key key);
    bool isDown(Key key);
    bool isReleased(Key key);

    KeyboardStatus(std::vector<Key> pressedKeys, std::vector<Key> downKeys, std::vector<Key> releasedKeys);
};