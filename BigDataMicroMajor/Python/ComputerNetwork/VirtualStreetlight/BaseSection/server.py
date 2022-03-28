# -*- coding: utf-8 -*-
# @Time    : 2021/1/1 14:32
# @Author  : 咸鱼型233
# @File    : server.py
# @Software: PyCharm
# @Function: 服务器端

import socket


PORT = 9222


def main():
    # 创建socket对象
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # 获取自己的ip地址
    HOST = socket.gethostname()
    # 绑定端口号
    serverSocket.bind((HOST, PORT))
    while True:
        data, address = serverSocket.recvfrom(1024)
        print("这是一个UDP server", address)
        print("接收到信息:", data.decode("utf-8"))
        serverSocket.sendto(data, address)
    serverSocket.close()
    pass


if __name__ == '__main__':
    main()
