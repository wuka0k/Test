# from aip import AipFace
""" 你的 APPID AK SK """
# APP_ID = '20482210'
# API_KEY = 'eWO1feyQ6OEIITtoaTOVjkZ1'
# SECRET_KEY = '0G5qku0VZwDEKdwRnzVMOddZAfn1Y0o7'


# 首先pip install baidu-aip
# SDK文档链接http://ai.baidu.com/docs#/Face-Python-SDK/top
import sys
import ssl
import urllib
import ssl
from urllib import request, parse
import json


# client_id 为官网获取的AK， client_secret 为官网获取的SK
def get_token():
    context = ssl._create_unverified_context()
    host = 'https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=MNoApV4aT5GaDcGE1DizXByb&client_secret=OHhIcMeIZVF1xkz9PmY386kHC75GGEtO'
    request = urllib.request.Request(host)
    request.add_header('Content-Type', 'application/json; charset=UTF-8')
    response = urllib.request.urlopen(request, context=context)
    # 获取请求结果
    content = response.read()
    # 转换为字符
    content = bytes.decode(content)
    # 转换为字典
    content = eval(content[:-1])
    return content['access_token']


# 转换图片
# 读取文件内容，转换为base64编码
# 二进制方式打开图文件
def imgdata(file1path, file2path):
    import base64
    f = open(r'%s' % file1path, 'rb')
    pic1 = base64.b64encode(f.read())
    f.close()
    f = open(r'%s' % file2path, 'rb')
    pic2 = base64.b64encode(f.read())
    f.close()
    # 将图片信息格式化为可提交信息，这里需要注意str参数设置
    params = json.dumps(
        [{"image": str(pic1, 'utf-8'), "image_type": "BASE64", "face_type": "LIVE", "quality_control": "LOW"},
         {"image": str(pic2, 'utf-8'), "image_type": "BASE64", "face_type": "IDCARD", "quality_control": "LOW"}]
    )
    return params.encode(encoding='UTF8')


# 进行对比获得结果
def img(file1path, file2path):
    token = get_token()
    # 人脸识别API
    # url = 'https://aip.baidubce.com/rest/2.0/face/v3/detect?access_token='+token
    # 人脸对比API
    context = ssl._create_unverified_context()
    # url = 'https://aip.baidubce.com/rest/2.0/face/v3/match?access_token=' + token
    params = imgdata(file1path, file2path)

    request_url = "https://aip.baidubce.com/rest/2.0/face/v3/match"
    request_url = request_url + "?access_token=" + token
    request = urllib.request.Request(url=request_url, data=params)
    request.add_header('Content-Type', 'application/json')
    response = urllib.request.urlopen(request, context=context)
    content = response.read()
    content = eval(content)
    # # 获得分数
    score = content['result']['score']
    if score > 80:
        return '1'
    else:
        return '0'


def yunxing():
    file1path = 'D:\\test\\zzz\\static\\img\\zhaopian.png'
    file2path = 'D:\\test\\zzz\\static\\img\\zhaopiancopy.png'
    res = img(file1path, file2path)


