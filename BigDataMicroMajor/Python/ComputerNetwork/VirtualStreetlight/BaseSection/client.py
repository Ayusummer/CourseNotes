# -*- coding: utf-8 -*-
# @Time    : 2021/1/1 14:14
# @Author  : 咸鱼型233
# @File    : client.py
# @Software: PyCharm
# @Function: 客户端
import socket

PORT = 9222


def main():
    # 创建socket对象
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # 获取本地主机名
    HOST = socket.gethostname()
    addr = (HOST, PORT)
    while True:
        text = input("请输入待上传信息:")
        # 发送udp数据报
        clientSocket.sendto(text.encode("utf-8"), addr)
        if text == 'exit':
            break
        ans = clientSocket.recvfrom(1024)
        print(ans[0].decode("utf-8"))
    clientSocket.close()
    pass


if __name__ == '__main__':
    main()
