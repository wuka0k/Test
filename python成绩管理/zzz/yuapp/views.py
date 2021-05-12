from django.shortcuts import render,redirect
from . models import Classer,UserExtension
from . forms import ClasserForm,RegisterForm
from django.contrib.auth.models import User
from django.contrib.auth import authenticate,login,logout
from django.contrib.auth.decorators import login_required
from yuapp.models import IMG
import os

# Create your views here.


import sys
import ssl
import urllib
import ssl
from urllib import request, parse
import json


# client_id 为官网获取的AK， client_secret 为官网获取的SK
def get_token():
    context = ssl._create_unverified_context()
    host = ''
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

    # 人脸对比API
    context = ssl._create_unverified_context()

    params = imgdata(file1path, file2path)

    request_url = ""
    request_url = request_url + "?access_token=" + token
    request = urllib.request.Request(url=request_url, data=params)
    request.add_header('Content-Type', 'application/json')
    response = urllib.request.urlopen(request, context=context)

    global null
    null=''

    content = response.read()
    # print(content)
    # b'{"error_code":222202,"error_msg":"pic not has face","log_id":3500189051515,"timestamp":1608653674,"cached":0,"result":null}'
    content = eval(content)
    # print(content)
    # # 获得分数

    if content['result']=='':
        return '0'
    else:

        score = content['result']['score']
        if score > 80:
            return '1'
        else:
            return '0'


def login_page(request):


    if request.user.is_authenticated:
        return redirect('homepage')
    else:
        message=''
        if request.method=='POST':
            name_get=request.POST.get('username')
            pwd_get=request.POST.get('password')
            user=authenticate(request,username=name_get,password=pwd_get)

            # imgs = IMG.objects.all()
            # last_one = []
            #
            # last_one.append(imgs[len(imgs) - 1])

            # 识别

            import cv2

            cap = cv2.VideoCapture(0)  # 打开摄像头

            while (cap.isOpened()):
                # get a frame
                ret, frame = cap.read()
                # show a frame
                cv2.imshow("capture", frame)  # 生成摄像头窗口
                cv2.imwrite("D:\\test\\zzz\\static\\img\\zzz.png", frame)  # 保存路径
                break

            cap.release()
            cv2.destroyAllWindows()








            import os
            file = os.listdir('D:\\test\\zzz\\static\\img\\')
            file_path=file[len(file)-1]
            fullflname = os.path.split(file_path)

            file1path = 'D:\\test\\zzz\\static\\img\\zhaopian.png'
            file2path = 'D:\\test\\zzz\\static\\img\\'+eval(str(fullflname).split(",",1)[1].split(')',1)[0])
            # print(file2path)
            res = img(file1path, file2path)

            if user is not None:
                if user.is_active:
                    if res=='1':
                        login(request,user)
                        return redirect('homepage')
                    else:
                        message='人脸识别错误'
                else:
                    message='此账号已被冻结！'
            else:
                message='用户名或密码错误！'
    context={
        'message':message
    }
    return render(request,'yuapp/loginpage.html',context)



