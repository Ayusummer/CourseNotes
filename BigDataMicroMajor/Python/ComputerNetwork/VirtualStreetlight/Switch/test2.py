# -*- coding: utf-8 -*-
# @Time    : 2021/1/1 15:57
# @Author  : 咸鱼型233
# @File    : test2.py
# @Software: PyCharm
# @Function:
import socket


def send_msg(udp_socket):
    # 获取发送内容
    ip_dst = input("请输入对方的ip:")
    port_dst = int(input("请输入对方的端口号:"))
    data_send = input("请输入发送信息：")
    udp_socket.sendto(data_send.encode("utf-8"), (ip_dst, port_dst))
    pass


def recv_msg(udp_socket):
    recv_data = udp_socket.recvfrom(1024)
    print("从(ip, 端口号)为{0}的主机收到消息:{1} ".format(str(recv_data[1]), recv_data[0].decode("utf-8")))
    pass


def main():
    # 创建udp套接字
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # 绑定信息
    udp_socket.bind(("", 8081))
    while True:
        send_msg(udp_socket)
        recv_msg(udp_socket)
    pass


if __name__ == '__main__':
    main()
