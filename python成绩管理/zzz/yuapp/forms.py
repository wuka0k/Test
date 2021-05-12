from django import forms
from django.forms import ModelForm
from . models import Classer

class RegisterForm(forms.Form):
    username=forms.CharField(
        label='用户名',
        max_length=128,
        widget=forms.TextInput(attrs={
            'class':'form-control',
            'placeholder':'username'
        })
    )
    password1=forms.CharField(
        label='密码',
        max_length=30,
        widget=forms.PasswordInput(attrs={
            'class':'form-control',
            'placeholder':'password'
        })
    )
    password2=forms.CharField(
        label='确认密码',
        max_length=30,
        widget=forms.PasswordInput(attrs={
            'class':'form-control',
            'placeholder':'password'
        })
    )
    email=forms.EmailField(
        label='邮箱',
        widget=forms.EmailInput(attrs={
            'class': 'form-control',
            'placeholder': 'Email Address'
        })
    )
    phone=forms.CharField(
        label='电话',
        max_length=128,
        widget=forms.TextInput(attrs={
            'class':'form-control',
            'placeholder':'tel'
        })
    )


class ClasserForm(ModelForm):
    class Meta:
        model=Classer
        fields='__all__'

        labels={
            'coursename':'课程名称',
            'starttime': '开课学期',
            'cursenumber': '课程编号',
            'grade': '成绩',
            'xuefen': '学分',
            'zongxueshi': '总学时',
            'jidian': '绩点',
            'kecehngshuxing': '课程属性'
        }
        widgets = {
            'coursename': forms.TextInput(attrs={
                'class': 'form-control',
                'placeholder': '请输入课程名称：'
            }),
            'starttime': forms.TextInput(attrs={
                'class': 'form-control',
                'placeholder': '请输入开课学期：'
            }),
            'cursenumber': forms.TextInput(attrs={
                'class': 'form-control',
                'placeholder': '请输入课程编号：'
            }),
            'grade': forms.TextInput(attrs={
                'class': 'form-control',
                'placeholder': '请输入成绩：'
            }),
            'xuefen': forms.TextInput(attrs={
                'class': 'form-control',
                'placeholder': '请输入学分：'
            }),
            'zongxueshi': forms.TextInput(attrs={
                'class': 'form-control',
                'placeholder': '请输入总学时：'
            }),
            'jidian': forms.TextInput(attrs={
                'class': 'form-control',
                'placeholder': '请输入绩点：'
            }),
            'kecehngshuxing': forms.TextInput(attrs={
                'class': 'form-control',
                'placeholder': '请输入课程属性：'
            })
        }