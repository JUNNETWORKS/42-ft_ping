#include "ft_ping.h"
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/*
 * icmp_checksum 関数は、ICMPパケットのチェックサムを計算します。
 * パケットの内容を16ビット単位で加算し、その結果の補数を取ります。
 * これにより、パケットのデータが転送中に変更された場合に検出できます。
 * 
 * https://datatracker.ietf.org/doc/html/rfc792
 * 
 * The checksum is the 16-bit ones's complement of the one's
 * complement sum of the ICMP message starting with the ICMP Type.
 * For computing the checksum , the checksum field should be zero.
 * If the total length is odd, the received data is padded with one
 * octet of zeros for computing the checksum.  This checksum may be
 * replaced in the future.
 */
uint16_t icmp_checksum(icmp_packet *packet, int len) {
    uint32_t sum = 0;
    uint16_t *ptr = (uint16_t *)packet;

    while (len >= 2) {
        sum += *ptr++;
        len -= 2;
    }

    if (len > 0) {
        sum += *(uint8_t *)ptr;
    }

    while (sum >> 16) {
        sum = (sum & 0xffff) + (sum >> 16);
    }

    return ~sum;
}


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <送信先IPv4アドレス>\n", argv[0]);
        return 1;
    }
    char *dest_ip_str = argv[1];
    in_addr_t dest_ip;
    if (inet_pton(AF_INET, dest_ip_str, &dest_ip) != 1) {
        fprintf(stderr, "invalid IPv4 address: %s\n", dest_ip_str);
        return 1;
    }
    icmp_packet request;
    request.type = ICMP_ECHO_REQUEST;
    request.code = ICMP_CODE;
    // どの要求に対応する応答なのかを発信元で判別する際に使う。
    request.id = htons(getpid());
    request.sequence = 0;
    request.checksum = 0;
    request.checksum = icmp_checksum(&request, sizeof(request));

    int sockfd;
    struct sockaddr_in dest_addr;

    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(0);
    dest_addr.sin_addr.s_addr = dest_ip;

    if (sendto(sockfd, &request, sizeof(request), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
        perror("sendto");
        return 1;
    }

    close(sockfd);

    return 0;
}