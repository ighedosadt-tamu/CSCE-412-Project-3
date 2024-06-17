#ifndef REQUEST_CPP
#include "Request.cpp"
#endif

/**
 * @class WebServer
 * @brief A class to represent a web server handling requests.
 */
class WebServer
{
private:
    Request r;                ///< The current request being processed by the server.
    int requestStartTime;     ///< The time at which the current request started.
    std::string serverName;   ///< The name of the server.

public:
    /**
     * @brief Default constructor for WebServer.
     * Initializes requestStartTime to 0 and serverName to an empty string.
     */
    WebServer(){
        requestStartTime = 0;
        serverName = " ";
    };

    /**
     * @brief Parameterized constructor for WebServer.
     * @param name The name of the server.
     * Initializes requestStartTime to 0 and serverName to the provided name.
     */
    WebServer(std::string name){
        requestStartTime = 0;
        serverName = name;
    };

    /**
     * @brief Adds a request to the server.
     * @param req The request to be added.
     * @param currTime The current time when the request is added.
     */
    void addRequest(Request req, int currTime)
    {
        r = req;
        requestStartTime = currTime;
    }

    /**
     * @brief Retrieves the current request being processed by the server.
     * @return The current request.
     */
    Request getRequest()
    {
        return r;
    }

    /**
     * @brief Retrieves the name of the server.
     * @return The name of the server.
     */
    std::string getName()
    {
        return serverName;
    }

    /**
     * @brief Checks if the current request is done based on the current time.
     * @param currTime The current time.
     * @return True if the request is done, otherwise false.
     */
    bool isRequestDone(int currTime){
        return (currTime >= (requestStartTime + r.processTime));
    }
};
