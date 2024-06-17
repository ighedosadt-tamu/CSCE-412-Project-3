#ifndef LOADBALANCER_H
#include "LoadBalancer.h"
#endif
#include <sstream>

/**
 * @brief Gets the current system time.
 * @return The current system time.
 */
int LoadBalancer::getTime()
{
    return systemTime;
}

/**
 * @brief Increments the system time by 1 unit.
 */
void LoadBalancer::incTime()
{
    systemTime++;
}

/**
 * @brief Adds a request to the load balancer's queue.
 * @param r The request to be added.
 */
void LoadBalancer::addRequest(Request r)
{
    requestQueue.push(r);
    incTime();
}

/**
 * @brief Retrieves and removes the next request from the queue.
 * If the queue is empty, returns a default request with a random process time.
 * @return The next request in the queue, or a default request if the queue is empty.
 */
Request LoadBalancer::getRequest()
{
    incTime();

    if (!requestQueue.empty())
    {
        Request r = requestQueue.front();
        requestQueue.pop();
        return r;
    }
    stringstream ips, ipd;
    Request r;
    ips << 255 << "." << 255 << "." << 255 << "." << 255;
    ipd << 255 << "." << 255 << "." << 255 << "." << 255;
    r.source = ips.str();
    r.destination = ipd.str();
    r.processTime = rand() % 500;
    return r;
}

/**
 * @brief Checks if the request queue is empty.
 * @return True if the request queue is empty, otherwise false.
 */
bool LoadBalancer::isRequestQueueEmpty()
{
    return requestQueue.empty();
}

/**
 * @brief Gets the size of the request queue.
 * @return The size of the request queue.
 */
int LoadBalancer::getRequestQueueSize()
{
    return requestQueue.size();
}
