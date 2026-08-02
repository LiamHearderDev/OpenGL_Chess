#ifndef MULTICAST_DELEGATE_H
#define MULTICAST_DELEGATE_H

#include <functional>
#include <utility>
#include <vector>
#include <memory>


/** A `Multicast Delegate` is a container that holds a list of references 
 * to multiple functions that can all be executed sequentially 
 * via a single trigger call. Based on the Unreal Engine implementation.
 * 
 * How to use:
 *  1. Create a MulticastDelegate object using the DECLARE_MULTICAST_DELEGATE macro,
 *  2. Add listeners using the `add()` method,
 *  3. Broadcast to all listeners using the `broadcast()` method.
 * */


#define DECLARE_MULTICAST_DELEGATE(name, ...) \
    const std::unique_ptr<MulticastDelegate<__VA_ARGS__>> name = std::make_unique<MulticastDelegate<__VA_ARGS__>>();


template <typename... Args>
class MulticastDelegate {

    /** The array of listening objects/functions. */
    std::vector<std::function<void(Args...)>> listeners;

public:

    /** Binds a member function to listen to this delegate. */
    template <typename T>
    void add(T* object, void (T::*member)(Args...)) {
        if (!object) {
            return;
        }

        listeners.emplace_back([object, member](Args... args) {
            (object->*member)(std::forward<Args>(args)...);
        });
    }

    /** Binds a raw function pointer to listen to this delegate. */
    void add(std::function<void(Args...)> listener) {
        if (listener) {
            listeners.emplace_back(std::move(listener));
        }
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