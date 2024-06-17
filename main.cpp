/** @file */ 
#include "Request.cpp"
#include "WebServer.cpp"
#include "LoadBalancer.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <chrono>

using namespace std;

int NUMWEBSERVERS;

int clockCycle;
std::ofstream logFile; 

/**
 * @brief Creates a random network request.
 * @return A Request object with random source, destination, and process time.
 */
Request createRandomRequest()
{
    stringstream ips, ipd;
    Request r;
    ips << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    ipd << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
    r.source = ips.str();
    r.destination = ipd.str();
    r.processTime = rand() % 500;
    return r;
}

/**
 * @brief Initializes the log file for the load balancer.
 */
void initializeLog() {
    logFile.open("loadbalancer_log.txt");
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        exit(1);
    }
}

/**
 * @brief Main function to simulate the load balancer and web servers.
 * @return int Exit status.
 */
int main()
{
    cout << "Enter the number of servers you wish to use: " << endl;
    cin >> NUMWEBSERVERS;
    cout << "Enter the clock cycle: " << endl;
    cin >> clockCycle;
    srand(time(0));
    LoadBalancer lb;
    initializeLog();

    // Add initial requests to the load balancer
    for (int i = 0; i < 10; i++)
    {
        Request r = createRandomRequest();
        lb.addRequest(r);
    }

    // Initialize web servers and assign initial requests
    WebServer webarray[NUMWEBSERVERS];
    for (int i = 0; i < NUMWEBSERVERS; i++)
    {
        WebServer w(to_string(i + 1));
        webarray[i] = w;
        webarray[i].addRequest(lb.getRequest(), lb.getTime());
    }

    // Main simulation loop
    while (lb.getTime() < clockCycle)
    {
        int currTime = lb.getTime();

        if (webarray[currTime % NUMWEBSERVERS].isRequestDone(currTime))
        {
            Request r = webarray[currTime % NUMWEBSERVERS].getRequest();
            cout << "At time: " << currTime << ", Server " << webarray[currTime % NUMWEBSERVERS].getName() << " processed request from " << r.source << " to " << r.destination << endl;
            webarray[currTime % NUMWEBSERVERS].addRequest(lb.getRequest(), currTime);
        }

        // Occasionally add new requests to the load balancer
        if (rand() % 10 == 0)
        {
            Request r = createRandomRequest();
            lb.addRequest(r);
        }

        // Log the current state
        logFile << "Clock cycle: " << lb.getTime() << ", Requests in queue: " << lb.getRequestQueueSize() << ", Servers: " << NUMWEBSERVERS << std::endl;
        lb.incTime();
    }
}
