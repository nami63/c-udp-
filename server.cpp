#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 12345

using namespace std;

struct Data {
    double f_lat;
    double f_lon;
    double f_alt;
    int n_pilot;
    bool mode_auto;
};

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        cerr << "Error creating socket" << endl;
        return 1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        cerr << "Error binding socket" << endl;
        close(sockfd);
        return 1;
    }

    cout << "Server running, waiting for data..." << endl;

    Data data;
    socklen_t len = sizeof(addr);
    recvfrom(sockfd, (char*)&data, sizeof(data), 0, (struct sockaddr*)&addr, &len);

    cout << "Data received:" << endl;
    cout << "Latitude: " << data.f_lat << endl;
    cout << "Longitude: " << data.f_lon << endl;
    cout << "Altitude: " << data.f_alt << endl;
    cout << "Number of pilots: " << data.n_pilot << endl;
    cout << "Auto mode: " << (data.mode_auto ? "true" : "false") << endl;

    close(sockfd);

    return 0;
}
