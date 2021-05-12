from django.db import models
from django.contrib.auth.models import User
# Create your models here.

class UserExtension(models.Model):
    user=models.OneToOneField(User,on_delete=models.CASCADE,related_name='extension')
    phone=models.CharField(max_length=100,null=True,blank=True)
    birthday=models.DateField(null=True,blank=True,auto_now_add=True)
    intro=models.TextField()
    stuff_status=models.NullBooleanField(default=False)

    def __str__(self):
        return str(self.user)


class Classer(models.Model):
    coursename=models.CharField(max_length=30)
    starttime=models.CharField(max_length=30)
    cursenumber=models.CharField(max_length=30)
    grade=models.CharField(max_length=30)
    xuefen=models.CharField(max_length=30)
    zongxueshi=models.CharField(max_length=30)
    jidian=models.CharField(max_length=30)
    kecehngshuxing=models.CharField(max_length=30)
    def __str__(self):
        return str(self.coursename)

class IMG(models.Model):
    img = models.ImageField(upload_to='img')
    name = models.CharField(max_length=20)

    def __str__(self):
        return self.name
