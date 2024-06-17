#define LOADBALANCER_H

#ifndef REQUEST_CPP
#include "Request.cpp"
#endif

#include <queue>

/**
 * @class LoadBalancer
 * @brief A class to represent a load balancer managing network requests.
 */
class LoadBalancer
{
public:
    /**
     * @brief Default constructor for LoadBalancer.
     * Initializes systemTime to 0.
     */
    LoadBalancer()
    {
        systemTime = 0;
    }

    /**
     * @brief Gets the current system time.
     * @return The current system time.
     */
    int getTime();

    /**
     * @brief Increments the system time by 1 unit.
     */
    void incTime();

    /**
     * @brief Adds a request to the load balancer's queue.
     * @param r The request to be added.
     */
    void addRequest(Request r);

    /**
     * @brief Retrieves and removes the next request from the queue.
     * @return The next request in the queue.
     */
    Request getRequest();

    /**
     * @brief Checks if the request queue is empty.
     * @return True if the request queue is empty, otherwise false.
     */
    bool isRequestQueueEmpty();

    /**
     * @brief Gets the size of the request queue.
     * @return The size of the request queue.
     */
    int getRequestQueueSize();

private:
    int systemTime;                ///< The current system time.
    std::queue<Request> requestQueue;  ///< The queue of requests.
};

#include "LoadBalancer.cpp"
