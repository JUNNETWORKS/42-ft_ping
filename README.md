# 42-ft_ping

ft_ping is one of the projects in 42 cursus.

## 課題概要

### 実行環境について

- VM で動かせるようにする必要がある。
  - OS: Debian 7.0 stable
    - Linux Kernel > 3.14
  - 必要なソフトウェアやパッケージはインストール済みであること

### Allowed functions

- gettimeofday.
- exit.
- [inet_ntop](https://linuxjm.osdn.jp/html/LDP_man-pages/man3/inet_ntop.3.html). / [inet_pton](https://linuxjm.osdn.jp/html/LDP_man-pages/man3/inet_pton.3.html).
  - IPv4/IPv6アドレスの文字列とバイナリ表現の変換
- [ntohs](https://linuxjm.osdn.jp/html/LDP_man-pages/man3/ntohs.3.html) / [htons](https://linuxjm.osdn.jp/html/LDP_man-pages/man3/htons.3.html).
  - ネットワークバイトオーダーとホストバイトオーダーの変換
- signal / alarm / usleep.
- [socket](https://linuxjm.osdn.jp/html/LDP_man-pages/man2/socket.2.html) / [setsockopt](https://linuxjm.osdn.jp/html/LDP_man-pages/man2/getsockopt.2.html) / close.
- [sendto](https://linuxjm.osdn.jp/html/LDP_man-pages/man2/send.2.html) / [recvmsg](https://linuxjm.osdn.jp/html/LDP_man-pages/man2/recvmsg.2.html).
- getpid / getuid.
- [getaddrinfo](https://linuxjm.osdn.jp/html/LDP_man-pages/man3/getaddrinfo.3.html) / [getnameinfo](https://linuxjm.osdn.jp/html/LDP_man-pages/man3/getnameinfo.3.html) / [freeaddrinfo](https://linuxjm.osdn.jp/html/LDP_man-pages/man3/getaddrinfo.3.html).
- strerror / [gai_strerror](https://linuxjm.osdn.jp/html/LDP_man-pages/man3/getaddrinfo.3.html).
- printf and its family
- Your libft functions
- You are allowed to use other functions to complete the bonus part as long as
their use is justified during your defense. Be smart.
- ATTENTION: **Usage of fcntl, poll, epoll is strictly forbidden.**

### Mandatory Part

- executable name: ft_ping
- ping の仕様は inetutils-2.0 (ping -V) の実装を元にすること。
  - [ping(8) - Linux man page](https://linux.die.net/man/8/ping)
  - [ping(1) — inetutils-ping — Debian stretch — Debian Manpages](https://manpages.debian.org/stretch/inetutils-ping/ping.1.en.html)
  - [ping - Wikipedia](https://ja.wikipedia.org/wiki/Ping)
  - [GNU、ftpやpingなどネットワーク系基本パッケージ「inetutils」v2.0 | TECH+（テックプラス）](https://news.mynavi.jp/techplus/article/20210208-1710802/)
- 以下のフラグを受け付ける必要がある。
    - `-v`
      - Verbose output. ICMP packets other than ECHO_RESPONSE that are received are listed.
    - `-?`
      - 公式のpingコマンドには。存在しない。
      - おそらく help のようなオプションだと思う。
- RTT行とDNSの逆引き解決を除いて、結果はinetutils-2.0の実装と同じインデントでなければなりません。
- パケット受信は ±30ms の遅延が許容されます。

### Bonus Part

- 以下のフラグを受け付ける必要がある。
 - `-f`
   - Flood ping. Outputs packets as fast as they come back or one hundred times per second, whichever is more. For every ECHO_REQUEST sent a period ``.'' is printed, while for every ECHO_REPLY received a backspace is printed. This provides a rapid display of how many packets are being dropped. Only the super-user may use this option. This can be very hard on a network and should be used with caution.
 - `-l preload`
   - If preload is specified, ping sends that many packets as fast as possible before falling into its normal mode of behavior.
 - `-n`
   - Numeric output only. No attempt will be made to lookup symbolic names for host addresses.
 - `-w deadline`
   - Specify a timeout, in seconds, before ping exits regardless of how many packets have been sent or received. In this case ping does not stop after count packet are sent, it waits either for deadline expire or until count probes are answered or for some error notification from network.
 - `-W timeout`
   - Time to wait for a response, in seconds. The option affects only timeout in absense of any responses, otherwise ping waits for two RTTs.
 - `-p pattern`
   - You may specify up to 16 ''pad'' bytes to fill out the packet you send. This is useful for diagnosing data-dependent problems in a network. For example, -p ff will cause the sent packet to be filled with all ones.
 - `-r`
   - Bypass the normal routing tables and send directly to a host on an attached interface. If the host is not on a directly-attached network, an error is returned. This option can be used to ping a local host through an interface that has no route through it provided the option -I is also used.
 - `-s packetsize`
   - Specifies the number of data bytes to be sent. The default is 56, which translates into 64 ICMP data bytes when combined with the 8 bytes of ICMP header data.
 - `-T timestamp option`
   - Set special IP timestamp options. timestamp option may be either tsonly (only timestamps), tsandaddr (timestamps and addresses) or tsprespec host1 [host2 [host3 [host4]]] (timestamp prespecified hops).
 - `--ttl ttl`
   - Set the IP Time to Live.
 - `--ip-timestamp`
   - `-T timestamp option` と同じ。

## メモ

### ping コマンドってなんだ

ICMP echo request/reply を使って

`ping 127.0.0.1` や `ping google.com` のようにして実行

## 作業環境

### 送信されたパケット情報の見方

#### Wireshark

適当にインストールして使えばおk

#### tcpdump

`ping 127.0.0.1` を実行し、受信したパケットを hex と ACII で表示する。

```sh
sudo tcpdump -i lo0 -X -vvv
```

## 参考資料

### ping の仕様

### ネットワーク関連

- [Internet Control Message Protocol - Wikipedia](https://ja.wikipedia.org/wiki/Internet_Control_Message_Protocol)
- [RFC 792 - Internet Control Message Protocol](https://datatracker.ietf.org/doc/html/rfc792)

### Linux コマンド

- [とほほのtcpdump入門 - とほほのWWW入門](https://www.tohoho-web.com/ex/tcpdump.html)