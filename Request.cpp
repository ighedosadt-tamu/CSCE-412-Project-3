#include <string>
using namespace std;

#define REQUEST_CPP

/**
 * @struct Request
 * @brief A structure to represent a network request.
 */
struct Request {
    string source;       ///< The source of the request.
    string destination;  ///< The destination of the request.
    int processTime;     ///< The time required to process the request.
};
