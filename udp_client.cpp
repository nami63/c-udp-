#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 12345 
#define REMOTE_IP "255.255.255.255" 

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
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, REMOTE_IP, &addr.sin_addr);
    Data data;
    data.f_lat = 12.96093;
    data.f_lon = 77.65333;
    data.f_alt = 860.0;
    data.n_pilot = 2;
    data.mode_auto = true;


    sendto(sockfd, (const char*)&data, sizeof(data), 0, (struct sockaddr*)&addr, sizeof(addr));

    cout << "Data sent successfully." << endl;

    close(sockfd);

    return 0;
}
