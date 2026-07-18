#ifndef MULTICAST_DELEGATE_H
#define MULTICAST_DELEGATE_H

#include <iostream>
#include <vector>
#include <functional>

/** A multicast delegate is a design pattern container that holds a list of
 * references to multiple functions that can all be executed sequentially 
 * via a single trigger call. Based on the Unreal Engine implementation.
 * 
 * How to use:
 *  1. Create a MulticastDelegate object, 
 *  2. Add listeners using the `add()` method,
 *  3. Broadcast to all listeners using the `broadcasts()` method.
 * */

template <typename... Args>
class MulticastDelegate {

    std::vector<std::function<void(Args...)>> listeners;

public:
    /** Adds a listener to the delegate */
    void add(std::function<void(Args...)> listener) {
        listeners.push_back(listener);
    }

    /** Broadcasts to all current listeners. */
    void broadcast(Args... args) {
        for (const auto& listener : listeners) {
            if (listener) { 
                listener(args...); 
            }
        }
    }

    /** Clears all current listeners. */
    void clear_listeners() {
        listeners.clear();
    }
};
#endif // MULTICAST_DELEGATE_H