def login_page(request):


    if request.user.is_authenticated:
        return redirect('homepage')
    else:
        message=''
        if request.method=='POST' and request.POST.get('denglu')=='denglu':
            # print(request.POST.get('denglu'),'denglu')
            name_get=request.POST.get('username')
            pwd_get=request.POST.get('password')
            user=authenticate(request,username=name_get,password=pwd_get)

            # imgs = IMG.objects.all()
            # last_one = []
            #
            # last_one.append(imgs[len(imgs) - 1])

            # 识别

            # import cv2
            #
            # # cap = cv2.VideoCapture('rtsp://admin:888888@10.5.3.105:10554/tcp/av0_0')
            #
            # cap = cv2.VideoCapture(0)  # 打开摄像头
            #
            # while (cap.isOpened()):
            #     # get a frame
            #     ret, frame = cap.read()
            #     # show a frame
            #     # cv2.imshow("capture", frame)  # 生成摄像头窗口
            #     cv2.imwrite(os.path.abspath('static/img/zzz.png'), frame)  # 保存路径
            #     break
            #
            # cap.release()
            # cv2.destroyAllWindows()








            # file = os.listdir('D:\\test\\zzz\\static\\img\\')
            # file_path=file[len(file)-1]
            # fullflname = os.path.split(file_path)

            # file1path = os.path.abspath('static/img/zhaopian.png')
            # file2path = os.path.abspath('static/img/zzz.png')
            # # print(file2path)
            # res = img(file1path, file2path)

            if user is not None:
                if user.is_active:
                    # if res=='1':
                        login(request,user)
                        return redirect('homepage')
                    # else:
                    #     message='人脸识别错误'
                else:
                    message='此账号已被冻结！'
            else:
                message='用户名或密码错误！'

    """
    图片上传
    :param request:
    :return:
    """
    if request.method == 'POST' and request.POST.get('shangchuan')=='shangchuan':
        if request.FILES.get('img')!=None:
            # print(request.POST.get('shangchuan'), 'shangchuan')
            new_img = IMG(
                img=request.FILES.get('img'),
                name=request.FILES.get('img').name
            )



            file = os.listdir(os.path.abspath('media/img'))
            # print(file)
            for i in range(len(file)):
                # if str(file[i]).split(".")[0] not in str(new_img).split(".")[0]:
                    file_name =file[i]
                    remove_path=os.path.abspath('media/img')+'/'+file_name
                    print(remove_path)
                    os.remove(remove_path)




            new_img.save()
            # print(new_img.name)


    imgs = IMG.objects.all()

    last_one=[]

    last_one.append(imgs[len(imgs)-1])
    # print(last_one)

    context={
        'last_one': last_one,
        'message':message
    }
    return render(request,'yuapp/loginpage.html',context)





# def uploadImg(request):
#     """
#     图片上传
#     :param request:
#     :return:
#     """
#     if request.method == 'POST':
#         new_img = IMG(
#             img=request.FILES.get('img'),
#             name=request.FILES.get('img').name
#         )
#         new_img.save()
#         # print(new_img.name)
#
#
#     imgs = IMG.objects.all()
#
#
#     last_one=[]
#
#     last_one.append(imgs[len(imgs)-1])
#
#     content = {
#         'last_one': last_one,
#     }
#     return render(request, 'yuapp/uploading.html',content)

# def showImg(request):
#     """
#     图片上传
#     :param request:
#     :return:
#     """
#
#
#     imgs = IMG.objects.all()
#
#
#     last_one=[]
#
#     last_one.append(imgs[len(imgs)-1])
#
#     content = {
#         'last_one': last_one,
#     }
#     return render(request, 'yuapp/uploading.html',content)


@login_required(login_url='login')
def homepage(request):
    classer=Classer.objects.all()


    if request.is_ajax and request.POST.get('classer_del'):
        del_classer_id=request.POST.get('classer_del')
        del_classer=Classer.objects.get(id=del_classer_id)
        del_classer.delete()


    context={
        'classer':classer
    }
    return render(request,'yuapp/home.html',context)


def register(request):
    r_form=RegisterForm()
    message=''

    if request.method=='POST':
        r_form=RegisterForm(request.POST)
        if r_form.is_valid():
            name_get=r_form.cleaned_data['username']
            pwd1_get = r_form.cleaned_data['password1']
            pwd2_get = r_form.cleaned_data['password2']
            email_get = r_form.cleaned_data['email']
            phone_get = r_form.cleaned_data['phone']

            try:
                if pwd1_get==pwd2_get:
                    new_user=User.objects.create_user(username=name_get,password=pwd1_get,email=email_get)
                    new_user.save()
                    UserExtension.objects.create(user=new_user,phone=phone_get).save()
                    return redirect('login')
                else:
                    message='两次密码输入的不一致！'
            except:
                message='用户名或邮箱已经被注册！'
                new_user.delete()

    context={
        'r_form':r_form,
        'message':message
    }
    return render(request,'yuapp/register.html',context)


