# Generated by Django 3.1.4 on 2020-12-16 04:59

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Classer',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('coursename', models.CharField(max_length=30)),
                ('starttime', models.CharField(max_length=30)),
                ('cursenumber', models.CharField(max_length=30)),
                ('grade', models.CharField(max_length=30)),
                ('xuefen', models.CharField(max_length=30)),
                ('zongxueshi', models.CharField(max_length=30)),
                ('jidian', models.CharField(max_length=30)),
                ('kecehngshuxing', models.CharField(max_length=30)),
            ],
        ),
    ]