# def login_page(request):
#     if request.user.is_authenticated:
#         return redirect('homepage')
#     else:
#         message=''
#         if request.method=='POST':
#             name_get=request.POST.get('username')
#             pwd_get=request.POST.get('password')
#             user=authenticate(request,username=name_get,password=pwd_get)
#             if user is not None :
#                 if user.is_active:
#                     login(request,user)
#                     return redirect('homepage')
#                 else:
#                     message='此账号已被冻结！'
#             else:
#                 message='用户名或密码错误！'
#     context={
#         'message':message
#     }
#     return render(request,'yuapp/loginpage.html',context)

def logout_user(request):
    logout(request)
    return redirect('login')


@login_required(login_url='login')
def modify_pwd(request):
    message=''

    if request.method=='POST':
        old_pwd=request.POST.get('old_pwd')
        new_pwd=request.POST.get('new_pwd')
        repeat_pwd=request.POST.get('repeat_pwd')
        user=authenticate(request,username=request.user.username,password=old_pwd)
        if user is not None:
            if user.is_active:
                if new_pwd != repeat_pwd:
                    message='两次输入的密码不一致!'
                else:
                    user.set_password(new_pwd)
                    user.save()
                    logout(request)
                    return redirect('login')
            else:
                message='此账号已被冻结!'
        else:
            message='原密码输入错误，或者用户不存在!'
    context={
        'message':message
    }
    return render(request,'yuapp/modifypwd.html',context)

@login_required(login_url='login')
def create(request):
    c_form=ClasserForm()

    if request.method=='POST':
        if 'c_button' in request.POST:
            c_form=ClasserForm(request.POST)
            if c_form.is_valid():
                coursename_get=c_form.cleaned_data['coursename']
                starttime_get = c_form.cleaned_data['starttime']
                cursenumber_get = c_form.cleaned_data['cursenumber']
                grade_get = c_form.cleaned_data['grade']
                xuefen_get = c_form.cleaned_data['xuefen']
                zongxueshi_get = c_form.cleaned_data['zongxueshi']
                jidian_get = c_form.cleaned_data['jidian']
                kecehngshuxing_get = c_form.cleaned_data['kecehngshuxing']
                classer=Classer.objects.create(coursename=coursename_get,starttime=starttime_get,cursenumber=cursenumber_get,grade=grade_get,xuefen=xuefen_get,
                                               zongxueshi=zongxueshi_get,jidian=jidian_get,kecehngshuxing=kecehngshuxing_get)
                classer.save()
                return redirect('homepage')


    context={
        'c_form':c_form
    }
    return render(request,'yuapp/create.html',context)

def update_classer(request,pk):
    classer=Classer.objects.get(id=pk)

    c_form=ClasserForm(instance=classer)

    if request.method=='POST':
        c_form=ClasserForm(request.POST)
        if c_form.is_valid():
            coursename_get=c_form.cleaned_data['coursename']
            starttime_get = c_form.cleaned_data['starttime']
            cursenumber_get = c_form.cleaned_data['cursenumber']
            grade_get = c_form.cleaned_data['grade']
            xuefen_get = c_form.cleaned_data['xuefen']
            zongxueshi_get = c_form.cleaned_data['zongxueshi']
            jidian_get = c_form.cleaned_data['jidian']
            kecehngshuxing_get = c_form.cleaned_data['kecehngshuxing']
            classer=Classer.objects.filter(id=pk)
            classer.update(id=pk,coursename=coursename_get,starttime=starttime_get,cursenumber=cursenumber_get,grade=grade_get,xuefen=xuefen_get,
                                           zongxueshi=zongxueshi_get,jidian=jidian_get,kecehngshuxing=kecehngshuxing_get)
            return redirect('homepage')


    context={
        'classer':classer,
        'c_form':c_form
    }
    return render(request,'yuapp/updateclasser.html',context)

def delete_classer(request,pk):
    classer = Classer.objects.get(id=pk)
    message = ''
    if request.method == 'POST':
        classer.delete()
        message = 'Delete successfully!'
        return redirect('homepage')

    context = {
        'classer': classer,
        'message': message
    }
    return render(request, 'yuapp/deleteclasser.html', context)